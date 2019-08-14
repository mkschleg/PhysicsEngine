
#include "event.h"

#include <SDL.h>

namespace SDL{
  void EventResponder::onEvent(SDL_Event* event){
    switch(event->type){
    case SDL_QUIT:
      onQuit();
      for(auto& l: listeners){
        l->onQuit();
      }
      break;
    case SDL_WINDOWEVENT:
      onWindowEvent((event->window));
      break;
    case SDL_KEYDOWN:
      onKeyDown(event->key.keysym.sym, event->key.keysym.scancode, event->key.keysym.mod);
      for(auto& l: listeners){
        l->onKeyDown(event->key.keysym.sym, event->key.keysym.scancode, event->key.keysym.mod);
      }
      break;
    case SDL_KEYUP:
      onKeyUp(event->key.keysym.sym, event->key.keysym.scancode, event->key.keysym.mod);
      for(auto& l: listeners){
        l->onKeyUp(event->key.keysym.sym, event->key.keysym.scancode, event->key.keysym.mod);
      }
      break;
    case SDL_TEXTEDITING:
      onTextEditing(event->edit.text, event->edit.start, event->edit.length);
      for(auto& l: listeners){
        l->onTextEditing(event->edit.text, event->edit.start, event->edit.length);
      }
      break;
    case SDL_TEXTINPUT:
      onTextInput(event->text.text);
      for(auto& l: listeners){
        l->onTextInput(event->text.text);
      }
      break;
    case SDL_MOUSEMOTION:
      onMouseMoved(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
      for(auto& l: listeners){
        l->onMouseMoved(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      onMouseDown(event->button.x, event->button.y, MouseButton(event->button.button));
      for(auto& l: listeners){
        l->onMouseDown(event->button.x, event->button.y, MouseButton(event->button.button));
      }
      break;
    case SDL_MOUSEBUTTONUP:
      onMouseUp(event->button.x, event->button.y, MouseButton(event->button.button));
      for(auto& l: listeners){
        l->onMouseUp(event->button.x, event->button.y, MouseButton(event->button.button));
      }
      break;
    case SDL_JOYAXISMOTION: case SDL_JOYBALLMOTION: case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP: case SDL_JOYDEVICEADDED:
    case SDL_JOYDEVICEREMOVED: case SDL_JOYHATMOTION:
      onJoystickEvent(event);
      for(auto& l: listeners){
        l->onJoystickEvent(event);
      }
      break;
    case SDL_CONTROLLERAXISMOTION: case SDL_CONTROLLERBUTTONDOWN: case SDL_CONTROLLERBUTTONUP: case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERDEVICEREMAPPED: case SDL_CONTROLLERDEVICEREMOVED:
      onControllerEvent(event);
      for(auto& l: listeners){
        l->onControllerEvent(event);
      }
      break;
    }
  }

  void EventResponder::registerEventListener(EventListener* listener){
    listeners.push_back(listener);
  }
  
  void EventResponder::onWindowEvent(SDL_WindowEvent& event){
    //GO Through Window Event Types and Run appropriate function.
    // std::cout<<"Window Event: "<<event.event<<" "<<SDL_WINDOWEVENT_SHOWN<<std::endl;
    switch(event.event){
    case SDL_WINDOWEVENT_SHOWN:
      onWindowShown();
      break;
    case SDL_WINDOWEVENT_HIDDEN:
      onWindowHidden();
      break;
    case SDL_WINDOWEVENT_EXPOSED:
      onWindowExposed();
      break;
    case SDL_WINDOWEVENT_MOVED:
      onWindowMove(event.data1, event.data2);
      break;
    case SDL_WINDOWEVENT_RESIZED:
      onWindowResize(event.data1, event.data2);
      break;
    case SDL_WINDOWEVENT_MINIMIZED:
      onWindowMinimized();
      break;
    case SDL_WINDOWEVENT_MAXIMIZED:
      onWindowMaximized();
      break;
    case SDL_WINDOWEVENT_RESTORED:
      onWindowRestored();
      break;
    case SDL_WINDOWEVENT_ENTER:
      onWindowMouseEnter();
      break;
    case SDL_WINDOWEVENT_LEAVE:
      onWindowMouseLeave();
      break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      onWindowKeyboardFocus();
      break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
      onWindowKeyboardBlur();
      break;
    case SDL_WINDOWEVENT_CLOSE:
      onWindowClose();
      break;
    }
  }


}
