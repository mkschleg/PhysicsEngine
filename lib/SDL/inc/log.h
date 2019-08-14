#ifndef _LOG_H_
#define _LOG_H_


#include <string>
#include <iostream>

//error, warn, info, debug, trace

#ifndef LOGLEVEL
#define LOGLEVEL 0
#endif

// constexpr enum levels{error, warn, info};


// #define _DEBUG 1

//#define Error(s) (std::string(__func__) + "() " + std::string(__LINE__) + ": " + s)
#define Error() "[" + std::string(__func__) + "] " + std::to_string(__LINE__) + ": "
#define LLOG(msg) Log::LOG(msg, __func__, __LINE__)



namespace Log{
  inline void LOG(const std::string& message, const char* file, int line){std::cout<<"["<<file<<"] "<<line<<": "<<"Log: "<<message<<std::endl;}
  inline void LOG(const std::string& message){std::cout<<"Log: "<<message<<std::endl;}
  inline void DEBUG(const std::string& message){std::cout<<"Debug Message: "<<message<<std::endl;}
  inline void RTERROR(const std::string& message){std::cout<<"Runtime Error: "<<message<<std::endl;}
};


#endif
