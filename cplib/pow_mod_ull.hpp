#pragma once

namespace cplib {

// (x ^ n) mod m を繰り返し二乗法で求める
// x >= 0, n >= 0, m >= 1
unsigned long long pow_mod_ull(unsigned long long x,
                               unsigned long long n,
                               const unsigned long long m) {
    unsigned long long result = ((n % 2 == 1) ? x : 1) % m;
    for (n /= 2; n > 0; n /= 2) {
        x = static_cast<unsigned long long>(__uint128_t(x) * __uint128_t(x) %
                                            __uint128_t(m));
        if (n % 2 == 1) {
            result = static_cast<unsigned long long>(
                __uint128_t(result) * __uint128_t(x) % __uint128_t(m));
        }
    }
    return result;
}

}  // namespace cplib
