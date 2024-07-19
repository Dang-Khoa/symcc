#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdio.h>
#include <sys/stat.h>
#include <z3.h>

#if defined(__ILP32__) || defined(_ILP32)
typedef uint32_t uint_t;
#else
typedef uint64_t uint_t;
#endif

typedef Z3_ast SymExpr;

// Type punning
extern union {
    uint_t uint;
    uint64_t u64;
    uint32_t u32;
    uint8_t u8;
    unsigned u;
    int i;
    double d;
    long l;
    bool b;
    size_t size;
    ssize_t ssize;
    uintptr_t uintptr;  
    mode_t mode;    
    char *str;
    const char *cstr;
    void *ptr; 
    const void *cptr; 
    uint8_t *u8ptr;
    const uint8_t *cu8ptr;
    FILE *fileptr;
    Z3_ast z3;
    SymExpr sym;
    SymExpr *symptr;
} pun;

#define HYPERCALL_KAFL_RAX_ID                0x01f
#define KAFL_HYPERCALL_PT(_rbx, _rcx, _rdx, _rdi, _rsi, _r8, _r9) ({ \
    uint_t _rax = HYPERCALL_KAFL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_rax) \
    : "b" (_rbx), "c" (_rcx), "d" (_rdx), "D" (_rdi), "S" (_rsi) \
    : "cc", "memory" \
    ); \
    _rax; \
})

static inline uint_t kAFL_hypercall(uint_t rbx, uint_t rcx, uint_t rdx, uint_t rdi, uint_t rsi, uint_t r8, uint_t r9) {
    return KAFL_HYPERCALL_PT(rbx, rcx, rdx, rdi, rsi, r8, r9);
}

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
    SYMCC_MAKE_SYMBOLIC,
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

#include <RuntimeCommon.h>

#endif
