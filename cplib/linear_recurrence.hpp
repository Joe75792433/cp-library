#pragma once

#include <cassert>
#include <ranges>
#include <vector>
#include "cplib/bostan_mori.hpp"

namespace cplib {

// d 次の線形回帰数列 a の第 n 項を求める (0-indexed)
// Bostan-Mori 法で O(d*logd*logn) または O(d^2 * logn)
// 入力: a のうち最初の d 項、線形漸化式の 1 <= i <= d 項前の係数 c_{i-1}、
//     畳み込み関数 convolution_func
template <typename T>
T linear_recurrence(unsigned long long n,
                    const std::vector<T>& a,
                    const std::vector<T>& c,
                    const auto& convolution_func) {
    if (n < a.size()) return a[n];

    const size_t d = c.size();
    assert(a.size() >= d);

    std::vector<T> q = {1};
    q.append_range(c |
                   std::views::transform([](const T& coef) { return -coef; }));
    const std::vector<T> p = convolution_func(a, q) | std::views::take(d) |
                             std::ranges::to<std::vector<T>>();
    return bostan_mori(n, p, q, convolution_func);
}

}  // namespace cplib
