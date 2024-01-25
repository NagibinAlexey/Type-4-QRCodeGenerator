cmake_minimum_required(VERSION 3.20.0)
project(CCQRCodeGenerator CXX)
enable_testing()

add_subdirectory(src bin)
add_subdirectory(tests)

include(ExternalProject)
ExternalProject_Add(libjpeg_turbo
        GIT_REPOSITORY https://github.com/libjpeg-turbo/libjpeg-turbo.git
        GIT_TAG MASTER
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libjpeg-turbo
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/libjpeg_turbo
)
include_directories(${CMAKE_BINARY_DIR}/libjpeg_turbo/include)
link_directories(${CMAKE_BINARY_DIR}/libjpeg_turbo/lib)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg-turbo)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg)
#target_include_directories(ccQRCodeGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg)
#link_directories(${CMAKE_BINARY_DIR}/extern/libjpeg)
#target_include_directories(ccQRCodeGenerator PRIVATE ${CMAKE_BINARY_DIR}/extern/libjpeg)
