
#include "exception.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace SDL{

  Exception::Exception(){}
  Exception::Exception(const std::string& msg, const std::string& place, const std::string& error):Exception(){
    trace.push_back(place);
    if(error != "") trace[0]+=std::string(" with error: ") + error;
    else trace[0]+=std::string(" with error: ") + SDL_GetError();
  }
  Exception::Exception(const Exception& e):Exception(){
    for(auto err: e.trace) trace.push_back(err);
  }
  Exception::Exception(Exception&& e):Exception(){
    for(auto err: e.trace) trace.push_back(err);
    e.trace.clear();
  }
  
  const char* Exception::what() const throw(){
    return nullptr;
  }
  Exception& operator<<(Exception& lhs, const std::string& rhs){
    lhs += rhs;
    return lhs;
  }
  void Exception::operator+=(const std::string& rhs){
    trace.push_back(rhs);
  }
  void Exception::operator+=(const Exception& rhs){
    for(auto str: rhs.trace) trace.push_back(str);
  }
  std::ostream& operator<<(std::ostream& os, const Exception& rhs){
    os<<rhs.type()<<": ";
    for(auto err: rhs.trace) os<<err<<'\n';
    return os;
  }
  
  std::string Exception::type() const throw(){
    return "SDL Error";
  }
  
  IMGException::IMGException(){}
  IMGException::IMGException(const std::string& msg, const std::string& place, const std::string& error):Exception(msg, place, (error == "")?IMG_GetError():error){}
  IMGException::IMGException(IMGException& e):Exception(e){}
  IMGException::IMGException(IMGException&& e):Exception(std::move(e)){}
  
  std::string IMGException::type() const throw(){
    return "Image Error";
  }
  
  EngineException::EngineException(){}
  EngineException::EngineException(const std::string& msg, const std::string& place, const std::string& error):EngineException(){
    trace.push_back(place);
    if(error != "") trace[0]+=std::string(" with error: ") + error;
    else trace[0]+=std::string(" with unspecified error");
  }
  EngineException::EngineException(const EngineException& e):EngineException(){
    for(auto err: e.trace) trace.push_back(err);
  }
  EngineException::EngineException(EngineException&& e):EngineException(){
    for(auto err: e.trace) trace.push_back(err);
    e.trace.clear();
  }
  
  const char* EngineException::what() const throw(){
    return nullptr;
  }
  EngineException& operator<<(EngineException& lhs, const std::string& rhs){
    lhs += rhs;
    return lhs;
  }
  void EngineException::operator+=(const std::string& rhs){
    trace.push_back(rhs);
  }
  void EngineException::operator+=(const EngineException& rhs){
    for(auto str: rhs.trace) trace.push_back(str);
  }
  std::ostream& operator<<(std::ostream& os, const EngineException& rhs){
    os<<rhs.type()<<": ";
    for(auto err: rhs.trace) os<<err<<'\n';
    return os;
  }
  
  std::string EngineException::type() const throw(){
    return "Engine Exception";
  }

}
