#ifndef _OCTOPUS_ROTATIONCONSTRAINEDOBJECT_H
#define _OCTOPUS_ROTATIONCONSTRAINEDOBJECT_H

#include "world"
#include "math"

using Physics::VectorXD;
using Physics::Vector2D;
using Physics::Object;
using Physics::sptr;


namespace Octopus{
  //Hacky just to get it implemented. Otherwise should solve this through the constraint system... Assumes the object passed is static which is equally as bad!!!!
  class RotationConstrainedObject: public Object{
    double angle, angularVelocity;
    Vector2D center;
    double radius;
    sptr<Object> staticObj;

  public:


    RotationConstrainedObject(Physics::World& _world, double _mass, Vector2D initPosition, Vector2D initVel, sptr<Object> _staticObj): Object(_world,_mass, initPosition, initVel), staticObj(_staticObj){
      state = VectorXD(2);
      rate = VectorXD(2);
      center = (initPosition + staticObj->getPosition())*0.5;
      Vector2D fromCenter = initPosition - center;
      radius = fromCenter.norm();
      angle = std::atan2(fromCenter.getY(), fromCenter.getX());
      angularVelocity = 0;
    }

    VectorXD getState() {
      state[0] = angle;
      state[1] = angularVelocity;
      return state;
    }
    VectorXD getRate(const VectorXD& _state) {
      rate[0] = _state[1];
      // angle = _state[0];
      // angularVelocity = _state[1];
      Vector2D angleVector(std::cos(_state[0]), std::sin(_state[0]));
      Vector2D posDiff = angleVector*radius;
      Vector2D tmpPos = posDiff + center;

      Vector2D tangent = (tmpPos - center).rotate90().normalize();
      Vector2D force = getForce();
      // std::cout<<force<<std::endl;
      // force = force;
      force = force - staticObj->getForce();
      double angularForce = std::atan2(force.dot(tangent), radius);
      double angularAccel = angularForce/mass;
      rate[1] = angularAccel;
      return rate;


    }
    void setState(const VectorXD& _state) {
      angle = _state[0];
      angularVelocity = _state[1];
      Vector2D angleVector(std::cos(angle), std::sin(angle));
      Vector2D posDiff = angleVector*radius;
      pos = center + posDiff;
      staticObj->setPosition(center - posDiff);
      vel = posDiff.rotate90()*angularVelocity;
      staticObj->setVelocity(vel*-1);
      // staticObj->setAppliedForce(Vector2D(0,0));
    }
    size_t size() {
      return 2;
    }

  };

}




#endif
