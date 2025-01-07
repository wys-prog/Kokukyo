// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include <cstdint>
#include <functional>

#include "set.h"
#include "except.hpp"

namespace kokuyo {
  class core {
  private:
    uint8_t              *memory_segment;
    uint64_t              code_section;
    uint64_t              stack_beg;
    uint64_t              stack_max;
    uint64_t              ip;
    bool                  _halt = false;
    uint8_t               flags;

    uint8_t               read_byte();
    uint16_t              read_word();
    uint32_t              read_dword();
    uint64_t              read_qword();
    uint128_t             read_dqword();

    void                  init_table();

    std::function<void()> ftable[INS_COUNT];

  public:
    void run() {
      while (!_halt) {
        uint8_t u = read_byte();

        if (u < INS_COUNT) {
          ftable[u](); // Call the function. 
        } else {
          exceptions::illegal(ip, u);
        }
      }

      delete[] memory_segment;
    }

  };
}