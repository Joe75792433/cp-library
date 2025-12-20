#ifndef CPLIB_INTERSECTION_HPP
#define CPLIB_INTERSECTION_HPP 1

#include <algorithm>
#include <utility>

namespace cplib {

// [l1, r1)と[l2, r2)の共通部分を求める
// 共通部分がない場合や入力が l>r の場合は(0, 0)を返す
template <typename T>
constexpr inline std::pair<T, T> intersection(const T& l1,
                                              const T& r1,
                                              const T& l2,
                                              const T& r2) {
    const T l = std::max(l1, l2);
    const T r = std::min(r1, r2);
    if (l < r)
        return std::make_pair(l, r);
    else
        return std::make_pair(0, 0);
}

}  // namespace cplib

#endif  // CPLIB_INTERSECTION_HPP
