#ifndef CPLIB_BOSTAN_MORI_HPP
#define CPLIB_BOSTAN_MORI_HPP 1

#include <cassert>
#include <ranges>
#include <vector>

namespace cplib {

// 有理式 p(x)/q(x) のn次の係数を求める
// deg(p) < deg(q) であること
template <typename T>
T bostan_mori(unsigned long long n,
              std::vector<T> p,
              std::vector<T> q,
              auto convolution_func) {
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

#endif  // CPLIB_BOSTAN_MORI_HPP
