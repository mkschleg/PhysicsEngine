#ifndef _SDL_ENGINE_H
#define _SDL_ENGINE_H

#include "renderer.h"
#include "window.h"
#include "event.h"
#include "misc.h"
#include "drawable.h"
#include "timer.h"

#include <vector>

namespace SDL{
  
  class Engine: public EventResponder{
    
  public:
    
    Engine();
    
    int onExecute();

    void onInit();

    void onEvent(SDL_Event* event);
    void onLoop(int FPS = 60);
    void onRender();
    void onCleanup();

    void reportError(std::string);

    Uint64 currentTime;
    Uint64 lastTime;
    int frames;

    int getHeight();
    int getWidth();


    void registerDrawable(drawable* d);
    
    bool isRunning(){return running;}
    //TextureManager textureManager;
    //Scene scene;
    
    //I don't have memory control of this object.
    std::vector<drawable*> drawables;
    
    //The frames per second timer
    Timer fpsTimer;
    
    //The frames per second cap timer
    Timer capTimer;
    
    int countedFrames = 0;

  private:


    //Singleton of SDLEngine
    //static SDLEngine engineInstance;
    
    //Screen and Width of screen
    //  - Currently const but when setting resolutions this will need to be updated.
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 960;
    
    size_t width = 1280;
    size_t height = 960;
    
    //Tell whether or not the engine is running
    bool running;
    //SDL_Window reference
    // SDL_Window *window;
    Window window;
    //SDL_Surface for the window
    SDL_Surface *screenSurface;
    //SDL_Renderer
    // SDL_Renderer *renderer;
    std::shared_ptr<SDL::Renderer> renderer;
    



    /**************
    Custom Processing/Variables
    **************/
    // SDL_Surface *imageSurface;
    // std::shared_ptr<Texture> texture;
    // std::shared_ptr<Texture> t2;
    
    //Function to load media on creation of the engine.
    // void loadMedia();
    //Function to load a surface.
    // SDL_Surface *loadSurface(const std::string&);
    // SDL_Texture *loadTexture(const std::string&);

    void onQuit() override;
    void onKeyDown(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod) override;
    void onWindowClose() override;

  };//class Engine
} //namespace SDL
#endif
