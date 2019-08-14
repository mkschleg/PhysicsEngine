#ifndef _OCTOPUS_CONSTRAINEDOBJECT_H
#define _OCTOPUS_CONSTRAINEDOBJECT_H
  
#include "world"

using Physics::VectorXD;
using Physics::Vector2D;

namespace Octopus{

  class ConstrainedObject : public Physics::Object{
  public:
    ConstrainedObject(Physics::World& _world, double _mass, Physics::Vector2D initPosition, Physics::Vector2D initVel):Physics::Object(_world,_mass,initPosition,initVel){}
    VectorXD getState() {
      return VectorXD(1);
    }
    VectorXD getRate(const VectorXD& _state) {

      return VectorXD(1);
    }
    void setState(const VectorXD& _state) {

    }
    size_t size() {
      return 1;
    }

  };

}


#endif
