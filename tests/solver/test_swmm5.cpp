
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

BOOST_AUTO_TEST_CASE(GetElapsedTimeTest) {
	int len;
	int *eTime = NULL;

	DateTime start = 36892.40416666666666667;
	DateTime stop = 36892.40972222222222221;

	std::vector<int> test;
	std::vector<int> ref_start = {0, 9, 42, 0};
	std::vector<int> ref_stop = {0, 9, 50, 0};

	sm_getElapsedTime(start, &eTime, &len);
	test.assign(eTime, eTime + len);
	BOOST_TEST(ref_start == test);
	sm_freeMemory(eTime);

	test.clear();

	sm_getElapsedTime(stop, &eTime, &len);
	test.assign(eTime, eTime + len);
	BOOST_TEST(ref_stop == test);
	sm_freeMemory(eTime);
}

BOOST_AUTO_TEST_CASE(RunTest) {
   int error;

   error = swmm_run(DATA_PATH_INP, DATA_PATH_RPT, DATA_PATH_OUT);
   BOOST_CHECK(error == 0);
}

BOOST_FIXTURE_TEST_CASE(StepTest, FixtureOpenClose) {
    double elapsedTime;

    swmm_start(true);

    do {
        swmm_step(&elapsedTime);
        //std::cout << elapsedTime << std::endl;
    } while (elapsedTime != 0);

    swmm_end();
    swmm_report();
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

BOOST_FIXTURE_TEST_CASE(TimeSeriesTest, FixtureOpenClose) {
    double elapsedTime, depth;
    DateTime eDateTime;
    DateTime start = 36892.40416666666666667;
    DateTime stop = 36892.40972222222222221;

    swmm_start(true);

    do {
        swmm_step(&elapsedTime);
//        sm_getDateTime(elapsedTime, &eDateTime);
//        if (eDateTime > start && eDateTime < stop) {
//            sm_getNodeResult(0, NODEDEPTH, &depth);
//            std::cout.precision(16);
//            std::cout << std::fixed << eDateTime << " " << depth << std::endl;
//        }

    } while (elapsedTime != 0);

    swmm_end();
    swmm_report();
}


BOOST_FIXTURE_TEST_CASE(NodeStatsTest, FixtureBeforeEnd) {
    int error, index = 0;
    SM_NodeStats test;

    error = sm_getNodeStats(index, &test);
    BOOST_CHECK(error == 0);

    BOOST_CHECK_CLOSE(test.maxRptDepth, 0.56763321161270142, 0.01);
    BOOST_CHECK_EQUAL(test.maxDepthDate, 36892.394508275465);
    //0.14729800820350647  0 9:49  36892.409407928244 32 bit
    //0.14729800820350647  0 9:43  36892.405540358799 64 bit
    //0.1472980153780030
}


BOOST_AUTO_TEST_SUITE_END()
