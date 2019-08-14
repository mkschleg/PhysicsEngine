#include "octopus"


namespace Octopus{

  Arm::Arm(Physics::World& world){
    
    // Vector2D pos = Vector2D(Constants::Initial::Nodes::X[0],Constants::Initial::Nodes::LowerY);
    // Vector2D vel = Vector2D(0,0);

    sptr<Object> lowerFirst = world.createObject<ConstrainedObject>(Constants::Initial::Nodes::Mass[0],
                                                        Vector2D(Constants::Initial::Nodes::X[0],Constants::Initial::Nodes::LowerY),
                                                        Vector2D(0,0));
                                                        // Vector2D(0,0));
    // lowerFirst->setPosition(Vector2D(Constants::Initial::Nodes::X[0],Constants::Initial::Nodes::LowerY));
    // lowerFirst->setVelocity(Vector2D(0,0));
    // lowerFirst->setDynamic(false);



    sptr<Object> upperFirst = world.createObject<RotationConstrainedObject>(Constants::Initial::Nodes::Mass[0],
                                                                            Vector2D(Constants::Initial::Nodes::X[0],Constants::Initial::Nodes::UpperY),
                                                                            Vector2D(0,0),
                                                                            lowerFirst);
    // upperFirst->setPosition(Vector2D(Constants::Initial::Nodes::X[0],Constants::Initial::Nodes::UpperY));
    // upperFirst->setVelocity(Vector2D(0,0));

    // for(int n = 1; n < Constants::Initial::Nodes::NumPairs; n++){
    //
    // }
    //
    
    upperNodes.push_back(upperFirst);
    lowerNodes.push_back(lowerFirst);

    // nodes.push_back(lowerFirst);
    // nodes.push_back(upperFirst);
    // 
    for(int n = 1; n < Constants::Initial::Nodes::NumPairs; n++){
      sptr<Object> upper = world.createObject<Object>(Constants::Initial::Nodes::Mass[n],
                                                          Vector2D(Constants::Initial::Nodes::X[n],Constants::Initial::Nodes::UpperY),
                                                          Vector2D(0,0));
      sptr<Object> lower = world.createObject<Object>(Constants::Initial::Nodes::Mass[n],
                                                          Vector2D(Constants::Initial::Nodes::X[n],Constants::Initial::Nodes::LowerY),
                                                          Vector2D(0,0));
      upperNodes.push_back(std::move(upper));
      lowerNodes.push_back(std::move(lower));

    }
    


    // nodes.append(upperNodes.begin(), upperNodes.end())
    nodes.insert(nodes.begin(), upperNodes.begin(), upperNodes.end());
    nodes.insert(nodes.end(), lowerNodes.begin(), lowerNodes.end());
    // sptr<LongitudinalMuscleConstraint> c = world.createConstraint<LongitudinalMuscleConstraint>(upperFirst, upperSecond, Constants::Initial::Nodes::X[1] - Constants::Initial::Nodes::X[0]);
    //
    // upperNodes.push_back(upperSecond);
    // nodes.push_back(upperSecond);
    // 
    // sptr<Physics::Constraint> mc = Physics::Memory::make_shared<LongitudinalMuscleConstraint>(upperFirst, upperSecond, Constants::Initial::Nodes::X[1] - Constants::Initial::Nodes::X[0]);
    // sptr<Physics::Constraint> c = mc;
    // Physics::Constraint* c = (new LongitudinalMuscleConstraint(upperFirst, upperSecond, Constants::Initial::Nodes::X[1] - Constants::Initial::Nodes::X[0]));
    
    for(int i = 1; i < upperNodes.size(); i++){
      compartments.push_back(Physics::Memory::make_shared<Compartment>(world,upperNodes[i-1], upperNodes[i], lowerNodes[i], lowerNodes[i-1]));
      // compartments.back()->pressure = world.createConstraint<PressureConstraint>(upperNodes[i-1], upperNodes[i], lowerNodes[i], lowerNodes[i-1],Constants::Pressure);
      // compartments[i-1]->setAction(1,0,0);
    }

    for(int i = 0; i < nodes.size(); i++){
      world.createForce<RepulsionForce>(nodes[i]);
    }

  }

  std::vector<sptr<Compartment>>& Arm::getCompartments(){return compartments;}
  std::vector<sptr<Object>>& Arm::getNodes(){return nodes;}

}//namespace octopus
