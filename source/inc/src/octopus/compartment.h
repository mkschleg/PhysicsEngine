#ifndef _OCTOPUS_COMPARTMENT_H
#define _OCTOPUS_COMPARTMENT_H

#include "muscleConstraint.h"
#include "axialFrictionConstraint.h"
#include "pressureConstraint.h"
#include "world"
#include "math"


#include "misc"

#include <vector>
#include <map>

namespace Octopus{

  class Compartment{
  public:
    // class PressureConstraint;
    class AngleConstraint;

  public:

    sptr<Object> d, dt, tv, v;
    std::vector<sptr<Object>> nodes;
    sptr<PressureConstraint> pressure;


    sptr<MuscleConstraint> dorsal, transversal, ventral;
    sptr<AxialFrictionConstraint> dorsalFriction, ventralFriction;
    //std::vector<sptr<Object>> nodes;


    std::map<sptr<Object>, Vector2D> normals;

    
    double area;
    double desiredArea;
    
    void computeNormals();
    void computeWeightedNormals();
    
  public:
    // OctopusCompartment();

    Compartment(Physics::World& world, sptr<Object> d, sptr<Object> dt, sptr<Object> tv, sptr<Object> v);
    
    void setAction(double da, double ta, double va);
    
    // void update(double dt);
    double getArea();
    
    std::vector<sptr<Object>>& getNodes();

    
    // class PressureConstraint: public Physics::Constraint{
    //   sptr<Compartment> oc;
    //   double pressure;
    //   std::map<sptr<Object>,Vector2D> forceMap;
    //   std::vector<sptr<Object>> nodes;
    // public:
    //   PressureConstraint(const sptr<Compartment>& _oc, double _pressure):oc(_oc),pressure(_pressure){
    // 
    //   }
    //   
    //   Vector2D getForce(sptr<Object> obj) override final{ return forceMap.count(obj) != 0 ? forceMap[obj]:Vector2D(0,0); }
    //   void applyForce() override final{
    //     for(auto& p: forceMap){
    //       p.first->applyForce(p.second);
    //     }
    //   }
    //   void update( double dt ) override final{
    //     double area = oc->area;
    //     double pressureForce = pressure * (std::abs(area) - std::abs(oc->desiredArea));
    //     pressureForce = std::copysign(1.0,area)*std::copysign(1.0, pressureForce)*std::sqrt(std::abs(pressureForce));
    //     std::cout<<"F "<<oc->nodes.size()<<std::endl;
    //     for(int i = 0; i < oc->nodes.size(); i++){
    //       sptr<Object> prevNode = oc->nodes[i];
    //       sptr<Object> curNode = oc->nodes[(i+1) % oc->nodes.size() ];
    //       sptr<Object> nextNode = oc->nodes[(i+2) % oc->nodes.size()];
    //       
    //       Vector2D prevVector = curNode->getPosition() - prevNode->getPosition().rotate270();
    //       Vector2D nextVector = nextNode->getPosition() - curNode->getPosition().rotate270();
    //       
    //       forceMap[curNode] = (prevVector+nextVector)*pressureForce;
    //       std::cout<<"E"<<std::endl;
    //     }
    //   }
    // }; //class PressureConstraint
    class AngleConstraint: public Physics::Constraint{
      Compartment& oc;
      constexpr static double ANGLE_CONSTANT = 0.1 / 90.0;
      constexpr static double NEIGHBOR_ANGLE_SCALE = 0.2;
      sptr<Object> cur, previous, next;
      std::map<sptr<Object>,Vector2D> forceMap;
      
    public:
      AngleConstraint(Compartment& _oc):oc(_oc){}
      Vector2D getForce(sptr<Object> obj) override final{ return forceMap.count(obj) != 0 ? forceMap[obj]:Vector2D(0,0);}
      void applyForce() override final{
        for(auto& p: forceMap){
          p.first->applyForce(p.second);
        }
      }
      void update( double dt ) override final{
        Vector2D prevVector = cur->getPosition() - previous->getPosition();
        Vector2D nextVector = next->getPosition() - cur->getPosition();
        
        double angleRad = std::cos(prevVector.dot(nextVector) / (prevVector.norm()*nextVector.norm()));
        const double c = 180.0/M_PI;
        double angle = angleRad*c;
        if (prevVector.cross(nextVector) > 0){
          angle = 360.0 - angle;
        }
        
        double forceMag = ANGLE_CONSTANT * (angle - 90.0);
        
        forceMap[previous] = prevVector.rotate270().normalize() * NEIGHBOR_ANGLE_SCALE * forceMag;
        forceMap[cur] = oc.normals[cur].normalize() * forceMag;
        forceMap[next] = nextVector.rotate270().normalize() * NEIGHBOR_ANGLE_SCALE * forceMag;
        
      }
    }; //class AngleConstraint
  }; //class Compartment
  
}//namespace Octopus

#endif
