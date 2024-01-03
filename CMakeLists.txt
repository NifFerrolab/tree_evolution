cmake_minimum_required (VERSION 3.12)
project (tree_evolution)

set(CMAKE_CXX_STANDARD 17)

option(SHOW "SHOW" on)
option(STATS "STATS" Off)

if (SHOW)
	set(SOURCES src/display/world_img.cpp
	            src/display/img_output.cpp
	            src/display/video_output.cpp
	            src/display/window_output.cpp
	            src/evolution/climat_monitor.cpp)
	add_compile_definitions(SHOW)
	find_package(OpenCV REQUIRED)
endif()

if (STATS)
	add_compile_definitions(AGE AGE_SEED SLEEP_SEED HEIGHT TREES_COUNT)
endif()

set(SOURCES ${SOURCES}
            src/evolution/DNA.cpp
            src/evolution/gene.cpp
            src/evolution/rand.cpp
            src/evolution/seed.cpp
            src/evolution/sun.cpp
            src/evolution/tree.cpp
            src/evolution/tree_evolution.cpp
            src/evolution/world.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/evolution)
if (SHOW)
    target_include_directories(${PROJECT_NAME} PRIVATE src/display)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
