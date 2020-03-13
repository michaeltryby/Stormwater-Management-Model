
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

    BOOST_CHECK_EQUAL(test.maxDepthDate, 36892.394508275465);
}


BOOST_AUTO_TEST_SUITE_END()
