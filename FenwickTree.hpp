#ifndef __FENWICK_TREE_
#define __FENWICK_TREE_
#include <type_traits>
#include <initializer_list>

namespace DS {
	template <typename T>
	class FenwickTree {
	public:
		using size_type = size_t;
		template<size_type N>
		explicit FenwickTree(T(&arr)[N]) noexcept
			:tree(new T[N + 1]), sz(N) {
			
			tree[0] = T();
			for (auto i = 0; i < sz; ++i)
				tree[i + 1] = arr[i];

			make_fenwick_tree();
		}
		template <typename ConstIter>
		explicit FenwickTree(ConstIter&& begin, ConstIter&& end) noexcept
			:tree(new T[(end - begin) + 1]), sz(end - begin)
		{
			tree[0] = T();
			auto i = 1;
			for (auto it = begin; it != end; ++it, ++i)
				tree[i] = *it;

			make_fenwick_tree();
		}
		explicit FenwickTree(std::initializer_list<T> list) noexcept
			:tree(new T[list.size() + 1]), sz(list.size())
		{
			tree[0] = T();
			auto i = 1;
			for (auto it = list.begin(); it != list.end(); ++it, ++i)
				tree[i] = *it;

			make_fenwick_tree();
		}
		T querySum(size_type from, size_type to) const noexcept{
			return sum(to) - sum(from - 1);
		}
		void queryAdd(size_type k, T x) noexcept {
			while (k <= sz) {
				tree[k] += x;
				k += p(k);
			}
		}
		~FenwickTree() {
			delete[] tree;
		}
	private:
		T* tree;
		size_type sz;
		
		static constexpr inline size_type p(size_type k) noexcept {
			using signed_type = std::make_signed_t<size_type>;
			return static_cast<signed_type>(k) & -static_cast<signed_type>(k);
		}

		void make_fenwick_tree() noexcept {
			auto* temp = new T[sz + 1];
			temp[0] = T();
			for (auto k = 1; k <= sz; ++k) {
				auto sum = T();
				for (auto j = k - (p(k) - 1); j <= k; ++j) {
					sum += tree[j];
				}
				temp[k] = sum;
			}
			delete[] tree;
			tree = temp;
		}

		T sum(size_type k) const noexcept {
			T s = T();
			while (k >= 1) {
				s += tree[k];
				k -= p(k);
			}
			return s;
		}
	};
};
#endif