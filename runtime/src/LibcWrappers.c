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

#include <Runtime.h>

#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

#define SYM(x) x##_symbolized

void *SYM(malloc)(size_t size) {
    return (void*) kAFL_hypercall(MALLOC, (uint_t) size, 0, 0, 0, 0, 0);
}

void *SYM(calloc)(size_t nmemb, size_t size) {
    return (void*) kAFL_hypercall(CALLOC, (uint_t) nmemb, (uint_t) size, 0, 0, 0, 0);
}

void *SYM(mmap64)(void *addr, size_t len, int prot, int flags, int fildes,
                  uint64_t off) {
    return (void*) kAFL_hypercall(MMAP64, (uint_t) addr, (uint_t) len, (uint_t) prot, (uint_t) flags, (uint_t) fildes, (uint_t) off);
}

void *SYM(mmap)(void *addr, size_t len, int prot, int flags, int fildes,
                uint32_t off) {
    return (void*) kAFL_hypercall(MMAP64, (uint_t) addr, (uint_t) len, (uint_t) prot, (uint_t) flags, (uint_t) fildes, (uint_t) off);
}

int SYM(open)(const char *path, int oflag, mode_t mode) {
    return (int) kAFL_hypercall(OPEN, (uint_t) path, (uint_t) oflag, (uint_t) mode, 0, 0, 0);
}

ssize_t SYM(read)(int fildes, void *buf, size_t nbyte) {
    return (ssize_t) kAFL_hypercall(READ, (uint_t) fildes, (uint_t) buf, (uint_t) nbyte, 0, 0, 0);
}

uint64_t SYM(lseek64)(int fd, uint64_t offset, int whence) {
    return (uint64_t) kAFL_hypercall(LSEEK64, (uint_t) fd, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}

uint32_t SYM(lseek)(int fd, uint32_t offset, int whence) {
    return (uint32_t) kAFL_hypercall(LSEEK, (uint_t) fd, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}

FILE *SYM(fopen)(const char *pathname, const char *mode) {
    return (FILE *) kAFL_hypercall(FOPEN, (uint_t) pathname, (uint_t) mode, 0, 0, 0, 0);
}

FILE *SYM(fopen64)(const char *pathname, const char *mode) {
    return (FILE *) kAFL_hypercall(FOPEN64, (uint_t) pathname, (uint_t) mode, 0, 0, 0, 0);
}

size_t SYM(fread)(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return (size_t) kAFL_hypercall(FREAD, (uint_t) ptr, (uint_t) size, (uint_t) nmemb, (uint_t) stream, 0, 0);
}

char *SYM(fgets)(char *str, int n, FILE *stream) {
    return (char *) kAFL_hypercall(FGETS, (uint_t) str, (uint_t) n, (uint_t) stream, 0, 0, 0);
}

void SYM(rewind)(FILE *stream) {
    kAFL_hypercall(REWIND, (uint_t) stream, 0, 0, 0, 0, 0);
}

int SYM(fseek)(FILE *stream, long offset, int whence) {
    return (int) kAFL_hypercall(FSEEK, (uint_t) stream, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}

int SYM(fseeko)(FILE *stream, off_t offset, int whence) {
    return (int) kAFL_hypercall(FSEEKO, (uint_t) stream, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}

int SYM(fseeko64)(FILE *stream, uint64_t offset, int whence) {
    return (int) kAFL_hypercall(FSEEKO64, (uint_t) stream, (uint_t) offset, (uint_t) whence, 0, 0, 0);
}

int SYM(getc)(FILE *stream) {
    return (int) kAFL_hypercall(GETC, (uint_t) stream, 0, 0, 0, 0, 0);
}

int SYM(fgetc)(FILE *stream) {
    return (int) kAFL_hypercall(FGETC, (uint_t) stream, 0, 0, 0, 0, 0);
}

int SYM(getchar)(void) { 
    return (int) kAFL_hypercall(GETCHAR, 0, 0, 0, 0, 0, 0);
}

int SYM(ungetc)(int c, FILE *stream) {
    return (int) kAFL_hypercall(UNGETC, (uint_t) c, (uint_t) stream, 0, 0, 0, 0);
}

void *SYM(memcpy)(void *dest, const void *src, size_t n) {
    return (void *) kAFL_hypercall(MEMCPY, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}

void *SYM(memset)(void *s, int c, size_t n) {
    return (void *) kAFL_hypercall(MEMSET, (uint_t) s, (uint_t) c, (uint_t) n, 0, 0, 0);
}

void SYM(bzero)(void *s, size_t n) {
    kAFL_hypercall(BZERO, (uint_t) s, (uint_t) n, 0, 0, 0, 0);
}

void *SYM(memmove)(void *dest, const void *src, size_t n) {
    return (void *) kAFL_hypercall(MEMMOVE, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}

void SYM(bcopy)(const void *src, void *dest, size_t n) {
    kAFL_hypercall(BCOPY, (uint_t) src, (uint_t) dest, (uint_t) n, 0, 0, 0);
}

char *SYM(strncpy)(char *dest, const char *src, size_t n) {
    return (char *) kAFL_hypercall(STRNCPY, (uint_t) dest, (uint_t) src, (uint_t) n, 0, 0, 0);
}

const char *SYM(strchr)(const char *s, int c) {
    return (char *) kAFL_hypercall(STRCHR, (uint_t) s, (uint_t) c, 0, 0, 0, 0);
}

int SYM(memcmp)(const void *a, const void *b, size_t n) {
    return (int) kAFL_hypercall(MEMCMP, (uint_t) a, (uint_t) b, (uint_t) n, 0, 0, 0);
}

int SYM(bcmp)(const void *a, const void *b, size_t n) {
    return (int) kAFL_hypercall(BCMP, (uint_t) a, (uint_t) b, (uint_t) n, 0, 0, 0);
}

uint32_t SYM(ntohl)(uint32_t netlong) {
    return (uint32_t) kAFL_hypercall(NTOHL, (uint_t) netlong, 0, 0, 0, 0, 0);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
