// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#include <functional>

#include "core.hpp"
#include "set.h"
#include "except.hpp"
#include "stk.hpp"
#include "uint128_t.h"

namespace kokuyo {

  uint8_t core::read_byte() { return memory_segment[ip++]; }

  uint16_t core::read_word() {
    uint16_t w = (memory_segment[ip] << 8) | memory_segment[ip + 1];

    ip += 2;
    return w;
  }

  uint32_t core::read_dword() {
    uint32_t d = (memory_segment[ip] << 24)    | (memory_segment[ip + 1] << 16) |
                 (memory_segment[ip + 2] << 8) | memory_segment[ip + 3];

    ip += 4;
    return d;
  }

  uint64_t core::read_qword() {
    uint64_t q = (memory_segment[ip] << 56)     | (memory_segment[ip + 1] << 48) |
                 (memory_segment[ip + 2] << 40) | (memory_segment[ip + 3] << 32) |
                 (memory_segment[ip + 4] << 24) | (memory_segment[ip + 5] << 16) |
                 (memory_segment[ip + 6] << 8)  | memory_segment[ip + 7];

    ip += 8;
    return q;
  }

  uint128_t core::read_dqword() {
    uint128_t d = (memory_segment[ip     ] << 120)  | (memory_segment[ip +  1] << 112)  |
                  (memory_segment[ip +  2] << 104)  | (memory_segment[ip +  3] << 96)   |
                  (memory_segment[ip +  4] << 88)   | (memory_segment[ip +  5] << 80)   |
                  (memory_segment[ip +  6] << 72)   | (memory_segment[ip +  7] << 64)   |
                  (memory_segment[ip +  8] << 56)   | (memory_segment[ip +  9] << 48)   |
                  (memory_segment[ip + 10] << 40)   | (memory_segment[ip + 11] << 32)   |
                  (memory_segment[ip + 12] << 24)   | (memory_segment[ip + 13] << 16)   |
                  (memory_segment[ip + 14] << 8)    | (memory_segment[ip + 15]);

    ip += 16;
    return d;
  }

  void core::_cmp(uint64_t a, uint64_t b) {
    if (a == b) flags     = 0x00;
    else if (a < b) flags = 0x01;
    else flags            = 0x10;
  }

  void core::_mod() {
    uint8_t op = read_byte();

    if (op == byte) { uint8_t a = read_byte(), b = read_byte(); memory_segment[a] = a % b; }
    else if (op == word) { uint16_t a = read_word(), b = read_word(); memory_segment[a] = a % b; }
    else if (op == dword) { uint32_t a = read_dword(), b = read_dword(); memory_segment[a] = a % b; }
    else if (op == qword) { uint64_t a = read_qword(), b = read_qword(); memory_segment[a] = a % b; }
  }

  void core::init_table() {
    ftable[nop] = [this]() { return; };

    ftable[mov] = [this]() {
      switch (read_byte()) {
        case byte:  memory_segment[read_byte()]  = memory_segment[read_byte()];  break;
        case word:  memory_segment[read_word()]  = memory_segment[read_word()];  break;
        case dword: memory_segment[read_dword()] = memory_segment[read_dword()]; break;
        case qword: memory_segment[read_qword()] = memory_segment[read_qword()]; break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };

    ftable[add] = [this]() {
      switch (read_byte()) {
        case byte:  memory_segment[read_byte()]  += memory_segment[read_byte()];  break;
        case word:  memory_segment[read_word()]  += memory_segment[read_word()];  break;
        case dword: memory_segment[read_dword()] += memory_segment[read_dword()]; break;
        case qword: memory_segment[read_qword()] += memory_segment[read_qword()]; break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };
    
    ftable[sub] = [this]() {
      switch (read_byte()) {
        case byte:  memory_segment[read_byte()]  -= memory_segment[read_byte()];  break;
        case word:  memory_segment[read_word()]  -= memory_segment[read_word()];  break;
        case dword: memory_segment[read_dword()] -= memory_segment[read_dword()]; break;
        case qword: memory_segment[read_qword()] -= memory_segment[read_qword()]; break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };

    ftable[mul] = [this]() {
      switch (read_byte()) {
        case byte:  memory_segment[read_byte()]  *= memory_segment[read_byte()];  break;
        case word:  memory_segment[read_word()]  *= memory_segment[read_word()];  break;
        case dword: memory_segment[read_dword()] *= memory_segment[read_dword()]; break;
        case qword: memory_segment[read_qword()] *= memory_segment[read_qword()]; break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };
    
    ftable[div] = [this]() {
      switch (read_byte()) {
        case byte:  memory_segment[read_byte()]  -= memory_segment[read_byte()];  break;
        case word:  memory_segment[read_word()]  -= memory_segment[read_word()];  break;
        case dword: memory_segment[read_dword()] -= memory_segment[read_dword()]; break;
        case qword: memory_segment[read_qword()] -= memory_segment[read_qword()]; break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };

    ftable[jmp] = [this]() { ip = read_qword(); };

    ftable[je] = [this]() {
      uint64_t u64 = read_qword();
      if (flags == 0x00) ip = u64;
    };

    ftable[jne] = [this]() {
      uint64_t u64 = read_qword();
      if (flags != 0x00) ip = u64;
    };

    ftable[jl] = [this]() {
      uint64_t u64 = read_qword();
      if (flags == 0x01) ip = u64;
    };

    ftable[jg] = [this]() {
      uint64_t u64 = read_qword();
      if (flags == 0x10) ip = u64;
    };

    ftable[jle] = [this]() {
      uint64_t u64 = read_qword();
      if (flags == 0x01 || flags == 0x00) ip = u64;
    };

    ftable[jge] = [this]() {
      uint64_t u64 = read_qword();
      if (flags == 0x10 || flags == 0x00) ip = u64;
    };

    ftable[cmp] = [this]() {
      switch (read_byte()) {
        case byte:  _cmp(read_byte(),  read_byte());  break;
        case word:  _cmp(read_word(),  read_word());  break;
        case dword: _cmp(read_dword(), read_dword()); break;
        case qword: _cmp(read_qword(), read_qword()); break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };

    ftable[lea] = [this]() {
      memory_segment[read_qword()] = read_qword();
    };

    ftable[push] = [this]() {
      uint8_t op = read_byte();

      switch (read_byte()) {
        case byte:  _push(read_byte());  break;
        case word:  _push(read_word());  break;
        case dword: _push(read_dword()); break;
        case qword: _push(read_qword()); break;
        default: __throw_rt(exceptions::illegal(ip, memory_segment[ip])); break;
      }
    };

    ftable[pop] = [this]() { memory_segment[read_qword()] = _pop(); };

    ftable[syscall] = [this]() {
      // todo
    };

    ftable[call] = [this]() {
      _push(ip);
      ip = read_qword();
    };

    ftable[ret] = [this]() {
      ip = _pop();
    };

    ftable[mod] = [this]() {
      _mod();
    };

    ftable[halt] = [this]() { _halt = true; };
  }
} // namespace kokuyo