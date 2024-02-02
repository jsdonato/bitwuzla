/***
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * Copyright (C) 2023 by the authors listed in the AUTHORS file at
 * https://github.com/bitwuzla/bitwuzla/blob/main/AUTHORS
 *
 * This file is part of Bitwuzla under the MIT license. See COPYING for more
 * information at https://github.com/bitwuzla/bitwuzla/blob/main/COPYING
 */

#ifndef BITWUZLA_API_C_PARSER_H_INCLUDED
#define BITWUZLA_API_C_PARSER_H_INCLUDED

#include <bitwuzla/c/bitwuzla.h>

/** A Bitwuzla parser. */
typedef struct BitwuzlaParser BitwuzlaParser;

/** \addtogroup c_bitwuzlaparser
 *  @{
 */

/**
 * Create a new Bitwuzla parser instance.
 *
 * The returned instance must be deleted via `bitwuzla_parser_delete()`.
 *
 * @note The parser creates and owns the associated Bitwuzla instance.
 * @param options The associated options.
 * @param language     The format of the input.
 * @param base         The base of the string representation of bit-vector
 *                     values; `2` for binary, `10` for decimal, and `16` for
 *                     hexadecimal. Always ignored for Boolean and RoundingMode
 *                     values.
 * @param outfile_name The output file name. If name is '<stdout>', the parser
 *                     writes to stdout.
 * @return A pointer to the created Bitwuzla parser instance.
 *
 * @see
 *   * `bitwuzla_parser_delete`
 */
BitwuzlaParser* bitwuzla_parser_new(BitwuzlaOptions* options,
                                    const char* language,
                                    uint8_t base,
                                    const char* outfile_name);

/**
 * Delete a Bitwuzla parser instance.
 *
 * The given instance must have been created via `bitwuzla_parser_new()`.
 *
 * @param parser The Bitwuzla parser instance to delete.
 *
 * @see
 *   * `bitwuzla_parser_new`
 */
void bitwuzla_parser_delete(BitwuzlaParser* parser);

/**
 * Parse input, either from a file or from a string.
 *
 * @param parser     The Bitwuzla parser instance.
 * @param input      The name of the input file if `parse_file` is true,
 *                   else a string with the input.
 * @param parse_only True to only parse without executing check-sat calls.
 * @param parse_file True to parse an input file with the given name `input`,
 *                   false to parse from `input` as a string input.
 * @return False on error. The error message can be queried via
 *         `bitwuzla_parser_get_error_msg()`.
 * @note Parameter `parse_only` is redundant for BTOR2 input, its the only
 *       available mode for BTOR2 (due to the language not supporting
 *       "commands" as in SMT2).
 */
bool bitwuzla_parser_parse(BitwuzlaParser* parser,
                           const char* input,
                           bool parse_only,
                           bool parse_file);

/**
 * Parse term from string.
 * @param input The input string.
 * @param term  Output parameter for the resulting term.
 * @return False on error. The error message can be queried via
 *         `bitwuzla_parser_get_error_msg()`.
 */
bool bitwuzla_parser_parse_term(BitwuzlaParser* parser,
                                const char* input,
                                BitwuzlaTerm* term);
/**
 * Parse sort from string.
 * @param input The input string.
 * @param sort  Output parameter for the resulting sort.
 * @return False on error. The error message can be queried via
 *         `bitwuzla_parser_get_error_msg()`.
 */
bool bitwuzla_parser_parse_sort(BitwuzlaParser* parser,
                                const char* input,
                                BitwuzlaSort* sort);

/**
 * Get the current error message.
 * @param parser The Bitwuzla parser instance.
 * @return The error message.
 */
const char* bitwuzla_parser_get_error_msg(BitwuzlaParser* parser);

/**
 * Get the associated Bitwuzla instance.
 * @return The Bitwuzla instance.
 */
Bitwuzla* bitwuzla_parser_get_bitwuzla(BitwuzlaParser* parser);

/** @} */

#endif
