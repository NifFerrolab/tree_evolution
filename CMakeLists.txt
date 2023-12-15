cmake_minimum_required (VERSION 3.12)
project (tree_evolution)

set(CMAKE_CXX_STANDARD 17)

if (SHOW)
	include_directories(src/display)
	set(SOURCES src/display/world_img.cpp
	            src/display/img_output.cpp
	            src/display/video_output.cpp
	            src/display/window_output.cpp
	            src/evolution/climat_monitor.cpp)
	add_compile_definitions(SHOW)
	find_package(OpenCV REQUIRED)
endif()

if (STATS)
	add_compile_definitions(AGE AGE_SEED SLEEP_SEED HEIGHT)
endif()

include_directories(src/evolution)
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
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
