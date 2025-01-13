// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#pragma once

#include <cstdint>
#include <stdexcept>

namespace wylma {
  template <typename T, uint64_t size>
  class array {
  private:
    T base[size];

  public:
    T &operator[](uint64_t index) {
      if (index >= size) throw std::out_of_range();

      return &base[index];
    };

    array &operator=(const array<T, size> &arr) {
      base = arr.base;

      return *this;
    }

  };

}