#ifndef CPLIB_PRIME_FACTORIZATION_HPP
#define CPLIB_PRIME_FACTORIZATION_HPP 1

#include <cassert>
#include <utility>
#include <vector>

namespace cplib {

// 素因数分解をする
// (素因数, 指数) のpairを要素とするvectorを返す
std::vector<std::pair<long long, long long>> prime_factorization(long long n) {
    assert(n >= 1);
    std::vector<std::pair<long long, long long>> result(0);
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i != 0) continue;
        long long count = 0;
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

#endif  // CPLIB_PRIME_FACTORIZATION_HPP
