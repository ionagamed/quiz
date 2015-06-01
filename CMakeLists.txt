cmake_minimum_required(VERSION 2.6)
project(quiz)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
set(EXECUTABLE_OUTPUT_PATH build)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -g")
else()
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11")
endif()

file(GLOB files src/*.cpp)
add_executable(quiz ${files})

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(quiz ${SFML_LIBRARIES})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(quiz ${PYTHON_LIBRARIES})

find_package(XLib REQUIRED)
include_directories(${XLIB_INCLUDE_PATH})
target_link_libraries(quiz ${XLIB_LIBRARY})
