#include "Hypercall.h"

#define HYPERCALL_KAFL_RAX_ID                0x01f
#define KAFL_HYPERCALL_PT(_rbx, _rcx, _rdx, _rdi, _rsi, _r8, _r9) ({ \
    uint_t _rax = HYPERCALL_KAFL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_rax) \
    : "b" (_rbx), "c" (_rcx), "d" (_rdx), "D" (_rdi), "S" (_rsi), "m" (_r8), "m" (_r9) \
    : "cc", "memory" \
    ); \
    _rax; \
})

uint_t kAFL_hypercall(uint_t rbx, uint_t rcx, uint_t rdx, uint_t rdi, uint_t rsi, uint_t r8, uint_t r9) {
    return KAFL_HYPERCALL_PT(rbx, rcx, rdx, rdi, rsi, r8, r9);
}
