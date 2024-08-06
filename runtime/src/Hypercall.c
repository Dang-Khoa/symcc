#include "Hypercall.h"

#define HYPERCALL_KAFL_RAX_ID                0x01f
#define KAFL_HYPERCALL_PT_64(_rbx, _rcx, _rdx, _rdi, _rsi, _r8, _r9, _r10) ({ \
    uint_t _rax = HYPERCALL_KAFL_RAX_ID; \
    asm volatile( \
        "vmmcall;" \
    : "+a" (_rax) \
    : "b" (_rbx), "c" (_rcx), "d" (_rdx), "D" (_rdi), "S" (_rsi), "r" (_r8), "r" (_r9), "r" (_r10) \
    : "cc", "memory" \
    ); \
    _rax; \
})

#define KAFL_HYPERCALL_PT_32(_ebx, _ecx, _edx, _edi, _esi, _param6, _param7, _param8) ({ \
    uint_t _eax = HYPERCALL_KAFL_RAX_ID; \
    asm volatile ( \
        "push %[param8]\n\t" \
        "push %[param7]\n\t" \
        "push %[param6]\n\t" \
        "vmmcall\n\t" \
        "add $12, %%esp\n\t" \
        : "+a" (_eax) \
        : "b" (_ebx), "c" (_ecx), "d" (_edx), "D" (_edi), "S" (_esi), [param6] "m" (_param6), [param7] "m" (_param7), [param8] "m" (_param8) \
        : "cc", "memory" \
    ); \
    _eax; \
})

uint_t kAFL_hypercall(uint_t type, uint_t var1, uint_t var2, uint_t var3, uint_t var4, uint_t var5, uint_t var6, uint_t var7) {
    if(is_64bit)
        return KAFL_HYPERCALL_PT_64(type, var1, var2, var3, var4, var5, var6, var7);
    else
        return KAFL_HYPERCALL_PT_32(type, var1, var2, var3, var4, var5, var6, var7); 
    return 0;
}
