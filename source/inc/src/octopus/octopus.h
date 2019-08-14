#pragma once
#include "world"
#include "math"
#include "ode"

#include <cmath>
#include <map>
#include <vector>

using namespace Physics;
class OctopusArm;

class OctopusODE: public Physics::ODE{
  OctopusArm& obj;
  Physics::VectorXD state, rate;
public:
  OctopusODE(OctopusArm& _obj);
  VectorXD getState() override final;
  VectorXD getRate(const VectorXD& state) override final;
  void setState(const VectorXD& _state) override final;
  size_t size() override final;
};

namespace Octopus{
class Octopus{


}; //class Octopus
} //namespace Octopus





//
// class MuscleForce: public Physics::Force{
// public:
//   // virtual ~Force() = default;
//   double getMagnitude() override final;
//   Vector2D getDirection() override final;
//   Vector2D getForce() override final;
// };




// class OctopusArm{
// 
//   // OctopusODE armODE;
// 
//   std::vector<OctopusCompartment> compartments;
//   std::vector<Physics::Object> nodes;
//   std::vector<Physics::Object*> upperNodes, lowerNodes;
// 
// public:
//   OctopusArm(Physics::World& world);
//   // Physics::ODE& getODE() override final{return armODE;}
//   
// 
// 
//   // 
// 
// 
// };
