#ifndef _SDL_EVENT_H
#define _SDL_EVENT_H
  
#include <SDL.h>
#include <vector>

namespace SDL{
  
  enum MouseButton:Uint8{
    Left = SDL_BUTTON_LEFT,
    Right = SDL_BUTTON_RIGHT,
    Middle = SDL_BUTTON_MIDDLE,
    X1 = SDL_BUTTON_X1,
    X2 = SDL_BUTTON_X2
  };
  
  class EventListener;

  class EventResponder{
    friend class EventListener;
  public:
    void onEvent(SDL_Event* event);
    
    void registerEventListener(EventListener* listener);

  private:

    std::vector<EventListener*> listeners;

    void onWindowEvent(SDL_WindowEvent& event);
    
    virtual void onQuit(){}
    
    virtual void onWindowResize(int width, int height){}
    virtual void onWindowClose(){}
    virtual void onWindowMove(int x, int y){}
    
    virtual void onWindowShown(){}
    virtual void onWindowHidden(){}
    virtual void onWindowExposed(){}
    
    virtual void onWindowMinimized(){}
    virtual void onWindowMaximized(){}
    virtual void onWindowRestored(){}
    
    virtual void onWindowMouseEnter(){}
    virtual void onWindowMouseLeave(){}
    virtual void onWindowKeyboardFocus(){}
    virtual void onWindowKeyboardBlur(){}
    
    virtual void onKeyDown(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod){}
    virtual void onKeyUp(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod){}
    
    virtual void onTextEditing(char* text, int start, int end){}
    virtual void onTextInput(char* text){}
    
    virtual void onMouseMoved(int x, int y, int relx, int rely){}
    virtual void onMouseDragged(int x, int y, int relx, int rely, MouseButton button){}
    
    virtual void onMouseDown(int x, int y, MouseButton button){}
    virtual void onMouseUp(int x, int y, MouseButton button){}
    
    // virtual void onControllerAxis();
    // virtual void onControllerButtonDown();
    // virtual void onControllerButtonUp();
    virtual void onControllerEvent(SDL_Event* event){}
    virtual void onJoystickEvent(SDL_Event* event){}
    
  }; // class EventResponder
  
  class EventListener{
    // friend class EventManager;
  public:
    
    // void onWindowEvent(SDL_WindowEvent& event);
    
    virtual void onQuit(){}
    
    virtual void onWindowResize(int width, int height){}
    virtual void onWindowClose(){}
    virtual void onWindowMove(int x, int y){}
    
    virtual void onWindowShown(){}
    virtual void onWindowHidden(){}
    virtual void onWindowExposed(){}
    
    virtual void onWindowMinimized(){}
    virtual void onWindowMaximized(){}
    virtual void onWindowRestored(){}
    
    virtual void onWindowMouseEnter(){}
    virtual void onWindowMouseLeave(){}
    virtual void onWindowKeyboardFocus(){}
    virtual void onWindowKeyboardBlur(){}
    
    virtual void onKeyDown(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod){}
    virtual void onKeyUp(SDL_Keycode kcode, SDL_Scancode scode, uint16_t mod){}
    
    virtual void onTextEditing(char* text, int start, int end){}
    virtual void onTextInput(char* text){}
    
    virtual void onMouseMoved(int x, int y, int relx, int rely){}
    virtual void onMouseDragged(int x, int y, int relx, int rely, MouseButton button){}
    
    virtual void onMouseDown(int x, int y, MouseButton button){}
    virtual void onMouseUp(int x, int y, MouseButton button){}
    
    // virtual void onControllerAxis();
    // virtual void onControllerButtonDown();
    // virtual void onControllerButtonUp();
    virtual void onControllerEvent(SDL_Event* event){}
    virtual void onJoystickEvent(SDL_Event* event){}
    
  }; // class EventResponder

}//namespace SDL

#endif
