#include "catch.hpp"
#include "testToolbox.h"

#include "toolbox/history.h"

TEST_CASE("History create", "[History]")
{
    History<int> history;

    CHECK(history.isEmpty());
    CHECK_FALSE(history.hasNext());
    CHECK_FALSE(history.hasPrevious());
}

TEST_CASE("History add item", "[History]")
{
    History<int> history;
    history.add(1);

    CHECK_FALSE(history.hasNext());
    CHECK_FALSE(history.hasPrevious());
    CHECK(history.current() == 1);
}

TEST_CASE("History add many items", "[History]")
{
    History<int> history;
    history.add(1);
    history.add(2);
    history.add(3);

    CHECK_FALSE(history.hasNext());
    CHECK(history.hasPrevious());

    CHECK(history.current() == 3);
    CHECK(history.previous() == 2);
    CHECK(history.previous() == 1);

    CHECK_FALSE(history.hasPrevious());
    CHECK(history.hasNext());
}

TEST_CASE("History iterate many items", "[History]")
{
    History<int> history;
    history.add(1);
    history.add(2);
    history.add(3);

    CHECK(history.previous() == 2);
    CHECK(history.previous() == 1);

    CHECK(history.next() == 2);
    CHECK(history.next() == 3);

    CHECK_FALSE(history.hasNext());
    CHECK(history.hasPrevious());
}

TEST_CASE("History delete on insert", "[History]")
{
    History<int> history;
    history.add(1);
    history.add(2);
    history.add(3);

    CHECK(history.previous() == 2);
    CHECK(history.previous() == 1);

    history.add(4);
    history.add(5);

    CHECK_FALSE(history.hasNext());
    CHECK(history.hasPrevious());

    CHECK(history.current() == 5);
    CHECK(history.previous() == 4);
    CHECK(history.previous() == 1);

    CHECK(history.hasNext());
    CHECK_FALSE(history.hasPrevious());
}