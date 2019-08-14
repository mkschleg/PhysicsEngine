

#include "renderer.h"

#include <SDL.h>


namespace SDL{

  Renderer::Renderer():renderer(nullptr){}

  Renderer::Renderer(const Window& window, int index, Uint32 flags){
    //SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags)
    renderer.reset(SDL_CreateRenderer(window.window.get(), index, flags), SDL_DestroyRenderer);
    if (renderer == nullptr) renderer.reset(SDL_GetRenderer(window.window.get()), SDL_DestroyRenderer);
    // if (renderer == nullptr) throw (SDLException("Renderer null __file__ at line __line__"));
  }

  Renderer::Renderer(Renderer&& rend){
    renderer = rend.renderer;
    rend.renderer = nullptr;
  }

  Renderer::Renderer(SDL_Renderer* rend){
    renderer.reset(rend, SDL_DestroyRenderer);
  }

  std::shared_ptr<SDL_Renderer> Renderer::get(){
    return renderer;
  }

  void Renderer::present(){
    if(renderer != nullptr) SDL_RenderPresent(renderer.get());
    else ; //Throw an error?
  }

  void Renderer::clear(){
    if (renderer != nullptr) SDL_RenderClear(renderer.get());
  }

  void Renderer::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    //SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect)
    uint8_t pr,pg,pb,pa;
    SDL_GetRenderDrawColor(renderer.get(), &pr, &pg, &pb, &pa);
    SDL_SetRenderDrawColor(renderer.get(), r,g,b, a);
    clear();
    SDL_SetRenderDrawColor(renderer.get(), pr, pg, pb, pa);
  }

  void Renderer::operator=(Renderer&& rhs){
    if(renderer != nullptr) SDL_DestroyRenderer(renderer.get());
    renderer = rhs.renderer;
    rhs.renderer = nullptr;
  }

  SDL_Renderer* Renderer::getRaw(){
    return renderer.get();
  }

}
