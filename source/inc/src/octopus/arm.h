#ifndef _OCTOPUS_ARM_H
#define _OCTOPUS_ARM_H

#include "compartment.h"
#include "constants.h"
#include "world"

#include <vector>


namespace Octopus{
  
  class Arm{
    std::vector<sptr<Compartment>> compartments;
    std::vector<sptr<Object>> upperNodes, lowerNodes;
    std::vector<sptr<Object>> nodes;
    
  public:
    
    Arm(Physics::World& world);
    
    std::vector<sptr<Compartment>>& getCompartments();
    std::vector<sptr<Object>>& getNodes();

  }; //class Arm
} //namespace Octopus




#endif
