#include "FenwickTree.hpp"
#include <iostream>
#include <vector>

int main() {
	double arr[] = { 1, 3, 4, 8, 6, 1, 4, 2 };
	std::vector<int> vec = { 1, 3, 4, 8, 6, 1, 4, 2 };

	{
		DS::FenwickTree<double> tree(arr);
		std::cout << tree.querySum(1, 7) << std::endl;
		tree.queryAdd(2, 40);
		std::cout << tree.querySum(1, 7) << std::endl;
	}
	
	{
		DS::FenwickTree<int> tree(vec.cbegin(), vec.cend());
		std::cout << tree.querySum(1, 7) << std::endl;
		tree.queryAdd(2, 40);
		std::cout << tree.querySum(1, 7) << std::endl;
	}
	
	{
		DS::FenwickTree<int> tree{ 1, 3, 4, 8, 6, 1, 4, 2 };
		std::cout << tree.querySum(1, 7) << std::endl;
		tree.queryAdd(2, 40);
		std::cout << tree.querySum(1, 7) << std::endl;
	}

	{
		DS::FenwickTree<int> tree(vec.cbegin(), vec.cend());
		std::cout << tree.querySum(1, 7) << std::endl;
		tree.queryAdd(2, 40);
		std::cout << tree.querySum(1, 7) << std::endl;
	}
	return 0;
}