# project(SDL)

# add_subdirectory(src)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

file(GLOB SDL_SRC src/*.cpp)

add_library(SDLEngine ${SDL_SRC})
target_link_libraries(SDLEngine SDL2 SDL2_IMAGE)

target_include_directories(SDLEngine PUBLIC inc/ ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
# add_dependencies(SDL)
# link_libraries(SDL )
