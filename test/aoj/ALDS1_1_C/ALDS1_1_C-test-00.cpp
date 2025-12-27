// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C
#include <bits/stdc++.h>
#include <atcoder/modint>
#include "cplib/is_prime.hpp"
#include "cplib/vector_io.hpp"

using namespace std;
using namespace atcoder;
using namespace cplib;

#ifdef DEBUG
template <typename T, typename U> void debug_print(T var_name, U value) {
    cerr << var_name << ": " << value << endl;
}
#define debug(x) debug_print(#x, x)
constexpr bool is_debug = true;
#else
//#pragma GCC target("arch=skylake-avx512")
#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
#define debug(x)
constexpr bool is_debug = false;
#endif

using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using vector2 = vector<vector<T>>;
template <typename T> using vector3 = vector<vector2<T>>;
template <typename T> using vector4 = vector<vector3<T>>;
template <typename T> using vector5 = vector<vector4<T>>;
template <typename T> using vector6 = vector<vector5<T>>;
template <typename T>
inline vector2<T> make_vector2(const size_t l0,
                               const size_t l1,
                               const T& init = T()) {
    return vector2<T>(l0, vector<T>(l1, init));
}
template <typename T>
inline vector3<T> make_vector3(const size_t l0,
                               const size_t l1,
                               const size_t l2,
                               const T& init = T()) {
    return vector3<T>(l0, make_vector2<T>(l1, l2, init));
}
template <typename T>
inline vector4<T> make_vector4(const size_t l0,
                               const size_t l1,
                               const size_t l2,
                               const size_t l3,
                               const T& init = T()) {
    return vector4<T>(l0, make_vector3<T>(l1, l2, l3, init));
}
template <typename T>
inline vector5<T> make_vector5(const size_t l0,
                               const size_t l1,
                               const size_t l2,
                               const size_t l3,
                               const size_t l4,
                               const T& init = T()) {
    return vector5<T>(l0, make_vector4<T>(l1, l2, l3, l4, init));
}
template <typename T>
inline vector6<T> make_vector6(const size_t l0,
                               const size_t l1,
                               const size_t l2,
                               const size_t l3,
                               const size_t l4,
                               const size_t l5,
                               const T& init = T()) {
    return vector6<T>(l0, make_vector5<T>(l1, l2, l3, l4, l5, init));
}

#define rep(...) overloadrep(__VA_ARGS__, rep4_, rep3_, rep2_)(__VA_ARGS__)
#define overloadrep(_1, _2, _3, _4, repn_, ...) repn_
#define rep2_(i, n) rep4_(i, 0, n, 1)
#define rep3_(i, a, b) rep4_(i, a, b, 1)
#define rep4_(i, a, b, s) for (auto i = (a); i < (b); i += (s))
#define repr(i, a, b) for (auto i = (b) - 1; i >= (a); --i)
#define foreach(x, a) for (auto& x : (a))

inline void din_() {}
template <class Head, class... Tail>
inline void din_(Head&& head, Tail&&... tail) {
    cin >> head;
    din_(move(tail)...);
}
#define din(T, ...) \
    T __VA_ARGS__;  \
    din_(__VA_ARGS__)

inline void dout() { cout << '\n'; }
template <typename Head, typename... Tail>
inline void dout(const Head& head, const Tail&... tail) {
    cout << head;
    if constexpr (sizeof...(tail) > 0) {
        cout << ' ';
    }
    dout(tail...);
}

template <class T = ll> inline T IN() {
    T x;
    cin >> x;
    return (x);
}

inline void YesNo(bool b, const string yes, const string no) noexcept {
    cout << (b ? yes : no) << '\n';
}
inline void YES(bool b) noexcept { YesNo(b, "YES", "NO"); }
inline void Yes(bool b) noexcept { YesNo(b, "Yes", "No"); }
inline void POSSIBLE(bool b) noexcept { YesNo(b, "POSSIBLE", "IMPOSSIBLE"); }
inline void Possible(bool b) noexcept { YesNo(b, "Possible", "Impossible"); }
inline void FIRST(bool b) noexcept { YesNo(b, "FIRST", "SECOND"); }
inline void First(bool b) noexcept { YesNo(b, "First", "Second"); }

#define all(x) (x).begin(), (x).end()
template <typename T> inline int siz(const T& x) { return int(x.size()); }
template <typename IntLike> constexpr int Pcnt(const IntLike n) {
    return popcount(static_cast<unsigned long long>(n));
}
template <typename IntLike> constexpr ll Bit(const IntLike n) {
    return 1LL << n;
}
template <typename T> inline void uniq(vector<T>& v) {
    auto result = ranges::unique(v);
    v.erase(result.begin(), result.end());
}

template <class T1, class T2>
    requires totally_ordered_with<T1, T2> && assignable_from<T1&, T2>
constexpr bool chmax(T1& a, const T2& b) noexcept {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T1, class T2>
    requires totally_ordered_with<T1, T2> && assignable_from<T1&, T2>
constexpr bool chmin(T1& a, const T2& b) noexcept {
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
//constexpr ll MOD = 1'000'000'007LL;
constexpr ll MOD = 998244353LL;
using mint = static_modint<MOD>;

void Main([[maybe_unused]] int testcase_i) {
    din(int, n);
    int ans = 0;
    rep(i, n) if (is_prime(IN()))++ ans;
    dout(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
    int t = 1;
    //cin >> t;
    rep(i, t) Main(i);
}