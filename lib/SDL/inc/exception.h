#ifndef _SDL_EXCEPTION_H
#define _SDL_EXCEPTION_H

#include <string>
#include <vector>
#include <exception>

// #define GET_PLACE() std::string(__FILE__) + ": " + std::to_string(__LINE__) + " [" + __func__ + "]"

namespace SDL{

  class Exception: public std::exception{
  protected:
    std::vector<std::string> trace;
  public:
    Exception();
    Exception(const std::string& msg, const std::string& place = "", const std::string& error = "");
    Exception(const Exception& e);
    Exception(Exception&& e);
    
    virtual std::string type() const throw();
    virtual const char* what() const throw();
    
    void operator+=(const std::string& rhs);
    void operator+=(const Exception& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Exception& rhs);
    
  };
  
  //std::ostream& operator<<(std::ostream& os, const SDLException& rhs);
  
  
  class IMGException: public Exception{
  public:
    IMGException();
    IMGException(const std::string& msg, const std::string& place = "", const std::string& error = "");
    IMGException(IMGException& e);
    IMGException(IMGException&& e);
    virtual std::string type() const throw();
  };
  
  class EngineException: public std::exception{
  protected:
    std::vector<std::string> trace;
  public:
    EngineException();
    EngineException(const std::string& msg, const std::string& place = "", const std::string& error = "");
    EngineException(const EngineException& e);
    EngineException(EngineException&& e);
    
    virtual std::string type() const throw();
    virtual const char* what() const throw();
    
    void operator+=(const std::string& rhs);
    void operator+=(const EngineException& rhs);
    friend std::ostream& operator<<(std::ostream& os, const EngineException& rhs);
  };

}
#endif
