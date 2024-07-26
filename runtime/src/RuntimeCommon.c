// This file is part of the SymCC runtime.
//
// The SymCC runtime is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// The SymCC runtime is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with SymCC. If not, see <https://www.gnu.org/licenses/>.

#include <stdbool.h>
#include <stddef.h>

#include <Runtime.h>
#include "RuntimeCommon.h"

void _sym_set_return_expression(SymExpr expr) { 
    return;
}

SymExpr _sym_get_return_expression(void) {
    return NULL;
}

void _sym_set_parameter_expression(uint8_t index, SymExpr expr) {
    return; 
}

SymExpr _sym_get_parameter_expression(uint8_t index) {
    return NULL;
}

void _sym_memcpy(uint8_t *dest, const uint8_t *src, size_t length) {
    return;
}

void _sym_memset(uint8_t *memory, SymExpr value, size_t length) {
    return;
}

void _sym_memmove(uint8_t *dest, const uint8_t *src, size_t length) {
    return;
}

SymExpr _sym_read_memory(uint8_t *addr, size_t length, bool little_endian) {
    return NULL;
}

void _sym_write_memory(uint8_t *addr, size_t length, SymExpr expr,
                       bool little_endian) {
    return;
}

SymExpr _sym_build_extract(SymExpr expr, uint64_t offset, uint64_t length,
                           bool little_endian) {
    return NULL;
}

SymExpr _sym_build_bswap(SymExpr expr) {
    return NULL;
}

SymExpr _sym_build_insert(SymExpr target, SymExpr to_insert, uint64_t offset,
                          bool little_endian) {
    return NULL;
}

SymExpr _sym_build_zero_bytes(size_t length) {
    return NULL;
}

SymExpr _sym_build_sadd_sat(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_uadd_sat(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_ssub_sat(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_usub_sat(SymExpr a, SymExpr b) {
    return NULL;
}

static SymExpr _sym_build_shift_left_overflow(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_sshl_sat(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_ushl_sat(SymExpr a, SymExpr b) {
    return NULL;
}

SymExpr _sym_build_add_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    return NULL;
}

SymExpr _sym_build_sub_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    return NULL;
}

SymExpr _sym_build_mul_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    return NULL;
}

SymExpr _sym_build_funnel_shift_left(SymExpr a, SymExpr b, SymExpr c) {
    return NULL;
}

SymExpr _sym_build_funnel_shift_right(SymExpr a, SymExpr b, SymExpr c) {
    return NULL;
}

SymExpr _sym_build_abs(SymExpr expr) {
    return NULL;
}

void _sym_register_expression_region(SymExpr *start, size_t length) {
	return;
}

void _sym_make_symbolic(const void *data, size_t byte_length,
                        size_t input_offset) {
	return;
}

void symcc_make_symbolic(const void *start, size_t byte_length) {
	return;
}

SymExpr _sym_build_bit_to_bool(SymExpr expr) {
    return NULL;
}
