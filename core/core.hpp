// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#include <cstdint>
#include <functional>

#include "set.h"
#include "except.hpp"
#include "uint128_t.h"

namespace kokuyo {
  class core {
  private:
    uint8_t              *memory_segment;
    uint64_t              segment_end;
    uint64_t             *stack_beg;
    uint64_t              stack_max;
    uint64_t              stack_pointer;
    uint64_t              ip;
    bool                  _halt;
    uint8_t               flags;

    uint8_t               read_byte();
    uint16_t              read_word();
    uint32_t              read_dword();
    uint64_t              read_qword();
    uint128_t             read_dqword();

    void                  _push(uint64_t bytes);
    uint64_t              _pop();
    void                  _cmp(uint64_t a, uint64_t b);
    void                  _mod();

    void                  init_table();

    std::function<void()> ftable[INS_COUNT];
    std::function<void()> undertable[9*4];

  public:
    void run() {
      while (!_halt || ip < segment_end) { // Code outside the segment cannot be executed.
        uint8_t u = read_byte();

        if (u < INS_COUNT) {
          ftable[u](); // Call the function. 
        } else {
          exceptions::illegal(ip, u);
        }
      }
    }

    core(uint8_t *mm_ptr, uint64_t s_end, uint64_t *st_beg, uint64_t st_max) 
      : memory_segment(mm_ptr), segment_end(s_end), stack_beg(st_beg), stack_max(st_max)
      {
        stack_pointer = 0x0000000000000000;
        ip            = 0x0000000000000000;
        flags         = 0x00;
        _halt         = 0x00;
      }
  };
}