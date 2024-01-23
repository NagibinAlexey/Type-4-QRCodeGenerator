add_library(sut STATIC
        QRGenerator.cpp
        QRGenerator.h
        domain.h
        analyzer.h
        ErCorCodewordsGenerator.cpp
        ErCorCodewordsGenerator.h
        GF256.h
        QRMatrix.cpp
        QRMatrix.h
        renderer.cpp
        renderer.h
        FormatStringGenerator.cpp
        FormatStringGenerator.h
        start_program.cpp
        alphanumericConverter.h
        numericConverter.h
        polynomialGenerator.h
        penalty_calculation.cpp
)
target_include_directories(sut PUBLIC .)

add_executable(ccQRCodeGenerator main.cpp)
#target_link_libraries(ccQRCodeGenerator PRIVATE sut)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif ()

#set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/libjpeg-cmake)
find_package(JPEG REQUIRED)
if (NOT JPEG_FOUND)
    message(FATAL_ERROR, " Libjpeg library not found, please install: sudo apt-get install libjpeg-dev")
endif ()
if (JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries(ccQRCodeGenerator PRIVATE sut ${JPEG_LIBRARIES})
endif ()