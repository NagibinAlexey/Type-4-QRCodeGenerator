add_library(sut STATIC
        stringConverter.cpp
        stringConverter.h
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
        byteConverter.h
        QRGenerator.cpp
        QRGenerator.h
)
target_include_directories(sut PUBLIC .)

add_executable(ccQRCodeGenerator main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif ()

#set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/libjpeg-turbo/cmakescripts)
#find_package(TURBOJPEG REQUIRED)
#if (NOT TURBOJPEG_FOUND)
#    message(FATAL_ERROR, " Libjpeg library not found, please install: sudo apt-get install libjpeg-dev")
#endif ()
#if (TURBOJPEG_FOUND)
#    include_directories(${TURBOJPEG_INCLUDE_DIR})
    target_link_libraries(ccQRCodeGenerator PRIVATE sut jpeg)
#endif ()