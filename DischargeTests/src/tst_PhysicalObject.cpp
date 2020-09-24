#include "catch.hpp"
#include "../physical/PhysicalObject.h"

TEST_CASE("PhysicalObject setter test", "[PhysicalObject]")
{
    PhysicalObject physical(1.0);

    physical.setMass(3.25);
    physical.setPosition(Vector<>({1, 0, 1}));
    physical.setVelocity(Vector<>({2, 1, 1}));

    CHECK(physical.getMass() == 3.25);
    CHECK(physical.getPosition() == Vector<>({1, 0, 1}));
    CHECK(physical.getVelocity() == Vector<>({2, 1, 1}));
}

TEST_CASE("PhysicalObject apply force", "[PhysicalObject]")
{
    PhysicalObject physical1(1.0);
    PhysicalObject physical2(4.0);

    physical1.applyForce(Vector<>({1, 0, 0}), 1);
    physical2.applyForce(Vector<>({1, 0.5, 0}), 2);

    CHECK(physical1.getVelocity() == Vector<>({1, 0, 0}));
    CHECK(physical2.getVelocity() == Vector<>({0.5, 0.25, 0}));
}

TEST_CASE("PhysicalObject apply time", "[PhysicalObject]")
{
    SECTION("No forces and no velocity")
    {
        PhysicalObject physical(1.0);

        physical.applyTime(1.0);
        CHECK(physical.getVelocity() == Vector<>({0, 0, 0}));
        CHECK(physical.getPosition() == Vector<>({0, 0, 0}));
    }

    SECTION("No forces but velocity")
    {
        PhysicalObject physical(1.0);

        physical.setVelocity(Vector<>({1, 0, 1}));
        physical.applyTime(2.0);

        CHECK(physical.getPosition() == Vector<>({2, 0, 2}));
    }

    SECTION("Forces and velocity")
    {
        PhysicalObject physical(1.0);

        physical.setVelocity(Vector<>({1, 0, 1}));
        physical.applyForce(Vector<>({0, 1, 0}), 2);

        CHECK(physical.getPosition() == Vector<>({2, 2, 2}));
    }
}

TEST_CASE("PhysicalObject memento", "[PhysicalObject]")
{
    PhysicalObject physical(1.0);
    PhysicalMemento *memento;

    physical.setMass(3.25);
    physical.setPosition(Vector<>({1, 0, 1}));
    physical.setVelocity(Vector<>({2, 1, 1}));

    memento = physical.createMemento();

    physical.setMass(20);
    physical.setPosition(Vector<>({50, 0, 1}));

    physical.restoreMemento(memento);
    
    CHECK(physical.getMass() == 3.25);
    CHECK(physical.getPosition() == Vector<>({1, 0, 1}));
    CHECK(physical.getVelocity() == Vector<>({2, 1, 1}));
}
