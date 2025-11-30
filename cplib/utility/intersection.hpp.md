---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: cplib/IntervalSet.hpp
    title: cplib/IntervalSet.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/2880/2880.test.cpp
    title: test/aoj/2880/2880.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"cplib/utility/intersection.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <utility>\n\nnamespace cplib {\n\n// [l1, r1)\u3068[l2, r2)\u306E\u5171\
    \u901A\u90E8\u5206\u3092\u6C42\u3081\u308B\n// \u5171\u901A\u90E8\u5206\u304C\u306A\
    \u3044\u5834\u5408\u3084\u5165\u529B\u304C l>r \u306E\u5834\u5408\u306F(0, 0)\u3092\
    \u8FD4\u3059\ntemplate <typename T>\nconstexpr inline std::pair<T, T> intersection(const\
    \ T& l1,\n                                              const T& r1,\n       \
    \                                       const T& l2,\n                       \
    \                       const T& r2) {\n    const T l = std::max(l1, l2);\n  \
    \  const T r = std::min(r1, r2);\n    if (l < r)\n        return std::make_pair(l,\
    \ r);\n    else\n        return std::make_pair(0, 0);\n}\n\n}  // namespace cplib\n\
    \n\n"
  code: "#ifndef CPLIB_INTERSECTION_HPP\n#define CPLIB_INTERSECTION_HPP 1\n\n#include\
    \ <algorithm>\n#include <utility>\n\nnamespace cplib {\n\n// [l1, r1)\u3068[l2,\
    \ r2)\u306E\u5171\u901A\u90E8\u5206\u3092\u6C42\u3081\u308B\n// \u5171\u901A\u90E8\
    \u5206\u304C\u306A\u3044\u5834\u5408\u3084\u5165\u529B\u304C l>r \u306E\u5834\u5408\
    \u306F(0, 0)\u3092\u8FD4\u3059\ntemplate <typename T>\nconstexpr inline std::pair<T,\
    \ T> intersection(const T& l1,\n                                             \
    \ const T& r1,\n                                              const T& l2,\n \
    \                                             const T& r2) {\n    const T l =\
    \ std::max(l1, l2);\n    const T r = std::min(r1, r2);\n    if (l < r)\n     \
    \   return std::make_pair(l, r);\n    else\n        return std::make_pair(0, 0);\n\
    }\n\n}  // namespace cplib\n\n#endif  // CPLIB_INTERSECTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: cplib/utility/intersection.hpp
  requiredBy:
  - cplib/IntervalSet.hpp
  timestamp: '2025-11-23 12:41:42+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/2880/2880.test.cpp
documentation_of: cplib/utility/intersection.hpp
layout: document
redirect_from:
- /library/cplib/utility/intersection.hpp
- /library/cplib/utility/intersection.hpp.html
title: cplib/utility/intersection.hpp
---
