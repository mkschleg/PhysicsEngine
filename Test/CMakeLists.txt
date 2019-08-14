
include_directories(../lib/)
file(GLOB SRCS *.cpp)

add_executable(physicstest ${SRCS})

target_link_libraries(physicstest
    gtest_main
    PHYSICS
)

add_test(NAME physics COMMAND physicstest)
