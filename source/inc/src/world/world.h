#ifndef _PHYSICS_WORLD_H
#define _PHYSICS_WORLD_H

// #include "force"
#include "force.h"
#include "constraint.h"
#include "misc"
#include "ode"
#include <list>



namespace Physics{
  class Object;
  class World{
    friend class Object;
    std::list<sptr<Force>> forces;
    std::list<sptr<Constraint>> constraints;
    std::list<sptr<Object>> objects;
    uptr<ODESolver> solver;

    // std::vector<std::unique_ptr<Force>> worldForces;
    // std::vector<std::unique_ptr<Body>> bodies;
  public:
    
    int numObjects = 0;

    World();

    template<typename ForceType, typename ...Args>
    sptr<Force> createForce(Args&&... args){
      forces.push_back(Memory::make_shared<ForceType>(std::forward<Args>(args)...));
      return forces.back();
    }

    void destroyForce(sptr<Force> force);

    template<typename ObjectType, typename ...Args>
    sptr<Object> createObject(Args&&... args){
      // bodies.push_back(BodyType(std::forward<Args...>(args...)));
      // objects.push_back(Memory::make_shared<ObjectType>(std::forward<World&>(*this),std::forward<Args...>(args...)));
      // objects.push_back(Memo)
      objects.push_back(Memory::make_shared<ObjectType>(std::forward<World&>(*this),std::forward<Args>(args)...));
      numObjects++;
      return objects.back();
    }

    template<typename ConstraintType, typename ...Args>
    sptr<ConstraintType> createConstraint(Args&&... args){
      sptr<ConstraintType> c = Memory::make_shared<ConstraintType>(std::forward<Args>(args)...);
      constraints.push_back(c);
      return c;
    }

    void destroyObject(sptr<Object>& object);
    void destroyConstraint(sptr<Constraint>& constraint);
    void destroyForce(sptr<Force>& force);

    const size_t getObjectCount() const;

    void step(double dt);


  };
}



#endif
