#include "catch.hpp"
#include "testToolbox.h"

#include "../physical/Simulation.h"
#include "../physical/SimulationState.h"

#include "physical/modificators/ModificatorFactory.h"
#include "physical/SimulationSubjectPtr.h"
#include "physical/SimulationSubject.h"
#include "toolbox/SavableData.h"

TEST_CASE("Simulation applying time", "[Simulation]")
{
    Simulation simulation;

    SimulationSubjectPtr obj(new SimulationSubject(3, 1, 1e6));
    SimulationSubjectPtr obj2(new SimulationSubject(3, 1, 1e6));

    obj->addModificator(ModificatorFactory::instance()->get("AllInOne"));
    obj2->addModificator(ModificatorFactory::instance()->get("AllInOne"));

    obj2->setPosition(Vector<>({1.4142, 1.4142, 0}));

    simulation.addSubject(obj);
    simulation.addSubject(obj2);

    simulation.applyTime(1.0);

    CHECK(obj->getVelocity().almostEqual(-obj2->getVelocity(), 1e-5));
    CHECK_FALSE(obj->getVelocity().almostEqual(obj2->getVelocity(), 1e-5));

    CHECK_FALSE(obj->getPosition().almostEqual(Vector<>({0, 0, 0})));
    CHECK_FALSE(obj2->getPosition().almostEqual(Vector<>({1.4142, 1.4142, 0})));
}

TEST_CASE("Simulation multiple apply time", "[Simulation]")
{
    Simulation simulation;
    constexpr int OBJECTS = 20;
    constexpr int REPEAT = 100;

    for(int i = 0; i < OBJECTS; ++i)
    {
        SimulationSubjectPtr obj(new SimulationSubject(3, 10, 1e6));
        simulation.addSubject(obj);
        obj->addModificator("AllInOne");
    }

    for(int i = 0; i < REPEAT; ++i)
    { 
        simulation.applyTime(0.25);
    }

    CHECK(simulation.getSubjects().size() == OBJECTS);
}

TEST_CASE("Simulation save and restore state", "[Simulation]")
{
    Simulation simulation;
    SimulationState *state;

    SimulationSubjectPtr obj(new SimulationSubject(3, 1, 2.0));
    SimulationSubjectPtr el(new SimulationSubject(3, 1, 1.0, 1.0));
    SimulationSubjectPtr el2(new SimulationSubject(3, 1, 1.0, 1.0));

    simulation.addSubject(obj);
    simulation.addSubject(el);
    simulation.addSubject(el2);

    SECTION("Without delete")
    {
        state = simulation.saveState();

        obj->setMass(50);
        el->setElectricCharge(120);
        el2->setVelocity(Vector<double>({10, 1, 1}));

        simulation.restoreState(state);
        delete state;

        CHECK(obj->getMass() == 2.0);
        CHECK(el->getElectricCharge() == 1.0);
        CHECK(el2->getVelocity() == Vector<double>({0, 0, 0}));
    }

    SECTION("Restore deleted")
    {
        state = simulation.saveState();

        simulation.removeSubject(el);
        el->setElectricCharge(120);
        obj->setMass(50);
        el2->setVelocity(Vector<double>({10, 1, 1}));

        simulation.restoreState(state);
        delete state;

        CHECK(obj->getMass() == 2.0);
        CHECK(el->getElectricCharge() == 1.0);
        CHECK(el2->getVelocity() == Vector<double>({0, 0, 0}));
    }

    SECTION("Without restore deleted")
    {
        simulation.removeSubject(el);
        el->setElectricCharge(120);

        CHECK(el->getElectricCharge() == 120.0);
        simulation.addSubject(el);
    }

    SECTION("Restore without some item")
    {
        state = simulation.saveState();

        simulation.addSubject(SimulationSubjectPtr(new SimulationSubject(3, 1, 50)));

        simulation.restoreState(state);
        delete state;

        CHECK(simulation.getSubjects().size() == 3);
    }
}

TEST_CASE("Simulation save and restore from raw data", "[Simulation]")
{
    Simulation simulation;
    SavableData *data;

    SimulationSubjectPtr obj(new SimulationSubject(3, 1, 2.0));
    SimulationSubjectPtr el(new SimulationSubject(3, 1, 1.0, 1.0));
    SimulationSubjectPtr el2(new SimulationSubject(3, 1, 1.0, 2.0));

    simulation.addSubject(obj);
    simulation.addSubject(el);
    simulation.addSubject(el2);

    data = simulation.save();

    simulation.removeSubject(obj);
    el2->setElectricCharge(3.0);

    CHECK(simulation.restore(data));
    delete data;

    CHECK(simulation.getSubjects().size() == 3);
    CHECK(simulation.getSubjects().back().get()->getElectricCharge() == 2);

    ModificatorFactory::deleteInstance();
}