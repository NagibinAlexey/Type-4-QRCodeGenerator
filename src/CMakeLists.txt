add_executable(ccQRCodeGenerator main.cpp
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
        FormatStringGenerator.h)

set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/libjpeg-cmake)
find_package(JPEG REQUIRED)
if (NOT JPEG_FOUND)
    message(FATAL_ERROR, " Libjpeg library not found, please install: sudo apt-get install libjpeg-dev")
endif ()
if (JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries(ccQRCodeGenerator ${JPEG_LIBRARIES})
endif ()