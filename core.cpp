#include <functional>

#include "core.hpp"

namespace kokuyo {
  uint8_t core::read_byte() {
    return memory_segment[ip++];
  }

  uint16_t core::read_word() {
    uint16_t w = (memory_segment[ip] << 8) | memory_segment[ip+1];

    ip += 2;
    return w;
  }

  uint32_t core::read_dword() {
    uint32_t d = (memory_segment[ip] << 24) | (memory_segment[ip+1] << 16) | (memory_segment[ip+2] << 8) | memory_segment[ip+3];

    ip += 4;
    return d;
  }

  uint64_t core::read_qword() {
    uint64_t q = (memory_segment[ip] << 56) | (memory_segment[ip+1] << 48) | (memory_segment[ip+2] << 40) | (memory_segment[ip+3] << 32) |
                 (memory_segment[ip+4] << 24) | (memory_segment[ip+5] << 16) | (memory_segment[ip+6] << 8) | memory_segment[ip+7];

    ip += 8;
    return q;
  }

  void core::init_table() {
    ftable[nop] = [this]() {return;};

    ftable[mov] = [this]() {

    };
  }
}