#pragma once

#include <cstdint>

namespace cplib {

// (x ^ n) mod m を繰り返し二乗法で求める
// x >= 0, n >= 0, m >= 1
uint64_t pow_mod_ull(uint64_t x, uint64_t n, const uint64_t m) {
    uint64_t result = ((n % 2 == 1) ? x : 1) % m;
    for (n /= 2; n > 0; n /= 2) {
        x = static_cast<uint64_t>(__uint128_t(x) * __uint128_t(x) %
                                  __uint128_t(m));
        if (n % 2 == 1) {
            result = static_cast<uint64_t>(__uint128_t(result) *
                                           __uint128_t(x) % __uint128_t(m));
        }
    }
    return result;
}

}  // namespace cplib
