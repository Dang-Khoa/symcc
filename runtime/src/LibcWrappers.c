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

#define SYM(x) x##_symbolized

void *SYM(malloc)(size_t size) {
    return malloc(size);
}

void *SYM(calloc)(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

void *SYM(mmap64)(void *addr, size_t len, int prot, int flags, int fildes,
                  uint64_t off) {
    return  mmap64(addr, len, prot, flags, fildes, off);
}

void *SYM(mmap)(void *addr, size_t len, int prot, int flags, int fildes,
                uint32_t off) {
    return SYM(mmap64)(addr, len, prot, flags, fildes, off);
}

int SYM(open)(const char *path, int oflag, mode_t mode) {
    return open(path, oflag, mode);
}

ssize_t SYM(read)(int fildes, void *buf, size_t nbyte) {
    return read(fildes, buf, nbyte);
}

uint64_t SYM(lseek64)(int fd, uint64_t offset, int whence) {
    return lseek64(fd, offset, whence);
}

uint32_t SYM(lseek)(int fd, uint32_t offset, int whence) {
    return SYM(lseek64)(fd, offset, whence);
}

FILE *SYM(fopen)(const char *pathname, const char *mode) {
    return fopen(pathname, mode);
}

FILE *SYM(fopen64)(const char *pathname, const char *mode) {
    return fopen64(pathname, mode);
}

size_t SYM(fread)(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fread(ptr, size, nmemb, stream);
}

char *SYM(fgets)(char *str, int n, FILE *stream) {
    return fgets(str, n, stream);
}

void SYM(rewind)(FILE *stream) {
    rewind(stream);
}

int SYM(fseek)(FILE *stream, long offset, int whence) {
    return fseek(stream, offset, whence);
}

int SYM(fseeko)(FILE *stream, off_t offset, int whence) {
    return fseeko(stream, offset, whence);
}

int SYM(fseeko64)(FILE *stream, uint64_t offset, int whence) {
    return fseeko64(stream, offset, whence);
}

int SYM(getc)(FILE *stream) {
    return getc(stream);
}

int SYM(fgetc)(FILE *stream) {
    return fgetc(stream);
}

int SYM(getchar)(void) { 
    return SYM(getc)(stdin);
}

int SYM(ungetc)(int c, FILE *stream) {
    return ungetc(c, stream);
}

void *SYM(memcpy)(void *dest, const void *src, size_t n) {
    return memcpy(dest, src, n);
}

void *SYM(memset)(void *s, int c, size_t n) {
    return memset(s, c, n);
}

void SYM(bzero)(void *s, size_t n) {
    bzero(s, n);
}

void *SYM(memmove)(void *dest, const void *src, size_t n) {
    return memmove(dest, src, n);
}

void SYM(bcopy)(const void *src, void *dest, size_t n) {
    bcopy(src, dest, n);
}

char *SYM(strncpy)(char *dest, const char *src, size_t n) {
    return strncpy(dest, src, n);
}

const char *SYM(strchr)(const char *s, int c) {
    return strchr(s, c);
}

int SYM(memcmp)(const void *a, const void *b, size_t n) {
    return memcmp(a, b, n);
}

int SYM(bcmp)(const void *a, const void *b, size_t n) {
    return bcmp(a, b, n);
}

uint32_t SYM(ntohl)(uint32_t netlong) {
    return ntohl(netlong);
}

