#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(__ILP32__) || defined(_ILP32)
typedef uint32_t uint_t;
#else
typedef uint64_t uint_t;
#endif

typedef void* Z3_ast;
typedef void* SymExpr;

void _sym_initialize(void);

/*
 * Construction of simple values
 */
SymExpr _sym_build_integer(uint_t value, uint8_t bits);
SymExpr _sym_build_integer128(uint_t high, uint_t low);
SymExpr _sym_build_integer_from_buffer(void *buffer, unsigned num_bits);
SymExpr _sym_build_float(double value, int is_double);
SymExpr _sym_build_null_pointer(void);
SymExpr _sym_build_true(void);
SymExpr _sym_build_false(void);
SymExpr _sym_build_bool(bool value);

/*
 * Integer arithmetic and shifts
 */
SymExpr _sym_build_neg(SymExpr expr);
SymExpr _sym_build_add(SymExpr a, SymExpr b);
SymExpr _sym_build_sub(SymExpr a, SymExpr b);
SymExpr _sym_build_mul(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_div(SymExpr a, SymExpr b);
SymExpr _sym_build_signed_div(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_rem(SymExpr a, SymExpr b);
SymExpr _sym_build_signed_rem(SymExpr a, SymExpr b);
SymExpr _sym_build_shift_left(SymExpr a, SymExpr b);
SymExpr _sym_build_logical_shift_right(SymExpr a, SymExpr b);
SymExpr _sym_build_arithmetic_shift_right(SymExpr a, SymExpr b);
SymExpr _sym_build_funnel_shift_left(SymExpr a, SymExpr b, SymExpr c);
SymExpr _sym_build_funnel_shift_right(SymExpr a, SymExpr b, SymExpr c);
SymExpr _sym_build_abs(SymExpr expr);

/*
 * Arithmetic with overflow
 */
SymExpr _sym_build_add_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian);
SymExpr _sym_build_sub_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian);
SymExpr _sym_build_mul_overflow(SymExpr a, SymExpr b, bool is_signed,
                                bool little_endian);

/*
 * Saturating integer arithmetic and shifts
 */
SymExpr _sym_build_sadd_sat(SymExpr a, SymExpr b);
SymExpr _sym_build_uadd_sat(SymExpr a, SymExpr b);
SymExpr _sym_build_ssub_sat(SymExpr a, SymExpr b);
SymExpr _sym_build_usub_sat(SymExpr a, SymExpr b);
SymExpr _sym_build_sshl_sat(SymExpr a, SymExpr b);
SymExpr _sym_build_ushl_sat(SymExpr a, SymExpr b);

/*
 * Floating-point arithmetic and shifts
 */
SymExpr _sym_build_fp_add(SymExpr a, SymExpr b);
SymExpr _sym_build_fp_sub(SymExpr a, SymExpr b);
SymExpr _sym_build_fp_mul(SymExpr a, SymExpr b);
SymExpr _sym_build_fp_div(SymExpr a, SymExpr b);
SymExpr _sym_build_fp_rem(SymExpr a, SymExpr b);
SymExpr _sym_build_fp_abs(SymExpr a);
SymExpr _sym_build_fp_neg(SymExpr a);

/*
 * Boolean operations
 */
SymExpr _sym_build_not(SymExpr expr);
SymExpr _sym_build_signed_less_than(SymExpr a, SymExpr b);
SymExpr _sym_build_signed_less_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_signed_greater_than(SymExpr a, SymExpr b);
SymExpr _sym_build_signed_greater_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_less_than(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_less_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_greater_than(SymExpr a, SymExpr b);
SymExpr _sym_build_unsigned_greater_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_not_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_bool_and(SymExpr a, SymExpr b);
SymExpr _sym_build_and(SymExpr a, SymExpr b);
SymExpr _sym_build_bool_or(SymExpr a, SymExpr b);
SymExpr _sym_build_or(SymExpr a, SymExpr b);
SymExpr _sym_build_bool_xor(SymExpr a, SymExpr b);
SymExpr _sym_build_xor(SymExpr a, SymExpr b);
SymExpr _sym_build_ite(SymExpr cond, SymExpr a, SymExpr b);

SymExpr _sym_build_float_ordered_greater_than(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered_greater_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered_less_than(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered_less_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered_not_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_ordered(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_greater_than(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_greater_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_less_than(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_less_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_equal(SymExpr a, SymExpr b);
SymExpr _sym_build_float_unordered_not_equal(SymExpr a, SymExpr b);

/*
 * Casts
 */
SymExpr _sym_build_sext(SymExpr expr, uint8_t bits);
SymExpr _sym_build_zext(SymExpr expr, uint8_t bits);
SymExpr _sym_build_trunc(SymExpr expr, uint8_t bits);
SymExpr _sym_build_bswap(SymExpr expr);
SymExpr _sym_build_int_to_float(SymExpr value, int is_double, int is_signed);
SymExpr _sym_build_float_to_float(SymExpr expr, int to_double);
SymExpr _sym_build_bits_to_float(SymExpr expr, int to_double);
SymExpr _sym_build_float_to_bits(SymExpr expr);
SymExpr _sym_build_float_to_signed_integer(SymExpr expr, uint8_t bits);
SymExpr _sym_build_float_to_unsigned_integer(SymExpr expr, uint8_t bits);
SymExpr _sym_build_bool_to_bit(SymExpr expr);
SymExpr _sym_build_bit_to_bool(SymExpr expr);

/*
 * Bit-array helpers
 */
SymExpr _sym_concat_helper(SymExpr a, SymExpr b);
SymExpr _sym_extract_helper(SymExpr expr, size_t first_bit, size_t last_bit);
size_t _sym_bits_helper(SymExpr expr);

/*
 * Function-call helpers
 */
void _sym_set_parameter_expression(uint8_t index, SymExpr expr);
SymExpr _sym_get_parameter_expression(uint8_t index);
void _sym_set_return_expression(SymExpr expr);
SymExpr _sym_get_return_expression(void);

/*
 * Constraint handling
 */
void _sym_push_path_constraint(SymExpr constraint, int taken,
                               uintptr_t site_id);
SymExpr _sym_get_input_byte(size_t offset, uint8_t concrete_value);
void _sym_make_symbolic(const void *data, size_t byte_length,
                        size_t input_offset);

/*
 * Memory management
 */
SymExpr _sym_read_memory(uint8_t *addr, size_t length, bool little_endian);
void _sym_write_memory(uint8_t *addr, size_t length, SymExpr expr,
                       bool little_endian);
void _sym_memcpy(uint8_t *dest, const uint8_t *src, size_t length);
void _sym_memset(uint8_t *memory, SymExpr value, size_t length);
void _sym_memmove(uint8_t *dest, const uint8_t *src, size_t length);
SymExpr _sym_build_zero_bytes(size_t length);
SymExpr _sym_build_insert(SymExpr target, SymExpr to_insert, uint_t offset,
                          bool little_endian);
SymExpr _sym_build_extract(SymExpr expr, uint_t offset, uint_t length,
                           bool little_endian);

/*
 * Call-stack tracing
 */
void _sym_notify_call(uintptr_t site_id);
void _sym_notify_ret(uintptr_t site_id);
void _sym_notify_basic_block(uintptr_t site_id);

/*
 * Debugging
 */
const char *_sym_expr_to_string(SymExpr expr); // statically allocated
bool _sym_feasible(SymExpr expr);

/*
 * Garbage collection
 */
void _sym_register_expression_region(SymExpr *start, size_t length);
void _sym_collect_garbage(void);

/*
 * User-facing functionality
 *
 * These are the only functions in the interface that we expect to be called by
 * users (i.e., calls to it aren't auto-generated by our compiler pass).
 */
void symcc_make_symbolic(const void *start, size_t byte_length);
typedef void (*TestCaseHandler)(const void *, size_t);
void symcc_set_test_case_handler(TestCaseHandler handler);

enum Sym {
    INITIALIZE = 1,
    BUILD_INTEGER,
    BUILD_INTEGER128,
    BUILD_INTEGER_FROM_BUFFER,
    BUILD_FLOAT,
    GET_INPUT_BYTE,
    BUILD_NULL_POINTER,
    BUILD_TRUE,
    BUILD_FALSE,
    BUILD_BOOL,
    BUILD_NEG,
    BUILD_ADD,
    BUILD_SUB,
    BUILD_MUL,
    BUILD_UNSIGNED_DIV,
    BUILD_SIGNED_DIV,
    BUILD_UNSIGNED_REM,
    BUILD_SIGNED_REM,
    BUILD_SHIFT_LEFT,
    BUILD_LOGICAL_SHIFT_RIGHT,
    BUILD_ARITHMETIC_SHIFT_RIGHT,
    BUILD_SIGNED_LESS_THAN,
    BUILD_SIGNED_LESS_EQUAL,
    BUILD_SIGNED_GREATER_THAN,
    BUILD_SIGNED_GREATER_EQUAL,
    BUILD_UNSIGNED_LESS_THAN,
    BUILD_UNSIGNED_LESS_EQUAL,
    BUILD_UNSIGNED_GREATER_THAN,
    BUILD_UNSIGNED_GREATER_EQUAL,
    BUILD_EQUAL,
    BUILD_AND,
    BUILD_OR,
    BUILD_BOOL_XOR,
    BUILD_XOR,
    BUILD_FLOAT_ORDERED_GREATER_THAN,
    BUILD_FLOAT_ORDERED_GREATER_EQUAL,
    BUILD_FLOAT_ORDERED_LESS_THAN,
    BUILD_FLOAT_ORDERED_LESS_EQUAL,
    BUILD_FLOAT_ORDERED_EQUAL,
    BUILD_ITE,
    BUILD_FP_ADD,
    BUILD_FP_SUB,
    BUILD_FP_MUL,
    BUILD_FP_DIV,
    BUILD_FP_REM,
    BUILD_FP_ABS,
    BUILD_FP_NEG,
    BUILD_NOT,
    BUILD_NOT_EQUAL,
    BUILD_BOOL_AND,
    BUILD_BOOL_OR,
    BUILD_FLOAT_ORDERED_NOT_EQUAL,
    BUILD_FLOAT_ORDERED,
    BUILD_FLOAT_UNORDERED,
    BUILD_FLOAT_UNORDERED_GREATER_THAN,
    BUILD_FLOAT_UNORDERED_GREATER_EQUAL,
    BUILD_FLOAT_UNORDERED_LESS_THAN,
    BUILD_FLOAT_UNORDERED_LESS_EQUAL,
    BUILD_FLOAT_UNORDERED_EQUAL,
BUILD_FLOAT_UNORDERED_NOT_EQUAL,
    BUILD_SEXT,
    BUILD_ZEXT,
    BUILD_TRUNC,
    BUILD_INT_TO_FLOAT,
    BUILD_FLOAT_TO_FLOAT,
    BUILD_BITS_TO_FLOAT,
    BUILD_FLOAT_TO_BITS,
    BUILD_FLOAT_TO_SIGNED_INTEGER,
    BUILD_FLOAT_TO_UNSIGNED_INTEGER,
    BUILD_BOOL_TO_BIT,
    PUSH_PATH_CONSTRAINT,
    CONCAT_HELPER,
    EXTRACT_HELPER,
    BITS_HELPER,
    NOTIFY_CALL,
    NOTIFY_RET,
    NOTIFY_BASIC_BLOCK,
    EXPR_TO_STRING,
    FEASIBLE,
    COLLECT_GARBAGE,
    BUILD_BIT_TO_BOOL,
    SET_RETURN_EXPRESSION,
    GET_RETURN_EXPRESSION,
    SET_PARAMETER_EXPRESSION,
    GET_PARAMETER_EXPRESSION,
    READ_MEMORY,
    WRITE_MEMORY,
    BUILD_EXTRACT,
    BUILD_BSWAP,
    BUILD_INSERT,
    BUILD_ZERO_BYTES,
    BUILD_SADD_SAT,
    BUILD_UADD_SAT,
    BUILD_SSUB_SAT,
    BUILD_USUB_SAT,
    BUILD_SHIFT_LEFT_OVERFLOW,
    BUILD_SSHL_SAT,
    BUILD_USHL_SAT,
    BUILD_ADD_OVERFLOW,
    BUILD_SUB_OVERFLOW,
    BUILD_MUL_OVERFLOW,
    BUILD_FUNNEL_SHIFT_LEFT,
    BUILD_FUNNEL_SHIFT_RIGHT,
    BUILD_ABS,
    REGISTER_EXPRESSION_REGION,
    MAKE_SYMBOLIC,
    MALLOC,
    CALLOC,
    MMAP,
    MMAP64,
    OPEN,
    READ,
    LSEEK,
    LSEEK64,
    FOPEN,
    FOPEN64,
    FREAD,
    FSEEK,
    FSEEKO,
    REWIND,
    FSEEKO64,
    GETC,
    UNGETC,
    MEMCPY,
    MEMSET,
    STRNCPY,
    STRCHR,
    MEMCMP,
    MEMMOVE,
    NTOHL,
    FGETS,
    FGETC,
    GETCHAR,
    BCOPY,
    BCMP,
    BZERO,
};

#endif
