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

#include <Runtime.h>

#include <stdbool.h>
#include <stddef.h>

#include "RuntimeCommon.h"

void _sym_set_return_expression(SymExpr expr) { 
    pun.sym = expr;
    uint_t rcx = pun.uint;

    kAFL_hypercall(SET_RETURN_EXPRESSION, rcx, 0, 0, 0, 0, 0);
}

SymExpr _sym_get_return_expression(void) {
    pun.uint = kAFL_hypercall(GET_RETURN_EXPRESSION, 0, 0, 0, 0, 0, 0);
    return pun.sym;
}

void _sym_set_parameter_expression(uint8_t index, SymExpr expr) {
    pun.u8 = index;
    uint_t rcx = pun.uint;
    pun.sym = expr;
    uint_t rdx = pun.uint;

    kAFL_hypercall(SET_PARAMETER_EXPRESSION, rcx, rdx, 0, 0, 0, 0);
}

SymExpr _sym_get_parameter_expression(uint8_t index) {
    pun.u8 = index;
    uint_t rcx = pun.uint;

    pun.uint = kAFL_hypercall(GET_PARAMETER_EXPRESSION, rcx, 0, 0, 0, 0, 0);
    return pun.sym;
}

void _sym_memcpy(uint8_t *dest, const uint8_t *src, size_t length) {
    pun.u8ptr = dest;
    uint_t rcx = pun.uint;
    pun.cu8ptr = src;
    uint_t rdx = pun.uint;
    pun.size = length;
    uint_t rdi = pun.uint;

    kAFL_hypercall(MEMCPY, rcx, rdx, rdi, 0, 0, 0);
}

void _sym_memset(uint8_t *memory, SymExpr value, size_t length) {
    pun.u8ptr = memory;
    uint_t rcx = pun.uint;
    pun.sym = value;
    uint_t rdx = pun.uint;
    pun.size = length;
    uint_t rdi = pun.uint;

    kAFL_hypercall(MEMSET, rcx, rdx, rdi, 0, 0, 0);
}

void _sym_memmove(uint8_t *dest, const uint8_t *src, size_t length) {
    pun.u8ptr = dest;
    uint_t rcx = pun.uint;
    pun.cu8ptr = src;
    uint_t rdx = pun.uint;
    pun.size = length;
    uint_t rdi = pun.uint;

    kAFL_hypercall(MEMMOVE, rcx, rdx, rdi, 0, 0, 0);
}

SymExpr _sym_read_memory(uint8_t *addr, size_t length, bool little_endian) {
    pun.u8ptr = addr;
    uint_t rcx = pun.uint;
    pun.size = length;
    uint_t rdx = pun.uint;
    pun.b = little_endian;
    uint_t rdi = pun.uint;

    pun.uint = kAFL_hypercall(READ_MEMORY, rcx, rdx, rdi, 0, 0, 0);
    return pun.sym;
}

void _sym_write_memory(uint8_t *addr, size_t length, SymExpr expr,
                       bool little_endian) {
    pun.u8ptr = addr;
    uint_t rcx = pun.uint;
    pun.size = length;
    uint_t rdx = pun.uint;
    pun.sym = expr;
    uint_t rdi = pun.uint;

    kAFL_hypercall(WRITE_MEMORY, rcx, rdx, rdi, 0, 0, 0);
}

SymExpr _sym_build_extract(SymExpr expr, uint64_t offset, uint64_t length,
                           bool little_endian) {
    pun.sym = expr;
    uint_t rcx = pun.uint;
    pun.u64 = offset;
    uint_t rdx = pun.uint;
    pun.u64 = length;
    uint_t rdi = pun.uint;
    pun.b = little_endian;
    uint_t rsi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_EXTRACT, rcx, rdx, rdi, rsi, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_bswap(SymExpr expr) {
    pun.sym = expr;
    uint_t rcx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_BSWAP, rcx, 0, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_insert(SymExpr target, SymExpr to_insert, uint64_t offset,
                          bool little_endian) {
    pun.sym = target;
    uint_t rcx = pun.uint;
    pun.sym = to_insert;
    uint_t rdx = pun.uint;
    pun.u64 = offset;
    uint_t rdi = pun.uint;
    pun.b = little_endian;
    uint_t rsi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_INSERT, rcx, rdx, rdi, rsi, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_zero_bytes(size_t length) {
    pun.size = length;
    uint_t rcx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_ZERO_BYTES, rcx, 0, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_sadd_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_SADD_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_uadd_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_UADD_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_ssub_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_SSUB_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_usub_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_USUB_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

static SymExpr _sym_build_shift_left_overflow(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_SHIFT_LEFT_OVERFLOW, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_sshl_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_SSHL_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_ushl_sat(SymExpr a, SymExpr b) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_USHL_SAT, rcx, rdx, 0, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_add_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;
    pun.b = is_signed;
    uint_t rdi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_ADD_OVERFLOW, rcx, rdx, rdi, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_sub_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;
    pun.b = is_signed;
    uint_t rdi = pun.uint;
    pun.b = little_endian;
    uint_t rsi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_SUB_OVERFLOW, rcx, rdx, rdi, rsi, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_mul_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;
    pun.b = is_signed;
    uint_t rdi = pun.uint;
    pun.b = little_endian;
    uint_t rsi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_MUL_OVERFLOW, rcx, rdx, rdi, rsi, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_funnel_shift_left(SymExpr a, SymExpr b, SymExpr c) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;
    pun.sym = c;
    uint_t rdi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_FUNNEL_SHIFT_LEFT, rcx, rdx, rdi, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_funnel_shift_right(SymExpr a, SymExpr b, SymExpr c) {
    pun.sym = a;
    uint_t rcx = pun.uint;
    pun.sym = b;
    uint_t rdx = pun.uint;
    pun.sym = c;
    uint_t rdi = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_FUNNEL_SHIFT_RIGHT, rcx, rdx, rdi, 0, 0, 0);
    return pun.sym;
}

SymExpr _sym_build_abs(SymExpr expr) {
    pun.sym = expr;
    uint_t rcx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_ABS, rcx, 0, 0, 0, 0, 0);
    return pun.sym;
}

void _sym_register_expression_region(SymExpr *start, size_t length) {
    pun.symptr = start;
    uint_t rcx = pun.uint;
    pun.size = length;
    uint_t rdx = pun.uint;

    kAFL_hypercall(REGISTER_EXPRESSION_REGION, rcx, rdx, 0, 0, 0, 0);
}

void _sym_make_symbolic(const void *data, size_t byte_length,
                        size_t input_offset) {
    pun.cptr = data;
    uint_t rcx = pun.uint;
    pun.size = byte_length;
    uint_t rdx = pun.uint;
    pun.size = input_offset;
    uint_t rdi = pun.uint;

    kAFL_hypercall(MAKE_SYMBOLIC, rcx, rdx, rdi, 0, 0, 0);
}

void symcc_make_symbolic(const void *start, size_t byte_length) {
    pun.cptr = start;
    uint_t rcx = pun.uint;
    pun.size = byte_length;
    uint_t rdx = pun.uint;

    kAFL_hypercall(SYMCC_MAKE_SYMBOLIC, rcx, rdx, 0, 0, 0, 0);
}

SymExpr _sym_build_bit_to_bool(SymExpr expr) {
    pun.sym = expr;
    uint_t rcx = pun.uint;

    pun.uint = kAFL_hypercall(BUILD_BIT_TO_BOOL, rcx, 0, 0, 0, 0, 0);
    return pun.sym;
}

/* void _sym_set_return_expression(SymExpr expr) {  */
/*     kAFL_hypercall(SET_RETURN_EXPRESSION, (uint_t) expr, 0, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_get_return_expression(void) { */
/*     return (SymExpr) kAFL_hypercall(GET_RETURN_EXPRESSION, 0, 0, 0, 0, 0, 0); */
/* } */
/**/
/* void _sym_set_parameter_expression(uint8_t index, SymExpr expr) { */
/*     kAFL_hypercall(SET_PARAMETER_EXPRESSION, (uint_t) index, (uint_t) expr, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_get_parameter_expression(uint8_t index) { */
/*     return (SymExpr) kAFL_hypercall(GET_PARAMETER_EXPRESSION, (uint_t) index, 0, 0, 0, 0, 0); */
/* } */
/**/
/* void _sym_memcpy(uint8_t *dest, const uint8_t *src, size_t length) { */
/*     kAFL_hypercall(MEMCPY, (uint_t) dest, (uint_t) src, (uint_t) length, 0, 0, 0); */
/* } */
/**/
/* void _sym_memset(uint8_t *memory, SymExpr value, size_t length) { */
/*     kAFL_hypercall(MEMSET, (uint_t) memory, (uint_t) value, (uint_t) length, 0, 0, 0); */
/* } */
/**/
/* void _sym_memmove(uint8_t *dest, const uint8_t *src, size_t length) { */
/*     kAFL_hypercall(MEMMOVE, (uint_t) dest, (uint_t) src, (uint_t) length, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_read_memory(uint8_t *addr, size_t length, bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(READ_MEMORY, (uint_t) addr, (uint_t) length, (uint_t) little_endian, 0, 0, 0); */
/* } */
/**/
/* void _sym_write_memory(uint8_t *addr, size_t length, SymExpr expr, */
/*                        bool little_endian) { */
/*     kAFL_hypercall(WRITE_MEMORY, (uint_t) addr, (uint_t) length, (uint_t) expr, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_extract(SymExpr expr, uint64_t offset, uint64_t length, */
/*                            bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_EXTRACT, (uint_t) expr, (uint_t) offset, (uint_t) length, (uint_t) little_endian, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_bswap(SymExpr expr) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_BSWAP, (uint_t) expr, 0, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_insert(SymExpr target, SymExpr to_insert, uint64_t offset, */
/*                           bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_INSERT, (uint_t) target, (uint_t) to_insert, (uint_t) offset, (uint_t) little_endian, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_zero_bytes(size_t length) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_ZERO_BYTES, (uint_t) length, 0, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_sadd_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_SADD_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_uadd_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_UADD_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_ssub_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_SSUB_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_usub_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_USUB_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* static SymExpr _sym_build_shift_left_overflow(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_SHIFT_LEFT_OVERFLOW, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_sshl_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_SSHL_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_ushl_sat(SymExpr a, SymExpr b) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_USHL_SAT, (uint_t) a, (uint_t) b, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_add_overflow(SymExpr a, SymExpr b, bool is_signed, */
/*                                 bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_ADD_OVERFLOW, (uint_t) a, (uint_t) b, (uint_t) is_signed, (uint_t) little_endian, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_sub_overflow(SymExpr a, SymExpr b, bool is_signed, */
/*                                 bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_SUB_OVERFLOW, (uint_t) a, (uint_t) b, (uint_t) is_signed, (uint_t) little_endian, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_mul_overflow(SymExpr a, SymExpr b, bool is_signed, */
/*                                 bool little_endian) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_MUL_OVERFLOW, (uint_t) a, (uint_t) b, (uint_t) little_endian, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_funnel_shift_left(SymExpr a, SymExpr b, SymExpr c) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_FUNNEL_SHIFT_LEFT, (uint_t) a, (uint_t) b, (uint_t) c, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_funnel_shift_right(SymExpr a, SymExpr b, SymExpr c) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_FUNNEL_SHIFT_RIGHT, (uint_t) a, (uint_t) b, (uint_t) c, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_abs(SymExpr expr) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_ABS, (uint_t) expr, 0, 0, 0, 0, 0); */
/* } */
/**/
/* void _sym_register_expression_region(SymExpr *start, size_t length) { */
/*     kAFL_hypercall(REGISTER_EXPRESSION_REGION, (uint_t) start, (uint_t) length, 0, 0, 0, 0); */
/* } */
/**/
/* void _sym_make_symbolic(const void *data, size_t byte_length, */
/*                         size_t input_offset) { */
/*     kAFL_hypercall(MAKE_SYMBOLIC, (uint_t) data, (uint_t) byte_length, (uint_t) input_offset, 0, 0, 0); */
/* } */
/**/
/* void symcc_make_symbolic(const void *start, size_t byte_length) { */
/*     kAFL_hypercall(MAKE_SYMBOLIC, (uint_t) start, (uint_t) byte_length, 0, 0, 0, 0); */
/* } */
/**/
/* SymExpr _sym_build_bit_to_bool(SymExpr expr) { */
/*     return (SymExpr) kAFL_hypercall(BUILD_BIT_TO_BOOL, (uint_t) expr, 0, 0, 0, 0, 0); */
/* } */
