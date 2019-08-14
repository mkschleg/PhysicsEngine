#ifndef MAKE_UNIQUE_H_INCLUDED
#define MAKE_UNIQUE_H_INCLUDED

#include <memory>
#include <utility>

namespace Physics{
  namespace Memory {
    #if __cplusplus > 201103L // After c++11 (as of now c++14 and c++17)
    
    using std::make_unique;

    #else // C++11
    
    template < typename T, typename... CONSTRUCTOR_ARGS >
    std::unique_ptr<T> make_unique( CONSTRUCTOR_ARGS&&... constructor_args )
    { return std::unique_ptr<T>( new T( std::forward<CONSTRUCTOR_ARGS>(constructor_args)... ) ); }
    
    #endif // __cplusplus == 201402L

    using std::make_shared;



  }

  // template<class _Tp>
  template<class _Tp>
  using sptr = std::shared_ptr<_Tp>;
  template<class _Tp>
  using uptr = std::unique_ptr<_Tp>;
  template<class _Tp>
  using wptr = std::weak_ptr<_Tp>;
  // typedef std::shared_ptr<class _Tp> sptr<class _Tp>;
  // typedef std::unique_ptr<class _Tp> uptr;
  // typedef std::weak_ptr<class _Tp> wptr;
  // template<class _Tp>
  // typedef std::shared_ptr<_Tp> uptr;

}

#endif // MAKE_UNIQUE_H_INCLUDED 
