#include "simphys/particle.h"

namespace simphys {

  Particle::Particle()
    : pos{0.0f, 0.0f, 0.0f}
    , vel{0.0f, 0.0f, 0.0f}
    , acc{0.0f, 0.0f, 0.0f}
    , accumulatedForces{0.0f, 0.0f, 0.0f}
    , damping{1.0f}
    , invMass{1.0f} { }

  void Particle::setPosition(const vec3& newPos) {
    pos = newPos;
  }

  void Particle::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void Particle::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void Particle::setDamping(float d) {
    damping = d;
  }

  void Particle::setMass(float m) {
    // TODO - decide if this is reasonable. Error handling?
    invMass = 1.0f / m;
  }

  vec3 Particle::getPosition() const {
    return pos;
  }

  vec3 Particle::getVelocity() const {
    return vel;
  }
  
  vec3 Particle::getAcceleration() const {
    return acc;
  }

  float Particle::getDamping() const {
    return damping;
  }
  
  float Particle::getMass() const {
    return 1.0f / invMass;
  }

  void Particle::integrate(fseconds duration) {

    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f) {
      return;
    }

    //update velocity using Verlet
    vel = vel + 1.0f/2.0f*acc*duration.count();
    // update position using Velocity Verlet
    pos = pos + vel * duration.count();
    vec3 resultantAcc  = (pos+duration.count())-(2.0f*pos+pos)-(duration.count());
    // update velocity using Velocity Verlet
    vel = vel + 1.0f/2.0f*resultantAcc*duration.count();
    // incorporate damping
    vel = vel * damping;

    clearForces();

  }

  void Particle::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }

  void Particle::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

}
