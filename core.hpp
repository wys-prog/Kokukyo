// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.


#pragma once

#include <stack>
#include <cstdint>
#include <stdfloat>
#include <functional>
#include <unordered_map>

#include "set.h"
#include "libs/array.hpp"

namespace wylma {
  namespace kokuyo {
    namespace cast_core {
      union _8_to_16 {  // These unions will be used
        uint16_t u16;   // for casting bits to arrays,
        uint8_t  u8[2]; // or cast arrays to bits.
      };                // the _f128 cast is standard.
                        // But it's deprecated, except
      union _8_to_32 {  // you will use it for floating 
        uint32_t u32;   // point operations.
        uint8_t  u8[4];
      };

      union _8_to_64 {
        uint64_t u64;
        uint8_t  u8[8];
      };
      
      union _8_to_f128 {
        std::float128_t f128;
        uint8_t         u8[16];
      };
    }

    template <uint64_t memory_len>
    class core {
    private:
      array<uint8_t, memory_len> &_memory; // Get a reference to the memory.
      uint64_t  _ip;
      uint64_t  _stackbeg;
      uint64_t  _stackend;
      uint64_t  _stackpos;
      bool      _halt = false;
      uint8_t   _flags;

      std::unordered_map<uint8_t, std::function<void()>> ftable = {
        {nop, [this]() {}},
        {halt, [this]() {_halt = true;}},

        {movb, [this]() {_memory[read_8()] = read_8();}},
        {addb, [this]() {_memory[read_8()] += read_8();}},
        {subb, [this]() {_memory[read_8()] -= read_8();}},
        {mulb, [this]() {_memory[read_8()] *= read_8();}},
        {divb, [this]() {_memory[read_8()] /= read_8();}},

        {movw, [this]() {_memory[read_16()] = read_16();}},
        {addw, [this]() {_memory[read_16()] += read_16();}},
        {subw, [this]() {_memory[read_16()] -= read_16();}},
        {mulw, [this]() {_memory[read_16()] *= read_16();}},
        {divw, [this]() {_memory[read_16()] /= read_16();}},

        {movd, [this]() {_memory[read_32()] = read_32();}},
        {addd, [this]() {_memory[read_32()] += read_32();}},
        {subd, [this]() {_memory[read_32()] -= read_32();}},
        {muld, [this]() {_memory[read_32()] *= read_32();}},
        {divd, [this]() {_memory[read_32()] /= read_32();}},

        {movq, [this]() {_memory[read_64()] = read_64();}},
        {addq, [this]() {_memory[read_64()] += read_64();}},
        {subq, [this]() {_memory[read_64()] -= read_64();}},
        {mulq, [this]() {_memory[read_64()] *= read_64();}},
        {divq, [this]() {_memory[read_64()] /= read_64();}},

        {jmp, [this]() {_ip = read_64();}},
        {je,  [this]() { auto next = read_64();  _ip = (_flags == 0x00 ? next : _ip); }}
        {jne, [this]() { auto next = read_64();  _ip = (_flags == 0x00 ? _ip  : next);}}
        {jl,  [this]() { auto next = read_64();  _ip = (_flags == 0x01 ? next : _ip); }}
        {jg,  [this]() { auto next = read_64();  _ip = (_flags == 0x10 ? next : _ip); }}
        {jle, [this]() { auto next = read_64();  _ip = (_flags == 0x01 ? next : _ip); _ip = (_flags == 0x00 ? next : _ip); }}
        {jlg, [this]() { auto next = read_64();  _ip = (_flags == 0x10 ? next : _ip); _ip = (_flags == 0x00 ? next : _ip); }}

        {call, [this]() {_pushq(_ip); _ip = read_64(); }}
        {ret, [this]() {_ip = _popq();}}

        {cmpb, [this]() {cmp(read_8(), read_8());}},
        {cmpw, [this]() {cmp(read_16(), read_16());}},
        {cmpd, [this]() {cmp(read_32(), read_32());}},
        {cmpq, [this]() {cmp(read_64(), read_64());}},

        {pushb, [this]() {_pushb(read_8());}},
        {pushw, [this]() {_pushb(read_16());}},
        {pushd, [this]() {_pushb(read_32());}},
        {pushq, [this]() {_pushb(read_64());}},

        {popb, [this]() {_memory[read_64()] = _popb();}},
        {popw, [this]() {for (char i = 0; i < 2; ++i) _memory[read_64()+1] = _popb();}},
        {popd, [this]() {for (char i = 0; i < 4; ++i) _memory[read_64()+1] = _popb();}},
        {popq, [this]() {for (char i = 0; i < 8; ++i) _memory[read_64()+1] = _popb();}},

        {modb, [this]() {auto i = read_8(); _memory[i] = _memory[i] % read_8();}},
        {modw, [this]() {_modw();}},
        {modd, [this]() {_modd();}},
        {modq, [this]() {_modq();}},

        {lea, [this]() {_memory[read_64()] = _memory[read_64()];}},
      };

      uint8_t read_8() {
        return _memory[ip++];
      } 

      uint16_t read_16() {
        cast_core::_8_to_16 _16;
        _16.u8[0] = _memory[ip++];
        _16.u8[1] = _memory[ip++];
      }

      uint32_t read_32() {
        cast_core::_8_to_32 _32;
        for (int i = 0; i < 4; i++) {
          _32.u8[i] = _memory[ip++];
        }
        return _32.u32;
      }

      uint64_t read_64() {
        cast_core::_8_to_64 _64;
        for (int i = 0; i < 8; i++) {
          _64.u8[i] = _memory[ip++];
        }
        return _64.u64;
      }

      std::float128_t read_128() {
        cast_core::_8_to_f128 _128;
        for (int i = 0; i < 16; i++) {
          _128.u8[i] = _memory[ip++];
        }

        return _128.f128;
      }

      void _pushb(uint8_t b) {
        if (_stackbeg + _stackpos < _stackmax) {
          _memory[_stackbeg + _stackpos] = b;
          _stackpos++;
        }
      }

      void _pushw(uint16_t w) {
        cast_core::_8_to_16 _16;
        _16.u16 = w;
        _pushb(_16.u8[0]);
        _pushb(_16.u8[1]);
      }

      void _pushd(uint32_t d) {
        cast_core::_8_to_32 _32;
        _32.u32 = d;

        for (char i = 0; i < 4; i++) {
          _pushb(_32.u8[i]);
        }
      }

      void _pushq(uint64_t q) {
        cast_core::_8_to_64 _64;
        _64.u64 = q;

        for (char i = 0; i < 8; i++) {
          _pushb(_64.u8[i]);
        }
      }
    
      uint8_t _popb() {
        if (_stackpos-1) {
          _stackpos--;
          return _memory[_stackbeg + _stackpos + 1];
        }

        return 0x00;
      }

      uint16_t _popw() {
        cast_core::_8_to_16 _16;
        _16.u8[0] = _popb();
        _16.u8[1] = _popb();

        return _16.u16;
      }

      uint32_t _popd() {
        cast_core::_8_to_32 _32;

        for (char i = 0; i < 4; i++) 
          _32.u8[i] = _popb();
        
        return _32.u32;
      }

      uint64_t _popq() {
        cast_core::_8_to_64 _64;

        for (char i = 0; i < 8; i++) 
          _64.u8[i] = _popb();
        
        return _64.u64;
      }

      void cmp(uint64_t a, uint64_t b) {
        if      (a == b) flags = 0x00;
        else if (a < b)  flags = 0x01;
        else             flags = 0x10; 
      }

      void _modw() {
        cast_core::_8_to_16 a, b;
        a.u16 = read_16();
        b.u16 = read_16();
        _memory[a.u16] = a.u16 % b.u16;
      }

      void _modd() {
        cast_core::_8_to_32 a, b;
        a.u32 = read_32();
        b.u32 = read_32();
        _memory[a.u32] = a.u32 % b.u32;
      }

      void _modq() {
        cast_core::_8_to_64 a, b;
        a.u64 = read_64();
        b.u64 = read_64();
        _memory[a.u64] = a.u64 % b.u64;
      }

    public:
      void invoke(uint64_t _at = 0) {
        _ip = _at;

        while (!_halt) {
          uint8_t current = read_8(); // Read the instruction.

          if (ftable.find(current) == ftable.end()) { // Not found.
            throw std::runtime_error("Illegal instruction."); // Illegal instrutioncs cannot be handled.
          }

          // Call the function.
          ftable[current]();
        }
      }

      core(array<uint8_t, memory_len> &_array, uint64_t _stak_beg, uint64_t _stack_end) : _memory(_array), _stackbeg(_stakbeg), _stackend(_stack_end) {}
    };
  
  } // namespace kokuyo
} // namespace wylma
