#include "catch.hpp"
#include "testToolbox.h"

#include "physical/ElectricCharge.h"
#include "toolbox/SavableData.h"

TEST_CASE("ElectricCharge setter test", "[ElectricCharge]")
{
    ElectricCharge charge(1.0, 1.0);

    charge.setMass(3.25);
    charge.setPosition(Vector<>({1, 0, 1}));
    charge.setVelocity(Vector<>({2, 1, 1}));
    charge.setCharge(2.0);

    CHECK(charge.getMass() == 3.25);
    CHECK(charge.getPosition() == Vector<>({1, 0, 1}));
    CHECK(charge.getVelocity() == Vector<>({2, 1, 1}));
    CHECK(charge.getCharge() == 2.0);
}

TEST_CASE("ElectricCharge apply force", "[ElectricCharge]")
{
    ElectricCharge charge(1.0);
    ElectricCharge charge2(4.0);

    charge.applyForce(Vector<>({1, 0, 0}), 1);
    charge2.applyForce(Vector<>({1, 0.5, 0}), 2);

    CHECK(charge.getVelocity() == Vector<>({1, 0, 0}));
    CHECK(charge2.getVelocity() == Vector<>({0.5, 0.25, 0}));
}

TEST_CASE("ElectricCharge apply time", "[ElectricCharge]")
{
    SECTION("No forces and no velocity")
    {
        ElectricCharge charge(1, 1);

        charge.applyTime(1);
        CHECK(charge.getVelocity() == Vector<>({0, 0, 0}));
        CHECK(charge.getPosition() == Vector<>({0, 0, 0}));
    }

    SECTION("No forces but velocity")
    {
        ElectricCharge charge(1.0);

        charge.setVelocity(Vector<>({1, 0, 1}));
        charge.applyTime(2.0);

        CHECK(charge.getPosition() == Vector<>({2, 0, 2}));
    }

    SECTION("Forces and velocity")
    {
        ElectricCharge charge(1.0);

        charge.setVelocity(Vector<>({1, 0, 1}));
        charge.applyForce(Vector<>({0, 1, 0}), 2);

        CHECK(charge.getPosition() == Vector<>({2, 2, 2}));
    }
}

TEST_CASE("ElectricCharge calculate force", "[ElectricCharge]")
{
    constexpr double fromGravity = 0.66743;
    constexpr double fromElectrostatic = 0.9001976419224258;
    constexpr double total = fromGravity + fromElectrostatic;

    ElectricCharge charge1(1e5, 1e-5);
    ElectricCharge charge2(1e5, 1e-5);

    charge2.setPosition(Vector<>({1, 0, 0}));

    CHECK(charge1.calculateForce(&charge2) == -charge2.calculateForce(&charge1));
    CHECK(charge1.calculateForce(&charge2).round(0.1) == Vector<>({total, 0, 0}).round(0.1));
}

TEST_CASE("ElectricCharge save and restore state", "[ElectricCharge]")
{
    ElectricCharge charge(1.0, 1.0);
    SavableData *savable;

    charge.setMass(3.25);
    charge.setPosition(Vector<>({1, 0, 1}));
    charge.setVelocity(Vector<>({2, 1, 1}));
    charge.setCharge(2.0);

    savable = charge.save();

    charge.setMass(20);
    charge.setPosition(Vector<>({50, 0, 1}));
    charge.setCharge(90);

    charge.restore(savable);

    CHECK(charge.getMass() == 3.25);
    CHECK(charge.getPosition() == Vector<>({1, 0, 1}));
    CHECK(charge.getVelocity() == Vector<>({2, 1, 1}));
    CHECK(charge.getCharge() == 2.0);

    delete savable;
}