
#include "world"
// #include "force"
#include "misc"
#include "ode"

#include <list>



namespace Physics{
  
  World::World():solver(Memory::make_unique<RK4>()){}
  
  void World::destroyForce(std::shared_ptr<Force> force){
    std::remove(forces.begin(), forces.end(), force);
  }
  
  void World::destroyObject(std::shared_ptr<Object>& object){
    std::remove(objects.begin(), objects.end(), object);
  }
  
  const size_t World::getObjectCount() const{
    return objects.size();
  }
  
  
  void World::step(double dt){
    for(auto& obj: objects){
      // if(obj->isDynamic()){
      for(auto& f: forces){
        obj->applyForce(*f);
      }
      // }
    }
    for(auto& cons: constraints){
      // std::cout<<"cons"<<std::endl;
      cons->update(dt);
      cons->applyForce();
    }
    //TODO: World should be a large ODE which we solve once... for now openmp.

    for(auto& obj: objects){
      if(obj->isDynamic()){
        // solver->step(*obj, dt);
        solver->solve(*obj, 0, dt, dt/20.0);
        obj->setAppliedForce(Vector2D(0,0));
      } else {
        obj->setAppliedForce(Vector2D(0,0));
      }
    }
  }
}
