/* 
 * The file belongs to task 4 of SFT Lab
 * No need to change.
 *
 * - specifies the test values of types FILE* and const char*
 * - make sure that you test all combinations of all test values
 * - if you are unsure about a meaning of a test value specification,
 *   then read the task description, use the forum or ask us
 * - use the functions specified by tools.h to create appropriate test values
 */

#ifndef _TESTS_H_
#define _TESTS_H_

#include <stdio.h>

struct TestCase {
    int id;                        // test value id
    const char *desc;              // descriptive string
    int expected_returnvalue;      // expected return value of fputs (not used)
};

const TestCase testCases_FILE[] = {
#define TC_FILE_NULL 0
    {TC_FILE_NULL, "NULL pointer", EOF},
#define TC_FILE_RONLY 1
    {TC_FILE_RONLY, "FILE opened for reading only", EOF},
#define TC_FILE_WONLY 2
    {TC_FILE_WONLY, "FILE opened for writing only", 1},
#define TC_FILE_RW 3
    {TC_FILE_RW, "FILE opened for reading and writing", 1},
#define TC_FILE_CLOSED 4
    {TC_FILE_CLOSED, "FILE already closed", EOF},
#define TC_FILE_MEM_RONLY 5
    {TC_FILE_MEM_RONLY, "pointer to valid file structure (memory read only)", EOF},
#define TC_FILE_MEM_WONLY 6
    {TC_FILE_MEM_WONLY, "pointer to valid file structure (memory write only)", 1},
#define TC_FILE_MEM_RW 7
    {TC_FILE_MEM_RW, "pointer to valid file structure (memory read/write)", 1},
#define TC_FILE_MEM_0_RONLY 8
    {TC_FILE_MEM_0_RONLY, "pointer to a \"0\" page (memory read only)", EOF},
#define TC_FILE_MEM_0_WONLY 9
    {TC_FILE_MEM_0_WONLY, "pointer to a \"0\" page (memory write only)", EOF},
#define TC_FILE_MEM_0_RW 10
    {TC_FILE_MEM_0_RW, "pointer to a \"0\" page (memory read/write)", EOF},
#define TC_FILE_MEM_INACCESSIBLE 11
    {TC_FILE_MEM_INACCESSIBLE, "pointer to inaccessible memory", EOF},
};

// number of test values for FILE*
const int testCases_FILE_count = sizeof(testCases_FILE) /
    sizeof(testCases_FILE[0]);

const TestCase testCases_CSTR[] = {
#define TC_CSTR_NULL 0
    {TC_CSTR_NULL, "NULL pointer", EOF},
#define TC_CSTR_MEM_RONLY 1
    {TC_CSTR_MEM_RONLY, "pointer to valid string (memory read only)", 1},
#define TC_CSTR_MEM_WONLY 2
    {TC_CSTR_MEM_WONLY, "pointer to valid string (memory write only)", EOF},
#define TC_CSTR_MEM_RW 3
    {TC_CSTR_MEM_RW, "pointer to valid string (memory read/write)", 1},
#define TC_CSTR_MEM_0_RONLY 4
    {TC_CSTR_MEM_0_RONLY, "pointer to a string without trailing 0 (memory read only)", 1},
#define TC_CSTR_MEM_0_WONLY 5
    {TC_CSTR_MEM_0_WONLY, "pointer to a string without trailing 0 (memory write only)", EOF},
#define TC_CSTR_MEM_0_RW 6
    {TC_CSTR_MEM_0_RW, "pointer to a string without trailing 0 (memory read/write)", 1},
#define TC_CSTR_MEM_INACCESSIBLE 7
    {TC_CSTR_MEM_INACCESSIBLE, "pointer to inaccessible memory", EOF},
};

// number of test values for const char*
const int testCases_CSTR_count = sizeof(testCases_CSTR) /
    sizeof(testCases_CSTR[0]);

#endif
