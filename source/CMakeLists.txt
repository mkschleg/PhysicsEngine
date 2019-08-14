include_directories(../lib/)
include_directories(inc/)

file(GLOB PHY_SRC src/*/*.cpp)

add_library(PHYSICS ${PHY_SRC})
