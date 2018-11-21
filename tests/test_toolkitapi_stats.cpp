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

// Custom test to check the minimum number of correct decimal digits between
// the test and the ref vectors.
boost::test_tools::predicate_result check_cdd(std::vector<double>& test,
    std::vector<double>& ref, long cdd_tol){
    double tmp, min_cdd = 10.0;

    // TODO: What if the vectors aren't the same length?

    std::vector<double>::iterator test_it;
    std::vector<double>::iterator ref_it;

    for (test_it = test.begin(), ref_it = ref.begin();
    (test_it < test.end()) && (ref_it < ref.end());
    ++test_it, ++ref_it) {
        if (*test_it != *ref_it) {
            // Compute log absolute error
            tmp = abs(*test_it - *ref_it);
            if (tmp < 1.0e-7)
                tmp = 1.0e-7;

            else if (tmp > 2.0)
                tmp = 1.0;

            tmp = -log10(tmp);
            if (tmp < 0.0)
                tmp = 0.0;

            if (tmp < min_cdd)
                min_cdd = tmp;
        }
    }

    return floor(min_cdd) >= cdd_tol;
}


struct FixtureBeforeEnd {
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

    std::vector<double> test_vec;
    std::vector<double> ref_vec = {
        7.8485901,
        35796.1673611,
        6.8433743,
        0.7871311
    };

    error = swmm_getObjectIndex(SM_LINK, link_id, &link_index);
    BOOST_REQUIRE(error == 0);

    error = swmm_getLinkStats(link_index, &link_stats);
    BOOST_REQUIRE(error == 0);

//    for (int i = 0; i < 4; i++) {
//        test_vec.push_back(*get_link_stats(link_stats, i));
//    }
//    BOOST_CHECK(check_cdd(test_vec, ref_vec, 3));

    swmm_free((void **)&link_stats);
}

BOOST_FIXTURE_TEST_CASE(test_getOutfallStats, FixtureBeforeEnd) {

    int n, outfall_index;

    char outfall_id[] = "18";

    SM_OutfallStats *outfall_stats = NULL;

    std::vector<double> test_vec;
    std::vector<double> ref_vec = {
        2.7089677,
        19.5966826,
        1574.
    };

    std::vector<double> pol_vec = {
        409.7508625,
        0.0819502
    };

    error = swmm_getObjectIndex(SM_NODE, outfall_id, &outfall_index);
    BOOST_REQUIRE(error == 0);

    error = swmm_getOutfallStats(outfall_index, &outfall_stats);
    BOOST_REQUIRE(error == 0);

//    for (int i = 0; i < 3; i++)
//        test_vec.push_back(*get_outfall_stats(outfall_stats, i));
//
//    BOOST_CHECK(check_cdd(test_vec, ref_vec, 6));


    test_vec.clear();

    error = swmm_countObjects(SM_POLLUT, &n);
    BOOST_REQUIRE(error == 0);

//    double *polluts = get_outfall_stats(outfall_stats, 3);
//    for (int i = 0; i < n; i++)
//        test_vec.push_back(polluts[i]);
//
//    BOOST_CHECK(check_cdd(test_vec, pol_vec, 3));
//
//    swmm_free((void **)&outfall_stats);
}

BOOST_FIXTURE_TEST_CASE(test_getSubcatchStats, FixtureBeforeEnd){

    int n, subc_ind;

    char subid[] = "1";

    // Subcatchment
    SM_SubcatchStats *subc_stats = NULL;

	vector<double> test_vec;
	std::vector<double> pol_vec = {
		33.5859153,
		0.0
	};


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

	error = swmm_countObjects(SM_POLLUT, &n);
	BOOST_REQUIRE(error == 0);

	for (int i = 0; i < n; i++)
		test_vec.push_back(subc_stats->surfaceBuildup[i]);

	BOOST_CHECK(check_cdd(test_vec, pol_vec, 3));

	swmm_free((void **)&subc_stats);
}

BOOST_AUTO_TEST_SUITE_END()
