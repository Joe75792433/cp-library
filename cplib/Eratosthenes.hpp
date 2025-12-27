#pragma once

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace cplib {

// エラトステネスの篩
struct Eratosthenes {
  private:
    const size_t sieve_size;
    std::vector<int> min_factor;

  public:
    // コンストラクタ
    // エラトステネスの篩を構成する
    // 計算量は O(nloglogn)
    Eratosthenes(const size_t max_input) : sieve_size(max_input + 1) {
        min_factor = std::vector<int>(sieve_size, -1);
        min_factor[0] = min_factor[1] = 1;
        for (int i = 2; i < int(sieve_size); ++i) {
            if (min_factor[i] != -1) continue;
            min_factor[i] = i;
            for (int j = 2 * i; j < int(sieve_size); j += i) {
                if (min_factor[j] == -1) {
                    min_factor[j] = i;
                }
            }
        }
    }

    // 正整数 n を素因数分解した結果を pair(素因数, 指数) の vector で返す
    // 計算量は O(nlogn)
    std::vector<std::pair<uint64_t, uint64_t>> prime_factorization(uint64_t n) {
        assert(n < sieve_size);
        std::vector<std::pair<uint64_t, uint64_t>> result;
        while (n > 1) {
            int p = min_factor[n];
            uint64_t count = 0;
            while (min_factor[n] == p) {
                n /= p;
                ++count;
            }
            result.emplace_back(p, count);
        }
        return result;
    }

    // n が素数であるか判定する
    // 計算量は O(1)
    bool is_prime(const uint64_t n) {
        assert(n < sieve_size);
        if (n <= 1) return false;
        return min_factor[n] == int(n);
    }
};

}  // namespace cplib
