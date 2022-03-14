/* 
 * The file belongs to task 4 of SFT Lab
 * No need to change.
 * 
 * - specifies function that help to generate the test values for testing fputs on
 * - should be used in generateFILE and generateCSTR
 * - sleep could be used in test_fputs to wait a shorted time than a second
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>

/**
 * Allocates memory of a given size and a given protection. The memory
 * is align to a page end. The next page is unmapped. So every overflow will
 * trigger a segmentation fault.
 * You have to specify the content of the new allocated memory. That is important,
 * because you can not set the content of a read only memory region later on.
 *
 * @param size size of the memory region to allocation in bytes
 * @param source pointer to a memory region, from where the content of the
 *        newly allocated memory should be copied from
 *        ATTENTION: make sure that you provide at least size bytes
 * @param prot binaries or'ed combination of PROT_NONE, PROT_READ, and PROT_WRITE
 *        to specify the protection of the allocated memory
 *        for more information see "man mprotect"
 */
void *malloc_prot(size_t size, const void *source, int prot);

/**
 * copies file source to file dest. Is not perfectly robust!
 *
 * @param source file name of the source file
 * @param dest file name of the destination file
 * @throws std::string in case of an IO error
 */
void filecopy(const char *source, const char *dest);

/**
 * returns a pointer to getpagesize bytes (not aligned), that are all 'nulled'.
 * ATTENTION: the page is only allocated once. If you change it, a later call
 * to NULLpage returns the same changed memory region.
 *
 * @return pointer to getpagesize (normally 4096) bytes that are all set to 0
 * @throws std::string in case of insufficent memory
 */
const void *NULLpage();

/**
 * Displacement for libc sleep and wrapper around nanosleep. Can be used to
 * sleep shorter amounts of time than a whole second.
 * @param time time to sleep in seconds. could also be used to specify fractions
 *        of seconds, e.g. 0.25 is a quarter second, 0.5 a half second,
 *        and 2.5 are two and a half second.
 */
void sleep(double time);

#endif
