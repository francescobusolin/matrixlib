#include<iostream>
#include "matrix.h"
#include "iterators.h"

int main() {
	size_t r = 5;
	size_t c = 5;
	size_t idx = 0;
	matrix<int> a(r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			a(i, j) = idx;
			idx++;
		}
	}
	std::cout << "matrix a" << " \n";
	for (int i = 0; i < a.get_rows(); i++) {
		for (int j = 0; j < a.get_cols(); j++) {
			std::cout << a(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	std::cout << "matrix aT" << " \n";
	auto at = a.transpose();
	for (int i = 0; i < at.get_rows(); i++) {
		for (int j = 0; j < at.get_cols(); j++) {
			std::cout << at(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	std::cout << "build a vector from main diagonal of a" << " \n";
	auto ad = a.vectorize();
	for (int i = 0; i < ad.get_rows(); i++) {
		for (int j = 0; j < ad.get_cols(); j++) {
			std::cout << ad(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;

	const auto adc = a.expand();
	std::cout << "build a diagonal matrix  from first coloumn of a" << " \n";
	for (int i = 0; i < adc.get_rows(); i++) {
		for (int j = 0; j < adc.get_cols(); j++) {
			std::cout << adc(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;

	a(0, 0) = 42;
	std::cout << "check sharing memory: matrix aT with changed (0,0) in a" << " \n";
	// I see the change since they share the memory
	for (int i = 0; i < at.get_rows(); i++) {
		for (int j = 0; j < at.get_cols(); j++) {
			std::cout << at(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;

	matrix<int> copy = a;
	a(0, 0) = 0;
	std::cout << "check deep copy: copy of matrix a in which  (0,0) is restored. " << " \n";
	std::cout << "In copy, element (0,0) is still 42" << " \n";
	// I do not see the change since they don't share the memory
	for (int i = 0; i < copy.get_rows(); i++) {
		for (int j = 0; j < copy.get_cols(); j++) {
			std::cout << copy(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	// of course we can chain operations, with little overhead at runtime, since none of them actually
	// perform any change in the data, we are just stacking decorators, at runtime we will unroll everything up to the standard
	//one that will have the correct (i,j) after all the transformations.
	//So for an arbitrary long chain, only 1 access to the data is performed, which is the best case scenario.
	const auto tdt = a.transpose().vectorize().expand();
	std::cout << "check chain: just to show that a sequence of operations is possible" << " \n";
	for (int i = 0; i < tdt.get_rows(); i++) {
		for (int j = 0; j < tdt.get_cols(); j++) {
			std::cout << tdt(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	std::cout << "iterators test get 1 row\n";
	for (auto iter = a.row_begin(1); iter != a.row_end(1); iter++) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	std::cout << "Get all elements by coloumn order \n";
	for (auto iter = a.col_begin(0); iter != a.col_end(a.get_cols()-1); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
	std::cout << "Get all elements by overall iterator \n";
	for (auto iter = a.begin(); iter != a.end(); iter++) {
		std::cout << *iter << " ";
	}
	std::cin.get();
	return 0;
}
