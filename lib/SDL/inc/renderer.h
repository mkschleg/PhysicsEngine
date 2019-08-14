#ifndef _SDL_RENDERER_H
#define _SDL_RENDERER_H

#include <SDL.h>
#include "window.h"
#include "misc.h"

namespace SDL{
  
  class Renderer{
      public:
    Renderer();
    Renderer(const Window& window, int index, Uint32 flags);
      //SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags)
    Renderer(Renderer&& rend);
    Renderer(SDL_Renderer* rend);

    std::shared_ptr<SDL_Renderer> get();

    void present();
    void clear();
    void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    // void setColor(r, g, b, a)
    // void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    //void copy(Texture texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
    //SDL_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)

    void operator=(Renderer&& rhs);

    SDL_Renderer* getRaw();
  protected:
  private:


    std::shared_ptr<SDL_Renderer> renderer;

  };//class Renderer

}// namespace SDL
#endif
