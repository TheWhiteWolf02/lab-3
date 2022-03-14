/* 
 * The file belongs to task 4 of SFT computer lab course
 * No need to change.
 * For documentation see stats.h
 */

#include <stdio.h>
#include "stats.h"

int terminated = 0;
int tested = 0;
int crashed = 0;
int started = 0;
int timedout = 0;
int stopped = 0;

TestCase last_cstr_value;
TestCase last_file_value;

void record_start_test_fputs(const TestCase &cstr_testCase,
                             const TestCase &file_testCase) {
    last_cstr_value = cstr_testCase;
    last_cstr_value = cstr_testCase;
    started++;
    printf("TEST fputs (%s, %s)\n", cstr_testCase.desc,
           file_testCase.desc);
}

void record_crashed_test_fputs(int signal) {
    crashed++;
    tested++;
    printf("  Test crashed by signal %d\n", signal);
}

void record_stopped_test_fputs(int signal) {
    stopped++;
    tested++;
    printf("  Test stopped by signal %d\n", signal);
}

void record_ok_test_fputs(int returnval) {
    terminated++;
    tested++;
    printf("  Test behaved robust - return value %d\n", returnval);
}

void record_timedout_test_fputs() {
    printf("  Functions runs for more than one second.\n"
           "  It will be terminated.\n");
    tested++;
    timedout++;
}

void print_summary() {
    printf("\n\nStatistics:\n");
    printf("%d out of %d behaved robust (%.2f%%)\n", terminated, tested,
           ((double) (terminated) * 100.0 / tested));
    printf("%d out of %d crashed (%.2f%%)\n", crashed, tested,
           ((double) (crashed) * 100.0 / tested));
    printf("%d out of %d stopped (%.2f%%)\n", stopped, tested,
           ((double) (stopped) * 100.0 / tested));
    printf("%d out of %d timed out (%.2f%%)\n", timedout, tested,
           ((double) (timedout) * 100.0 / tested));
}
