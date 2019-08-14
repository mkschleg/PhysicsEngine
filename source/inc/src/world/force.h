#ifndef _PHYSICS_FORCE_H
#define _PHYSICS_FORCE_H

// #include "object.h"
#include "misc"
#include "math"


namespace Physics{
  class Object;
  class Force{
  public:
    virtual ~Force() = default;
    virtual double getMagnitude(const Object& obj) {return getForce(obj).norm();}
    virtual Vector2D getDirection(const Object& obj) {return getForce(obj).normalize();}
    virtual Vector2D getForce(const Object& obj) = 0;
  };
}



#endif
