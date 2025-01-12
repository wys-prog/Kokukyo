// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include <string>
#include <cstdint>
#include <sstream>
#include <stdexcept>

#define __throw_rt(e)  throw std::runtime_error(e)

namespace wylma {
  namespace kokuyo {
    class exceptions {
    private:

    public:
      static std::string illegal(uint64_t ip, uint64_t instruction) {
        std::stringstream ss;
        ss << "Illegal instruction.\n\tInstruction: " << std::hex << std::uppercase << instruction << " | ip: " << ip;
        return ss.str();
      }

      static std::string stack_out(uint64_t ip, uint64_t stack_max, uint64_t size_of_push) {
        std::stringstream ss;

        ss << "Stack out of bounds.\n"
              "\tStack max:    " << stack_max    << "\n"
              "\tSize of push: " << size_of_push << "\n";

        return ss.str();
      }

      static std::string stack_null(uint64_t ip) {
        std::stringstream ss;

        ss << "Nulling the stack.\n"
              "\tip: " << std::uppercase << std::hex << ip << "\n";

        return ss.str();
      }
    };
  }
}