// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2880
#include <bits/stdc++.h>
#include <atcoder/modint>
#include "cplib/IntervalSet.hpp"
#ifdef DEBUG
#define debug(x) std::cerr << #x << ": " << (x) << std::endl
#define is_debug true
#else
// #pragma GCC target("arch=skylake-avx512")
#pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#define debug(x)
#define is_debug false
#endif

using namespace std;
using namespace atcoder;
using ll = long long;

#define rep(...) overloadrep(__VA_ARGS__, rep4_, rep3_, rep2_)(__VA_ARGS__)
#define overloadrep(_1, _2, _3, _4, repn_, ...) repn_
#define rep2_(i, n) rep4_(i, 0, n, 1)
#define rep3_(i, a, b) rep4_(i, a, b, 1)
#define rep4_(i, a, b, s) for (auto i = (a); i < (b); i += (s))
#define repr(i, a, b) for (auto i = (b) - 1; i >= (a); --i)
#define foreach(x, a) for (auto& x : (a))

#define vcin(v) \
    for (auto& elm_vcin : (v)) cin >> elm_vcin
#define vcout(v) \
    for (auto& elm_vcout : (v)) cout << elm_vcout << '\n'
#define vprintln(v)                                                            \
    for (int i_vprintln = 0, n_vprintln = (v).size(); i_vprintln < n_vprintln; \
         ++i_vprintln)                                                         \
    cout << (v)[i_vprintln] << " \n"[i_vprintln == n_vprintln - 1]

void din_() {}
template <class Head, class... Tail> void din_(Head&& head, Tail&&... tail) {
    cin >> head;
    din_(move(tail)...);
}
#define din(T, ...) \
    T __VA_ARGS__;  \
    din_(__VA_ARGS__)

template <class T = ll> T IN() {
    T x;
    cin >> x;
    return (x);
}

#define YES(n) cout << ((n) ? "YES" : "NO") << '\n'
#define Yes(n) cout << ((n) ? "Yes" : "No") << '\n'
#define POSSIBLE(n) cout << ((n) ? "POSSIBLE" : "IMPOSSIBLE") << '\n'
#define Possible(n) cout << ((n) ? "Possible" : "Impossible") << '\n'
#define Alice(n) cout << ((n) ? "Alice" : "Bob") << '\n'
#define First(n) cout << ((n) ? "First" : "Second") << '\n'

#define all(x) (x).begin(), (x).end()
#define siz(x) int((x).size())
#define Pcnt(n) popcount(static_cast<unsigned long long>(n))
#define Bit(n) (1LL << (n))
#define uniq(v) (v).erase(unique((v).begin(), (v).end()), (v).end())
template <class T1, class T2> inline bool chmax(T1& a, const T2& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T1, class T2> inline bool chmin(T1& a, const T2& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

constexpr char enl = '\n';
constexpr int dx[] = {1, 0, -1, 0, 1, -1, -1, 1};
constexpr int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
constexpr long double eps = 1e-10;
constexpr int INF = 1'010'000'000;                 // 1e9
constexpr ll llINF = 3'010'000'000'000'000'000LL;  // 3e18
// constexpr ll MOD = 1'000'000'007LL;
constexpr ll MOD = 998244353LL;
using mint = static_modint<MOD>;

void Main([[maybe_unused]] int testcase_i) {
    din(int, n, m, q);
    vector<tuple<int, int, int, int>> event(m + q);
    rep(i, m) {
        din(int, d, a, b);
        event[i] = {d, INF, a, b};
    }
    rep(i, q) {
        din(int, e, s, t);
        event[i + m] = {e, i, s, t};
    }
    ranges::sort(event);
    cplib::IntervalSet<int> s;
    vector<bool> ans(q);
    for (auto& [day, qi, x, y] : event) {
        if (qi != INF) {
            ans[qi] = x >= y || s.mex(x) == s.mex(y);
        } else {
            s.insert(x, y);
        }
    }
    for (auto bo : ans) Yes(bo);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
    int t = 1;
    // cin >> t;
    rep(i, t) Main(i);
}