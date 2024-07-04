#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include "Runtime.h"

typedef void * Z3_ast;
typedef void * SymExpr;

#define HYPERCALL_KAFL_RAX_ID                0x01f
#define KAFL_HYPERCALL_PT(_rbx, _rcx, _rdx, _rsi) ({ \
    uint64_t _rax = HYPERCALL_KAFL_RAX_ID; \
    do{ \
    asm volatile( \
        "vmcall;" \
    : "+a" (_rax) \
    : "b" (_rbx), "c" (_rcx), "d" (_rdx), "S" (_rsi) \
    : "cc", "memory" \
    ); \
    } while(0); \
    _rax; \
})

static inline Z3_ast kAFL_hypercall(uint64_t rbx, ...) {
    va_list args;
    va_start(args, rbx);
    uint64_t rcx = va_arg(args, uint64_t);
    uint64_t rdx = va_arg(args, uint64_t);
    uint64_t rsi = va_arg(args, uint64_t);
    va_end(args);
    
    return (Z3_ast)(uintptr_t)KAFL_HYPERCALL_PT(rbx, rcx, rdx, rsi);
}

void _sym_initialize(void) {
    uint64_t value = 1;
    kAFL_hypercall(INITIALIZE);
    return;
}

Z3_ast _sym_build_integer(uint64_t value, uint8_t bits) {
    return kAFL_hypercall(BUILD_INTEGER, value, bits);
}

Z3_ast _sym_build_integer128(uint64_t high, uint64_t low) {
    return kAFL_hypercall(BUILD_INTEGER128, high, low);
}

Z3_ast _sym_build_float(double value, int is_double) {
    return kAFL_hypercall(BUILD_FLOAT, value, is_double);
}

Z3_ast _sym_get_input_byte(size_t offset, ...) {
    return kAFL_hypercall(GET_INPUT_BYTE, offset);
}

Z3_ast _sym_build_null_pointer(void)  {
    return kAFL_hypercall(BUILD_NULL_POINTER);
}
Z3_ast _sym_build_true(void)  {
    return kAFL_hypercall(BUILD_TRUE);
}
Z3_ast _sym_build_false(void)  {
    return kAFL_hypercall(BUILD_FALSE);
}

// in cpp it was bool
Z3_ast _sym_build_bool(uint64_t value)  {
    return kAFL_hypercall(BUILD_BOOL, value);
}


// TODO check
Z3_ast _sym_build_neg(Z3_ast expr) {
    return kAFL_hypercall(BUILD_NEG, (uint64_t)expr);
}

#define DEF_BINARY_EXPR_BUILDER(name, z3_name) \
    Z3_ast _sym_build_##name(Z3_ast a, Z3_ast b) { \
        return kAFL_hypercall(z3_name, (uint64_t)a, (uint64_t)b); \
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

Z3_ast _sym_build_ite(Z3_ast cond, Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_ITE, (uint64_t)cond, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_add(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_ADD, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_sub(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_SUB, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_mul(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_MUL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_div(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_DIV, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_rem(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FP_REM, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_fp_abs(Z3_ast a) {
	return kAFL_hypercall(BUILD_FP_ABS, (uint64_t)a);
}

Z3_ast _sym_build_fp_neg(Z3_ast a) {
	return kAFL_hypercall(BUILD_FP_NEG, (uint64_t)a);
}

Z3_ast _sym_build_not(Z3_ast expr) {
	return kAFL_hypercall(BUILD_NOT, (uint64_t)expr);
}

Z3_ast _sym_build_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_NOT_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_bool_and(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_BOOL_AND, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_bool_or(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_BOOL_OR, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_ordered_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_ORDERED_NOT_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_ordered(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_ORDERED, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_greater_than(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_THAN, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_greater_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_less_than(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_THAN, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_less_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_float_unordered_not_equal(Z3_ast a, Z3_ast b) {
	return kAFL_hypercall(BUILD_FLOAT_UNORDERED_NOT_EQUAL, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_build_sext(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_SEXT, (uint64_t)expr, bits);
}

Z3_ast _sym_build_zext(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_ZEXT, (uint64_t)expr, bits);
}

Z3_ast _sym_build_trunc(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_TRUNC, (uint64_t)expr, bits);
}

Z3_ast _sym_build_int_to_float(Z3_ast value, int is_double, int is_signed) {
	return kAFL_hypercall(BUILD_INT_TO_FLOAT, (uint64_t)value, is_double, is_signed);
}

Z3_ast _sym_build_float_to_float(Z3_ast expr, int to_double) {
	return kAFL_hypercall(BUILD_FLOAT_TO_FLOAT, (uint64_t)expr, to_double);
}

Z3_ast _sym_build_bits_to_float(Z3_ast expr, int to_double) {
	return kAFL_hypercall(BUILD_BITS_TO_FLOAT, (uint64_t)expr, to_double);
}

Z3_ast _sym_build_float_to_bits(Z3_ast expr) {
	return kAFL_hypercall(BUILD_FLOAT_TO_BITS, (uint64_t)expr);
}

Z3_ast _sym_build_float_to_signed_integer(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_FLOAT_TO_SIGNED_INTEGER, (uint64_t)expr, bits);
}

Z3_ast _sym_build_float_to_unsigned_integer(Z3_ast expr, uint8_t bits) {
	return kAFL_hypercall(BUILD_FLOAT_TO_UNSIGNED_INTEGER, (uint64_t)expr, bits);
}

Z3_ast _sym_build_bool_to_bit(Z3_ast expr) {
	return kAFL_hypercall(BUILD_BOOL_TO_BIT, (uint64_t)expr);
}

void _sym_push_path_constraint(Z3_ast constraint, int taken, uintptr_t size_id [[maybe_unused]]) {
    kAFL_hypercall(PUSH_PATH_CONSTRAINT, (uint64_t) constraint, taken, size_id);
}

Z3_ast _sym_concat_helper(SymExpr a, SymExpr b) {
	return kAFL_hypercall(CONCAT_HELPER, (uint64_t)a, (uint64_t)b);
}

Z3_ast _sym_extract_helper(SymExpr expr, size_t first_bit, size_t last_bit) {
	return kAFL_hypercall(EXTRACT_HELPER, (uint64_t) expr, first_bit);
}

size_t _sym_bits_helper(SymExpr expr) {
	return (size_t) kAFL_hypercall(BITS_HELPER, (uint64_t) expr);
}

void _sym_build_bit_to_bool() {
	kAFL_hypercall(BUILD_BIT_TO_BOOL);
}

// mocked stuff

/* Debugging */
const char *_sym_expr_to_string(SymExpr expr) { return ""; }

int _sym_feasible(SymExpr expr) { return 1; }

/* Garbage collection */
void _sym_collect_garbage() {
  return;
}


/* Test-case handling */
void symcc_set_test_case_handler(int handler) {
  // ignore
  return;
}


