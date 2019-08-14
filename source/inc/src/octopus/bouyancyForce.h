#ifndef _OCTOPUS_BOUYANCYFORCE_H
#define _OCTOPUS_BOUYANCYFORCE_H

#include "world"

using Physics::Vector2D;
using Physics::Object;
using Physics::sptr;

namespace Octopus{

class BouyancyForce: public Physics::Force{

public:

  double surfaceLevel;
  double gravity;

  BouyancyForce(double _surfaceLevel, double _gravity):surfaceLevel(_surfaceLevel), gravity(_gravity){}

  double getMagnitude(const Object& obj) override final {
    return getForce(obj).norm();
  }
  Vector2D getDirection(const Object& obj) override final {
    return getForce(obj).normalize();
  }
  Vector2D getForce(const Object& obj) override final {
    Vector2D pos = obj.getPosition();
    double surfaceDist = surfaceLevel - pos.getY();
    if(surfaceDist > 0){
      return Vector2D(0,gravity*obj.getMass());
    } else {
      return Vector2D(0,0);
    }
  }
  
};//class BoyancyForce
}//namespace Octopus



#endif
