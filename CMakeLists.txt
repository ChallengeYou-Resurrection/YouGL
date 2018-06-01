cmake_minimum_required(VERSION 3.0)

#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(YouGL)

#Add the files
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(YouGL ${SOURCES})

#Include directory
include_directories("${CMAKE_MODULE_PATH}/Source/Dependancies")

#Add libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics network audio window system)
target_link_libraries(YouGL ${SFML_LIBRARIES})

#Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

