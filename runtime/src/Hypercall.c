#include "Hypercall.h"

static volatile int SYMCC_ON __attribute__((section(".data"))) = 0;

#define HYPERCALL_RAX_ID 0xFF
#define HYPERCALL_PT_64(_rbx, _rcx, _rdx, _rdi, _rsi) ({ \
    uint_t _rax = HYPERCALL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_rax) \
    : "b" (_rbx), "c" (_rcx), "d" (_rdx), "D" (_rdi), "S" (_rsi) \
    : "cc", "memory" \
    ); \
    _rax; \
})

#define HYPERCALL_PT_32(_ebx, _ecx, _edx, _edi, _esi) ({ \
    uint_t _eax = HYPERCALL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_eax) \
    : "b" (_ebx), "c" (_ecx), "d" (_edx), "D" (_edi), "S" (_esi) \
    : "cc", "memory" \
    ); \
    _eax; \
})

uint_t hypercall(uint_t type, uint_t var1, uint_t var2, uint_t var3, uint_t var4) {
    if(SYMCC_ON == 1) {
        if(is_64bit) 
            return HYPERCALL_PT_64(type, var1, var2, var3, var4); 
        return HYPERCALL_PT_32(type, var1, var2, var3, var4);
    }
    return 0;
}
