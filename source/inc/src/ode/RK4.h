#ifndef _PHYSICS_RK4_H
#define _PHYSICS_RK4_H

#include "math"
#include "ODE.h"
#include "ODESolver.h"


namespace Physics{

  class RK4: public ODESolver{
  private:
    VectorXD rate1,rate2,rate3,rate4,estimatedState;
  
  public:
    // RK4(ODE& _ode, double _stepSize = 0.1):ODESolver(_ode, _stepSize),
    //   rate1(_ode.size()), rate2(_ode.size()), rate3(_ode.size()), rate4(_ode.size()), estimatedState(_ode.size()){}

    void step(ODE& ode, double dt) override final{
      VectorXD state = ode.getState();
      rate1 = ode.getRate(state);
      estimatedState = state+dt*rate1/2;
      rate2 = ode.getRate(estimatedState);
      estimatedState = state+dt*rate2/2;
      rate3 = ode.getRate(estimatedState);
      estimatedState = state+dt*rate3;
      rate4 = ode.getRate(estimatedState);
      state += dt*(rate1+2*rate2+2*rate3+rate4)/6.0;
      // std::cout<<state[1]<<" "<<(rate1+2*rate2+2*rate3+rate4)<<std::endl;
      ode.setState(state);
    }

  };


}//namespace Physics


#endif
