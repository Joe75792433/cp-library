#pragma once

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace cplib {

// エラトステネスの篩
// 素数判定・最小の素因数・メビウス関数値を前計算しクエリ O(1) で返す
struct Eratosthenes {
  private:
    const size_t sieve_size;
    std::vector<uint64_t> min_factor;
    std::vector<int> mobius;

  public:
    // コンストラクタ
    // エラトステネスの篩を構成する
    // 計算量は O(nloglogn)
    Eratosthenes(const size_t max_input) : sieve_size(max_input + 1) {
        min_factor = std::vector<uint64_t>(sieve_size, 0);
        min_factor[0] = min_factor[1] = 1;
        mobius = std::vector<int>(sieve_size, 1);
        for (uint64_t i = 2; i < sieve_size; ++i) {
            if (min_factor[i] != 0) continue;
            min_factor[i] = i;
            mobius[i] = -1;
            for (uint64_t j = 2 * i; j < sieve_size; j += i) {
                if (min_factor[j] == 0) {
                    min_factor[j] = i;
                }
                mobius[j] *= -1;
            }
            for (uint64_t j = i * i; j < sieve_size; j += i * i) {
                mobius[j] = 0;
            }
        }
    }

    // 正整数 n を素因数分解した結果を pair(素因数, 指数) の vector で返す
    // 計算量は O(nlogn)
    std::vector<std::pair<uint64_t, uint64_t>> prime_factorization(uint64_t n) {
        assert(n > 0);
        assert(n < sieve_size);
        std::vector<std::pair<uint64_t, uint64_t>> result;
        while (n > 1) {
            uint64_t p = min_factor[n];
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

    // 正整数 n のメビウス関数値 μ(n) を返す
    // 計算量は O(1)
    int get_mobius(const uint64_t n) {
        assert(n > 0);
        assert(n < sieve_size);
        return mobius[n];
    }
};

}  // namespace cplib
