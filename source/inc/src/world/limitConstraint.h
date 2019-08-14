#ifndef _PHYSICS_LIMIT_CONSTRAINT_H
#define _PHYSICS_LIMIT_CONSTRAINT_H

#include "constraint.h"
#include <map>

namespace Physics{

  class DistanceConstraint: public Constraint{
    // std::map<sptr<Object>, Vector2D> forceMap;
    sptr<Object> objA;
    sptr<Object> objB;
    Vector2D forceA;
    Vector2D forceB;
    double distance;
  public:
    DistanceConstraint(sptr<Object> _objA, sptr<Object> _objB, double dist): objA(_objA), objB(_objB), distance(dist){
      // forceMap[objA] = Vector2D();
      // forceMap[objB] = Vector2D();
    }
    Vector2D getForce(sptr<Object> obj) override final{
      if(obj == objA) return forceA;
      else return forceB;
    }
    void applyForce() override final{
      objA->applyForce(forceA);
      objB->applyForce(forceB);
    }
    void update(double dt) override final{

      // double theta =


      // const Vector2D relDist = objB->getPosition() - objA->getPosition();
      // const double currentDistance = relDist.norm();
      // const Vector2D unitAxis = relDist.normalize();
      // 
      // //Calculate relative force
      // const double relVel = (objB->getVelocity() - objA->getVelocity());
      // const Vector2D relForce = (objB->getAppliedForce() - objA->getAppliedForce());
      // // const double relDist = currentDistance - distance;
      // 
      // const double lambda = -relForce.dot(relDist) -
      // 
      // // const double removeVel = remove;
      // // const double removeForce =
      // 
      // 
    }
  };



}
#endif
