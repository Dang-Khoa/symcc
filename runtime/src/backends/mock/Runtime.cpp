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

#include <Runtime.h>

#include <atomic>
#include <cassert>
#include <cstring>
#include <set>

#ifndef NDEBUG
// Helper to print pointers properly.
#define P(ptr) reinterpret_cast<void *>(ptr)
#endif

/* TODO Eventually we'll want to inline as much of this as possible. I'm keeping
   it in C for now because that makes it easier to experiment with new features,
   but I expect that a lot of the functions will stay so simple that we can
   generate the corresponding bitcode directly in the compiler pass. */

namespace {

/// Indicate whether the runtime has been initialized.
std::atomic_flag g_initialized = ATOMIC_FLAG_INIT;

/// The global floating-point rounding mode.
Z3_ast g_rounding_mode;

// Some global constants for efficiency.
Z3_ast g_null_pointer, g_true, g_false;

FILE *g_log = stderr;

#ifndef NDEBUG
[[maybe_unused]] void dump_known_regions() { return; }

void handle_z3_error(Z3_context c [[maybe_unused]], Z3_error_code e) { return; }
#endif

SymExpr build_variable(const char *name, uint8_t bits) {
  //  std::cout << "mock build_variable";
  return g_null_pointer;
}

/// The set of all expressions we have ever passed to client code.
std::set<SymExpr> allocatedExpressions;

SymExpr registerExpression(SymExpr expr) {
  //  std::cout << "mock registerExpression";
  return expr;
}
} // namespace

void _sym_initialize(void) {
  //  std::cout << "mock _sym_initialize\n";
  return;
}

Z3_ast _sym_build_integer(uint64_t value, uint8_t bits) {
  //  std::cout << "mocked _sym_build_integer\n";
  return g_null_pointer;
}

Z3_ast _sym_build_integer128(uint64_t high, uint64_t low) {
  //  std::cout << "mocked _sym_build_integer128\n";
  return g_null_pointer;
}

Z3_ast _sym_build_float(double value, int is_double) {
  //  std::cout << "mocked _sym_build_float\n";
  return g_null_pointer;
}

Z3_ast _sym_get_input_byte(size_t offset, uint8_t) {
  // Not sure here
  //  std::cout << "mocked _sym_get_input_byte\n";
  return g_null_pointer;
}

Z3_ast _sym_build_null_pointer(void) { return g_null_pointer; }
Z3_ast _sym_build_true(void) { return g_true; }
Z3_ast _sym_build_false(void) { return g_false; }
Z3_ast _sym_build_bool(bool value) { return value ? g_true : g_false; }

Z3_ast _sym_build_neg(Z3_ast expr) {
  //  std::cout << "mocked _sym_build_neg\n";
  return expr;
}

#define DEF_BINARY_EXPR_BUILDER(name, z3_name)                                 \
  SymExpr _sym_build_##name(SymExpr a, SymExpr b) { return a; }

DEF_BINARY_EXPR_BUILDER(add, bvadd)
DEF_BINARY_EXPR_BUILDER(sub, bvsub)
DEF_BINARY_EXPR_BUILDER(mul, bvmul)
DEF_BINARY_EXPR_BUILDER(unsigned_div, bvudiv)
DEF_BINARY_EXPR_BUILDER(signed_div, bvsdiv)
DEF_BINARY_EXPR_BUILDER(unsigned_rem, bvurem)
DEF_BINARY_EXPR_BUILDER(signed_rem, bvsrem)
DEF_BINARY_EXPR_BUILDER(shift_left, bvshl)
DEF_BINARY_EXPR_BUILDER(logical_shift_right, bvlshr)
DEF_BINARY_EXPR_BUILDER(arithmetic_shift_right, bvashr)

DEF_BINARY_EXPR_BUILDER(signed_less_than, bvslt)
DEF_BINARY_EXPR_BUILDER(signed_less_equal, bvsle)
DEF_BINARY_EXPR_BUILDER(signed_greater_than, bvsgt)
DEF_BINARY_EXPR_BUILDER(signed_greater_equal, bvsge)
DEF_BINARY_EXPR_BUILDER(unsigned_less_than, bvult)
DEF_BINARY_EXPR_BUILDER(unsigned_less_equal, bvule)
DEF_BINARY_EXPR_BUILDER(unsigned_greater_than, bvugt)
DEF_BINARY_EXPR_BUILDER(unsigned_greater_equal, bvuge)
DEF_BINARY_EXPR_BUILDER(equal, eq)

DEF_BINARY_EXPR_BUILDER(and, bvand)
DEF_BINARY_EXPR_BUILDER(or, bvor)
DEF_BINARY_EXPR_BUILDER(bool_xor, xor)
DEF_BINARY_EXPR_BUILDER(xor, bvxor)

DEF_BINARY_EXPR_BUILDER(float_ordered_greater_than, fpa_gt)
DEF_BINARY_EXPR_BUILDER(float_ordered_greater_equal, fpa_geq)
DEF_BINARY_EXPR_BUILDER(float_ordered_less_than, fpa_lt)
DEF_BINARY_EXPR_BUILDER(float_ordered_less_equal, fpa_leq)
DEF_BINARY_EXPR_BUILDER(float_ordered_equal, fpa_eq)

#undef DEF_BINARY_EXPR_BUILDER

Z3_ast _sym_build_ite(Z3_ast cond, Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_ite\n";
  return a;
}

Z3_ast _sym_build_fp_add(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_fp_add\n";
  return a;
}

Z3_ast _sym_build_fp_sub(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_fp_sub\n";
  return a;
}

Z3_ast _sym_build_fp_mul(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_fp_mul\n";
  return a;
}

Z3_ast _sym_build_fp_div(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_fp_div\n";
  return a;
}

Z3_ast _sym_build_fp_rem(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_fp_rem\n";
  return a;
}

Z3_ast _sym_build_fp_abs(Z3_ast a) {
  //  std::cout << "mocked _sym_build_fp_abs\n";
  return a;
}

Z3_ast _sym_build_fp_neg(Z3_ast a) {
  //  std::cout << "mocked _sym_build_fp_neg\n";
  return a;
}

Z3_ast _sym_build_not(Z3_ast expr) {
  //  std::cout << "mocked _sym_build_not\n";
  return expr;
}

Z3_ast _sym_build_not_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_not_equal\n";
  return a;
}

Z3_ast _sym_build_bool_and(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_bool_and\n";
  return a;
}

Z3_ast _sym_build_bool_or(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_bool_or\n";
  return a;
}

Z3_ast _sym_build_float_ordered_not_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_ordered_not_equal\n";
  return a;
}

Z3_ast _sym_build_float_ordered(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_ordered\n";
  return a;
}

Z3_ast _sym_build_float_unordered(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered\n";
  return a;
}

Z3_ast _sym_build_float_unordered_greater_than(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_not_greater_than\n";
  return a;
}

Z3_ast _sym_build_float_unordered_greater_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_not_greater_equal\n";
  return a;
}

Z3_ast _sym_build_float_unordered_less_than(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_less_than\n";
  return a;
}

Z3_ast _sym_build_float_unordered_less_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_less_equal\n";
  return a;
}

Z3_ast _sym_build_float_unordered_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_not_equalt\n";
  return a;
}

Z3_ast _sym_build_float_unordered_not_equal(Z3_ast a, Z3_ast b) {
  //  std::cout << "mocked _sym_build_float_unordered_not_equalt\n";
  return a;
}

Z3_ast _sym_build_sext(Z3_ast expr, uint8_t bits) {
  //  std::cout << "mocked _sym_build_sext\n";
  return expr;
}

Z3_ast _sym_build_zext(Z3_ast expr, uint8_t bits) {
  //  std::cout << "mocked _sym_build_zext\n";
  return expr;
}

Z3_ast _sym_build_trunc(Z3_ast expr, uint8_t bits) {
  //  std::cout << "mocked _sym_build_trunc\n";
  return expr;
}

Z3_ast _sym_build_int_to_float(Z3_ast value, int is_double, int is_signed) {
  //  std::cout << "mocked _sym_build_int_to_float\n";
  return value;
}

Z3_ast _sym_build_float_to_float(Z3_ast expr, int to_double) {
  //  std::cout << "mocked _sym_build_float_to_float\n";
  return expr;
}

Z3_ast _sym_build_bits_to_float(Z3_ast expr, int to_double) {
  //  std::cout << "mocked _sym_build_bits_to_float\n";
  return expr;
}

Z3_ast _sym_build_float_to_bits(Z3_ast expr) {
  //  std::cout << "mocked _sym_build_float_to_bits\n";
  return expr;
}

Z3_ast _sym_build_float_to_signed_integer(Z3_ast expr, uint8_t bits) {
  //  std::cout << "mocked _sym_build_float_to_signed_integer\n";
  return expr;
}

Z3_ast _sym_build_float_to_unsigned_integer(Z3_ast expr, uint8_t bits) {
  //  std::cout << "mocked _sym_build_float_to_unsigned_integer\n";
  return expr;
}

Z3_ast _sym_build_bool_to_bit(Z3_ast expr) {
  //  std::cout << "mocked __sym_build_bool_to_bit\n";
  return expr;
}

void _sym_push_path_constraint(Z3_ast constraint, int taken,
                               uintptr_t site_id [[maybe_unused]]) {
  //  std::cout << "mocked __sym_push_path_constraint\n";
  return;
}

SymExpr _sym_concat_helper(SymExpr a, SymExpr b) {
  //  std::cout << "mocked __sym_concat_helper\n";
  return a;
}

SymExpr _sym_extract_helper(SymExpr expr, size_t first_bit, size_t last_bit) {
  //  std::cout << "mocked _sym_extract_helper\n";
  return expr;
}

size_t _sym_bits_helper(SymExpr expr) {
  //  std::cout << "mocked _sym_bits_helper\n";
  return 0;
}

/* No call-stack tracing */
void _sym_build_add() {
  return;
}

void _sym_build_bit_to_bool() {
  return;
}

void _sym_build_bool() {
  return;
}

void _sym_build_bool_to_bit() {
  return;
}

void _sym_build_bool_xor() {
  return;
}

void _sym_build_equal() {
  return;
}

void _sym_build_integer() {
  return;
}

void _sym_build_mul() {
  return;
}

void _sym_build_not_equal() {
  return;
}

void _sym_build_or() {
  return;
}

void _sym_build_sext() {
  return;
}

void _sym_build_signed_greater_equal() {
  return;
}

void _sym_build_signed_greater_than() {
  return;
}

void _sym_build_signed_less_than() {
  return;
}

void _sym_build_sub() {
  return;
}

void _sym_build_trunc() {
  return;
}

void _sym_build_unsigned_greater_equal() {
  return;
}

void _sym_build_unsigned_greater_than() {
  return;
}

void _sym_build_zext() {
  return;
}

void _sym_get_parameter_expression() {
  return;
}

void _sym_notify_basic_block() {
  return;
}

void _sym_notify_basic_block(uintptr_t) {
  return;
}

void _sym_notify_call() {
  return;
}

void _sym_notify_call(uintptr_t) {
  return;
}

void _sym_notify_ret() {
  return;
}

void _sym_notify_ret(uintptr_t) {
  return;
}

void _sym_push_path_constraint() {
  return;
}

void _sym_read_memory() {
  return;
}

void _sym_set_parameter_expression() {
  return;
}

void _sym_set_return_expression() {
  return;
}

void _sym_write_memory() {
  return;
}


/* Debugging */
// -> can do nothing
const char *_sym_expr_to_string(SymExpr expr) { return ""; }

bool _sym_feasible(SymExpr expr) { return true; }

/* Garbage collection */
void _sym_collect_garbage() {
  //  std::cout << "mocked _sym_collect_garbage\n";
  return;
}

/* Test-case handling */
