#pragma once

#include <vector>

namespace cplib {

// 畳み込みをする
// 一方が空の配列ならば空の配列を返す
// 計算量は O(|a||b|)
template <typename T>
std::vector<T> convolution_naive(const std::vector<T>& a,
                                 const std::vector<T>& b) {
    const size_t n = a.size(), m = b.size();
    if (n == 0 || m == 0) return std::vector<T>();

    std::vector<T> result(n + m - 1);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

}  // namespace cplib
