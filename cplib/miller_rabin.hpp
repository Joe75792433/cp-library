#pragma once

#include <bit>
#include <ranges>
#include <vector>
#include "cplib/pow_mod_ull.hpp"

namespace cplib {

// n が素数であるかをミラーラビン法で判定する
// vector で渡した整数を証人とする
bool miller_rabin(const unsigned long long n,
                  const std::vector<unsigned long long>& wits) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    const int s = std::countr_zero(n - 1);
    const unsigned long long d = (n - 1) >> s;

    for (const unsigned long long a :
         wits | std::views::transform(
                    [n](unsigned long long x) { return x % n; })) {
        if (a == 0) continue;

        unsigned long long tmp = pow_mod_ull(a, d, n);
        if (tmp == 1) continue;

        for (int i = 0; i < s + 1; ++i) {
            if (i == s) return false;
            if (tmp == n - 1) break;
            tmp = pow_mod_ull(tmp, 2, n);
        }
    }

    return true;
}

}  // namespace cplib
