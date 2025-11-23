#ifndef CPLIB_INTERVALSET_HPP
#define CPLIB_INTERVALSET_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <ranges>
#include <set>
#include <utility>
#include <vector>
#include "cplib/utility/intersection.hpp"

namespace cplib {

// Reference:
// https://github.com/drken1215/algorithm/blob/c9e99d6fe51137f0dc10cf3ca7f28ec4b07a14a9/DataStructureSegment/intervals_management_with_noninvertible_del.cpp

// 区間をsetで管理するクラス
template <std::totally_ordered coord = long long> struct IntervalSet {
  public:
    struct Interval {
        coord l;
        coord r;
        auto operator<=>(const Interval&) const = default;
    };
    using Set = std::set<Interval>;

  private:
    Set set;

  public:
    IntervalSet() {}
    template <typename T>
        requires std::ranges::input_range<T> &&
                 std::convertible_to<std::ranges::range_reference_t<T>,
                                     Interval>
    IntervalSet(const T& v) {
        set = std::ranges::to<Set>(v);
    }

    constexpr auto begin() const { return std::ranges::begin(set); }
    constexpr auto end() const { return std::ranges::end(set); }

    // p以上の点を含む区間のうち最も左にあるものへのイテレーターを取得する
    // p以上の点を含む区間が存在しない場合endを返す
    constexpr auto lower_bound(const coord& p) const
        requires std::same_as<decltype(std::numeric_limits<coord>::max()),
                              coord>
    {
        auto it =
            set.upper_bound(Interval(p, std::numeric_limits<coord>::max()));
        // assert(it == end() || p < it->l);
        if (it == begin()) return it;
        auto pit = std::ranges::prev(it);
        // assert(pit->l <= p);
        if (p < pit->r)
            return pit;
        else
            return it;
    }

    // pを含む区間へのイテレーターを取得する
    // pを含む区間が存在しない場合endを返す
    constexpr auto get_iterator(const coord& p) const {
        auto it = lower_bound(p);
        if (it == end()) return it;
        // assert(p < it->r);
        if (it->l <= p)
            return it;
        else
            return end();
    }

    // pを含む区間が存在するか判定する
    constexpr bool covered(const coord& p) const {
        return get_iterator(p) != end();
    }

    // [l, r)を完全に含む区間が存在するか判定する
    constexpr bool covered(const coord& l, const coord& r) const {
        if (l >= r) return true;
        auto it = get_iterator(l);
        return it != end() && r <= it->r;
    }

    // pとqが同じ区間に含まれるか判定する
    // pまたはqがどの区間にも含まれていない場合falseを返す
    constexpr bool same(const coord& p, const coord& q) const {
        if (!(covered(p) && covered(q))) return false;
        return get_iterator(p) == get_iterator(q);
    }

    // p以上の点のうち、どの区間にも含まれないような最左の点を返す
    constexpr coord mex(const coord& p = 0) const {
        if (!covered(p)) return p;
        return lower_bound(p)->r;
    }

    // setに含まれる区間全体と[l, r)の共通部分をvectorで返す
    constexpr std::vector<Interval> intersection(const coord& l,
                                                 const coord& r) const {
        if (l >= r) return std::vector<Interval>();
        std::vector<Interval> result;
        for (auto it = lower_bound(l); it != end() && it->l < r;
             std::ranges::advance(it, 1)) {
            auto [inter_l, inter_r] = cplib::intersection(l, r, it->l, it->r);
            // assert(inter_l < inter_r);
            result.push_back(Interval(inter_l, inter_r));
        }
        return result;
    }

    // [l, r)のうちsetに含まれない部分をvectorで返す
    constexpr std::vector<Interval> excluded(const coord& l,
                                             const coord& r) const {
        if (l >= r) return std::vector<Interval>();
        std::vector<Interval> inter_v = intersection(l, r);
        auto len = std::ranges::size(inter_v);
        if (len == 0) {
            return std::vector<Interval>(1, Interval(l, r));
        }
        std::vector<Interval> result;
        if (l < inter_v[0].l) {
            result.emplace_back(l, inter_v[0].l);
        }
        for (int i = 0; i < int(len) - 1; ++i) {
            result.emplace_back(inter_v[i].r, inter_v[i + 1].l);
        }
        if (inter_v.back().r < r) {
            result.emplace_back(inter_v.back().r, r);
        }
        return result;
    }

    // todo: get_state(l, r) intersectionとexcludedを合わせる
    // get_stateを使ってnot invertibleな関数に対応する

    // 区間[l, r)を追加する
    // setに区間を追加した直後、追加した区間への読み取り専用イテレーターを引数としてadd_funcを呼び出す
    // setの区間を削除する直前、削除する区間への読み取り専用イテレーターを引数としてdel_funcを呼び出す
    template <std::invocable<std::ranges::const_iterator_t<Set>> AddFunc,
              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>
    void insert(coord l,
                coord r,
                const AddFunc& add_func,
                const DelFunc& del_func) {
        if (l >= r) return;
        // 消す区間のうち最も左のものを探す
        // 右端がlの区間があればまとめるために消す
        auto it = lower_bound(l);
        if (it != begin()) {
            auto pit = std::ranges::prev(it);
            // assert(pit->r <= l);
            if (pit->r == l) it = pit;
        }
        // [l, r]と共通部分がある区間を消す
        // 左端がrの区間もまとめるために消す
        while (it != end() && it->l <= r) {
            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));
            if (it->l < l) l = it->l;
            if (r < it->r) r = it->r;
            it = set.erase(it);
        }
        // insert
        if (l < r) {
            it = set.emplace_hint(it, l, r);
            add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));
        }
    }
    // 区間[l, r)を追加する
    void insert(const coord& l, const coord& r) {
        insert(
            l, r, [](std::ranges::const_iterator_t<Set>) {},
            [](std::ranges::const_iterator_t<Set>) {});
    }

    // 区間[l, r)を削除する
    // setに区間を追加した直後、追加した区間への読み取り専用イテレーターを引数としてadd_funcを呼び出す
    // setの区間を削除する直前、削除する区間への読み取り専用イテレーターを引数としてdel_funcを呼び出す
    template <std::invocable<std::ranges::const_iterator_t<Set>> AddFunc,
              std::invocable<std::ranges::const_iterator_t<Set>> DelFunc>
    void erase(coord l,
               coord r,
               const AddFunc& add_func,
               const DelFunc& del_func) {
        if (l >= r) return;
        auto it = lower_bound(l);
        while (it != end() && it->l < r) {
            del_func(static_cast<std::ranges::const_iterator_t<Set>>(it));
            coord tl = it->l, tr = it->r;
            it = set.erase(it);
            if (r < tr) {
                it = set.emplace_hint(it, r, tr);
                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));
            }
            if (tl < l) {
                it = set.emplace_hint(it, tl, l);
                add_func(static_cast<std::ranges::const_iterator_t<Set>>(it));
                std::ranges::advance(it, 1);
            }
        }
    }
    // 区間[l, r)を削除する
    void erase(const coord& l, const coord& r) {
        erase(
            l, r, [](std::ranges::const_iterator_t<Set>) {},
            [](std::ranges::const_iterator_t<Set>) {});
    }
};

}  // namespace cplib

#endif  // CPLIB_INTERVALSET_HPP
