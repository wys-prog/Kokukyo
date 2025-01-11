// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include <stack>
#include <thread>
#include <iosfwd>
#include <cstdint>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "core/core.hpp"

namespace kokuyo {
  typedef struct {
    core        c;
    std::thread t;
  } core_handler;

  template <size_t s_memory, size_t s_threads>
  class vm {
  private:
    uint8_t     memory[s_memory];
    std::unordered_map<uint64_t, core_handler> cores;

    void start_core(uint64_t segment_size = 1024, uint64_t stack_size = 1024) {
      
    }

  public:

    void run(std::istream &boot_file) {
      // create a new core.
      core(&memory[0], 512, &memory[512], 512);

      boot_file.read(memory, 512); // Read the boot sector's code.
      // Boot on the file.

    }

  };

}