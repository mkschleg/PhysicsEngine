cmake_minimum_required(VERSION 3.8)



# project(filesystem)

# add_subdirectory(googletest)

option(build_tests "Build all of gtest's own tests." ON)

# SET(CMAKE_C_COMPILER gcc-7)
# SET(CMAKE_CXX_COMPILER g++-7)

# find_package(OpenMP REQUIRED)

# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -march=native -O3")
# include_directories("./inc/")

include_directories("./source/inc/")
include_directories("./lib")

add_subdirectory(source)
# add_subdirectory(lib)


if (build_tests)
  # Download and unpack googletest at configure time
  configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()
  
  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                  ${CMAKE_BINARY_DIR}/googletest-build)

  # The gtest/gtest_main targets carry header search path
  # dependencies automatically when using CMake 2.8.11 or
  # later. Otherwise we have to add them here ourselves.
  if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
  endif()
  
  include_directories(("./googletest/include"))

  # This must be set in the root directory for the tests to be run by
  # 'make test' or ctest.
  # enable_testing()
  # cxx_executable(Filesystem_test test gtest_main test/Filesystem_test.cpp)
  # add_executable(test/Filesystem_test gtest)
  # add_executable(test/Filesystem_test gtest)
  
  add_subdirectory(test)
  
  INCLUDE(FindPkgConfig)

  PKG_SEARCH_MODULE(SDL2 sdl2)
  PKG_SEARCH_MODULE(SDL2IMAGE SDL2_image>=2.0.0)

  if(SDL2_FOUND AND SDL2IMAGE_FOUND)
    # message("${CMAKE_ROOT}")
    message("Found SDL2 ${SDL2_CFLAGS} ${SDL2_INCLUDE_DIRS} -l${SDL2_LIBRARIES}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
      # INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
    # INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    add_subdirectory(lib/SDL)
    add_subdirectory(sdlTests)
  else()
    message("FAIL")
    if(NOT SDL2_FOUND)
      message("SDL2 Not Found")
    endif()
  endif()
  # if(SDL2IMAGE_FOUND)
  #   message("Found SDL2Image ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2IMAGE_LIBRARY}")
  #   # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2IMAGE_CFLAGS}")
  #   INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
  # endif()

  # target_link_libraries()

endif()
