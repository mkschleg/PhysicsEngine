
#include "world"
#include "math"
#include "SDL/SDL"

class BallDrawable: public SDL::drawable{
public:
  BallDrawable(SDL::Engine& _engine, std::shared_ptr<Physics::Object> _obj):obj(_obj),engine(_engine){}
  std::shared_ptr<Physics::Object> obj;
  SDL::Engine& engine;
  void draw(std::shared_ptr<SDL::Renderer>& renderer) override final{
    int width = engine.getWidth();
    int height = engine.getHeight();

    Physics::Vector2D pos = obj->getPosition();

    SDL_Rect fillRect = { width - int(pos.getX()), height - int(pos.getY()), 10,  10};
    // SDL_Rect fillRect = {200,200,100,100};

    SDL_SetRenderDrawColor( renderer->getRaw(), 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRect( renderer->getRaw(), &fillRect );
    // SDL_SetRenderDrawColor( renderer->getRaw(), 0x00, 0x00, 0x00, 0xFF );
  }


};

int main(){

  Physics::World world;
  world.createForce<Physics::Gravity2D>(9.8);
  // double mass =1;
  std::shared_ptr<Physics::Object> obj = world.createObject<Physics::Object>(1.0, Physics::Vector2D(200,400), Physics::Vector2D(0,0));
  std::shared_ptr<Physics::Object> obj2 = world.createObject<Physics::Object>(1.0,Physics::Vector2D(200,400),Physics::Vector2D(50, 0));
  // obj->setPosition(Physics::Vector2D(200,400));
  obj->setDynamic(false);
  // std::shared_ptr<Physics::Object> obj3 = obj->addChild<Physics::Object>(1.0);
  obj2->setPosition(Physics::Vector2D(200,400));
  obj2->setVelocity(Physics::Vector2D(50, 0));
  double dt = 0.15;

  SDL::Engine engine;

  BallDrawable bd(engine,obj);
  BallDrawable bd2(engine,obj2);
  engine.registerDrawable(&bd);
  engine.registerDrawable(&bd2);

  engine.onInit();

  while(obj2->getPosition().getY() > 0 && engine.isRunning()){
    engine.onLoop();
    world.step(dt);
    // SDL_Delay(60);
  }

  engine.onCleanup();



}
