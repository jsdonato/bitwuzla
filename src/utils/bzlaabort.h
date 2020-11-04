/**
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * This file is part of Bitwuzla.
 * See COPYING for more information on using this software.
 */

#ifndef BZLAABORT_H_INCLUDED
#define BZLAABORT_H_INCLUDED

#include <stdbool.h>

/* -------------------------------------------------------------------------- */

void bzla_abort_fun(const char* msg);

void bzla_abort_warn(
    bool abort, const char* filename, const char* fun, const char* fmt, ...);

/* -------------------------------------------------------------------------- */

#define BZLA_ABORT(condition, msg...)                     \
  if (condition)                                          \
  {                                                       \
    bzla_abort_warn(true, __FILE__, __FUNCTION__, ##msg); \
  }

#define BZLA_WARN(condition, msg...)                       \
  if (condition)                                           \
  {                                                        \
    bzla_abort_warn(false, __FILE__, __FUNCTION__, ##msg); \
  }

/* -------------------------------------------------------------------------- */
#endif
