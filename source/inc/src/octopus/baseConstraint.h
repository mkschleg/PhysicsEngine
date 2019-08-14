#ifndef _OCTOPUS_BASECONSTRAINT_H
#define _OCTOPUS_BASECONSTRAINT_H
  
#include "world"

using Physics::Vector2D;
using Physics::Object;
using Physics::sptr;

// 
// namespace Octopus{
//   
//   class BaseConstraint: public Physics::Constraint{
//     sptr<Object> staticObj, dynamicObj;
//     double distance;
//     Vector2D force;
//   public:
// 
//     BaseConstraint(sptr<Object> _staticObj, sptr<Object> _dynamicObj, double dist): staticObj(std::move(_staticObj)), dynamicObj(std::move(_dynamicObj)), distance(dist){}
//     
//     //Find tangential force, assume staticOBj has no force acting on it (not always true, should update for non-static version)
// 
//     Vector2D getForce(sptr<Object> obj) override final{
// 
//     }
//     void applyForce() override final{
// 
//     }
//     void update( double dt ) override final{
//     
//     }
// 
// 
// 
//   }; //class BaseConstraint
// }//namespace Octopus



#endif
