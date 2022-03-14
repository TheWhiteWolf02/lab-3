/* 
 * The file belongs to task 4 of SFT computer lab course
 * No need to change.
 * For documentation see tools.h
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>

#include <string>

#include "tools.h"

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

#define MMAP_INSTEAD_MPROTECT

void *malloc_prot(size_t s, const void *source, int prot) {
    static const int pagesize = getpagesize();
    void *chunk, *result;

    int pages = (s / pagesize) + (s % pagesize == 0 ? 0 : 1);
    size_t res_size = (pages + 1) * pagesize;
#if defined (__linux__) || defined (__Linux__) || defined (__LINUX__)
    if (PROT_WRITE == prot) {
        chunk = mmap(0, res_size, prot, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if ((void *) -1 == chunk)
            return 0;
        result = (char *) chunk + pages * pagesize - s;
        if (0 != munmap((char *) chunk + pages * pagesize, pagesize))
            return 0;

        return result;
    }
#endif // LINUX
    chunk = valloc(res_size);
    if (0 == chunk)
        return 0;
    result = (char *) chunk + pages * pagesize - s;
    memcpy(result, source, s);
    if (0 != mprotect(chunk, pages * pagesize, prot))
        return 0;
    if (0 != munmap((char *) chunk + pages * pagesize, pagesize))
        return 0;

    return result;
}

void filecopy(const char *source, const char *dest) {
    const static int PUFFER_SIZE = 1024;
    void *puffer;
    FILE *fsource, *fdest;
    int read;

    puffer = malloc(PUFFER_SIZE);
    if (0 == puffer)
        throw std::string("Insufficient memory to copy a file.");

    fsource = fopen(source, "r");
    fdest = fopen(dest, "w");
    if (0 == fsource || 0 == fdest)
        throw std::string("Couldn't open files to copy.");

    while (!feof(fsource)) {
        read = fread(puffer, 1, PUFFER_SIZE, fsource);
        if (ferror(fsource))
            throw std::string("Error reading source file.");
        if (read != fwrite(puffer, 1, read, fdest))
            throw std::string("Error writing destination file.");
    }

    fclose(fsource);
    fclose(fdest);

    free(puffer);
}

const void *NULLpage() {
    static void *NULL_page = 0;
    if (0 == NULL_page) {
        int size = getpagesize();
        NULL_page = malloc(size);
        if (0 == NULL_page)
            throw std::string("couldn't reserve memory");
        memset(NULL_page, 0, size);
    }

    return NULL_page;
}

void sleep(double time) {
    timespec tm;
    tm.tv_sec = (int) (time);
    tm.tv_nsec = (int) ((time - trunc(time)) * 1000000000);
    nanosleep(&tm, 0);
}
