#ifndef _PHYSICS_GRAVITY_H
#define _PHYSICS_GRAVITY_H

#include "math"
#include "force.h"
#include "object.h"

namespace Physics{
  class Gravity2D: public Force{
  private:
    const double g;
    // const Vector dir{}
  public:
    Gravity2D(double _g = 9.8):g(_g){}
    double getMagnitude(const Object& obj) override final {
      return g;
    }
    Vector2D getDirection(const Object& obj) override final {
      Vector2D dir;
      dir.set(0,-1);
      return dir;
    }
    Vector2D getForce(const Object& obj) override final {
      return g*obj.getMass()*getDirection(obj);
    }
  };
  // class Gravity3D: public Force{
  // private:
  //   const double g;
  // public:
  //   Gravity3D(double _g = 9.8):g(_g){}
  //   double getMagnitude() override final {
  //     return g;
  //   }
  //   Vector2D getDirection() override final {
  //     Vector2D dir;
  //     dir[0] = 0;
  //     dir[1] = -1;
  //     // dir[0] = 0;
  //     return dir;
  //     // v[
  //   }
  //   VectorXD getForce() override final {
  //     return g*getDirection();
  //   }
  // };

}



#endif
