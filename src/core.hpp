// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.


#pragma once

#include <cstdint>
#include <stdfloat>
#include <functional>
#include <unordered_map>

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
      array<uint8_t, memory_len> &memory; // Get a reference to the memory.
      uint64_t  _ip;
      bool      _halt = false;
      std::unordered_map<uint8_t, std::function<void()>> ftable;

      uint8_t           read_8();   // The virtual machine reads only 8 bits.
      uint16_t          read_16();  // To read more bits, you need make a 
      uint32_t          read_32();  // cast, from an array, to an intiger.
      uint64_t          read_64();
      std::float128_t   read_128(); // The standard 128. Use it only for floats. 
                                    // Manipulation of 128 intigers will maybe 
                                    // come in another arch, or on another version.

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

      core(array<uint8_t, memory_len> &_array) : memory(_array) {}
    };
  
  } // namespace kokuyo
} // namespace wylma
