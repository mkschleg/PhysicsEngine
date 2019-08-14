#ifndef _OCTOPUS_REPULSTIONFORCE_H
#define _OCTOPUS_REPULSTIONFORCE_H

#include "world"
#include "constants.h"

using Physics::Vector2D;
using Physics::Object;
using Physics::sptr;

namespace Octopus{
  
  class RepulsionForce: public Physics::Force{
  public:
    sptr<Object> source;
    RepulsionForce(sptr<Object> _source):source(_source){}
    Vector2D getForce(const Object& obj) override final{
      // if(obj.id != source->id)
      // std::cout<<"Repulse"<<std::endl;
      Vector2D displacement = obj.getPosition() - source->getPosition();
      double distance = displacement.norm();
      if(distance < Octopus::Constants::Repulsion::Threshold && obj.getID() != source->getID()){
        double forceMag = Octopus::Constants::Repulsion::Constant / std::pow(distance, Constants::Repulsion::Power);
        return displacement.normalize()*forceMag;
      } else {
        return Vector2D(0,0);
      }
    }
  };

}//namespace Octopus



#endif
