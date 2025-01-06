// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include "kernel.h"
#include <cstdint>

namespace kokuyo {
  class core {
  private:
    uint8_t *memory_segment;
    uint64_t code_section;
    uint64_t stack_beg;
    uint64_t stack_max;
    uint64_t ip;
    bool     _halt = false;

  public:
    void run() {
      while (!_halt) {
        
      }

      delete[] memory_segment;
    }

  };
}