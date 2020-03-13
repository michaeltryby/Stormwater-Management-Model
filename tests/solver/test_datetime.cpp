

#define BOOST_TEST_MODULE datetime

#include <boost/test/unit_test.hpp>

#include "datetime.h"


BOOST_AUTO_TEST_SUITE(test_datetime)

BOOST_AUTO_TEST_CASE(test_encodeDateTime)
{
    //START_DATE            01/01/2001
    DateTime date = datetime_encodeDate(2001, 1, 1);
    BOOST_CHECK_EQUAL(36892, date);

    //START_TIME            00:00:00
    DateTime t0 = datetime_encodeTime(0,0,0);
    BOOST_CHECK_EQUAL(0.0, t0);

    DateTime t1 = datetime_encodeTime(9,28,6);
    BOOST_CHECK_EQUAL(0.39451388888888889, t1);
}

BOOST_AUTO_TEST_CASE(test_decodeTime)
{
    DateTime x0, x1;

    int hrs, mins, secs;

    x0 = 0.394508275465;

    datetime_decodeTime(x0, &hrs, &mins, &secs);
    BOOST_CHECK_EQUAL(9, hrs);
    BOOST_CHECK_EQUAL(28, mins);
    BOOST_CHECK_EQUAL(6, secs);

    x1 = 0.39451388888888889;

    datetime_decodeTime(x1, &hrs, &mins, &secs);
    BOOST_CHECK_EQUAL(9, hrs);
    BOOST_CHECK_EQUAL(28, mins);
    BOOST_CHECK_EQUAL(6, secs);

    datetime_decodeTime(x1 - x0, &hrs, &mins, &secs);
    BOOST_CHECK_EQUAL(0, hrs);
    BOOST_CHECK_EQUAL(0, mins);
    BOOST_CHECK_EQUAL(0, secs);
}

BOOST_AUTO_TEST_SUITE_END()
