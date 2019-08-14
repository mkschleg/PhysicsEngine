#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

#include "misc.h"
#include <SDL.h>


namespace SDL{

  class Window{
    friend class Renderer;
  public:
    Window();
    ~Window();
    Window(SDL_Window* wind);
    Window(Window&& wind);
    Window(const std::string& title, int x, int y, int w, int h, Uint32 flags);

    void operator=(Window&& rhs);

    std::shared_ptr<SDL_Window> get();

    SDL_Renderer* getRenderer();
    SDL_Surface* getWindowSurface();

  protected:
    //SDL_Window* window;
    std::shared_ptr<SDL_Window> window;
  private:
    Window(const Window&) = default;

  };//class Window

}//namespace SDL


#endif
