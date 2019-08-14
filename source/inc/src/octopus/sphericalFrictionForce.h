#ifndef _OCTOPUS_SPHERICALFRICTIONFORCE_H
#define _OCTOPUS_SPHERICALFRICTIONFORCE_H

#include "constants.h"

#include "world"


using Physics::Vector2D;
using Physics::Object;
using Physics::sptr;

namespace Octopus{
  
  class SphericalFrictionForce: public Physics::Force{
    
    Vector2D getForce(const Object& obj) override final{
      double speed = obj.getVelocity().norm();
      return obj.getVelocity().normalize()*(-speed*speed*Constants::Friction::Perpendicular);
    }
  };//class SpericalFrictionForce
}//namespace Octopus


#endif
