#ifndef _PHYSICS_EULER_H
#define _PHYSICS_EULER_H

#include "math"
#include "ODESolver.h"

namespace Physics{

  class Euler: public ODESolver{
  private:
    VectorXD rate;
    // Vector& curState;
  public:
    void step(ODE& ode, double dt) override final{
      VectorXD state = ode.getState();
      rate = ode.getRate(state);
      state = state + dt*rate;
      ode.setState(state);
    }
  };

} //namespace Physics





#endif
