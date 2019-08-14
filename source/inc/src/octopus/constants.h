#pragma once

#include <array>
#include <math>


namespace Octopus{ namespace Constants{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

namespace Muscle{
  const double Active = 0.5;
  const double Passive = 0.2;
  const double NormalizedMinLength = 0.4;
  const double Damping = -0.3;
} // namespace Muscle

namespace Friction{
  const double Tangential = 0.2;
  const double Perpendicular = 1.0;
}

namespace Repulsion{
  const double Constant = 0.04;
  const double Power = 2.3;
  const double Threshold = 0.7;
}


const double Pressure = 0.5;
const double Gravity = 0.01;
const double SurfaceLevel = 5;
const double Bouyancy = 0.08;

namespace Initial{
  namespace Nodes{
    const std::array<double,13> Mass{{1, 0.9900990099, 0.9803921569, 0.9708737864, 0.9615384615,
                                      0.9523809524, 0.8433962264, 0.8345794393, 0.8259259259, 0.8174311927,
                                      0.7090909091, 0.7009009009, 0.7928571429}};
    const std::array<double,13> X{{0,1,2,3,4,5,6,7,8,9,10,11,12}};
    const double UpperY = 1;
    const double LowerY = 0;
    const Physics::Vector2D Velocity(0,0);
    const size_t NumPairs = 13;
  }//namespace Nodes
}//namespace Initial

#pragma clang diagnostic pop
}} // namespaces Octopus::Constants
