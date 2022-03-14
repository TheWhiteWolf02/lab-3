#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <signal.h>

#include <string>
#include <iostream>

#include "tools.h"
#include "tests.h"
#include "stats.h"

using namespace std;

FILE *generateFILE(int test_id) {
    // generate test FILE* test value
    // see tests.h
    // use the functions specified by tools.h to create appropriate test values
    // you can use a copy of test.txt as a file to test on
    FILE *file;
    filecopy("test.txt", "test1.txt");

    if(test_id == TC_FILE_NULL) {
        return NULL;
    } else if(test_id == TC_FILE_RONLY) {
        file = fopen("test1.txt", "r");
        return file;
    } else if(test_id == TC_FILE_WONLY) {
        file = fopen("test1.txt", "w");
        return file;
    } else if(test_id == TC_FILE_RW) {
        file = fopen("test1.txt", "rw");
        return file;
    } else if(test_id == TC_FILE_CLOSED) {
        file = fopen("test1.txt", "rw");
        fclose(file);
        return file;
    } else if(test_id == TC_FILE_MEM_RONLY) {
        file = (FILE*)malloc(sizeof(FILE));
        file = (FILE*)malloc_prot(sizeof(FILE), file, PROT_READ);
        return file;
    } else if(test_id == TC_FILE_MEM_WONLY) {
        file = (FILE*)malloc(sizeof(FILE));
        file = (FILE*)malloc_prot(sizeof(FILE), file, PROT_WRITE);
        return file;
    } else if(test_id == TC_FILE_MEM_RW) {
        file = (FILE*)malloc(sizeof(FILE));
        file = (FILE*)malloc_prot(sizeof(FILE), file, PROT_READ | PROT_WRITE);
        return file;
    } else if(test_id == TC_FILE_MEM_0_RONLY) {
        file = (FILE*)NULLpage();
        file = (FILE*)malloc_prot(0, file, PROT_READ);
        return file;
    } else if(test_id == TC_FILE_MEM_0_WONLY) {
        file = (FILE*)NULLpage();
        file = (FILE*)malloc_prot(0, file, PROT_WRITE);
        return file;
    } else if(test_id == TC_FILE_MEM_0_RW) {
        file = (FILE*)NULLpage();
        file = (FILE*)malloc_prot(0, file, PROT_READ | PROT_WRITE);
        return file;
    } else if(test_id == TC_FILE_MEM_INACCESSIBLE) {
        file = (FILE*)malloc(sizeof(FILE));
        file = (FILE*)malloc_prot(sizeof(FILE), file, PROT_NONE);
        return file;
    } else {
        throw std::invalid_argument("File id not matched");
    }
}

const char *generateCSTR(int test_id) {
    // generate a `const char*` test value
    // see tests.h
    // use the functions specified by tools.h to create appropriate test values
    char *ch = (char *) malloc(5 * sizeof(char));

    char temp[5] = {'t','e','s','t','\0'};
    char temp1[5] = {'t','e','s','t','y'};

    if(test_id == TC_CSTR_NULL) {
        return NULL;
    } else if(test_id == TC_CSTR_MEM_RONLY) {
        ch = temp;
        ch = (char*)malloc_prot(5, ch, PROT_READ);
    } else if(test_id == TC_CSTR_MEM_WONLY) {
        ch = temp;
        ch = (char*)malloc_prot(5, ch, PROT_WRITE);
    } else if(test_id == TC_CSTR_MEM_RW) {
        ch = temp;
        ch = (char*)malloc_prot(5, ch, PROT_READ | PROT_WRITE);
    } else if(test_id == TC_CSTR_MEM_0_RONLY) {
        ch = temp1;
        ch = (char*)malloc_prot(5, ch, PROT_READ);
    } else if(test_id == TC_CSTR_MEM_0_WONLY) {
        ch = temp1;
        ch = (char*)malloc_prot(5, ch, PROT_WRITE);
    } else if(test_id == TC_CSTR_MEM_0_RW) {
        ch = temp1;
        ch = (char*)malloc_prot(5, ch, PROT_READ | PROT_WRITE);
    } else if(test_id == TC_CSTR_MEM_INACCESSIBLE) {
        ch = temp;
        ch = (char*)malloc_prot(5, ch, PROT_NONE);
    } else {
        throw std::invalid_argument("String id not matched");
    }
    return ch;
}

// waiting time before querying the child's exit status
// You might want to try using a smaller value in order to get the CI results faster,
// but there is a chance that your tests will start failing because of the timeout
const double wait_time = 0.5;

void test_fputs(const TestCase &str_testCase, const TestCase &file_testCase) {
    // execute a single test
    // use the functions in stats.h to record all tests
    record_start_test_fputs(str_testCase, file_testCase);

    pid_t child_pid = fork();
    int status;
    FILE *file;

    if(child_pid == 0) {
        const char* c = generateCSTR(str_testCase.id);
        file = generateFILE(file_testCase.id);
        int result = fputs(c, file);
        
        exit(result);
    } else {
        sleep(wait_time);
        int result = waitpid(child_pid, &status, WNOHANG);
        //waitpid failed
        if(result == -1) exit(1);
        
        if(result == 0) {
            // timeout
            record_timedout_test_fputs();
        } else if(WIFEXITED(status)) {
            // exited correctly
            record_ok_test_fputs(WEXITSTATUS(status));
        } else if(WIFSIGNALED(status)) {
            // child crashed
            record_crashed_test_fputs(WTERMSIG(status));
        } else if(WIFSTOPPED(status)) {
            // child was stopped
            record_stopped_test_fputs(WSTOPSIG(status));
        }
    }
}

int main(int argc, const char **argv) {
    // execute all tests and catch exceptions
    try
    {
        //test_fputs(testCases_CSTR[0], testCases_FILE[1]);
        int i,j;
        for(i = 0; i < testCases_CSTR_count; i++) {
            for(j = 0; j < testCases_FILE_count; j++) {
                test_fputs(testCases_CSTR[i], testCases_FILE[j]);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    print_summary();

    return 0;
}

