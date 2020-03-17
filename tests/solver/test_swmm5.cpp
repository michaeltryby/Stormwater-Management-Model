
#include <iostream>

#include <boost/test/unit_test.hpp>

#include "test_solver.hpp"


BOOST_AUTO_TEST_SUITE (test_swmm5)


BOOST_AUTO_TEST_CASE(OpenCloseTest) {
    int error;

    error = swmm_open(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
    BOOST_CHECK(error == 0);

    error = swmm_close();
    BOOST_CHECK(error == 0);
}

BOOST_AUTO_TEST_CASE(RunTest) {
   int error;

   error = swmm_run(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
   BOOST_CHECK(error == 0);
}

BOOST_AUTO_TEST_CASE(StepTest) {
    double elapsedTime;

    swmm_open(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
    swmm_start(0);

    do {
        swmm_step(&elapsedTime);
        //std::cout << elapsedTime << std::endl;
    } while (elapsedTime != 0);

    swmm_end();
    swmm_close();
}

BOOST_AUTO_TEST_CASE(ObjectIndexTest) {
    int error, index;

    error = swmm_open(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
    BOOST_CHECK(error == 0);

    error = sm_getObjectIndex(NODE, "KRO3001", &index);
    BOOST_CHECK(error == 0);
    BOOST_CHECK(index == 0);

    error = swmm_close();
    BOOST_CHECK(error == 0);
}



BOOST_FIXTURE_TEST_CASE(NodeStatsTest, FixtureBeforeEnd) {
    int error, index = 0;
    SM_NodeStats test;

    error = sm_getNodeStats(index, &test);
    BOOST_CHECK(error == 0);

    BOOST_CHECK_CLOSE(test.maxRptDepth, 0.56763321161270142, 0.01);
    BOOST_CHECK_EQUAL(test.maxDepthDate, 36892.394508275465);
    //0 9:49  36892.409407928244 32 bit
    //0 9:43  36892.405540358799 64 bit
}


BOOST_AUTO_TEST_SUITE_END()
