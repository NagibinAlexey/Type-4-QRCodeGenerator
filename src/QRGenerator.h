#pragma once

#include "stringConverter.h"
#include "ErCorCodewordsGenerator.h"
#include "QRMatrix.h"
#include "renderer.h"

namespace QR {

    void generate(std::string& string, int version, ErrorCorLevel level);

} // QR
