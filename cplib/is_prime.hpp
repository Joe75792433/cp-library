#pragma once

#include <cstdint>
#include <vector>
#include "cplib/miller_rabin.hpp"

namespace cplib {

// n が素数であるかを判定する(Miller-Rabin法)
// n < 2^64, q <= 10^5 程度が間に合う
bool is_prime(const uint64_t n) {
    if (n < 4759123141ULL) {
        return miller_rabin(n, {2, 7, 61});
    } else {
        return miller_rabin(n,
                            {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    }
}

}  // namespace cplib
