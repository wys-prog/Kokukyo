// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#include <cstdint>
#include <functional>

#include "core.hpp"
#include "set.h"
#include "except.hpp"
#include "uint128_t.h"

namespace kokuyo {
  void core::init_undertable() {
    // mov byte DST SRC
    undertable[0x00] = [this]() { memory_segment[read_byte()] = read_byte(); };

    // mov word DST SRC
    undertable[0x01] = [this]() { memory_segment[read_word()] = read_word(); };

    // mov dword DST SRC
    undertable[0x02] = [this]() { memory_segment[read_dword()] = read_dword(); };

    // mov qword DST SRC
    undertable[0x03] = [this]() { memory_segment[read_qword()] = read_qword(); };


    // add byte DST SRC
    undertable[0x04] = [this]() { memory_segment[read_byte()] += read_byte(); };

    // add word DST SRC
    undertable[0x05] = [this]() { memory_segment[read_word()] += read_word(); };

    // add dword DST SRC
    undertable[0x06] = [this]() { memory_segment[read_dword()] += read_dword(); };

    // add qword DST SRC
    undertable[0x07] = [this]() { memory_segment[read_qword()] += read_qword(); };


    // sub byte DST SRC
    undertable[0x08] = [this]() { memory_segment[read_byte()] -= read_byte(); };

    // sub word DST SRC
    undertable[0x09] = [this]() { memory_segment[read_word()] -= read_word(); };

    // sub dword DST SRC
    undertable[0x0A] = [this]() { memory_segment[read_dword()] -= read_dword(); };

    // sub qword DST SRC
    undertable[0x0B] = [this]() { memory_segment[read_qword()] -= read_qword(); };


    // mul byte DST SRC
    undertable[0x0C] = [this]() { memory_segment[read_byte()] *= read_byte(); };

    // mul word DST SRC
    undertable[0x0D] = [this]() { memory_segment[read_word()] *= read_word(); };

    // mul dword DST SRC
    undertable[0x0E] = [this]() { memory_segment[read_dword()] *= read_dword(); };

    // mul qword DST SRC
    undertable[0x0F] = [this]() { memory_segment[read_qword()] *= read_qword(); };


    // div byte DST SRC
    undertable[0x10] = [this]() { memory_segment[read_byte()] /= read_byte(); };

    // div word DST SRC
    undertable[0x11] = [this]() { memory_segment[read_word()] /= read_word(); };

    // div dword DST SRC
    undertable[0x12] = [this]() { memory_segment[read_dword()] /= read_dword(); };

    // div qword DST SRC
    undertable[0x13] = [this]() { memory_segment[read_qword()] /= read_qword(); };


    // mod byte
    undertable[0x14] = [this]() {
      uint8_t dst = read_byte(), src = read_byte(); 
      memory_segment[dst] = dst % src;
    };

    // mod word
    undertable[0x15] = [this]() {
      uint16_t dst = read_word(), src = read_word(); 
      memory_segment[dst] = dst % src;
    };

    // mod qword
    undertable[0x15] = [this]() {
      uint32_t dst = read_dword(), src = read_dword(); 
      memory_segment[dst] = dst % src;
    };

    // mod dword
    undertable[0x15] = [this]() {
      uint64_t dst = read_qword(), src = read_qword(); 
      memory_segment[dst] = dst % src;
    };

    // push byte
    undertable[0x16] = [this]() {
      
    };

    // push word
    // push dword
    // push qword

  }
}