#pragma once

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace cplib {

// n を素因数分解する
// (素因数, 指数) の pair を要素とする vector を返す
// 計算量は O(n^(1/2))
// n < (2^32-1)^2 でなければならない
std::vector<std::pair<uint64_t, uint64_t>> prime_factorization(uint64_t n) {
    std::vector<std::pair<uint64_t, uint64_t>> result(0);
    // (2^32-1)^2 <= n のとき i^2 がオーバーフローして壊れる
    for (uint64_t i = 2; i * i <= n; ++i) {
        if (n % i != 0) continue;
        uint64_t count = 0;
        while (n % i == 0) {
            ++count;
            n /= i;
        }
        result.emplace_back(i, count);
    }
    if (n > 1) result.emplace_back(n, 1);
    return result;
}

}  // namespace cplib
