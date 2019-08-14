#ifndef _PHYSICS_BODY_H
#define _PHYSICS_BODY_H

// #include "force"
#include "ode"
#include "math"
#include "misc"
#include "force.h"
#include <list>
#include <type_traits>
// #include "world.h"


namespace Physics{
  
class World;

class Object;

class ObjectODE: public ODE{
  Object& obj;
  VectorXD state, rate;
public:
  ObjectODE(Object& _obj);
  VectorXD getState() override final;
  VectorXD getRate(const VectorXD& state) override final;
  void setState(const VectorXD& _state) override final;
  size_t size() override final;
};

class Object: public ODE {
  friend class ObjectODE;
protected:
  
  VectorXD state, rate;
  World& world;
  double mass = 0.1;

  Vector2D pos;
  // Vector2D rot;
  Vector2D vel;
  // Vector2D angVel;

  // ObjectODE ode;

  Vector2D appliedForce;

  bool dynamic = true;

  int id;

  // std::list<std::shared_ptr<Object>> children;
  std::list<std::shared_ptr<Force>> constraints;

  // bool rotationLocked;


public:
  // Object(World& _world, std::shared_ptr<Object>)
  // Object(Object* _parent, double mass):world(_parent->getWorld()),ode(*this),mass(mass){}
  Object(World& _world, double _mass, Physics::Vector2D initPosition, Physics::Vector2D initVel);
  ~Object(){ std::cout<< "destroy" <<std::endl;}
  Vector2D getAppliedForce();
  void setAppliedForce(const Vector2D& _appliedForce);
  void applyForce(Force& force);
  void applyForce(Vector2D& force);
  // void applyForce(Force& force, const Vector2D& point);
  virtual Vector2D getForce();

  Vector2D getPosition() const;
  void setPosition(const Vector2D _pos);

  Vector2D getVelocity() const;
  void setVelocity(const Vector2D _vel);


  std::vector<std::shared_ptr<Object>>& getChildren();

  World& getWorld();
  const World& getWorld() const;
  
  const double getMass() const;
  void setMass(double m);
  // template<typename ObjType, typename ...Args>
  // std::shared_ptr<ObjType> addChild(Args... args){
  //   children.push_back(Memory::make_shared<ObjType>(this, args...));
  //   return children.back();
  // }
  
  bool isDynamic(){return dynamic;}
  void setDynamic(bool _dynamic){dynamic=_dynamic;}
  
  int getID() const {return id;}

  template <typename ForceType, typename ...Args>
  std::shared_ptr<ForceType> addConstraint(Args... args){
    static_assert(std::is_base_of<Force, ForceType>::value, "Constraint needs to have a base of Force right now.");
    constraints.push_back(Memory::make_shared<ForceType>(args...));
    return constraints.back();
  }
  
  VectorXD getState() override;
  VectorXD getRate(const VectorXD& state) override;
  void setState(const VectorXD& _state) override;
  size_t size() override;
  
};
} //namespace Physics
#endif
