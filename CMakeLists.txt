cmake_minimum_required (VERSION 2.8.11)
project (tree_evolution)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(src)
set(SOURCES src/climat_monitor.cpp
            src/DNA.cpp
            src/gene.cpp
            src/rand.cpp
            src/seed.cpp
            src/sun.cpp
            src/tree.cpp
            src/tree_evolution.cpp
            src/world.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
