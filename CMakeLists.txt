cmake_minimum_required(VERSION 3.10)

# Set the project name
project(LiftSync)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Add your executable
add_executable(main
    src/main.cpp
    src/Elevator.cpp
    src/ElevatorSystem.cpp
    src/RequestHandler.cpp
)

# ✅ Link the pthread library for std::thread support
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE Threads::Threads)

# # Enable testing
# enable_testing()

# # Find GoogleTest package installed system-wide
# find_package(GTest REQUIRED)

# # Add the test executable
# add_executable(MyTests tests/test_main.cpp src/TwoPointers.cpp src/ArrayHashing.cpp src/Graph.cpp)

# # Link against the system-installed GTest
# target_link_libraries(MyTests GTest::GTest GTest::Main)