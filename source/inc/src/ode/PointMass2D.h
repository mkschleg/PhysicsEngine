#ifndef _PHYSICS_POINTMASS2D_H
#define _PHYSICS_POINTMASS2D_H

#include "pvector"
#include "../vector/Vector2D.h"
#include "ODE.h"

namespace Physics{
  
  class PointMass2D: public ODE{
  protected:
    Vector2D pos;
    Vector2D vel;
    double mass;
    // Vector state;
    PointMass2D(Vector2D _pos, Vector2D _vel):pos(_pos),vel(_vel){}

  public:
    
    // virtual Vector getRate(const Vector& state) = 0;

    virtual Vector2D getForce() = 0;

    VectorXD getState(){
      VectorXD state(4);
      state[0] = pos.getX();
      state[1] = pos.getY();
      state[2] = vel.getX();
      state[3] = vel.getY();
      return state;
    }
    VectorXD getRate(const VectorXD& state){
      VectorXD rate(4);
      
      rate[0] = vel.getX();
      rate[1] = vel.getY();

      Vector2D a = getForce();
      rate[2] = a.getX();
      rate[3] = a.getY();
      



      return rate;
    }

    void setState(const VectorXD& _state){
      pos.setX(_state[0]);
      pos.setY(_state[1]);
      vel.setX(_state[2]);
      vel.setY(_state[3]);

      // pos.set(_state[0],_state[1]);

      // state = _state;
    }
    size_t size(){
      return 4;
    }



    Vector2D getPostion() {return pos;}
    void setPosition(const Vector2D& _pos) {pos = _pos;}
    Vector2D getVelocity() {return vel;}
    void setVelocity(const Vector2D& _vel) {vel = _vel;}
  };


}


#endif
