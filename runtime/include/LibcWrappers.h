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
// along with the SymCC runtime. If not, see <https://www.gnu.org/licenses/>.

#ifndef LIBCWRAPPERS_H
#define LIBCWRAPPERS_H

/// Initialize the libc wrappers.
///
/// The configuration needs to be loaded so that we can apply settings related
/// to symbolic input.
void initLibcWrappers();

void *malloc_symbolized(size_t size);
void *calloc_symbolized(size_t nmemb, size_t size);
void *mmap64_symbolized(void *addr, size_t len, int prot, int flags, int fildes, uint64_t off);
void *mmap_symbolized(void *addr, size_t len, int prot, int flags, int fildes, uint32_t off);
int open_symbolized(const char *path, int oflag, mode_t mode);
ssize_t read_symbolized(int fildes, void *buf, size_t nbyte);
uint64_t lseek64_symbolized(int fd, uint64_t offset, int whence);
uint32_t lseek_symbolized(int fd, uint32_t offset, int whence);
FILE *fopen_symbolized(const char *pathname, const char *mode);
FILE *fopen64_symbolized(const char *pathname, const char *mode);
size_t fread_symbolized(void *ptr, size_t size, size_t nmemb, FILE *stream);
char *fgets_symbolized(char *str, int n, FILE *stream);
void rewind_symbolized(FILE *stream);
int fseek_symbolized(FILE *stream, long offset, int whence);
int fseeko_symbolized(FILE *stream, off_t offset, int whence);
int fseeko64_symbolized(FILE *stream, uint64_t offset, int whence);
int getc_symbolized(FILE *stream);
int fgetc_symbolized(FILE *stream);
int getchar_symbolized(void); 
int ungetc_symbolized(int c, FILE *stream);
void *memcpy_symbolized(void *dest, const void *src, size_t n);
void *memset_symbolized(void *s, int c, size_t n);
void bzero_symbolized(void *s, size_t n);
void *memmove_symbolized(void *dest, const void *src, size_t n);
void bcopy_symbolized(const void *src, void *dest, size_t n);
char *strncpy_symbolized(char *dest, const char *src, size_t n);
const char *strchr_symbolized(const char *s, int c);
int memcmp_symbolized(const void *a, const void *b, size_t n);
int bcmp_symbolized(const void *a, const void *b, size_t n);
uint32_t ntohl_symbolized(uint32_t netlong);

#endif
