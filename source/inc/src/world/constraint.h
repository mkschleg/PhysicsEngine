#ifndef _PHYSICS_CONSTRAINT_H
#define _PHYSICS_CONSTRAINT_H

#include "math"
#include "misc"
#include "object.h"
namespace Physics{
  class Constraint{
  public:
    virtual ~Constraint() = default;
    virtual Vector2D getForce(sptr<Object> obj) = 0;
    virtual void applyForce() = 0;
    virtual void update( double dt ) = 0;
  };
}


#endif
