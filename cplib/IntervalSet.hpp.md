---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: cplib/utility/intersection.hpp
    title: cplib/utility/intersection.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/2880/2880.test.cpp
    title: test/aoj/2880/2880.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/drken1215/algorithm/blob/c9e99d6fe51137f0dc10cf3ca7f28ec4b07a14a9/DataStructureSegment/intervals_management_with_noninvertible_del.cpp
  bundledCode: "#line 1 \"cplib/IntervalSet.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <limits>\n#include <ranges>\n#include\
    \ <set>\n#include <utility>\n#include <vector>\n#line 1 \"cplib/utility/intersection.hpp\"\
    \n\n\n\n#line 6 \"cplib/utility/intersection.hpp\"\n\nnamespace cplib {\n\n//\
    \ [l1, r1)\u3068[l2, r2)\u306E\u5171\u901A\u90E8\u5206\u3092\u6C42\u3081\u308B\
    \n// \u5171\u901A\u90E8\u5206\u304C\u306A\u3044\u5834\u5408\u3084\u5165\u529B\u304C\
    \ l>r \u306E\u5834\u5408\u306F(0, 0)\u3092\u8FD4\u3059\ntemplate <typename T>\n\
    constexpr inline std::pair<T, T> intersection(const T& l1,\n                 \
    \                             const T& r1,\n                                 \
    \             const T& l2,\n                                              const\
    \ T& r2) {\n    const T l = std::max(l1, l2);\n    const T r = std::min(r1, r2);\n\
    \    if (l < r)\n        return std::make_pair(l, r);\n    else\n        return\
    \ std::make_pair(0, 0);\n}\n\n}  // namespace cplib\n\n\n#line 13 \"cplib/IntervalSet.hpp\"\
    \n\nnamespace cplib {\n\n// Reference:\n// https://github.com/drken1215/algorithm/blob/c9e99d6fe51137f0dc10cf3ca7f28ec4b07a14a9/DataStructureSegment/intervals_management_with_noninvertible_del.cpp\n\
    \n// \u533A\u9593\u3092set\u3067\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\ntemplate\
    \ <std::totally_ordered coord = long long> struct IntervalSet {\n  public:\n \
    \   struct Interval {\n        coord l;\n        coord r;\n        auto operator<=>(const\
    \ Interval&) const = default;\n    };\n    using Set = std::set<Interval>;\n\n\
    \  private:\n    Set set;\n\n  public:\n    IntervalSet() {}\n    template <typename\
    \ T>\n        requires std::ranges::input_range<T> &&\n                 std::convertible_to<std::ranges::range_reference_t<T>,\n\
    \                                     Interval>\n    IntervalSet(const T& v) {\n\
    \        set = std::ranges::to<Set>(v);\n    }\n\n    constexpr auto begin() const\
    \ { return std::ranges::begin(set); }\n    constexpr auto end() const { return\
    \ std::ranges::end(set); }\n\n    // p\u4EE5\u4E0A\u306E\u70B9\u3092\u542B\u3080\
    \u533A\u9593\u306E\u3046\u3061\u6700\u3082\u5DE6\u306B\u3042\u308B\u3082\u306E\
    \u3078\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u53D6\u5F97\u3059\u308B\
    \n    // p\u4EE5\u4E0A\u306E\u70B9\u3092\u542B\u3080\u533A\u9593\u304C\u5B58\u5728\
    \u3057\u306A\u3044\u5834\u5408end\u3092\u8FD4\u3059\n    constexpr auto lower_bound(const\
    \ coord& p) const\n        requires std::same_as<decltype(std::numeric_limits<coord>::max()),\n\
    \                              coord>\n    {\n        auto it =\n            set.upper_bound(Interval(p,\
    \ std::numeric_limits<coord>::max()));\n        // assert(it == end() || p < it->l);\n\
    \        if (it == begin()) return it;\n        auto pit = std::ranges::prev(it);\n\
    \        // assert(pit->l <= p);\n        if (p < pit->r)\n            return\
    \ pit;\n        else\n            return it;\n    }\n\n    // p\u3092\u542B\u3080\
    \u533A\u9593\u3078\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u53D6\u5F97\
    \u3059\u308B\n    // p\u3092\u542B\u3080\u533A\u9593\u304C\u5B58\u5728\u3057\u306A\
    \u3044\u5834\u5408end\u3092\u8FD4\u3059\n    constexpr auto get_iterator(const\
    \ coord& p) const {\n        auto it = lower_bound(p);\n        if (it == end())\
    \ return it;\n        // assert(p < it->r);\n        if (it->l <= p)\n       \
    \     return it;\n        else\n            return end();\n    }\n\n    // p\u3092\
    \u542B\u3080\u533A\u9593\u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\
    \u308B\n    constexpr bool covered(const coord& p) const {\n        return get_iterator(p)\
    \ != end();\n    }\n\n    // [l, r)\u3092\u5B8C\u5168\u306B\u542B\u3080\u533A\u9593\
    \u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\u308B\n    constexpr bool\
    \ covered(const coord& l, const coord& r) const {\n        if (l >= r) return\
    \ true;\n        auto it = get_iterator(l);\n        return it != end() && r <=\
    \ it->r;\n    }\n\n    // p\u3068q\u304C\u540C\u3058\u533A\u9593\u306B\u542B\u307E\
    \u308C\u308B\u304B\u5224\u5B9A\u3059\u308B\n    // p\u307E\u305F\u306Fq\u304C\u3069\
    \u306E\u533A\u9593\u306B\u3082\u542B\u307E\u308C\u3066\u3044\u306A\u3044\u5834\
    \u5408false\u3092\u8FD4\u3059\n    constexpr bool same(const coord& p, const coord&\
    \ q) const {\n        if (!(covered(p) && covered(q))) return false;\n       \
    \ return get_iterator(p) == get_iterator(q);\n    }\n\n    // p\u4EE5\u4E0A\u306E\
    \u70B9\u306E\u3046\u3061\u3001\u3069\u306E\u533A\u9593\u306B\u3082\u542B\u307E\
    \u308C\u306A\u3044\u3088\u3046\u306A\u6700\u5DE6\u306E\u70B9\u3092\u8FD4\u3059\
    \n    constexpr coord mex(const coord& p = 0) const {\n        if (!covered(p))\
    \ return p;\n        return lower_bound(p)->r;\n    }\n\n    // set\u306B\u542B\
    \u307E\u308C\u308B\u533A\u9593\u5168\u4F53\u3068[l, r)\u306E\u5171\u901A\u90E8\
    \u5206\u3092vector\u3067\u8FD4\u3059\n    constexpr std::vector<Interval> intersection(const\
    \ coord& l,\n                                                 const coord& r)\
    \ const {\n        if (l >= r) return std::vector<Interval>();\n        std::vector<Interval>\
    \ result;\n        for (auto it = lower_bound(l); it != end() && it->l < r;\n\
    \             std::ranges::advance(it, 1)) {\n            auto [inter_l, inter_r]\
    \ = cplib::intersection(l, r, it->l, it->r);\n            // assert(inter_l <\
    \ inter_r);\n            result.push_back(Interval(inter_l, inter_r));\n     \
    \   }\n        return result;\n    }\n\n    // [l, r)\u306E\u3046\u3061set\u306B\
    \u542B\u307E\u308C\u306A\u3044\u90E8\u5206\u3092vector\u3067\u8FD4\u3059\n   \
    \ constexpr std::vector<Interval> excluded(const coord& l,\n                 \
    \                            const coord& r) const {\n        if (l >= r) return\
    \ std::vector<Interval>();\n        std::vector<Interval> inter_v = intersection(l,\
    \ r);\n        auto len = std::ranges::size(inter_v);\n        if (len == 0) {\n\
    \            return std::vector<Interval>(1, Interval(l, r));\n        }\n   \
    \     std::vector<Interval> result;\n        if (l < inter_v[0].l) {\n       \
    \     result.emplace_back(l, inter_v[0].l);\n        }\n        for (int i = 0;\
    \ i < int(len) - 1; ++i) {\n            result.emplace_back(inter_v[i].r, inter_v[i\
    \ + 1].l);\n        }\n        if (inter_v.back().r < r) {\n            result.emplace_back(inter_v.back().r,\
    \ r);\n        }\n        return result;\n    }\n\n    // todo: get_state(l, r)\
    \ intersection\u3068excluded\u3092\u5408\u308F\u305B\u308B\n    // get_state\u3092\
    \u4F7F\u3063\u3066not invertible\u306A\u95A2\u6570\u306B\u5BFE\u5FDC\u3059\u308B\
    \n    // \u9589\u533A\u9593\u30D0\u30FC\u30B8\u30E7\u30F3\u3092\u4F5C\u308B\n\n\
    \    // \u533A\u9593[l, r)\u3092\u8FFD\u52A0\u3059\u308B\n    // set\u306B\u533A\
    \u9593\u3092\u8FFD\u52A0\u3057\u305F\u76F4\u5F8C\u3001\u8FFD\u52A0\u3057\u305F\
    \u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\u5C02\u7528\u30A4\u30C6\u30EC\
    \u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\u3066add_func\u3092\u547C\u3073\
    \u51FA\u3059\n    // set\u306E\u533A\u9593\u3092\u524A\u9664\u3059\u308B\u76F4\
    \u524D\u3001\u524A\u9664\u3059\u308B\u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\
    \u308A\u5C02\u7528\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\
    \u3057\u3066del_func\u3092\u547C\u3073\u51FA\u3059\n    template <std::invocable<std::ranges::const_iterator_t<Set>>\
    \ AddFunc,\n              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>\n\
    \    void insert(coord l,\n                coord r,\n                const AddFunc&\
    \ add_func,\n                const DelFunc& del_func) {\n        if (l >= r) return;\n\
    \        // \u6D88\u3059\u533A\u9593\u306E\u3046\u3061\u6700\u3082\u5DE6\u306E\
    \u3082\u306E\u3092\u63A2\u3059\n        // \u53F3\u7AEF\u304Cl\u306E\u533A\u9593\
    \u304C\u3042\u308C\u3070\u307E\u3068\u3081\u308B\u305F\u3081\u306B\u6D88\u3059\
    \n        auto it = lower_bound(l);\n        if (it != begin()) {\n          \
    \  auto pit = std::ranges::prev(it);\n            // assert(pit->r <= l);\n  \
    \          if (pit->r == l) it = pit;\n        }\n        // [l, r]\u3068\u5171\
    \u901A\u90E8\u5206\u304C\u3042\u308B\u533A\u9593\u3092\u6D88\u3059\n        //\
    \ \u5DE6\u7AEF\u304Cr\u306E\u533A\u9593\u3082\u307E\u3068\u3081\u308B\u305F\u3081\
    \u306B\u6D88\u3059\n        while (it != end() && it->l <= r) {\n            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            if (it->l < l) l = it->l;\n            if (r < it->r) r = it->r;\n\
    \            it = set.erase(it);\n        }\n        // insert\n        // assert(l\
    \ < r);\n        it = set.emplace_hint(it, l, r);\n        add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \    }\n    // \u533A\u9593[l, r)\u3092\u8FFD\u52A0\u3059\u308B\n    void insert(const\
    \ coord& l, const coord& r) {\n        insert(\n            l, r, [](std::ranges::const_iterator_t<Set>)\
    \ {},\n            [](std::ranges::const_iterator_t<Set>) {});\n    }\n\n    //\
    \ \u533A\u9593[l, r)\u3092\u524A\u9664\u3059\u308B\n    // set\u306B\u533A\u9593\
    \u3092\u8FFD\u52A0\u3057\u305F\u76F4\u5F8C\u3001\u8FFD\u52A0\u3057\u305F\u533A\
    \u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\u5C02\u7528\u30A4\u30C6\u30EC\u30FC\
    \u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\u3066add_func\u3092\u547C\u3073\u51FA\
    \u3059\n    // set\u306E\u533A\u9593\u3092\u524A\u9664\u3059\u308B\u76F4\u524D\
    \u3001\u524A\u9664\u3059\u308B\u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\
    \u5C02\u7528\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\
    \u3066del_func\u3092\u547C\u3073\u51FA\u3059\n    template <std::invocable<std::ranges::const_iterator_t<Set>>\
    \ AddFunc,\n              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>\n\
    \    void erase(coord l,\n               coord r,\n               const AddFunc&\
    \ add_func,\n               const DelFunc& del_func) {\n        if (l >= r) return;\n\
    \        auto it = lower_bound(l);\n        while (it != end() && it->l < r) {\n\
    \            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            coord tl = it->l, tr = it->r;\n            it = set.erase(it);\n\
    \            if (r < tr) {\n                it = set.emplace_hint(it, r, tr);\n\
    \                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            }\n            if (tl < l) {\n                it = set.emplace_hint(it,\
    \ tl, l);\n                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \                std::ranges::advance(it, 1);\n            }\n        }\n    }\n\
    \    // \u533A\u9593[l, r)\u3092\u524A\u9664\u3059\u308B\n    void erase(const\
    \ coord& l, const coord& r) {\n        erase(\n            l, r, [](std::ranges::const_iterator_t<Set>)\
    \ {},\n            [](std::ranges::const_iterator_t<Set>) {});\n    }\n};\n\n\
    }  // namespace cplib\n\n\n"
  code: "#ifndef CPLIB_INTERVALSET_HPP\n#define CPLIB_INTERVALSET_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include\
    \ <ranges>\n#include <set>\n#include <utility>\n#include <vector>\n#include \"\
    cplib/utility/intersection.hpp\"\n\nnamespace cplib {\n\n// Reference:\n// https://github.com/drken1215/algorithm/blob/c9e99d6fe51137f0dc10cf3ca7f28ec4b07a14a9/DataStructureSegment/intervals_management_with_noninvertible_del.cpp\n\
    \n// \u533A\u9593\u3092set\u3067\u7BA1\u7406\u3059\u308B\u30AF\u30E9\u30B9\ntemplate\
    \ <std::totally_ordered coord = long long> struct IntervalSet {\n  public:\n \
    \   struct Interval {\n        coord l;\n        coord r;\n        auto operator<=>(const\
    \ Interval&) const = default;\n    };\n    using Set = std::set<Interval>;\n\n\
    \  private:\n    Set set;\n\n  public:\n    IntervalSet() {}\n    template <typename\
    \ T>\n        requires std::ranges::input_range<T> &&\n                 std::convertible_to<std::ranges::range_reference_t<T>,\n\
    \                                     Interval>\n    IntervalSet(const T& v) {\n\
    \        set = std::ranges::to<Set>(v);\n    }\n\n    constexpr auto begin() const\
    \ { return std::ranges::begin(set); }\n    constexpr auto end() const { return\
    \ std::ranges::end(set); }\n\n    // p\u4EE5\u4E0A\u306E\u70B9\u3092\u542B\u3080\
    \u533A\u9593\u306E\u3046\u3061\u6700\u3082\u5DE6\u306B\u3042\u308B\u3082\u306E\
    \u3078\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u53D6\u5F97\u3059\u308B\
    \n    // p\u4EE5\u4E0A\u306E\u70B9\u3092\u542B\u3080\u533A\u9593\u304C\u5B58\u5728\
    \u3057\u306A\u3044\u5834\u5408end\u3092\u8FD4\u3059\n    constexpr auto lower_bound(const\
    \ coord& p) const\n        requires std::same_as<decltype(std::numeric_limits<coord>::max()),\n\
    \                              coord>\n    {\n        auto it =\n            set.upper_bound(Interval(p,\
    \ std::numeric_limits<coord>::max()));\n        // assert(it == end() || p < it->l);\n\
    \        if (it == begin()) return it;\n        auto pit = std::ranges::prev(it);\n\
    \        // assert(pit->l <= p);\n        if (p < pit->r)\n            return\
    \ pit;\n        else\n            return it;\n    }\n\n    // p\u3092\u542B\u3080\
    \u533A\u9593\u3078\u306E\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u53D6\u5F97\
    \u3059\u308B\n    // p\u3092\u542B\u3080\u533A\u9593\u304C\u5B58\u5728\u3057\u306A\
    \u3044\u5834\u5408end\u3092\u8FD4\u3059\n    constexpr auto get_iterator(const\
    \ coord& p) const {\n        auto it = lower_bound(p);\n        if (it == end())\
    \ return it;\n        // assert(p < it->r);\n        if (it->l <= p)\n       \
    \     return it;\n        else\n            return end();\n    }\n\n    // p\u3092\
    \u542B\u3080\u533A\u9593\u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\
    \u308B\n    constexpr bool covered(const coord& p) const {\n        return get_iterator(p)\
    \ != end();\n    }\n\n    // [l, r)\u3092\u5B8C\u5168\u306B\u542B\u3080\u533A\u9593\
    \u304C\u5B58\u5728\u3059\u308B\u304B\u5224\u5B9A\u3059\u308B\n    constexpr bool\
    \ covered(const coord& l, const coord& r) const {\n        if (l >= r) return\
    \ true;\n        auto it = get_iterator(l);\n        return it != end() && r <=\
    \ it->r;\n    }\n\n    // p\u3068q\u304C\u540C\u3058\u533A\u9593\u306B\u542B\u307E\
    \u308C\u308B\u304B\u5224\u5B9A\u3059\u308B\n    // p\u307E\u305F\u306Fq\u304C\u3069\
    \u306E\u533A\u9593\u306B\u3082\u542B\u307E\u308C\u3066\u3044\u306A\u3044\u5834\
    \u5408false\u3092\u8FD4\u3059\n    constexpr bool same(const coord& p, const coord&\
    \ q) const {\n        if (!(covered(p) && covered(q))) return false;\n       \
    \ return get_iterator(p) == get_iterator(q);\n    }\n\n    // p\u4EE5\u4E0A\u306E\
    \u70B9\u306E\u3046\u3061\u3001\u3069\u306E\u533A\u9593\u306B\u3082\u542B\u307E\
    \u308C\u306A\u3044\u3088\u3046\u306A\u6700\u5DE6\u306E\u70B9\u3092\u8FD4\u3059\
    \n    constexpr coord mex(const coord& p = 0) const {\n        if (!covered(p))\
    \ return p;\n        return lower_bound(p)->r;\n    }\n\n    // set\u306B\u542B\
    \u307E\u308C\u308B\u533A\u9593\u5168\u4F53\u3068[l, r)\u306E\u5171\u901A\u90E8\
    \u5206\u3092vector\u3067\u8FD4\u3059\n    constexpr std::vector<Interval> intersection(const\
    \ coord& l,\n                                                 const coord& r)\
    \ const {\n        if (l >= r) return std::vector<Interval>();\n        std::vector<Interval>\
    \ result;\n        for (auto it = lower_bound(l); it != end() && it->l < r;\n\
    \             std::ranges::advance(it, 1)) {\n            auto [inter_l, inter_r]\
    \ = cplib::intersection(l, r, it->l, it->r);\n            // assert(inter_l <\
    \ inter_r);\n            result.push_back(Interval(inter_l, inter_r));\n     \
    \   }\n        return result;\n    }\n\n    // [l, r)\u306E\u3046\u3061set\u306B\
    \u542B\u307E\u308C\u306A\u3044\u90E8\u5206\u3092vector\u3067\u8FD4\u3059\n   \
    \ constexpr std::vector<Interval> excluded(const coord& l,\n                 \
    \                            const coord& r) const {\n        if (l >= r) return\
    \ std::vector<Interval>();\n        std::vector<Interval> inter_v = intersection(l,\
    \ r);\n        auto len = std::ranges::size(inter_v);\n        if (len == 0) {\n\
    \            return std::vector<Interval>(1, Interval(l, r));\n        }\n   \
    \     std::vector<Interval> result;\n        if (l < inter_v[0].l) {\n       \
    \     result.emplace_back(l, inter_v[0].l);\n        }\n        for (int i = 0;\
    \ i < int(len) - 1; ++i) {\n            result.emplace_back(inter_v[i].r, inter_v[i\
    \ + 1].l);\n        }\n        if (inter_v.back().r < r) {\n            result.emplace_back(inter_v.back().r,\
    \ r);\n        }\n        return result;\n    }\n\n    // todo: get_state(l, r)\
    \ intersection\u3068excluded\u3092\u5408\u308F\u305B\u308B\n    // get_state\u3092\
    \u4F7F\u3063\u3066not invertible\u306A\u95A2\u6570\u306B\u5BFE\u5FDC\u3059\u308B\
    \n    // \u9589\u533A\u9593\u30D0\u30FC\u30B8\u30E7\u30F3\u3092\u4F5C\u308B\n\n\
    \    // \u533A\u9593[l, r)\u3092\u8FFD\u52A0\u3059\u308B\n    // set\u306B\u533A\
    \u9593\u3092\u8FFD\u52A0\u3057\u305F\u76F4\u5F8C\u3001\u8FFD\u52A0\u3057\u305F\
    \u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\u5C02\u7528\u30A4\u30C6\u30EC\
    \u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\u3066add_func\u3092\u547C\u3073\
    \u51FA\u3059\n    // set\u306E\u533A\u9593\u3092\u524A\u9664\u3059\u308B\u76F4\
    \u524D\u3001\u524A\u9664\u3059\u308B\u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\
    \u308A\u5C02\u7528\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\
    \u3057\u3066del_func\u3092\u547C\u3073\u51FA\u3059\n    template <std::invocable<std::ranges::const_iterator_t<Set>>\
    \ AddFunc,\n              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>\n\
    \    void insert(coord l,\n                coord r,\n                const AddFunc&\
    \ add_func,\n                const DelFunc& del_func) {\n        if (l >= r) return;\n\
    \        // \u6D88\u3059\u533A\u9593\u306E\u3046\u3061\u6700\u3082\u5DE6\u306E\
    \u3082\u306E\u3092\u63A2\u3059\n        // \u53F3\u7AEF\u304Cl\u306E\u533A\u9593\
    \u304C\u3042\u308C\u3070\u307E\u3068\u3081\u308B\u305F\u3081\u306B\u6D88\u3059\
    \n        auto it = lower_bound(l);\n        if (it != begin()) {\n          \
    \  auto pit = std::ranges::prev(it);\n            // assert(pit->r <= l);\n  \
    \          if (pit->r == l) it = pit;\n        }\n        // [l, r]\u3068\u5171\
    \u901A\u90E8\u5206\u304C\u3042\u308B\u533A\u9593\u3092\u6D88\u3059\n        //\
    \ \u5DE6\u7AEF\u304Cr\u306E\u533A\u9593\u3082\u307E\u3068\u3081\u308B\u305F\u3081\
    \u306B\u6D88\u3059\n        while (it != end() && it->l <= r) {\n            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            if (it->l < l) l = it->l;\n            if (r < it->r) r = it->r;\n\
    \            it = set.erase(it);\n        }\n        // insert\n        // assert(l\
    \ < r);\n        it = set.emplace_hint(it, l, r);\n        add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \    }\n    // \u533A\u9593[l, r)\u3092\u8FFD\u52A0\u3059\u308B\n    void insert(const\
    \ coord& l, const coord& r) {\n        insert(\n            l, r, [](std::ranges::const_iterator_t<Set>)\
    \ {},\n            [](std::ranges::const_iterator_t<Set>) {});\n    }\n\n    //\
    \ \u533A\u9593[l, r)\u3092\u524A\u9664\u3059\u308B\n    // set\u306B\u533A\u9593\
    \u3092\u8FFD\u52A0\u3057\u305F\u76F4\u5F8C\u3001\u8FFD\u52A0\u3057\u305F\u533A\
    \u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\u5C02\u7528\u30A4\u30C6\u30EC\u30FC\
    \u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\u3066add_func\u3092\u547C\u3073\u51FA\
    \u3059\n    // set\u306E\u533A\u9593\u3092\u524A\u9664\u3059\u308B\u76F4\u524D\
    \u3001\u524A\u9664\u3059\u308B\u533A\u9593\u3078\u306E\u8AAD\u307F\u53D6\u308A\
    \u5C02\u7528\u30A4\u30C6\u30EC\u30FC\u30BF\u30FC\u3092\u5F15\u6570\u3068\u3057\
    \u3066del_func\u3092\u547C\u3073\u51FA\u3059\n    template <std::invocable<std::ranges::const_iterator_t<Set>>\
    \ AddFunc,\n              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>\n\
    \    void erase(coord l,\n               coord r,\n               const AddFunc&\
    \ add_func,\n               const DelFunc& del_func) {\n        if (l >= r) return;\n\
    \        auto it = lower_bound(l);\n        while (it != end() && it->l < r) {\n\
    \            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            coord tl = it->l, tr = it->r;\n            it = set.erase(it);\n\
    \            if (r < tr) {\n                it = set.emplace_hint(it, r, tr);\n\
    \                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \            }\n            if (tl < l) {\n                it = set.emplace_hint(it,\
    \ tl, l);\n                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));\n\
    \                std::ranges::advance(it, 1);\n            }\n        }\n    }\n\
    \    // \u533A\u9593[l, r)\u3092\u524A\u9664\u3059\u308B\n    void erase(const\
    \ coord& l, const coord& r) {\n        erase(\n            l, r, [](std::ranges::const_iterator_t<Set>)\
    \ {},\n            [](std::ranges::const_iterator_t<Set>) {});\n    }\n};\n\n\
    }  // namespace cplib\n\n#endif  // CPLIB_INTERVALSET_HPP\n"
  dependsOn:
  - cplib/utility/intersection.hpp
  isVerificationFile: false
  path: cplib/IntervalSet.hpp
  requiredBy: []
  timestamp: '2025-11-30 04:04:06+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/2880/2880.test.cpp
documentation_of: cplib/IntervalSet.hpp
layout: document
redirect_from:
- /library/cplib/IntervalSet.hpp
- /library/cplib/IntervalSet.hpp.html
title: cplib/IntervalSet.hpp
---
