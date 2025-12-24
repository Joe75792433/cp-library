#pragma once

#include <cmath>
#include <cstdint>

namespace cplib {

// reference: https://rsk0315.hatenablog.com/entry/2023/11/07/221428

// i^2 <= n を満たす最大の整数 i を求める
uint64_t floor_sqrt(const uint64_t n) {
    if (n == 0) return 0;
    const uint64_t tmp_m1 = std::sqrt(n) - 1;
    return tmp_m1 * (tmp_m1 + 2) < n ? tmp_m1 + 1 : tmp_m1;
}

}  // namespace cplib
