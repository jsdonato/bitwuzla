/***
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * Copyright (C) 2024 by the authors listed in the AUTHORS file at
 * https://github.com/bitwuzla/bitwuzla/blob/main/AUTHORS
 *
 * This file is part of Bitwuzla under the MIT license. See COPYING for more
 * information at https://github.com/bitwuzla/bitwuzla/blob/main/COPYING
 */

#ifndef BZLA_UTIL_SET_BV_FORMAT_H_INCLUDED
#define BZLA_UTIL_SET_BV_FORMAT_H_INCLUDED

#include <cstdint>
#include <iostream>

namespace bzla::util {

/** Struct to set bit-vector number format of nodes via stream manipulator. */
struct set_bv_format
{
  /** std::ios_base index for setting the number format of bit-vector values. */
  static int32_t s_stream_index_bv_format;

  /**
   * Constructor.
   * @param format The number format: 2 for binary, 10 for decimal and 16 for
   *               hexadecimal.
   */
  set_bv_format(uint8_t format) : d_format(format) {}
  /** @return The configured format. */
  uint8_t format() const { return d_format; }

 private:
  /** The configured number format. */
  uint8_t d_format;
};

std::ostream& operator<<(std::ostream& ostream, const set_bv_format& f);

}  // namespace bzla::util

#endif
