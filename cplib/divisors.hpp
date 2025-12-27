#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "cplib/prime_factorization.hpp"

namespace cplib {

// pair(素因数, 指数) の vector を受け取り正の約数を昇順にすべて求める
// 入力の vector が空の場合は {1} を返す
// 計算量は 約数の個数を s として O(slogs)
std::vector<uint64_t> divisors(
    const std::vector<std::pair<uint64_t, uint64_t>>& primes) {
    size_t res_size = 1;
    for (auto [prime, count] : primes) res_size *= count + 1;

    std::vector<uint64_t> result = {1};
    result.reserve(res_size);

    for (auto [prime, count] : primes) {
        size_t tmp_size = result.size();
        for (size_t i = 0; i < tmp_size; ++i) {
            uint64_t prime_power = 1;
            for (uint64_t j = 0; j < count; ++j) {
                prime_power *= prime;
                result.push_back(result[i] * prime_power);
            }
        }
    }
    std::ranges::sort(result);
    return result;
}

// 正の整数 n の正の約数を昇順にすべて求める
// 計算量は O(n^(1/2))
std::vector<uint64_t> divisors(uint64_t n) {
    assert(n > 0);
    std::vector<std::pair<uint64_t, uint64_t>> primes = prime_factorization(n);
    return divisors(primes);
}

}  // namespace cplib
