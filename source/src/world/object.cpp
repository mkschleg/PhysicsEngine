#include "world"
// #include "force"
#include "ode"
#include "math"
#include <list>
// #include "world.h"


namespace Physics{

// class World;
// 
// class Object;

// class ObjectODE: public ODE{
//   // VectorXD state;
// public:
  // ObjectODE::ObjectODE(Object& _obj):obj(_obj), state(4), rate(4){
  // 
  // }
  
  Object::Object(World& _world, double _mass, Physics::Vector2D initPosition, Physics::Vector2D initVel):world(_world), mass(_mass), pos(initPosition), vel(initVel){
    state = VectorXD(4);
    rate = VectorXD(4);
    id = _world.numObjects;
  }

  Vector2D Object::getForce(){
    // for(auto& f: constraints){
    //   applyForce(*f.get());
    // }
    // Vector2D af = appliedForce;
    // appliedForce.set(0,0);
    return appliedForce;
  }


  World& Object::getWorld(){return world;}

  Vector2D Object::getAppliedForce(){return appliedForce;}
  void Object::setAppliedForce(const Physics::Vector2D &_appliedForce){appliedForce = _appliedForce;}

  void Object::applyForce(Force& force){
    //Assume applied to center of mass.
    // if(dynamic){
      appliedForce += force.getForce(*this);
    // }
  }

  void Object::applyForce(Vector2D& force){
    //Assume applied to center of mass.
    // if(dynamic){
      appliedForce += force;
    // }
  }
  Vector2D Object::getPosition() const { return pos; }
  void Object::setPosition(const Vector2D _pos){ pos = _pos; }
  Vector2D Object::getVelocity() const { return vel; }
  void Object::setVelocity(const Vector2D _vel){ vel = _vel; }
  
  const double Object::getMass() const {return mass;}

  VectorXD Object::getState(){
    state[0] = pos.getX();
    state[1] = pos.getY();
    state[2] = vel.getX();
    state[3] = vel.getY();
    return state;
  }
  VectorXD Object::getRate(const VectorXD& _state){
    Vector2D forces = getForce()/mass;
    rate[0] = _state[2];
    rate[1] = _state[3];
    rate[2] = forces.getX();
    rate[3] = forces.getY();
    // std::cout<<forces.getY()<<std::endl;
    return rate;
  }
  void Object::setState(const VectorXD& _state){
    state = _state;
    // std::cout<<_state[1]<<std::endl;
    // if(dynamic){
      pos = Vector2D(state[0], state[1]);
      vel = Vector2D(state[2], state[3]);
    // }
  }
  size_t Object::size(){
    return state.size();
  }



// 
// 
// 
// };
} //namespace Physics
