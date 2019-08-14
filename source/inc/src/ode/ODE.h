#ifndef _PHYSICS_ODE_H
#define _PHYSICS_ODE_H


#include "math"
// #include <vector>
namespace Physics{

class ODE{
public:
  virtual ~ODE() = default;
  
  // virtual Vector& getStateRef() = 0;
  virtual VectorXD getState() = 0;
  virtual VectorXD getRate(const VectorXD& state) = 0;
  virtual void setState(const VectorXD& _state) = 0;
  virtual size_t size() = 0;
  

};
}//namespace Physics




#endif
