#include "catch.hpp"
#include "../physical/PhysicalObject.h"

TEST_CASE("PhysicalObject create test", "[PhysicalObject]")
{
    PhysicalObject physical(1.0);

    CHECK(physical.getMass() == 1.0);
    CHECK(physical.getPosition() == Vector<>({0, 0}));
    CHECK(physical.getVelocity() == Vector<>({0, 0}));
}
