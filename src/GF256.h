#pragma once
#include <array>

namespace GF256 {

    constexpr std::array<int, 256> InitializeLogToInt() {
        std::array<int, 256> logToInt{1};
        int current = 1;
        for (int i = 1; i < 256; ++i) {
            current *= 2;
            if (current >= 256) {
                current = current ^ 285;
            }
            logToInt[i] = current;
        }
        return logToInt;
    }

    constexpr auto logToInt = InitializeLogToInt();

    constexpr std::array<int, 256> InitializeIntToLog() {
        std::array<int, 256> intToLog{};
        for (int i = 0; i < 256; ++i) {
            intToLog[logToInt[i]] = i;
        }
        intToLog[1] = 0;
        return intToLog;
    }

    constexpr auto intToLog = InitializeIntToLog();
}
