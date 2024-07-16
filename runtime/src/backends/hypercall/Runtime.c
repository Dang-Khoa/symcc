#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>

#include "Runtime.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif



#define HYPERCALL_KAFL_RAX_ID                0x01f
#define KAFL_HYPERCALL_PT(_rbx, _rcx, _rdx, _rsi, _rdi, _r8, _r9) ({ \
    uint_t _rax = HYPERCALL_KAFL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_rax) \
    : "b" ((uint64_t) (_rbx)), "c" ((uint64_t)(_rcx)), "d" ((uint64_t)(_rdx)), "D" ((uint64_t)(_rdi)), "S" ((uint64_t)(_rsi)), "r" ((uint64_t)(_r8)), "r" ((uint64_t)(_r9)) \
    : "cc", "memory" \
    ); \
    _rax; \
})

static inline Z3_ast kAFL_hypercall(uint_t rbx, uint_t rcx, uint_t rd, uint_t rsi, uint_t rdi, uint_t r8, uint_t r9) {
    return (Z3_ast)rbx;
}

void _sym_initialize(void) {
    kAFL_hypercall(INITIALIZE, 0, 0, 0, 0, 0, 0);
    return;
}

Z3_ast _sym_build_integer(uint_t value, uint8_t bits) {
    return kAFL_hypercall(BUILD_INTEGER, value, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_integer128(uint_t high, uint_t low) {
    return kAFL_hypercall(BUILD_INTEGER128, high, low, 0, 0, 0, 0);
}

SymExpr _sym_build_integer_from_buffer(void *buffer, unsigned num_bits) {
    return kAFL_hypercall(BUILD_INTEGER_FROM_BUFFER, (uint_t) buffer, (uint_t) num_bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_float(double value, int is_double) {
    return kAFL_hypercall(BUILD_FLOAT, (uint_t) value, (uint_t) is_double, 0, 0, 0, 0);
}

Z3_ast _sym_get_input_byte(size_t offset,  uint8_t concrete_value){
    return kAFL_hypercall(GET_INPUT_BYTE, offset, (uint_t) concrete_value, 0, 0, 0, 0);
}

Z3_ast _sym_build_null_pointer(void)  {
    return kAFL_hypercall(BUILD_NULL_POINTER, 0, 0, 0, 0, 0, 0);
}
Z3_ast _sym_build_true(void)  {
    return kAFL_hypercall(BUILD_TRUE, 0, 0, 0, 0, 0, 0);
}
Z3_ast _sym_build_false(void)  {
    return kAFL_hypercall(BUILD_FALSE, 0, 0, 0, 0, 0, 0);
}

// in cpp it was bool
Z3_ast _sym_build_bool(bool value)  {
    return kAFL_hypercall(BUILD_BOOL, (uint_t) value, 0, 0, 0, 0, 0);
}


// TODO check
Z3_ast _sym_build_neg(Z3_ast expr) {
    return kAFL_hypercall(BUILD_NEG, (uint_t) expr, 0, 0, 0, 0, 0);
}

#define DEF_BINARY_EXPR_BUILDER(name, z3_name) \
    Z3_ast _sym_build_##name(Z3_ast a, Z3_ast b) { \
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

Z3_ast _sym_build_ite(Z3_ast cond, Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_ITE, (uint_t)cond, (uint_t)a, (uint_t)b, 0, 0, 0);
}

Z3_ast _sym_build_fp_add(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FP_ADD, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_sub(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FP_SUB, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_mul(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FP_MUL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_div(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FP_DIV, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_rem(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FP_REM, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_abs(Z3_ast a) {
        return kAFL_hypercall(BUILD_FP_ABS, (uint_t)a, 0, 0, 0, 0, 0);
}

Z3_ast _sym_build_fp_neg(Z3_ast a) {
        return kAFL_hypercall(BUILD_FP_NEG, (uint_t)a, 0, 0, 0, 0, 0);
}

Z3_ast _sym_build_not(Z3_ast expr) {
        return kAFL_hypercall(BUILD_NOT, (uint_t)expr, 0, 0, 0, 0, 0);
}

Z3_ast _sym_build_not_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_bool_and(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_BOOL_AND, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_bool_or(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_BOOL_OR, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_ordered_not_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_ORDERED_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_ordered(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_ORDERED, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_greater_than(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_THAN, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_greater_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_GREATER_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_less_than(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_THAN, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_less_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_LESS_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_unordered_not_equal(Z3_ast a, Z3_ast b) {
        return kAFL_hypercall(BUILD_FLOAT_UNORDERED_NOT_EQUAL, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_build_sext(Z3_ast expr, uint8_t bits) {
        return kAFL_hypercall(BUILD_SEXT, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_zext(Z3_ast expr, uint8_t bits) {
        return kAFL_hypercall(BUILD_ZEXT, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_trunc(Z3_ast expr, uint8_t bits) {
        return kAFL_hypercall(BUILD_TRUNC, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_int_to_float(Z3_ast value, int is_double, int is_signed) {
        return kAFL_hypercall(BUILD_INT_TO_FLOAT, (uint_t)value, (uint_t) is_double, (uint_t) is_signed, 0, 0, 0);
}

Z3_ast _sym_build_float_to_float(Z3_ast expr, int to_double) {
        return kAFL_hypercall(BUILD_FLOAT_TO_FLOAT, (uint_t)expr, (uint_t) to_double, 0, 0, 0, 0);
}

Z3_ast _sym_build_bits_to_float(Z3_ast expr, int to_double) {
        return kAFL_hypercall(BUILD_BITS_TO_FLOAT, (uint_t)expr, (uint_t) to_double, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_to_bits(Z3_ast expr) {
        return kAFL_hypercall(BUILD_FLOAT_TO_BITS, (uint_t)expr, 0, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_to_signed_integer(Z3_ast expr, uint8_t bits) {
        return kAFL_hypercall(BUILD_FLOAT_TO_SIGNED_INTEGER, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_float_to_unsigned_integer(Z3_ast expr, uint8_t bits) {
        return kAFL_hypercall(BUILD_FLOAT_TO_UNSIGNED_INTEGER, (uint_t)expr, (uint_t) bits, 0, 0, 0, 0);
}

Z3_ast _sym_build_bool_to_bit(Z3_ast expr) {
        return kAFL_hypercall(BUILD_BOOL_TO_BIT, (uint_t)expr, 0, 0, 0, 0, 0);
}

void _sym_push_path_constraint(Z3_ast constraint, int taken, uintptr_t size_id [[maybe_unused]]) {
    kAFL_hypercall(PUSH_PATH_CONSTRAINT, (uint_t) constraint, (uint_t) taken, (uint_t) size_id, 0, 0, 0);
}

Z3_ast _sym_concat_helper(SymExpr a, SymExpr b) {
        return kAFL_hypercall(CONCAT_HELPER, (uint_t)a, (uint_t)b, 0, 0, 0, 0);
}

Z3_ast _sym_extract_helper(SymExpr expr, size_t first_bit, size_t last_bit) {
        return kAFL_hypercall(EXTRACT_HELPER, (uint_t) expr, (uint_t) first_bit, (uint_t) last_bit, 0, 0, 0);
}

size_t _sym_bits_helper(SymExpr expr) {
        return (size_t) kAFL_hypercall(BITS_HELPER, (uint_t) expr, 0, 0, 0, 0, 0);
}

/* No call-stack tracing */
void _sym_notify_call(uintptr_t) {}
void _sym_notify_ret(uintptr_t) {}
void _sym_notify_basic_block(uintptr_t) {}

// RuntimeCommon stuff
void _sym_set_return_expression(SymExpr expr1) {
        kAFL_hypercall(SET_RETURN_EXPRESSION, (uint_t) expr1, 0, 0, 0, 0, 0);
}
SymExpr _sym_get_return_expression(void) {
        return kAFL_hypercall(GET_RETURN_EXPRESSION, 0, 0, 0, 0, 0, 0);
}
void _sym_set_parameter_expression(uint8_t index, SymExpr expr1) {
        kAFL_hypercall(SET_PARAMETER_EXPRESSION, (uint_t) index, (uint_t) expr1, 0, 0, 0, 0);
}
SymExpr _sym_get_parameter_expression(uint8_t index1) {
        return kAFL_hypercall(GET_PARAMETER_EXPRESSION, (uint_t) index1, 0, 0, 0, 0, 0);
}
void _sym_memcpy(uint8_t *dest, const uint8_t *src, size_t length1) {
        kAFL_hypercall(MEMCPY, (uint_t)dest, (uint_t)src, length1, 0, 0, 0);
}
void _sym_memset(uint8_t *memory, SymExpr value, size_t length1) {
        kAFL_hypercall(MEMSET, (uint_t)memory, (uint_t)value, length1, 0, 0, 0);
}
void _sym_memmove(uint8_t *dest, const uint8_t *src, size_t length1) {
        kAFL_hypercall(MEMMOVE, (uint_t)src, length1, (uint_t) dest, 0, 0, 0);
}
SymExpr _sym_read_memory(uint8_t *addr, size_t length, bool little_endian1) {
        return kAFL_hypercall(READ_MEMORY, (uint_t)addr, (uint_t) length, (uint_t) little_endian1, 0, 0, 0);
}
//TODO: 5th par
void _sym_write_memory(uint8_t *addr, size_t length, SymExpr expr, bool little_endian1) {
        kAFL_hypercall(WRITE_MEMORY, (uint_t)addr, (uint_t) length, (uint_t) expr, (uint_t) little_endian1, 0, 0);
}
SymExpr _sym_build_extract(SymExpr expr, uint_t offset, uint_t length, bool little_endian1) {
        return kAFL_hypercall(BUILD_EXTRACT, offset, length, (uint_t) little_endian1, 0, 0, 0);
}
SymExpr _sym_build_bswap(SymExpr expr1) {
        return kAFL_hypercall(BUILD_BSWAP, (uint_t) expr1, 0, 0, 0, 0, 0);
}
//TODO: 5th parameter
SymExpr _sym_build_insert(SymExpr target, SymExpr to_insert, uint_t offset, bool little_endian1) {
        return kAFL_hypercall(BUILD_INSERT, (uint_t) target, (uint_t) to_insert, offset, (uint_t) little_endian1, 0, 0);
}
SymExpr _sym_build_zero_bytes(size_t length1) {
        return kAFL_hypercall(BUILD_ZERO_BYTES, (uint_t) length1, 0, 0, 0, 0, 0);
}
SymExpr _sym_build_sadd_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_SADD_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
SymExpr _sym_build_uadd_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_UADD_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
SymExpr _sym_build_ssub_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_SSUB_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
SymExpr _sym_build_usub_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_USUB_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
static SymExpr _sym_build_shift_left_overflow(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_SHIFT_LEFT_OVERFLOW, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
SymExpr _sym_build_sshl_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_SSHL_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
SymExpr _sym_build_ushl_sat(SymExpr a, SymExpr b1) {
        return kAFL_hypercall(BUILD_USHL_SAT, (uint_t)a, (uint_t)b1, 0, 0, 0, 0);
}
//TODO 5th parameter for next 3
SymExpr _sym_build_add_overflow(SymExpr a, SymExpr b, bool is_signed, bool little_endian1) {
        return kAFL_hypercall(BUILD_ADD_OVERFLOW, (uint_t)a, (uint_t)b, (uint_t) is_signed, (uint_t) little_endian1, 0, 0);
}
SymExpr _sym_build_sub_overflow(SymExpr a, SymExpr b, bool is_signed, bool little_endian1) {
        return kAFL_hypercall(BUILD_SUB_OVERFLOW, (uint_t)a, (uint_t)b, (uint_t) is_signed, (uint_t) little_endian1, 0, 0);
}
SymExpr _sym_build_mul_overflow(SymExpr a, SymExpr b, bool is_signed, bool little_endian1) {
        return kAFL_hypercall(BUILD_MUL_OVERFLOW, (uint_t)a, (uint_t)b, (uint_t) is_signed, (uint_t) little_endian1, 0, 0);
}
SymExpr _sym_build_funnel_shift_left(SymExpr a, SymExpr b, SymExpr c1) {
        return kAFL_hypercall(BUILD_FUNNEL_SHIFT_LEFT, (uint_t)a, (uint_t)b, (uint_t)c1, 0, 0, 0);
}
SymExpr _sym_build_funnel_shift_right(SymExpr a, SymExpr b, SymExpr c1) {
        return kAFL_hypercall(BUILD_FUNNEL_SHIFT_RIGHT, (uint_t)a, (uint_t)b, (uint_t)c1, 0, 0, 0);
}
SymExpr _sym_build_abs(SymExpr expr1) {
        return kAFL_hypercall(BUILD_ABS, (uint_t)expr1, 0, 0, 0, 0, 0);
}
void _sym_register_expression_region(SymExpr *start, size_t length1) {
        kAFL_hypercall(REGISTER_EXPRESSION_REGION, (uint_t)start, length1, 0, 0, 0, 0);
}
void _sym_make_symbolic(const void *data, size_t byte_length, size_t input_offset) {
        kAFL_hypercall(MAKE_SYMBOLIC, (uint_t)data, byte_length, input_offset, 0, 0, 0);
}
SymExpr _sym_build_bit_to_bool(SymExpr expr1) {
        return kAFL_hypercall(BUILD_BIT_TO_BOOL, (uint_t)expr1, 0, 0, 0, 0, 0);
}


// TODO: implement libcWrapper hypercalls
// for now: mocks
void *malloc_symbolized(size_t size) {
        return kAFL_hypercall(MALLOC, (uint_t) size, 0, 0, 0, 0, 0);
}
void *calloc_symbolized(size_t nmemb, size_t size) {
        return kAFL_hypercall(CALLOC, (uint_t) nmemb, (uint_t) size, 0, 0, 0, 0);
}
void *mmap64_symbolized(void *addr, size_t len, int prot, int flags, int fildes, uint_t off) {
        return kAFL_hypercall(MMAP64, (uint_t) len, (uint_t) prot, (uint_t) flags, (uint_t) fildes, off, 0);
}
void *mmap_symbolized(void *addr, size_t len, int prot, int flags, int fildes, uint_t off) {
        return kAFL_hypercall(MMAP, (uint_t) addr, (uint_t) len, (uint_t) prot, (uint_t) flags, (uint_t) fildes, off);
}
int open_symbolized(const char *path, int oflag, mode_t mode) {
        return (int)kAFL_hypercall(OPEN, (uint_t) path, (uint_t) oflag, (uint_t) mode, 0, 0, 0);
}
ssize_t read_symbolized(int fildes, void *buf, size_t nbyte) {
        return (ssize_t)kAFL_hypercall(READ, (uint_t) fildes, (uint_t) buf, (uint_t) nbyte, 0, 0, 0);
}
uint_t lseek64_symbolized(int fd, uint_t offset, int whence) {
        return (uint_t)kAFL_hypercall(LSEEK64, (uint_t) fd, offset, (uint_t) whence, 0, 0, 0);
}
uint_t lseek_symbolized(int fd, uint_t offset, int whence) {
        return (uint_t)kAFL_hypercall(LSEEK, (uint_t) fd, offset, (uint_t) whence, 0, 0, 0);
}
FILE *fopen_symbolized(const char *pathname, const char *mode) {
        return (FILE*)kAFL_hypercall(FOPEN, (uint_t) pathname, (uint_t) mode, 0, 0, 0, 0);
}
FILE *fopen64_symbolized(const char *pathname, const char *mode) {
        return (FILE*)kAFL_hypercall(FOPEN64, (uint_t) pathname, (uint_t) mode, 0, 0, 0, 0);
}
size_t fread_symbolized(void *ptr, size_t size, size_t nmemb, FILE *stream) {
        return (size_t)kAFL_hypercall(FREAD, (uint_t) ptr, (uint_t) size, (uint_t) nmemb, (uint_t) stream, 0, 0);
}
char *fgets_symbolized(char *str, int n, FILE *stream) {
        return (char*)kAFL_hypercall(FGETS, (uint_t) str, (uint_t) n, (uint_t) stream, 0, 0, 0);
}
void rewind_symbolized(FILE *stream) {
        kAFL_hypercall(REWIND, (uint_t) stream, 0, 0, 0, 0, 0);
}
int fseek_symbolized(FILE *stream, long offset, int whence) {
        return (int)kAFL_hypercall(FSEEK, (uint_t) stream, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}
int fseeko_symbolized(FILE *stream, off_t offset, int whence) {
        return (int)kAFL_hypercall(FSEEKO, (uint_t) stream, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}
int fseeko64_symbolized(FILE *stream, uint_t offset, int whence) {
        return (int)kAFL_hypercall(FSEEKO64, (uint_t) stream, offset, (uint_t) whence, 0, 0, 0);
}
int getc_symbolized(FILE *stream) {
        return (int)kAFL_hypercall(GETC, (uint_t) stream, 0, 0, 0, 0, 0);
}
int fgetc_symbolized(FILE *stream) {
        return (int)kAFL_hypercall(FGETC, (uint_t) stream, 0, 0, 0, 0, 0);
}
int getchar_symbolized(void) {
        return (int)kAFL_hypercall(GETCHAR, 0, 0, 0, 0, 0, 0);
}
int ungetc_symbolized(int c, FILE *stream) {
        return (int)kAFL_hypercall(UNGETC, (uint_t) c, (uint_t) stream, 0, 0, 0, 0);
}
void *memcpy_symbolized(void *dest, const void *src, size_t n) {
        return kAFL_hypercall(MEMCPY, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}
void *memset_symbolized(void *s, int c, size_t n) {
        return kAFL_hypercall(MEMSET, (uint_t)s, (uint_t)c, (uint_t)n, 0, 0, 0);
}
void bzero_symbolized(void *s, size_t n) {
        kAFL_hypercall(BZERO, (uint_t)s, (uint_t)n, 0, 0, 0, 0);
}
void *memmove_symbolized(void *dest, const void *src, size_t n) {
        return kAFL_hypercall(MEMMOVE, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}
void bcopy_symbolized(const void *src, void *dest, size_t n) {
        kAFL_hypercall(BCOPY, (uint_t) src, (uint_t) dest, (uint_t) n, 0, 0, 0);
        return;
}
char *strncpy_symbolized(char *dest, const char *src, size_t n) {
        return (char*)kAFL_hypercall(STRNCPY, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}
const char *strchr_symbolized(const char *s, int c) {
        return (char*)kAFL_hypercall(STRCHR, (uint_t) s, (uint_t) c, 0, 0, 0, 0);
}
int memcmp_symbolized(const void *a, const void *b, size_t n) {
        return (int)kAFL_hypercall(MEMCMP, (uint_t) a, (uint_t) b, (uint_t) n, 0, 0, 0);
}
int bcmp_symbolized(const void *a, const void *b, size_t n) {
        return (int)kAFL_hypercall(BCMP, (uint_t) a, (uint_t) b, (uint_t) n, 0, 0, 0);
}
uint_t ntohl_symbolized(uint_t netlong) {
        return (uint_t)kAFL_hypercall(NTOHL, (uint_t) netlong, 0, 0, 0, 0, 0);
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


