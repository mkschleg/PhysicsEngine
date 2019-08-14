#ifndef _SDL_MISC_H
#define _SDL_MISC_H

#include <memory>
  
namespace SDL{ namespace Memeory{
  
#if __cplusplus > 201103L // After c++11 (as of now c++14 and c++17)

using std::make_unique ;

#else // C++11

template < typename T, typename... CONSTRUCTOR_ARGS >
std::unique_ptr<T> make_unique( CONSTRUCTOR_ARGS&&... constructor_args ) {
  return std::unique_ptr<T>( new T( std::forward<CONSTRUCTOR_ARGS>(constructor_args)... ) );
}

#endif // __cplusplus == 201402L

using std::make_shared;


}} // namespaces SDL::Memory

#endif
