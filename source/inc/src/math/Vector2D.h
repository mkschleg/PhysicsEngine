#ifndef _PHYSICS_VECTOR_H
#define _PHYSICS_VECTOR_H

// #include "pvector"
// #include <Eigen/Eigen>
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

namespace Physics{
  

  class Vector2D {
    friend Vector2D operator+(const Vector2D& rhs, double scalar);
    friend Vector2D operator-(const Vector2D& rhs, double scalar);
    friend Vector2D operator*(const Vector2D& rhs, double scalar);
    friend Vector2D operator/(const Vector2D& rhs, double scalar);
    friend Vector2D operator+(double scalar, const Vector2D& rhs);
    friend Vector2D operator-(double scalar, const Vector2D& rhs);
    friend Vector2D operator*(double scalar, const Vector2D& rhs);
    friend Vector2D operator/(double scalar, const Vector2D& rhs);
    friend Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs);
    friend Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs);
    friend Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs);
    friend Vector2D operator/(const Vector2D& rhs, const Vector2D& lhs);
    double x,y,_norm;
    // double _norm;

  public:
    Vector2D():x(0),y(0),_norm(0){}
    Vector2D(double _x, double _y):x(_x),y(_y){
      _norm = std::sqrt(x*x+y*y);
    }
    
    Vector2D(const Vector2D& cp): x(cp.x), y(cp.y), _norm(cp._norm){}
    Vector2D(Vector2D&& mv): x(mv.x), y(mv.y), _norm(mv._norm){ mv.x = 0; mv.y = 0; mv._norm = 0; }
    Vector2D& operator=(const Vector2D& cp){
      this->x = cp.x; this->y = cp.y; this->_norm = cp._norm;
      return *this;
    }
    Vector2D& operator=(Vector2D&& mv){
      this->x = mv.x; this->y = mv.y; this->_norm = mv._norm;
      mv.x = 0; mv.y = 0; mv._norm = 0;
      return *this;
    }


    double getX() const {return x;}
    double getY() const {return y;}

    void setX(double _x){x=_x;}
    void setY(double _y){y=_y;}
    
    void set(double _x, double _y){
      x = _x; y = _y;
    }

    Vector2D& unaryExpr(std::function<double(const double&)> op){
      x = op(x);
      y = op(y);
      return *this;
    }
    Vector2D& binaryExpr(const Vector2D& vec, std::function<double(const double, const double)> op){
      x = op(x,vec.x);
      y = op(y,vec.y);
      return *this;
    }
    
    double dot(const Vector2D& vec) const{
      return this->x*vec.x + this->y*vec.y;
    }

    double norm() const{
      // _norm = std::sqrt(x*x+y*y)
      return std::sqrt(x*x+y*y);
    }
    
    Vector2D normalize() const{
      if(norm() != 0){
        return *this/norm();
      } else {
        return *this;
      }
    }

    double cross(const Vector2D& vec) const{
      return this->x*vec.y + this->y*vec.x;
    }
    
    Vector2D rotate90(){
      return Vector2D(-y,x);
    }
    Vector2D rotate270(){
      return Vector2D(y,-x);
    }

    Vector2D& operator+=(const Vector2D& vec){
      this->x += vec.x;
      this->y += vec.y;
      return *this;
    }
    Vector2D& operator-=(const Vector2D& vec){
      this->x -= vec.x;
      this->y -= vec.y;
      return *this;
    }
    Vector2D& operator*=(const Vector2D& vec){
      this->x *= vec.x;
      this->y *= vec.y;
      return *this;
    }
    Vector2D& operator/=(const Vector2D& vec){
      this->x /= vec.x;
      this->y /= vec.y;
      return *this;
    }
    Vector2D& operator+=(const double scalar){
      this->x += scalar;
      this->y += scalar;
      return *this;
    }
    Vector2D& operator-=(const double scalar){
      this->x -= scalar;
      this->y -= scalar;
      return *this;
    }
    Vector2D& operator*=(const double scalar){
      this->x *= scalar;
      this->y *= scalar;
      return *this;
    }
    Vector2D& operator/=(const double scalar){
      this->x /= scalar;
      this->y /= scalar;
      return *this;
    }

    // Vector2D operator+()

  };
  
  inline Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs){
    return Vector2D(rhs.x + lhs.x, rhs.y + lhs.y);
  }
  inline Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs){
    return Vector2D(rhs.x - lhs.x, rhs.y - lhs.y);
  }
  inline Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs){
    return Vector2D(rhs.x * lhs.x, rhs.y * lhs.y);
  }
  inline Vector2D operator/(const Vector2D& rhs, const Vector2D& lhs){
    return Vector2D(rhs.x / lhs.x, rhs.y / lhs.y);
  }
  inline Vector2D operator+(const Vector2D& rhs,double scalar){
    return Vector2D(rhs.x + scalar, rhs.y + scalar);
  }
  inline Vector2D operator-(const Vector2D& rhs,double scalar){
    return Vector2D(rhs.x - scalar, rhs.y - scalar);
  }
  inline Vector2D operator*(const Vector2D& rhs,double scalar){
    return Vector2D(rhs.x * scalar, rhs.y * scalar);
  }
  inline Vector2D operator/(const Vector2D& rhs,double scalar){
    return Vector2D(rhs.x / scalar, rhs.y / scalar);
  }
  inline Vector2D operator+(double scalar,const Vector2D& rhs){
    return Vector2D(rhs.x + scalar, rhs.y + scalar);
  }
  inline Vector2D operator-(double scalar,const Vector2D& rhs){
    return Vector2D(rhs.x - scalar, rhs.y - scalar);
  }
  inline Vector2D operator*(double scalar,const Vector2D& rhs){
    return Vector2D(rhs.x * scalar, rhs.y * scalar);
  }
  inline Vector2D operator/(double scalar,const Vector2D& rhs){
    return Vector2D(rhs.x / scalar, rhs.y / scalar);
  }
  
  inline std::ostream& operator<<(std::ostream& os, const Vector2D& vec){
    os<<vec.getX()<<" "<<vec.getY();
    return os;
  }

}




// inline void operator+=(std::vector<double>)




#endif
