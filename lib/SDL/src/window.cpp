
#include <SDL.h>
#include "window.h"

#include <string>


namespace SDL{


  Window::Window():window(nullptr){}
  Window::Window(SDL_Window* _window):Window(){
    window.reset(_window, SDL_DestroyWindow);
    // std::cout<<window<<std::endl;
  }
  Window::~Window(){}
  Window::Window(SDL::Window&& _window){
    window = _window.window;
    _window.window = nullptr;
  }
  
  void Window::operator=(SDL::Window&& rhs){
    window = rhs.window;
    rhs.window = 0;
  }
  
  Window::Window(const std::string& title, int x, int y, int w, int h, Uint32 flags){
    window = nullptr;
    window.reset(SDL_CreateWindow(title.c_str(), x, y, w, h, flags), SDL_DestroyWindow);
    if(window.get() == nullptr){
      // throw SDLException("Create Window");
      throw "Create Window";
    }
  }
  
  std::shared_ptr<SDL_Window> Window::get(){
    return window;
  }

}//namespace SDL
