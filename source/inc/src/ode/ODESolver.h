#ifndef _PHYSICS_ODE_SOLVER_H
#define _PHYSICS_ODE_SOLVER_H

#include "math"
#include "ODE.h"


namespace Physics{
  class ODESolver{
  protected:
  public:
    virtual void solve(ODE& ode, double initialTime, double finalTime, double dt){
      double t;
      for(t = initialTime; t+dt < finalTime; t+=dt){
        step(ode,dt);
      }
      if( t < finalTime ){
        step(ode,finalTime-t);
      }
    }
    virtual void step(ODE& ode, double dt) = 0;

  };
} // namespace Physics


#endif
