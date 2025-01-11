// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

// This file: 
//    Kokuyo -S 
//    Kokuyo -S (or Kokuyos) is a version of Kokuyo Virtual Machine, but in a single thread.
//    It supports all features of the standard version of KoVM. Only the -t (for threads) is not supported.

#include <cstdint>
#include <fstream>
#include <stdexcept>

#include "libs/kargs/kargs.h"
#include "core/core.hpp"

typedef char *cstr;

namespace kokuyo {
  template <unsigned long _mmlen, cstr _input, bool _bios, bool _libs>
  class KoVMS {
  private:
    uint8_t memory[_mmlen];
    // todo: support of BIOS
    // todo: support of libs

  public:

    void boot() {
      std::ifstream input(_input);

      if (!input) throw std::runtime_error(_input + std::string(": Cannot open file."));

      input.read(memory, 512);

      core c(&memory[0x00], _mmlen-1024, _mmlen-1024, _mmlen);
      c.run();
    }

  };

}
