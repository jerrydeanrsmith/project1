/*
  Main program.
*/

#include <iostream>
#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject2D.h"
#include "simphys/particle.h"
#include "simphys/vec3.h"
#include "simphys/spring_force.h"

int main(int argc, char **argv) {

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  sim.setClock(clock_ptr);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>(); 
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::Particle p;
  simphys::Sprite s;
  simphys::SimObject2D testObject(p,s);
  auto obj_ptr = std::make_shared<simphys::SimObject2D>(testObject);
  auto objState = testObject.getState();
  objState->setPosition(simphys::vec3{420, 500.5, 0});
  objState->setVelocity(simphys::vec3{-50.0, 50.0, 0});
  objState->setAcceleration(simphys::vec3{0, -9.8, 0});
  objState->setMass(1.0);
  objState->setDamping(0.8);

  // add spring force generator
  auto springy = std::make_shared<simphys::SpringForce>(simphys::vec3{420.0f, 500.0f, 0.0f}, 0.1, 10.0);
  
  (sim.getPhysicsEngine())->addSpringPair(springy, objState);

  // add object to the world.
  world_ptr->add(obj_ptr);

  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
