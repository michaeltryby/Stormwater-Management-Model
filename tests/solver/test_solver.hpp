


#ifndef TEST_SOLVER_HPP
#define TEST_SOLVER_HPP


#include <stdbool.h>

#include "swmm5_2.h"


#define DATA_PATH_INP "./example3.inp"
#define DATA_PATH_RPT "./test.rpt"
#define DATA_PATH_OUT "./test.out"



struct FixtureOpenClose{
    FixtureOpenClose() {
        swmm_open(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
    }
    ~FixtureOpenClose() {
        swmm_close();
    }
};


struct FixtureBeforeEnd{
    FixtureBeforeEnd() {
        double elapsedTime;

        swmm_open(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
        swmm_start(true);

        do {
            swmm_step(&elapsedTime);
        } while (elapsedTime != 0);

    }
    ~FixtureBeforeEnd() {
        swmm_end();
        swmm_report();
        swmm_close();
    }
};


boost::test_tools::predicate_result check_cdd_double(std::vector<double>& test,
    std::vector<double>& ref, long cdd_tol);
boost::test_tools::predicate_result check_string(std::string test, std::string ref);


#endif //TEST_SOLVER_HPP
