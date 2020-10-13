#include "catch.hpp"
#include "testToolbox.h"

#include "../physical/Simulation.h"
#include "../physical/PhysicalObject.h"
#include "../physical/ElectricCharge.h"
#include "../physical/SimulationState.h"

#include "physical/PhysicalObjectPtr.h"
#include "toolbox/SavableData.h"

TEST_CASE("Simulation applying time", "[Simulation]")
{
    Simulation simulation;

    PhysicalObjectPtr obj(new PhysicalObject(1e6));
    PhysicalObjectPtr obj2(new PhysicalObject(1e6));

    obj2->setPosition(Vector<>({1.4142, 1.4142, 0}));

    simulation.addSubject(obj);
    simulation.addSubject(obj2);

    simulation.applyTime(1.0);

    CHECK(obj->getVelocity().almostEqual(-obj2->getVelocity(), 1e-5));
    CHECK_FALSE(obj->getVelocity().almostEqual(obj2->getVelocity(), 1e-5));

    CHECK_FALSE(obj->getPosition().almostEqual(Vector<>({0, 0, 0})));
    CHECK_FALSE(obj2->getPosition().almostEqual(Vector<>({1.4142, 1.4142, 0})));
}

TEST_CASE("Simulation save and restore state", "[Simulation]")
{
    Simulation simulation;
    SimulationState *state;

    PhysicalObjectPtr obj(new PhysicalObject(2.0));
    ElectricChargePtr el(new ElectricCharge(1.0, 1.0));
    ElectricChargePtr el2(new ElectricCharge(1.0, 1.0));

    simulation.addSubject(obj);
    simulation.addSubject(el);
    simulation.addSubject(el2);

    SECTION("Without delete")
    {
        state = simulation.saveState();

        obj->setMass(50);
        el->setCharge(120);
        el2->setVelocity(Vector<double>({10, 1, 1}));

        simulation.restoreState(state);
        delete state;

        CHECK(obj->getMass() == 2.0);
        CHECK(el->getCharge() == 1.0);
        CHECK(el2->getVelocity() == Vector<double>({0, 0, 0}));
    }

    SECTION("Restore deleted")
    {
        state = simulation.saveState();

        simulation.removeSubject(el);
        el->setCharge(120);
        obj->setMass(50);
        el2->setVelocity(Vector<double>({10, 1, 1}));

        simulation.restoreState(state);
        delete state;

        CHECK(obj->getMass() == 2.0);
        CHECK(el->getCharge() == 1.0);
        CHECK(el2->getVelocity() == Vector<double>({0, 0, 0}));
    }

    SECTION("Without restore deleted")
    {
        simulation.removeSubject(el);
        el->setCharge(120);

        CHECK(el->getCharge() == 120.0);
        simulation.addSubject(el);
    }

    SECTION("Restore without some item")
    {
        state = simulation.saveState();

        simulation.addSubject(PhysicalObjectPtr(new PhysicalObject(50)));

        simulation.restoreState(state);
        delete state;

        CHECK(simulation.getSubjects().size() == 3);
    }
}

TEST_CASE("Simulation save and restore from raw data", "[Simulation]")
{
    Simulation simulation;
    SavableData *data;

    PhysicalObjectPtr obj(new PhysicalObject(2.0));
    ElectricChargePtr el(new ElectricCharge(1.0, 1.0));
    ElectricChargePtr el2(new ElectricCharge(1.0, 2.0));

    simulation.addSubject(obj);
    simulation.addSubject(el);
    simulation.addSubject(el2);

    data = simulation.save();

    simulation.removeSubject(obj);
    el2->setCharge(3.0);

    CHECK(simulation.restore(data));
    delete data;

    CHECK(simulation.getSubjects().size() == 3);

    ElectricCharge *el2_restored = dynamic_cast<ElectricCharge*>(
        simulation.getSubjects().back().get()
    );

    REQUIRE(el2_restored);
    CHECK(el2_restored->getCharge() == 2);
    
}