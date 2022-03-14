/* 
 * The file belongs to task 4 of SFT Lab
 * No need to change.
 *
 * - specifies functions for statistic recording in a unified way
 * - make sure that you use the functions as described
 * - these function will be instrumented for automatic task checking
 * - wrong use may lead to failing the task
 */

#ifndef _STATS_H_
#define _STATS_H_

#include "tests.h"

/**
 * must be called for each test before it is started.
 * prints the current test configuration.
 * after each test, the corresponding `record_*_test_fputs (..)` function must
 * be called to record the test results
 * @param cstr_testCase specifies the test value used as a string parameter for fputs
 * @param file_testCase specifies the test value used as a stream parameter for fputs
 */
void record_start_test_fputs(const TestCase &cstr_testCase,
                             const TestCase &file_testCase);

/**
 * must be called for each test where fputs has crashed
 * prints the the test result
 * @param signal signal number that causes the crash
 */
void record_crashed_test_fputs(int signal);

/**
 * must be called for each test where fputs is stopped in a debugger
 * (very unlikely to happen)
 * prints the the test result
 * @param signal signal number that causes the stop
 */
void record_stopped_test_fputs(int signal);

/**
 * must be called for each test where fputs terminates normally
 * prints the the test result
 * @param returnval the return value of the process
 */
void record_ok_test_fputs(int returnval);

/**
 * must be called for each test where fputs does not finish within the given timeout
 * prints the the test result
 */
void record_timedout_test_fputs();

/**
 * prints the overall statistics of the experiments
 * must be called after all test has been performed
 */
void print_summary();

#endif
