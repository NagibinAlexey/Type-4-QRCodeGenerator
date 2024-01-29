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

if (WIN32)
    set(JPEG_INC ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)
    set(JPEG_LIB ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib/jpeg.lib)
endif (WIN32)

if (UNIX)
    set(JPEG_INC ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/include)
    set(JPEG_LIB ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/lib/libjpeg.a)
endif (UNIX)

include_directories(${JPEG_INC})
target_link_libraries(ccQRCodeGenerator PRIVATE sut ${JPEG_LIB})

#find_package(JPEG REQUIRED)
#if (NOT JPEG_FOUND)
#    message(FATAL_ERROR, " Libjpeg library not found, please install: sudo apt-get install libjpeg-dev")
#endif()
#if (JPEG_FOUND)
#    include_directories(${JPEG_INCLUDE_DIR})
#    target_link_libraries(ccQRCodeGenerator PRIVATE sut ${JPEG_LIBRARIES})
#endif()