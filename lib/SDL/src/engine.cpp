

#include "engine.h"
#include "log.h"
#include "exception.h"
#include <SDL.h>
#include <SDL_image.h>


namespace SDL{
  
  

Engine::Engine(){
  screenSurface = nullptr;
  running = true;
}

//onExecute

int Engine::onExecute(){
  try{
    onInit();
    Log::LOG("InitDone");
    // SDL_Event Event;

    while(running){
      onLoop();
    }

    onCleanup();
  } catch(Exception& e){
    std::cerr<<e<<std::endl;
    return 1;
  } catch(EngineException& e){
    std::cerr<<e<<std::endl;
    return 1;
  } catch(std::exception& e){
    std::cerr<<e.what()<<std::endl;
    return 1;
  }
  return 0;
}

//Initialize

void Engine::onInit(){

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    //Log::SDL_ReportError("Failed at SDL_Init()");
    throw Exception("Failed at SDL_Init()");
    //return false;
  }

  window = SDL::Window("Engine",SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);


  if(window.get() == nullptr){
    //throw SDLException("Failed at SDL_CreateWindow(...)");
    // std::cout<<__func__<<" "<<__FILE__<<" "<<__LINE__<<std::endl;
    throw Exception("Failed at SDL_CreateWindow(...)");
  }

  renderer = std::make_shared<SDL::Renderer>(window, -1, SDL_RENDERER_ACCELERATED);

  Log::LOG("Created Renderer");
  // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

  if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
    throw IMGException(Error() + "Failed at IMG_Init(...)");
  }

  // try{loadMedia();}
  // catch(SDLException& e){
  //   e+=Error() + "Failed at loadMedia in onInit()";
  //   throw e;
  // } catch(std::exception& e){
  //   throw e;
  // }

  currentTime = SDL_GetTicks();
  frames = 0;

  // scene.onQuit();
  
  fpsTimer.start();

  return;

}

//Check for Events

void Engine::onEvent(SDL_Event* event){
  // SceneManager::onEvent(event);
  // SceneManager::sendEvent(event);
  EventResponder::onEvent(event);
}

void Engine::onQuit(){
  // std::cout<<"Quit Function!"<<std::endl;
  Log::LOG("Quit Function");
  running = false;
}

void Engine::onKeyDown(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod){
  switch (kcode){
  case SDLK_q:
    //onQuit();
    {
    SDL_Event * event = new SDL_Event();
    event->type = SDL_QUIT;
    SDL_PushEvent(event);
    }
    break;
  case SDLK_LSHIFT: case SDLK_RSHIFT:
    Log::LOG("Key: shift");
    break;
  // case SDLK_UP:
  //   Log::LOG("Key: UP");
  //   pushScene(std::make_shared<Scene>(this, 255, 0, 0));
  //   break;
  // case SDLK_DOWN:
  //   Log::LOG("Key: Down");
  //   popScene();
  //   break;
  // case SDLK_RIGHT:
  //   Log::LOG("Key: Right");
  //   changeScene(std::make_shared<Scene>(this, 0, 255, 0));
  //   break;
  case SDLK_LEFT:
    Log::LOG("Key: Left");
    break;
  default:
    char c = kcode;
    if(mod & KMOD_SHIFT){
      c -= 32;
    }
    std::string s = "Key: ";
    s.push_back(c);
    Log::LOG(s + " Mod: " + std::to_string(mod));
    break;
  }
}

void Engine::onWindowClose(){
  Log::LOG("Window Close Event");
}

//On a loop

void Engine::onLoop(int FPS){
  // SceneManager::onUpdate();
  capTimer.start();
  int SCREEN_TICKS_PER_FRAME = 1000 / FPS;
  float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
  if( avgFPS > 2000000 )
  {
    avgFPS = 0;
  }

  SDL_Event Event;
  while(SDL_PollEvent(&Event)){
    onEvent(&Event);
  }
  //onLoop();
  onRender();
  ++countedFrames;
  int frameTicks = capTimer.getTicks();
  if( frameTicks < SCREEN_TICKS_PER_FRAME ) {
    //Wait remaining time
    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
  }
}

//When Rendered

void Engine::onRender(){
  SDL_SetRenderDrawColor(renderer->getRaw(), 0,0,0,255);
  renderer->clear();
  // texture->render(0, 0);
  // t2->render(50, 0);
  // SceneManager::onRender();

  for(auto& d: drawables){
    d->draw(renderer);
  }

  
  renderer->present();
}

//Cleanup

void Engine::onCleanup(){

  screenSurface = nullptr;

  SDL_Quit();
}

void Engine::registerDrawable(drawable* d){
  drawables.push_back(d);
}

int Engine::getWidth(){
  return width;
}

int Engine::getHeight(){
  return height;
}


//PRIVATE FUNCTIONS

//Load the media for the game.
// void Engine::loadMedia(){
// 
//   try{
//     //imageSurface = loadSurface("images/tileSet.png");
//     textureManager.registerTextureFromPath("images/tileSet.png", "tileSet", renderer);
//     textureManager.registerTextureFromPath("images/char.png", "char", renderer);
//     texture = textureManager.getTexture("tileSet");
//     t2 = textureManager.getTexture("char");
//   } catch(SDLException &e){
//     //e+= std::string(__func__) + "() " + std::to_string(__LINE__) + ": " +"Load media failed";
//     e += "Load media failed";
//     throw e;
//   } catch(std::exception &e){
//     throw e;
//   }
// 
//   return;
// 
// 
// }

// Engine& Engine::getInstance(){
//   static Engine instance;
//   return instance;
// }


}
