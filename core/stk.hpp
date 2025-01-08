// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include <cstdint>

#include "core.hpp"
#include "except.hpp"

namespace kokuyo {
  union array_8 {
    uint64_t u64;
    uint8_t  u8[8];
  };
  

  void core::_push(uint64_t bytes) {
    if (!stack_beg + stack_pointer <= stack_max) {
      array_8 arr;
      arr.u64 = bytes;

      for (int i = 0; i < 8; i++) *(stack_beg + stack_pointer + i) = arr.u8[i];
      
      stack_pointer += 8;
    } else {
      __throw_rt(exceptions::stack_out(ip, stack_max, 8));
    }
  }

  uint64_t core::_pop() {
    array_8 arr{0x0000000000000000};

    if (!stack_beg + stack_pointer - 8 >= 0) {
      

    } else {
      __throw_rt(exceptions::stack_null(ip));
    }

    return arr.u64;
  }
}