#include "catch.hpp"
#include "testToolbox.h"

#include "../physical/Simulation.h"
#include "../physical/PhysicalObject.h"
#include "../physical/ElectricCharge.h"
#include "../physical/SimulationState.h"

TEST_CASE("Simulation applying time", "[Simulation]")
{
    Simulation simulation;

    PhysicalObject *obj = new PhysicalObject(1e6);
    PhysicalObject *obj2 = new PhysicalObject(1e6);

    obj2->setPosition(Vector<>({1.4142, 1.4142, 0}));

    simulation.addSubject(obj);
    simulation.addSubject(obj2);

    simulation.applyTime(1.0);

    CHECK(obj->getVelocity().almostEqual(-obj2->getVelocity(), 1e-5));
    CHECK_FALSE(obj->getVelocity().almostEqual(obj2->getVelocity(), 1e-5));

    CHECK_FALSE(obj->getPosition().almostEqual(Vector<>({0, 0, 0})));
    CHECK_FALSE(obj2->getPosition().almostEqual(Vector<>({1.4142, 1.4142, 0})));
}
/*
TEST_CASE("Simulation save and restore state", "[Simulation]")
{
    Simulation simulation;
    SimulationState *state;

    PhysicalObject *obj = new PhysicalObject(2.0);
    ElectricCharge *el = new ElectricCharge(1.0, 1.0);
    ElectricCharge *el2 = new ElectricCharge(1.0, 1.0);

    simulation.addSubject(obj);
    simulation.addSubject(el);
    simulation.addSubject(el2);

    state = simulation.saveState();

    obj->setMass(50);
    el->setCharge(120);
    el2->setVelocity(Vector<double>({10, 1, 1}));

    simulation.restoreState(state);

    CHECK(obj->getMass() == 2.0);
    CHECK(el->getCharge() == 1.0);
    CHECK(el2->getVelocity() == Vector<double>({0, 0, 0}));
}*/