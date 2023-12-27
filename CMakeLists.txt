cmake_minimum_required(VERSION 3.20.0)
project(CCQRCodeGenerator CXX)
enable_testing()

add_subdirectory(src bin)
add_subdirectory(tests)
set(CMAKE_INSTALL_DOCDIR "docs")

execute_process(
        COMMAND ${GIT_EXECUTABLE} clone
        https://github.com/stohrendorf/libjpeg-cmake.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/extern
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg-cmake)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg)
#target_include_directories(ccQRCodeGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern/libjpeg)
#link_directories(${CMAKE_BINARY_DIR}/extern/libjpeg)
#target_include_directories(ccQRCodeGenerator PRIVATE ${CMAKE_BINARY_DIR}/extern/libjpeg)
