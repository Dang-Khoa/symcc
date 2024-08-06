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

//
// Libc wrappers
//
// This file contains the wrappers around libc functions which add symbolic
// computations; using the wrappers frees instrumented code from having to link
// against an instrumented libc.
//
// We define a wrapper for function X with SYM(X), which just changes the name
// "X" to something predictable and hopefully unique. It is then up to the
// compiler pass to replace calls of X with calls of SYM(X).
//
// In general, the wrappers ask the solver to generate alternative parameter
// values, then call the wrapped function, create and store symbolic expressions
// matching the libc function's semantics, and finally return the wrapped
// function's result.
#define _LARGEFILE64_SOURCE
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <arpa/inet.h>

#include <Runtime.h>
#include <Hypercall.h>

#define SYM(x) x##_symbolized

static pun_t pun;

void *SYM(malloc)(size_t size) {
    void *result = malloc(size);
	
    pun.ptr = malloc(size);
    uint_t rcx = pun.uint;
    pun.size = size;
    uint_t rdx = pun.uint;
    kAFL_hypercall(MALLOC, rcx, rdx, 0, 0, 0, 0, 0);

    return result;
}

void *SYM(calloc)(size_t nmemb, size_t size) {
    void *result = calloc(nmemb, size);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.size = nmemb;
    uint_t rdx = pun.uint;
    pun.size = size;
    uint_t rdi = pun.uint;
    kAFL_hypercall(CALLOC, rcx, rdx, rdi, 0, 0, 0, 0);

    return result;
}

void *SYM(mmap64)(void *addr, size_t len, int prot, int flags, int fildes,
                  uint64_t off) {
    void *result = mmap64(addr, len, prot, flags, fildes, off);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.ptr = addr;
    uint_t rdx = pun.uint;
    pun.size = len;
    uint_t rdi = pun.uint;
    pun.i = prot;
    uint_t rsi = pun.uint;
    pun.i = flags;
    uint_t r8 = pun.uint;
    pun.i = fildes;
    uint_t r9 = pun.uint;
    pun.u64 = off;
    uint_t r10 = pun.uint;
    kAFL_hypercall(MMAP64, rcx, rdx, rdi, rsi, r8, r9, r10);

    return result;
}

void *SYM(mmap)(void *addr, size_t len, int prot, int flags, int fildes,
                uint32_t off) {
    return SYM(mmap64)(addr, len, prot, flags, fildes, off);
}

int SYM(open)(const char *path, int oflag, mode_t mode) {
    int result = open(path, oflag, mode);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.cstr = path;
    uint_t rdx = pun.uint;
    pun.i = oflag;
    uint_t rdi = pun.uint;
    pun.mode = mode;
    uint_t rsi = pun.uint;
    kAFL_hypercall(OPEN, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

ssize_t SYM(read)(int fildes, void *buf, size_t nbyte) {
    ssize_t result = read(fildes, buf, nbyte);
	
	pun.ssize = result;
	uint_t rcx = pun.uint;
    pun.i = fildes;
    uint_t rdx = pun.uint;
    pun.ptr = buf;
    uint_t rdi = pun.uint;
    pun.size = nbyte;
    uint_t rsi = pun.uint;
    kAFL_hypercall(READ, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

uint64_t SYM(lseek64)(int fd, uint64_t offset, int whence) {
    uint64_t result = lseek64(fd, offset, whence);
	
	pun.uint = result;
	uint_t rcx = pun.uint;
    pun.i = fd;
    uint_t rdx = pun.uint;
    pun.u64 = offset;
    uint_t rdi = pun.uint;
    pun.i = whence;
    uint_t rsi = pun.uint;
    kAFL_hypercall(LSEEK64, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

uint32_t SYM(lseek)(int fd, uint32_t offset, int whence) {
    uint64_t result = SYM(lseek64)(fd, offset, whence);

    // Perform the same overflow check as glibc in the 32-bit version of lseek.
    uint32_t result32 = (uint32_t)result;
    if (result == result32)
        return result32;
	
    errno = EOVERFLOW;
    return (uint32_t)-1;
}

FILE *SYM(fopen)(const char *pathname, const char *mode) {
    FILE *result = fopen(pathname, mode);
	
	pun.fileptr = result;
	uint_t rcx = pun.uint;
    pun.cstr = pathname;
    uint_t rdx = pun.uint;
    pun.cstr = mode;
    uint_t rdi = pun.uint;
    kAFL_hypercall(FOPEN, rcx, rdx, rdi, 0, 0, 0, 0);

    return result;
}

FILE *SYM(fopen64)(const char *pathname, const char *mode) {
    FILE *result = fopen64(pathname, mode);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.cstr = pathname;
    uint_t rdx = pun.uint;
    pun.cstr = mode;
    uint_t rdi = pun.uint;
    kAFL_hypercall(FOPEN64, rcx, rdx, rdi, 0, 0, 0, 0);

    return result;
}

size_t SYM(fread)(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t result = fread(ptr, size, nmemb, stream);
	
	pun.size = result;
	uint_t rcx = pun.uint;
    pun.ptr = ptr;
    uint_t rdx = pun.uint;
    pun.size = size;
    uint_t rdi = pun.uint;
    pun.size = nmemb;
    uint_t rsi = pun.uint;
    pun.fileptr = stream;
    uint_t r8 = pun.uint;
    kAFL_hypercall(FREAD, rcx, rdx, rdi, rsi, r8, 0, 0);

    return  result;
}

char *SYM(fgets)(char *str, int n, FILE *stream) {
    char *result = fgets(str, n, stream);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.str = str;
    uint_t rdx = pun.uint;
    pun.i = n;
    uint_t rdi = pun.uint;
    pun.fileptr = stream;
    uint_t rsi = pun.uint;
    kAFL_hypercall(FGETS, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

void SYM(rewind)(FILE *stream) {
    rewind(stream);

    pun.fileptr = stream;
    uint_t rcx = pun.uint;
    
    kAFL_hypercall(REWIND, rcx, 0, 0, 0, 0, 0, 0);
}

int SYM(fseek)(FILE *stream, long offset, int whence) {
    int result = fseek(stream, offset, whence);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.fileptr = stream;
    uint_t rdx = pun.uint;
    pun.l = offset;
    uint_t rdi = pun.uint;
    pun.i = whence;
    uint_t rsi = pun.uint;
    kAFL_hypercall(FSEEK, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

int SYM(fseeko)(FILE *stream, off_t offset, int whence) {
    int result = fseeko(stream, offset, whence);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.fileptr = stream;
    uint_t rdx = pun.uint;
    pun.l = offset;
    uint_t rdi = pun.uint;
    pun.i = whence;
    uint_t rsi = pun.uint;
    kAFL_hypercall(FSEEKO, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

int SYM(fseeko64)(FILE *stream, uint64_t offset, int whence) {
    int result = fseeko64(stream, offset, whence);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.fileptr = stream;
    uint_t rdx = pun.uint;
    pun.l = offset;
    uint_t rdi = pun.uint;
    pun.i = whence;
    uint_t rsi = pun.uint;
    kAFL_hypercall(FSEEKO64, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

int SYM(getc)(FILE *stream) {
    int result = getc(stream);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.fileptr = stream;
    uint_t rdx = pun.uint;
    kAFL_hypercall(GETC, rcx, rdx, 0, 0, 0, 0, 0);

    return result;
}

int SYM(fgetc)(FILE *stream) {
    int result = fgetc(stream);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.fileptr = stream;
    uint_t rdx = pun.uint;
    kAFL_hypercall(FGETC, rcx, rdx, 0, 0, 0, 0, 0);

    return result;
}

int SYM(getchar)(void) { 
    return SYM(getc)(stdin);
}

int SYM(ungetc)(int c, FILE *stream) {
    int result = ungetc(c, stream);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.i = c;
    uint_t rdx = pun.uint;
    pun.fileptr = stream;
    uint_t rdi = pun.uint;
    kAFL_hypercall(UNGETC, rcx, rdx, rdi, 0, 0, 0, 0);

    return result;
}

void *SYM(memcpy)(void *dest, const void *src, size_t n) {
    void *result = memcpy(dest, src, n);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.ptr = dest;
    uint_t rdx = pun.uint;
    pun.cptr = src;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(MEMCPY, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

void *SYM(memset)(void *s, int c, size_t n) {
    void *result = memset(s, c, n);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.ptr = s;
    uint_t rdx = pun.uint;
    pun.i = c;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(MEMSET_SYM, rcx, rdx, rdi, rsi, 0, 0, 0);

    return result;
}

void SYM(bzero)(void *s, size_t n) {
    bzero(s, n);

    pun.ptr = s;
    uint_t rcx = pun.uint;
    pun.size = n;
    uint_t rdx = pun.uint;
    kAFL_hypercall(BZERO, rcx, rdx, 0, 0, 0, 0, 0);
}

void *SYM(memmove)(void *dest, const void *src, size_t n) {
    void *result = memmove(dest, src, n);
	
	pun.ptr = result;
	uint_t rcx = pun.uint;
    pun.ptr = dest;
    uint_t rdx = pun.uint;
    pun.cptr = src;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(MEMMOVE_SYM, rcx, rdx, rdi, rsi, 0, 0, 0);

	return result;
}

void SYM(bcopy)(const void *src, void *dest, size_t n) {
    bcopy(src, dest, n);

    pun.cptr = src;
    uint_t rcx = pun.uint;
    pun.ptr = dest;
    uint_t rdx = pun.uint;
    pun.size = n;
    uint_t rdi = pun.uint;
    kAFL_hypercall(BCOPY, rcx, rdx, rdi, 0, 0, 0, 0);
}

char *SYM(strncpy)(char *dest, const char *src, size_t n) {
    char *result = strncpy(dest, src, n);
	
	pun.str = result;
	uint_t rcx = pun.uint;
    pun.str = dest;
    uint_t rdx = pun.uint;
    pun.cstr = src;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(STRNCPY, rcx, rdx, rdi, rsi, 0, 0, 0);

	return result;
}

const char *SYM(strchr)(const char *s, int c) {
    const char *result = strchr(s, c);
	
	pun.cstr = result;
	uint_t rcx = pun.uint;
    pun.cstr = s;
    uint_t rdx = pun.uint;
    pun.i = c;
    uint_t rdi = pun.uint;
	kAFL_hypercall(STRCHR, rcx, rdx, rdi, 0, 0, 0, 0);

	return result;
}

int SYM(memcmp)(const void *a, const void *b, size_t n) {
    int result = memcmp(a, b, n);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.cptr = a;
    uint_t rdx = pun.uint;
    pun.cptr = b;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(MEMCMP, rcx, rdx, rdi, rsi, 0, 0, 0);

	return result;
}

int SYM(bcmp)(const void *a, const void *b, size_t n) {
    int result = bcmp(a, b, n);
	
	pun.i = result;
	uint_t rcx = pun.uint;
    pun.cstr = a;
    uint_t rdx = pun.uint;
    pun.cstr = b;
    uint_t rdi = pun.uint;
    pun.size = n;
    uint_t rsi = pun.uint;
	kAFL_hypercall(BCMP, rcx, rdx, rdi, rsi, 0, 0, 0);

	return result;
}

uint32_t SYM(ntohl)(uint32_t netlong) {
    uint32_t result = ntohl(netlong);
	
	pun.u32 = result;
	uint_t rcx = pun.uint;
    pun.u32 = netlong;
    uint_t rdx = pun.uint;
	kAFL_hypercall(NTOHL, rcx, rdx, 0, 0, 0, 0, 0);

	return result;
}

