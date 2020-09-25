#include "catch.hpp"
#include "testToolbox.h"

#include "../physical/Simulation.h"
#include "../physical/PhysicalObject.h"
#include "../physical/ElectricCharge.h"
#include "../physical/SimulationState.h"

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
}