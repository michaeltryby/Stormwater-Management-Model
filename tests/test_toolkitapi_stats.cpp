/*
 *   test_toolkitapi_stats.cpp
 *
 *   Created: October 30, 2018
 *   Author: Michael E. Tryby
 *           US EPA ORD/NRMRL
 *
 *   Unit testing for SWMM-ToolkitAPI functions returning stats structs. .
 */

// NOTE: Travis installs libboost test version 1.5.4
//#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "toolkitapi_stats"
#include <boost/test/included/unit_test.hpp>

#include "swmm5.h"
#include "toolkitAPI.h"

// NOTE: Test Input File
#define DATA_PATH_INP "swmm_api_test.inp"
#define DATA_PATH_RPT "swmm_api_test.rpt"
#define DATA_PATH_OUT "swmm_api_test.out"


using namespace std;
using namespace boost;

struct FixtureBeforeEnd{
    FixtureBeforeEnd() {
        error = swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
        BOOST_REQUIRE(error == 0);

        error = swmm_start(0);
        BOOST_REQUIRE(error == 0);

        elapsedTime = 0.;
        do {
            error = swmm_step(&elapsedTime);
            BOOST_REQUIRE(error == 0);

        } while (elapsedTime != 0 && !error);

    }
    ~FixtureBeforeEnd() {
        error = swmm_end();
        BOOST_REQUIRE(error == 0);

        swmm_close();
        BOOST_REQUIRE(error == 0);
    }

    int error;
    double elapsedTime;
};


BOOST_AUTO_TEST_SUITE(test_toolkitapi_fixture)

BOOST_FIXTURE_TEST_CASE(test_getLinkStats, FixtureBeforeEnd) {

	int link_index;

	char link_id[] = "8";

	SM_LinkStats *link_stats = NULL;

	error = swmm_getObjectIndex(SM_LINK, link_id, &link_index);
	BOOST_REQUIRE(error == 0);

	error = swmm_getLinkStats(link_index, &link_stats);
	BOOST_REQUIRE(error == 0);

	BOOST_CHECK_SMALL(link_stats->maxFlow - 7.8485901, 0.001);
	BOOST_CHECK_SMALL(link_stats->maxFlowDate - 35796.1673611, 0.001);
	BOOST_CHECK_SMALL(link_stats->maxVeloc - 6.8433743, 0.001);
	BOOST_CHECK_SMALL(link_stats->maxDepth - 0.7871311, 0.001);

}

BOOST_FIXTURE_TEST_CASE(test_getOutfallStats, FixtureBeforeEnd) {

	int outfall_index;

	char outfall_id[] = "18";

	SM_OutfallStats *outfall_stats = NULL;

	error = swmm_getObjectIndex(SM_NODE, outfall_id, &outfall_index);
	BOOST_REQUIRE(error == 0);

	error = swmm_getOutfallStats(outfall_index, &outfall_stats);
	BOOST_REQUIRE(error == 0);

	BOOST_CHECK_SMALL(outfall_stats->avgFlow - 2.7089677, 0.001);
	BOOST_CHECK_SMALL(outfall_stats->maxFlow - 19.5761380, 0.01);
	BOOST_CHECK_EQUAL(outfall_stats->totalPeriods, 1574);
	
	BOOST_CHECK_SMALL(outfall_stats->totalLoad[0] - 409.7508625, 0.1);
	BOOST_CHECK_SMALL(outfall_stats->totalLoad[1] - 0.0819502, 0.1);

	swmm_free((void **)&outfall_stats);
}

BOOST_FIXTURE_TEST_CASE(test_getSubcatchStats, FixtureBeforeEnd){

    int subc_ind;

    char subid[] = "1";

    // Subcatchment
    SM_SubcatchStats *subc_stats = NULL;

    error = swmm_getObjectIndex(SM_SUBCATCH, subid, &subc_ind);
    BOOST_REQUIRE(error == 0);

    error = swmm_getSubcatchStats(subc_ind, &subc_stats);
    BOOST_REQUIRE(error == 0);

    BOOST_CHECK_SMALL(subc_stats->runon - 0.0, 0.0001);
    BOOST_CHECK_SMALL(subc_stats->infil - 42088, 1.0);
    BOOST_CHECK_SMALL(subc_stats->runoff - 53781, 1.0);
    BOOST_CHECK_SMALL(subc_stats->maxFlow - 4.6561, 0.0001);
    BOOST_CHECK_SMALL(subc_stats->precip - 2.65, 0.0001);
    BOOST_CHECK_SMALL(subc_stats->evap - 0.0, 0.0001);

    swmm_free((void **)&subc_stats);
}

BOOST_AUTO_TEST_SUITE_END()
