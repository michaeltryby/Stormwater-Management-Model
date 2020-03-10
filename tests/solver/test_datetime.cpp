

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

    DateTime t1 = datetime_encodeTime(9,28,0);
    BOOST_CHECK_EQUAL(0.39444444444444443, t1);
}

BOOST_AUTO_TEST_CASE(test_decodeTime)
{
    DateTime x, a_date, s_date;

    int hrs, mins, secs;

    s_date = 39892.0;
    a_date = 39892.0 + 0.39444444444444443;

    x = a_date - s_date;

    datetime_decodeTime(x, &hrs, &mins, &secs);
    BOOST_CHECK_EQUAL(9, hrs);
    BOOST_CHECK_EQUAL(28, mins);
    BOOST_CHECK_EQUAL(0, secs);
}

BOOST_AUTO_TEST_SUITE_END()
