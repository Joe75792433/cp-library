#pragma once

#include <bit>
#include <cstdint>
#include <ranges>
#include <vector>
#include "cplib/pow_mod_ull.hpp"

namespace cplib {

// n が素数であるかをミラーラビン法で判定する
// vector で渡した整数を証人とする
bool miller_rabin(const uint64_t n, const std::vector<uint64_t>& wits) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    const int s = std::countr_zero(n - 1);
    const uint64_t d = (n - 1) >> s;

    for (const uint64_t a :
         wits | std::views::transform([n](uint64_t x) { return x % n; })) {
        if (a == 0) continue;

        uint64_t tmp = pow_mod_ull(a, d, n);
        if (tmp == 1) continue;

        for (int i = 0; tmp != n - 1; ++i) {
            if (i == s - 1) return false;
            tmp = pow_mod_ull(tmp, 2, n);
        }
    }

    return true;
}

}  // namespace cplib
