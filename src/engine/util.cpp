#include "sys.hpp"
#include <chrono>
#include <limits>
#include <random>


namespace util {


    std::mt19937 mrand;

    void init() {
        mrand = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    void release() {

    }

    bool nextBool() {
        return (mrand() % 2 == 0) ? true : false;
    }

    uint32_t nextInteger() {
        return mrand();
    }

    uint32_t nextIntegerRange(int min, int max) {
        return (mrand() % (max - min)) + min;
    }

    float nextFloat() {
        return mrand() / (float)std::numeric_limits<uint32_t>().max();
    }

    float nextFloatRange(float min, float max) {
        return (nextFloat() * (max - min)) + min;
    }

}