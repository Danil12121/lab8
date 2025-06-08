#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


template <class It, class Out, class Compare=std::less<>>
Out merge(It first1, It last1, It first2, It last2, Out out, Compare cmp=Compare{}){
    while (first1 != last1 && first2 != last2){
        if (cmp(*first1, *first2)) {
            *out = *first1;
            ++first1;
        } else {
            *out = *first2;
            ++first2;
        }
        ++out;
    }
    out = std::copy(first1, last1, out);
    out = std::copy(first2, last2, out);

    return out;
}
template <class It, class Out, class Compare=std::less<>>
Out merge_sort(It first, It last, Out out, Compare cmp=Compare{}){
    auto len = std::distance(first, last);

    if (len <= 1) {
        return std::copy(first, last, out);
    }

    auto mid = std::next(first, len / 2);
    std::vector<typename std::iterator_traits<It>::value_type> left_buf, right_buf;

    merge_sort(first, mid, std::back_inserter(left_buf), cmp);
    merge_sort(mid, last, std::back_inserter(right_buf), cmp);

    return merge(
            left_buf.begin(), left_buf.end(),
            right_buf.begin(), right_buf.end(),
            out, cmp
    );
}
template <class It, class Compare = std::less<>>
void inplace_merge_sort(It first, It last, Compare cmp = Compare{}) {
    auto inplace_merge = [&](It begin, It mid, It end) {
        if (begin == mid || mid == end) return;

        It left = begin;
        It right = mid;

        while (left != right && right != end) {
            if (cmp(*right, *left)) {
                std::rotate(left, right, std::next(right));
                ++right;
            }
            ++left;
        }
    };

    auto sort = [&](auto& self, It start, It end) -> void {
        if (std::distance(start, end) <= 1)
            return;

        It mid = std::next(start, std::distance(start, end) / 2);
        self(self, start, mid);
        self(self, mid, end);
        inplace_merge(start, mid, end);
    };

    sort(sort, first, last);
}

template<class It, class Compare = std::less<>>
void heap_sort(It first, It last, Compare cmp = Compare{}) {
    using std::swap;

    auto heap_size = last - first;
    if (heap_size <= 1) return;
    std::function<void(decltype(heap_size), decltype(heap_size))> heapify;
    heapify = [&first, &cmp, &heapify](auto heap_size, auto i) {
        auto largest = i;
        auto left = 2 * i + 1;
        auto right = 2 * i + 2;

        if (left < heap_size && cmp(*(first + largest), *(first + left))) {
            largest = left;
        }

        if (right < heap_size && cmp(*(first + largest), *(first + right))) {
            largest = right;
        }

        if (largest != i) {
            swap(*(first + i), *(first + largest));
            heapify(heap_size, largest);
        }
    };


    for (auto i = heap_size / 2 - 1; i >= 0; --i) {
        heapify(heap_size, i);
    }


    for (auto i = heap_size - 1; i > 0; --i) {
        swap(*first, *(first + i));
        heapify(i, 0);
    }
}

template <class It, class Compare = std::less<>>
void quick_sort(It first, It last, Compare cmp = Compare{}) {
    if (first == last || std::next(first) == last) {
        return;
    }

    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto left = first;
    auto right = std::prev(last);

    while (left <= right) {
        while (cmp(*left, pivot)) {
            ++left;
        }
        while (cmp(pivot, *right)) {
            --right;
        }

        if (left <= right) {
            std::iter_swap(left, right);
            ++left;
            --right;
        }
    }

    quick_sort(first, right + 1, cmp);
    quick_sort(left, last, cmp);
}
template <class It, class Compare = std::less<>>
void insertion_sort(It first, It last, Compare cmp = Compare{}) {
    if (first == last) {
        return;
    }

    for (auto it = std::next(first); it != last; ++it) {
        auto key = std::move(*it);
        auto j = it;

        while (j != first && cmp(key, *std::prev(j))) {
            *j = std::move(*std::prev(j));
            --j;
        }

        *j = std::move(key);
    }
}
int main() {
    std::vector<int> a = {1, 3, 5, 9};
    std::vector<int> b = {2, 4, 6, 7, 8};
    std::vector<int> result;

    merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(result), std::less());
    for (int x: result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<int> v = {5, 3, 1, 4, 2};
    std::vector<int> result2;
    merge_sort(v.begin(), v.end(), std::back_inserter(result2));
    for (int x: result2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    inplace_merge_sort(v.begin(), v.end());
    for (int x: v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<int> v2 = {5, 3, 1, 4, 2};
    heap_sort(v2.begin(), v2.end());
    for (int x: v2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<int> v3 = {5, 3, 1, 4, 2};
    quick_sort(v3.begin(), v3.end());
    for (int x: v3) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<int> v4 = {5, 3, 1, 4, 2};
    insertion_sort(v4.begin(), v4.end());
    for (int x: v4) {
        std::cout << x << " ";
    }
}
