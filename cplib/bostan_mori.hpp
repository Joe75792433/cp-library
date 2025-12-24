#pragma once

#include <cassert>
#include <cstdint>
#include <ranges>
#include <vector>

namespace cplib {

// 有理式 p(x)/q(x) のn次の係数を求める
// deg(p) < deg(q) かつ q[0] != 0 であること
template <typename T>
T bostan_mori(uint64_t n,
              std::vector<T> p,
              std::vector<T> q,
              const auto& convolution_func) {
    while (n > 0) {
        const size_t len_q = q.size();
        std::vector<T> q_ = q;
        for (size_t i = 1; i < len_q; i += 2) {
            q_[i] *= -1;
        }
        p = convolution_func(p, q_) | std::views::drop(n % 2) |
            std::views::stride(2) | std::ranges::to<std::vector<T>>();
        q = convolution_func(q, q_) | std::views::stride(2) |
            std::ranges::to<std::vector<T>>();
        n /= 2;
    }
    assert(p.size() > 0);
    assert(q.size() > 0);
    return p[0] / q[0];
}

}  // namespace cplib
