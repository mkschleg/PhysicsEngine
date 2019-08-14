#ifndef _SLD_DRAWABLE_H
#define _SLD_DRAWABLE_H

#include "renderer.h"

namespace SDL{

  class drawable{
  public:
    virtual void draw(std::shared_ptr<Renderer>& renderer) = 0;
  };
}



#endif
