#include "octopus"

namespace Octopus{

  // class Compartment{
  // public:
    // class PressureConstraint;
    // class AngleConstraint;

  // private:

    // sptr<Object> d, dt, tv, v;
    // std::vector<sptr<Object>> nodes;
    // sptr<PressureConstraint> pressure;
    // 
    // 
    // sptr<MuscleConstraint> dorsal, traversal, ventral;
    // sptr<AxialFrictionConstraint> dorsalFriction, ventralFriction;
    // //std::vector<sptr<Object>> nodes;
    // 
    // 
    // std::map<sptr<Object>, Vector2D> normals;
    // 
    // 
    // double area;
    // double desiredArea;
    
    void Compartment::computeNormals(){

    }
    void Compartment::computeWeightedNormals(){
    
    }
    
  // public:
    // OctopusCompartment();

    Compartment::Compartment(Physics::World& world, sptr<Object> _d, sptr<Object> _dt, sptr<Object> _tv, sptr<Object> _v)
    : d(std::move(_d)), dt(std::move(_dt)), tv(std::move(_tv)), v(std::move(_v)){
      
      nodes.push_back(d);
      nodes.push_back(dt);
      nodes.push_back(tv);
      nodes.push_back(v);
      
      // std::cout<<nodes.size();

      pressure = world.createConstraint<PressureConstraint>(d,dt,tv,v, Constants::Pressure);

      dorsal = world.createConstraint<LongitudinalMuscleConstraint>(d, dt, (dt->getPosition() - tv->getPosition()).norm());
      transversal = world.createConstraint<TransversalMuscleConstraint>(dt, tv, (dt->getPosition() - d->getPosition()).norm());
      ventral = world.createConstraint<LongitudinalMuscleConstraint>(tv, v, (dt->getPosition() - tv->getPosition()).norm());
      
      dorsalFriction = world.createConstraint<AxialFrictionConstraint>(dt,d);
      ventralFriction = world.createConstraint<AxialFrictionConstraint>(tv,v);

      area = getArea();
      desiredArea = area;

      
    }
    
    void Compartment::setAction(double da, double ta, double va){
      dorsal->activate(da);
      transversal->activate(ta);
      ventral->activate(va);
    }
    
    // void update(double dt);
    double Compartment::getArea(){
      Vector2D P = tv->getPosition() - d->getPosition();
      Vector2D Q = dt->getPosition() - v->getPosition();

      area = 0.5*P.rotate90().dot(Q);

      if(std::copysign(1.0, area) != std::copysign(1.0, desiredArea) && desiredArea != 0){
        std::cerr<<"Compartment has flipped inside out. Area: " + std::to_string(area)<<std::endl;
      }
      
      return area;
    }



}
