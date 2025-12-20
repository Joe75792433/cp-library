#ifndef CPLIB_VECTOR_IO_HPP
#define CPLIB_VECTOR_IO_HPP 1

#include <cassert>
#include <iostream>
#include <vector>

namespace cplib {

template <typename T>
inline std::istream& operator>>(std::istream& is, std::vector<T>& v) {
#ifdef DEBUG
    assert(v.size() != 0);
#endif
    for (auto& x : v) is >> x;
    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    const size_t len = v.size();
    for (size_t i = 0; i < len - 1; ++i) os << v[i] << ' ';
    if (len > 0) os << v[len - 1];
    return os;
}

}  // namespace cplib

#endif  // CPLIB_VECTOR_IO_HPP
