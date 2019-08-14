#include "gtest/gtest.h"
// #include "../source/inc/ode"
#include "ode"
#include <iostream>

class FallingParticleODE: public Physics::ODE{
  constexpr static double g = 9.8;
  Physics::VectorXD state;
public:
  FallingParticleODE(double y, double v):state(3){
    // state = Physics::Vector(3);
    state[0] = y;
    state[1] = v;
    state[2] = 0;
  }
  Physics::VectorXD getState() override final{
    return state;
  }
  Physics::VectorXD getRate(const Physics::VectorXD& _state) override final{
    Physics::VectorXD rate(state.size());
    rate[0] = _state[1];
    rate[1] = -g;
    rate[2] = 1;
    return rate;
  }
  void setState(const Physics::VectorXD& _state) override final{
    state = _state;
  }
  size_t size() override final{
    return state.size();
  }
};


TEST(ode,eulertest){

  double y0 = 10;
  double v0 = 0;
  double dt = 0.01;

  FallingParticleODE ball(y0,v0);
  Physics::ODESolver* solver = new Physics::RK4;
  while(ball.getState()[0] > 0){
    solver->step(ball,dt);
    // std::cout<<ball.getState()[0]<<" "<<ball.getState()[1]<<" "<<ball.getState()[2]<<std::endl;
  }
  
  std::cout<<ball.getState()[0]<<" "<<ball.getState()[1]<<" "<<ball.getState()[2]<<std::endl;

}
