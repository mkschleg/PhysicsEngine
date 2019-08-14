#include "gtest/gtest.h"

#include "world"
// #include "force"
#include "math"

// class myObj

TEST(World, initialTest){

  Physics::World world;
  world.createForce<Physics::Gravity2D>(9.8);
  // double mass =1;
  std::shared_ptr<Physics::Object> obj = world.createObject<Physics::Object>(1.0,Physics::Vector2D(0,10), Physics::Vector2D(0,0));
  std::shared_ptr<Physics::Object> obj2 = world.createObject<Physics::Object>(1.0,Physics::Vector2D(0,10), Physics::Vector2D(0,0));
  // obj->setPosition(Physics::Vector2D(0,10));
  // std::shared_ptr<Physics::Object> obj3 = obj->addChild<Physics::Object>(1.0);
  // obj2->setPosition(Physics::Vector2D(2,10));
  // obj2->setVelocity(Physics::Vector2D(1, 0));
  double dt = 0.01;

  while(obj2->getPosition().getY() > 0){
    world.step(dt);
    // std::cout<<obj->getPosition().getY()<<" "<<obj->getVelocity().getY()<<std::endl;

  }

  std::cout<<obj->getPosition().getX()<<" "<<obj->getPosition().getY()<<" "<<obj->getVelocity().getY()<<std::endl;
  // std::cout<<obj3->getPosition().getX()<<" "<<obj3->getPosition().getY()<<" "<<obj3->getVelocity().getY()<<std::endl;
  std::cout<<obj2->getPosition().getX()<<" "<<obj2->getPosition().getY()<<" "<<obj2->getVelocity().getY()<<std::endl;
}
