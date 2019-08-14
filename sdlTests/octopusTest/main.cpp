#include "world"
#include "math"
#include "SDL/SDL"
#include "octopus"

class OctopusDrawable: public SDL::drawable, public SDL::EventListener{
public:
  OctopusDrawable(SDL::Engine& _engine, std::shared_ptr<Octopus::Arm> _arm):arm(_arm),engine(_engine){}
  std::shared_ptr<Octopus::Arm> arm;
  SDL::Engine& engine;
  void draw(std::shared_ptr<SDL::Renderer>& renderer) override final{
    renderer->fill(0x00,0x00,0xFF,0xFF);
    int width = engine.getWidth();
    int height = engine.getHeight();

    SDL_Rect fillRect = { 0,0,0,0};
    
    int i = 0;

    for(const auto& n: arm->getNodes()){
      Vector2D pos = n->getPosition();
      fillRect = { width/2 - int(40*pos.getX()), height/2 - int(40*pos.getY()), 4, 4};
      SDL_SetRenderDrawColor( renderer->getRaw(), 0xFF, 0xFF, 0x00, 0xFF );
      SDL_RenderDrawRect( renderer->getRaw(), &fillRect );
      i++;
    }
  }
  
  void onKeyDown(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod) override final{
    switch (kcode){
    case SDLK_LSHIFT:
      for(auto& c: arm->getCompartments()){
        c->setAction(0, 1, 0);
      }
      break;
    case SDLK_RIGHT:
      for(auto& c: arm->getCompartments()){
        c->setAction(0, 1, 1);
      }
      break;
    case SDLK_LEFT:
      // Log::LOG("Key: Left");
      // std::cout<<("Key: left")<<std::endl;
      for(auto& c: arm->getCompartments()){
        c->setAction(1, 1, 0);
      }
      break;
    case SDLK_a:
      for(int i = 0; i < arm->getCompartments().size()/2; i++){
        arm->getCompartments()[i]->setAction(1,0,0);
      }
      break;
    case SDLK_d:
      for(int i = 0; i < arm->getCompartments().size()/2; i++){
        arm->getCompartments()[i]->setAction(0,0,1);
      }
      break;
    case SDLK_s:
      for(int i = 0; i < arm->getCompartments().size()/2; i++){
        arm->getCompartments()[i]->setAction(0,0,1);
      }
      for(int i = arm->getCompartments().size()/2 + 1; i < arm->getCompartments().size(); i++){
        arm->getCompartments()[i]->setAction(1,0,0);
      }
      break;
    default:
      break;
    }
  }
  void onKeyUp(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod) override final{
    for(auto& c: arm->getCompartments()){
      c->setAction(0, 0, 0);
    }
  }

};



int main(){

  Physics::World world;
  world.createForce<Physics::Gravity2D>(Octopus::Constants::Gravity);
  world.createForce<Octopus::BouyancyForce>(Octopus::Constants::SurfaceLevel, Octopus::Constants::Gravity);
  // world.createForce<Octopus::SphericalFrictionForce>();
  // double mass =1;
  
  std::shared_ptr<Octopus::Arm> arm = std::make_shared<Octopus::Arm>(world);

  SDL::Engine engine;
  OctopusDrawable od(engine,arm);
  engine.registerDrawable(&od);
  engine.registerEventListener(&od);
  engine.onInit();

  double dt = 0.1;

  // int armCount = 0;
  // for(int i = 0; i < 1000000; i++){
  //   if(i % 10000 == 0) std::cout<<i<<"\r"<<std::flush;
  //   world.step(dt);
  // }
  while(engine.isRunning()){
  
    // if(armCount == 200){
    //   for(auto& c: arm->getCompartments()){
    //     c->setAction(0, 0, 1);
    //   }
    // } if(armCount == 400){
    //   for(auto& c: arm->getCompartments()){
    //     c->setAction(1, 0, 0);
    //   }
    //   armCount = 0;
    // }
    for(int i = 0; i < 10; i++){
      world.step(dt);
    }
    engine.onLoop();
    // SDL_Delay(60);
    // armCount++;
  }
  
  engine.onCleanup();



}
