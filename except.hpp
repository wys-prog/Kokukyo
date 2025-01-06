#pragma once

#include <string>
#include <cstdint>
#include <sstream>
#include <stdexcept>

namespace kokuyo {
  class exceptions {
  private:
    static std::string make(const std::string &_what, uint64_t ip, uint64_t instruction) {
      std::stringstream ss;
      ss << _what << "\n\tinstruction: " << std::hex << std::uppercase << instruction << " | ip: " << ip;
      return ss.str();
    }
  public:
    static std::string make_illegal_instruction(uint64_t ip, uint64_t instruction) {
      return make("Illegal instruction", ip, instruction);
    }
  };
}