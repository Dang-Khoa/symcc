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
// along with the SymCC runtime. If not, see <https://www.gnu.org/licenses/>.

#include "Runtime.h"

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

void _sym_initialize(void) {
    kAFL_hypercall(INITIALIZE, 0, 0, 0, 0, 0, 0);
    return;
}

SymExpr _sym_build_integer(uint64_t value, uint8_t bits) {
    return kAFL_hypercall(BUILD_INTEGER, value, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_integer128(uint64_t high, uint64_t low) {
    return kAFL_hypercall(BUILD_INTEGER128, high, low, 0, 0, 0, 0);
}

SymExpr _sym_build_integer_from_buffer(void *buffer, unsigned num_bits) {
    return kAFL_hypercall(BUILD_INTEGER_FROM_BUFFER, (uint_t) buffer, (uint_t) num_bits, 0, 0, 0, 0);
}

SymExpr _sym_build_float(double value, int is_double) {
    return kAFL_hypercall(BUILD_FLOAT, (uint_t) value, (uint_t) is_double, 0, 0, 0, 0);
}

SymExpr _sym_get_input_byte(size_t offset,  uint8_t concrete_value){
    return kAFL_hypercall(GET_INPUT_BYTE, offset, (uint_t) concrete_value, 0, 0, 0, 0);
}

SymExpr _sym_build_null_pointer(void)  {
    return kAFL_hypercall(BUILD_NULL_POINTER, 0, 0, 0, 0, 0, 0);
}
SymExpr _sym_build_true(void)  {
    return kAFL_hypercall(BUILD_TRUE, 0, 0, 0, 0, 0, 0);
}
SymExpr _sym_build_false(void)  {
    return kAFL_hypercall(BUILD_FALSE, 0, 0, 0, 0, 0, 0);
}

// in cpp it was bool
SymExpr _sym_build_bool(bool value)  {
    return kAFL_hypercall(BUILD_BOOL, (uint_t) value, 0, 0, 0, 0, 0);
}


// TODO check
SymExpr _sym_build_neg(Z3_ast expr) {
    return kAFL_hypercall(BUILD_NEG, (uint_t) expr, 0, 0, 0, 0, 0);
}

#define DEF_BINARY_EXPR_BUILDER(name, z3_name) \
    SymExpr _sym_build_##name(Z3_ast a, Z3_ast b) { \
	return kAFL_hypercall(z3_name, (uint_t) a, (uint_t) b, 0, 0, 0, 0); \
    }

DEF_BINARY_EXPR_BUILDER(add, BUILD_ADD)
DEF_BINARY_EXPR_BUILDER(sub, BUILD_SUB)
DEF_BINARY_EXPR_BUILDER(mul, BUILD_MUL)
DEF_BINARY_EXPR_BUILDER(unsigned_div, BUILD_UNSIGNED_DIV)
DEF_BINARY_EXPR_BUILDER(signed_div, BUILD_SIGNED_DIV)
DEF_BINARY_EXPR_BUILDER(unsigned_rem, BUILD_UNSIGNED_REM)
DEF_BINARY_EXPR_BUILDER(signed_rem, BUILD_SIGNED_REM)
DEF_BINARY_EXPR_BUILDER(shift_left, BUILD_SHIFT_LEFT)
DEF_BINARY_EXPR_BUILDER(logical_shift_right, BUILD_LOGICAL_SHIFT_RIGHT)
DEF_BINARY_EXPR_BUILDER(arithmetic_shift_right, BUILD_ARITHMETIC_SHIFT_RIGHT)

DEF_BINARY_EXPR_BUILDER(signed_less_than, BUILD_SIGNED_LESS_THAN)
DEF_BINARY_EXPR_BUILDER(signed_less_equal, BUILD_SIGNED_LESS_EQUAL)
DEF_BINARY_EXPR_BUILDER(signed_greater_than, BUILD_SIGNED_GREATER_THAN)
DEF_BINARY_EXPR_BUILDER(signed_greater_equal, BUILD_SIGNED_GREATER_EQUAL)
DEF_BINARY_EXPR_BUILDER(unsigned_less_than, BUILD_UNSIGNED_LESS_THAN)
DEF_BINARY_EXPR_BUILDER(unsigned_less_equal, BUILD_UNSIGNED_LESS_EQUAL)
DEF_BINARY_EXPR_BUILDER(unsigned_greater_than, BUILD_UNSIGNED_GREATER_THAN)
DEF_BINARY_EXPR_BUILDER(unsigned_greater_equal, BUILD_UNSIGNED_GREATER_EQUAL)
DEF_BINARY_EXPR_BUILDER(equal, BUILD_EQUAL)

DEF_BINARY_EXPR_BUILDER(and, BUILD_AND)
DEF_BINARY_EXPR_BUILDER(or, BUILD_OR)
DEF_BINARY_EXPR_BUILDER(bool_xor, BUILD_BOOL_XOR)
DEF_BINARY_EXPR_BUILDER(xor, BUILD_XOR)

DEF_BINARY_EXPR_BUILDER(float_ordered_greater_than, BUILD_FLOAT_ORDERED_GREATER_THAN)
DEF_BINARY_EXPR_BUILDER(float_ordered_greater_equal, BUILD_FLOAT_ORDERED_GREATER_EQUAL)
DEF_BINARY_EXPR_BUILDER(float_ordered_less_than, BUILD_FLOAT_ORDERED_LESS_THAN)
DEF_BINARY_EXPR_BUILDER(float_ordered_less_equal, BUILD_FLOAT_ORDERED_LESS_EQUAL)
DEF_BINARY_EXPR_BUILDER(float_ordered_equal, BUILD_FLOAT_ORDERED_EQUAL)

#undef DEF_BINARY_EXPR_BUILDER

SymExpr _sym_build_ite(Z3_ast cond, Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_ITE, (uint_t)cond, (uint_t)a, (uint_t)b, 0, 0, 0);
}

SymExpr _sym_build_fp_add(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_ADD, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_sub(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_SUB, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_mul(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_MUL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_div(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_DIV, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_rem(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_REM, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_abs(Z3_ast a) {
	return kAFL_hypercall(BUILD_FP_ABS, (uint_t)a, 0, 0, 0, 0, 0);
}

SymExpr _sym_build_fp_neg(Z3_ast a) {
	return kAFL_hypercall(BUILD_FP_NEG, (uint_t)a, 0, 0, 0, 0, 0);
}

SymExpr _sym_build_not(Z3_ast expr) {
	return kAFL_hypercall(BUILD_NOT, (uint_t)expr, 0, 0, 0, 0, 0);
}

SymExpr _sym_build_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_bool_and(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_BOOL_AND, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_bool_or(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_BOOL_OR, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_ordered_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_ORDERED_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_ordered(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_ORDERED, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_greater_than(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_THAN, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_greater_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_less_than(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_THAN, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_less_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_float_unordered_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_build_sext(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_SEXT, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_zext(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_ZEXT, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_trunc(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_TRUNC, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_int_to_float(Z3_ast value, int is_double, int is_signed) {
	return kAFL_hypercall(BUILD_INT_TO_FLOAT, (uint_t)value, (uint_t) is_double, (uint_t) is_signed, 0, 0, 0);
}

SymExpr _sym_build_float_to_float(Z3_ast expr, int to_double) {
	return kAFL_hypercall(BUILD_FLOAT_TO_FLOAT, (uint_t)expr, (uint_t) to_double, 0, 0, 0, 0);
}

SymExpr _sym_build_bits_to_float(Z3_ast expr, int to_double) {
	return kAFL_hypercall(BUILD_BITS_TO_FLOAT, (uint_t)expr, (uint_t) to_double, 0, 0, 0, 0);
}

SymExpr _sym_build_float_to_bits(Z3_ast expr) {
	return kAFL_hypercall(BUILD_FLOAT_TO_BITS, (uint_t)expr, 0, 0, 0, 0, 0);
}

SymExpr _sym_build_float_to_signed_integer(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_FLOAT_TO_SIGNED_INTEGER, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_float_to_unsigned_integer(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_FLOAT_TO_UNSIGNED_INTEGER, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

SymExpr _sym_build_bool_to_bit(Z3_ast expr) {
	return kAFL_hypercall(BUILD_BOOL_TO_BIT, (uint_t)expr, 0, 0, 0, 0, 0);
}

void _sym_push_path_constraint(SymExpr constraint, int taken, uintptr_t size_id [[maybe_unused]]) {
    kAFL_hypercall(PUSH_PATH_CONSTRAINT, (uint_t) constraint, (uint_t) taken, (uint_t) size_id, 0, 0, 0);
}

SymExpr _sym_concat_helper(SymExpr a, SymExpr b) {
	return kAFL_hypercall(CONCAT_HELPER, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

SymExpr _sym_extract_helper(SymExpr expr, size_t first_bit, size_t last_bit) {
	return kAFL_hypercall(EXTRACT_HELPER, (uint_t) expr, (uint_t) first_bit, (uint_t) last_bit, 0, 0, 0);
}

size_t _sym_bits_helper(SymExpr expr) {
	return (size_t) kAFL_hypercall(BITS_HELPER, (uint_t) expr, 0, 0, 0, 0, 0);
}

/* No call-stack tracing */
void _sym_notify_call(uintptr_t) {}
void _sym_notify_ret(uintptr_t) {}
void _sym_notify_basic_block(uintptr_t) {}


const char *_sym_expr_to_string(SymExpr expr) {
    return kAFL_hypercall(EXPR_TO_STRING, (uint_t) expr, 0, 0, 0, 0, 0);
}

bool _sym_feasible(SymExpr expr) {
    return kAFL_hypercall(FEASIBLE, (uint_t) expr, 0, 0, 0, 0, 0);
}

void _sym_collect_garbage() {
    kAFL_hypercall(COLLECT_GARBAGE, 0, 0, 0, 0, 0, 0);
}

void symcc_set_test_case_handler(TestCaseHandler) {
    return;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
