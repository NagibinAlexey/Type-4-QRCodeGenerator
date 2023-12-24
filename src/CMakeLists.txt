add_executable(ccQRCodeGenerator main.cpp
        QRGenerator.cpp
        QRGenerator.h
        domain.h
        analyzer.h
        ErCorCodewordsGenerator.cpp
        ErCorCodewordsGenerator.h
        GF256.h
        QRMatrix.cpp
        QRMatrix.h)

find_package(JPEG REQUIRED)
if (JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries(ccQRCodeGenerator ${JPEG_LIBRARIES})
endif ()