#ifndef _OCTOPUS_AXIALFRICTIONCONSTRAINT_H
#define _OCTOPUS_AXIALFRICTIONCONSTRAINT_H

#include "constants.h"
#include "world"

using Physics::sptr;
using Physics::Object;
using Physics::Vector2D;

namespace Octopus{

class AxialFrictionConstraint: public Physics::Constraint{
public:
  // private Node target;
  // private Node axialNode;
  sptr<Object> target;
  sptr<Object> axialNode;
  Vector2D force;

  /**
  * The friction influence will only influence the target, the axial
  * node serves only to give the orientation of the segment that
  * gives the tangential direction for friction computation.
  * @param target The node on which the friction will be computed.
  * @param axialNode A node that serves only to determine the orientation of the axis.
  // */
  AxialFrictionConstraint(sptr<Object> _target, sptr<Object> _axialNode):target(std::move(_target)),axialNode(std::move(_axialNode)){}
  void update(double dt) override{
    Vector2D axis = (target->getPosition() - axialNode->getPosition()).normalize();
    Vector2D velocity = target->getVelocity();
    double tanSpeed = velocity.dot(axis);
    Vector2D tangential = axis.normalize()*tanSpeed;
    Vector2D perpendicular = velocity - tangential;
    double perSpeed = perpendicular.norm();
    force = tangential.normalize()*(-tanSpeed*tanSpeed*Octopus::Constants::Friction::Tangential)
            + perpendicular.normalize()*(-perSpeed*perSpeed*Constants::Friction::Perpendicular);
  }
  void applyForce() override{
    target->applyForce(force);
  }
  Vector2D getForce(sptr<Object> obj) override{
    if(obj == target){
      return force;
    } else {
      return Vector2D(0,0);
    }
  }

};//class AxialFrictionConstraint
}//namepsace Octopus
#endif
