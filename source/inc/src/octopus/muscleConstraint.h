#ifndef _OCTOPUS_MUSCLECONSTRAINT_H
#define _OCTOPUS_MUSCLECONSTRAINT_H


#include "world"
#include "constants.h"
#include "misc"
#include "math"
#include <map>

using Physics::sptr;
using Physics::Object;
using Physics::Vector2D;

namespace Octopus{

  class MuscleConstraint : public Physics::Constraint {

  public:
    sptr<Physics::Object> n1,n2;
    double width;
    double initialLength;
    double action;
    std::map<sptr<Object>, Physics::Vector2D> forceMap;
    
    
    double activeConstant = 0.0;
    double passiveConstant = 0.0;
    double dampingConstant = 0.0;
    
    MuscleConstraint(sptr<Object> _n1, sptr<Object> _n2, double _width): n1(_n1), n2(_n2), width(_width){
      action = 0;
      initialLength = (n1->getPosition() - n2->getPosition()).norm();
      std::cout<<initialLength<<std::endl;
    }
    
  public:

    void update(double dt) override{
      Vector2D displacement = n2->getPosition() - n1->getPosition();
      Vector2D center = n1->getPosition() + (displacement*0.5);
      Vector2D velocity = n1->getVelocity() - n2->getVelocity();
      
      double projectedVelocity = velocity.dot(displacement.normalize());
      double normalizedLength = displacement.norm()/initialLength;
      
      double forceMag = 0;
      
      if(normalizedLength > Constants::Muscle::NormalizedMinLength) {
        forceMag = (activeConstant * action + passiveConstant) * (normalizedLength - Constants::Muscle::NormalizedMinLength);
      }
      forceMag += projectedVelocity * dampingConstant;
      // for(auto& o: )
      forceMap[n1] = (center - n1->getPosition()).normalize()*forceMag;
      forceMap[n2] = (center - n2->getPosition()).normalize()*forceMag;
      // for (Node n: Arrays.asList(n1, n2)) {
      //   forces.put(n, center.subtract(n.getPosition()).scaleTo(forceMag));
      // }

    }
    void applyForce() override{
      for(auto& p: forceMap){
        p.first->applyForce(p.second);
      }
    }
    Vector2D getForce(sptr<Object> obj) override{
      return forceMap.count(obj) != 0 ? forceMap[obj]:Vector2D(0,0);
    }
    void activate(double a){
      action = std::max(0.0, std::min(1.0,a));
    }
  };//class MuscleConstraint
  
class LongitudinalMuscleConstraint : public MuscleConstraint{

  public:
    
    LongitudinalMuscleConstraint(sptr<Object> o1, sptr<Object> o2, double width): MuscleConstraint(o1,o2,width) {
      activeConstant = 0.5*Constants::Muscle::Active*width*width/initialLength;
      passiveConstant = 0.5*Constants::Muscle::Passive*width*width/initialLength;
      dampingConstant = 0.5*Constants::Muscle::Damping*width*width/initialLength;
    }
  };//class LongitudinalMuscleConstraint
  
  class TransversalMuscleConstraint : public MuscleConstraint {

  public:
    
    TransversalMuscleConstraint(sptr<Object> o1, sptr<Object> o2, double width): MuscleConstraint(o1,o2,width) {
      activeConstant = Constants::Muscle::Active*initialLength;
      passiveConstant = Constants::Muscle::Passive*initialLength;
      dampingConstant = Constants::Muscle::Damping*initialLength;
    }
  };//class TraversalMuscleConstraint
} //namespace Octopus

#endif
