
#ifndef _OCTOPUS_PRESSURECONSTRAINT_H
#define _OCTOPUS_PRESSURECONSTRAINT_H


#include "world"
using Physics::sptr;
using Physics::Object;
using Physics::Vector2D;

#include <map>

class PressureConstraint: public Physics::Constraint{

  sptr<Object> d, dt, tv, v;

  double pressure;
  double area;
  double desiredArea;

  std::map<sptr<Object>,Vector2D> forceMap;
  std::vector<sptr<Object>> nodes;
public:
  PressureConstraint(sptr<Object> _d, sptr<Object> _dt, sptr<Object> _tv, sptr<Object> _v, double _pressure):
    d(_d), dt(_dt), tv(_tv), v(_v), pressure(_pressure){
    nodes.push_back(d);
    nodes.push_back(dt);
    nodes.push_back(tv);
    nodes.push_back(v);
    

    Vector2D P = tv->getPosition() - d->getPosition();
    Vector2D Q = dt->getPosition() - v->getPosition();

    area = 0.5*P.rotate90().dot(Q);
    // std::cout<<P<<" "<<Q<<std::endl;
    desiredArea = area;
    // std::cout<<desiredArea<<std::endl;
  }
  
  Vector2D getForce(sptr<Object> obj) override final{ return forceMap.count(obj) != 0 ? forceMap[obj]:Vector2D(0,0); }
  void applyForce() override final{
    // std::cout<<forceMap.size()<<std::endl;
    for(auto& p: forceMap){
      p.first->applyForce(p.second);
    }
  }
  void update( double _dt ) override final{
    
    Vector2D P = tv->getPosition() - d->getPosition();
    Vector2D Q = dt->getPosition() - v->getPosition();

    area = 0.5*P.rotate90().dot(Q);
    
    // std::cout<<area<<std::endl;

    double pressureForce = pressure * (std::abs(area) - std::abs(desiredArea));
     pressureForce = std::copysign(1.0,area)*std::copysign(1.0, pressureForce)*std::sqrt(std::abs(pressureForce));
     for(int i = 0; i < nodes.size(); i++){
       sptr<Object> prevNode = nodes[i];
       sptr<Object> curNode = nodes[(i+1) % nodes.size() ];
       sptr<Object> nextNode = nodes[(i+2) % nodes.size()];

       Vector2D prevVector = (curNode->getPosition() - prevNode->getPosition()).rotate270();
       Vector2D nextVector = (nextNode->getPosition() - curNode->getPosition()).rotate270();

       forceMap[curNode] = (prevVector+nextVector)*pressureForce;
      //  std::cout<<forceMap[curNode]<<std::endl;
      //  std::cout<<"E"<<std::endl;
     }

    // double area =

    // double area = oc->area;
    // double pressureForce = pressure * (std::abs(area) - std::abs(oc->desiredArea));
    // pressureForce = std::copysign(1.0,area)*std::copysign(1.0, pressureForce)*std::sqrt(std::abs(pressureForce));
    // std::cout<<"F "<<oc->nodes.size()<<std::endl;
    // for(int i = 0; i < oc->nodes.size(); i++){
    //   sptr<Object> prevNode = oc->nodes[i];
    //   sptr<Object> curNode = oc->nodes[(i+1) % oc->nodes.size() ];
    //   sptr<Object> nextNode = oc->nodes[(i+2) % oc->nodes.size()];
    //   
    //   Vector2D prevVector = curNode->getPosition() - prevNode->getPosition().rotate270();
    //   Vector2D nextVector = nextNode->getPosition() - curNode->getPosition().rotate270();
    //   
    //   forceMap[curNode] = (prevVector+nextVector)*pressureForce;
    //   std::cout<<"E"<<std::endl;
    // }
  }
};

#endif
