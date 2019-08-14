#ifndef _PHYSICS_TRANSFORM_H
#define _PHYSICS_TRANSFORM_H

#include "Vector2D.h"
#include "ode"

namespace Physics{
class Transform: public ODE{
public:
  Transform() = default;
  Transform(const Vector2D& _pos, const Vector2D& _vel):pos(_pos), vel(_vel){}
  Vector2D getPosition();

private:
  Vector2D pos;
};
}

#endif
