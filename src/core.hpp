// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.


#pragma once

#include <stack>
#include <cstdint>
#include <stdfloat>
#include <functional>
#include <unordered_map>

#include "src/set.h"
#include "libs/array.hpp"

namespace wylma {
  namespace kokuyo {
    namespace cast_core {
      union _8_to_16 {  // These unions will be used
        uint16_t u16;   // for casting bits to arrays,
        uint8_t  u8[2]; // or cast arrays to bits.
      };                // the _f128 cast is standard.
                        // But it's deprecated, except
      union _8_to_32 {  // You will use it for floating 
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
        {jle, [this]() { auto next = read_64();  _ip = (_flags == 0x01 ? next : _ip); auto next = read_64(); _ip = (_flags == 0x00 ? next : _ip); }}
        {jlg, [this]() { auto next = read_64();  _ip = (_flags == 0x10 ? next : _ip); auto next = read_64(); _ip = (_flags == 0x00 ? next : _ip); }}

        {call, [this]() {}}
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
        _stackpos--;
        return _memory[_stackbeg + _stackpos + 1];
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
