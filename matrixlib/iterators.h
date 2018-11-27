#pragma once
#include "matrix_types.h"
template<typename T, class type> class template_col_iterator {
private:
	matrix_decorated<T, type> &ref;
	size_t current_row, current_col;
	typedef template_col_iterator this_type;
public:
	template_col_iterator(matrix_decorated<T, type> &object, size_t starting_row, size_t starting_col) :
		ref(object), current_row(starting_row), current_col(starting_col) {}

	this_type& operator++ () {
		current_row++;
		if (current_row >= ref.get_cols()) {
			current_col++;
			current_row = 0;
		}
		return *this;
	}
	this_type operator++ (int) {
		this_type to_ret = *this;
		current_row++;
		if (current_row >= ref.get_rows()) {
			current_col++;
			current_row = 0;
		}
		return to_ret;
	}
	T& operator *() {
		return ref(current_row, current_col);
	}
	bool operator== (const this_type& oth_iter) const {
		return current_row == oth_iter.current_row && current_col == oth_iter.current_col;
	}
	bool operator!= (const this_type& oth_iter) const {
		return !operator==(oth_iter);
	}
};

template<typename T, class type> class const_template_col_iterator {
private:
	const matrix_decorated<T, type> &ref;
	size_t current_row, current_col;
	typedef const_template_col_iterator this_type;
public:
	const_template_col_iterator(const matrix_decorated<T, type> &object, size_t starting_row, size_t starting_col) :
		ref(object), current_row(starting_row), current_col(starting_col) {}

	this_type& operator++ () {
		current_row++;
		if (current_row >= ref.get_cols()) {
			current_col++;
			current_row = 0;
		}
		return *this;
	}
	this_type operator++ (int) {
		this_type to_ret = *this;
		current_row++;
		if (current_row >= ref.get_rows()) {
			current_col++;
			current_row = 0;
		}
		return to_ret;
	}
	const T& operator *() {
		return ref(current_row, current_col);
	}
	bool operator== (const this_type& oth_iter) const {
		return current_row == oth_iter.current_row && current_col == oth_iter.current_col;
	}
	bool operator!= (const this_type& oth_iter) const {
		return !operator==(oth_iter);
	}
};


template<typename T, class type> class template_row_iterator {
private:
	matrix_decorated<T, type> &ref;
	size_t current_row, current_col;
	typedef template_row_iterator this_type;
public:
	template_row_iterator(matrix_decorated<T, type> &object, size_t starting_row, size_t starting_col) :
		ref(object), current_row(starting_row), current_col(starting_col) {}

	this_type& operator++ () {
		current_col++;
		if (current_col >= ref.get_cols()) {
			current_row++;
			current_col = 0;
		}
		return *this;
	}
	this_type operator++ (int) {
		this_type to_ret = *this;
		current_col++;
		if (current_col >= ref.get_cols()) {
			current_row++;
			current_col = 0;
		}
		return to_ret;
	}
	T& operator *() {
		return ref(current_row, current_col);
	}
	bool operator== (const this_type& oth_iter) const {
		return current_row == oth_iter.current_row && current_col == oth_iter.current_col;
	}
	bool operator!= (const this_type& oth_iter) const {
		return !operator==(oth_iter);
	}
};

template<typename T, class type> class const_template_row_iterator {
private:
	const matrix_decorated<T, type> &ref;
	size_t current_row, current_col;
	typedef const_template_row_iterator this_type;
public:
	const_template_row_iterator(const matrix_decorated<T, type> &object, size_t starting_row, size_t starting_col) :
		ref(object), current_row(starting_row), current_col(starting_col) {}

	this_type& operator++ () {
		current_col++;
		if (current_col >= ref.get_cols()) {
			current_row++;
			current_col = 0;
		}
		return *this;
	}
	this_type operator++ (int) {
		this_type to_ret = *this;
		current_row++;
		if (current_col >= ref.get_cols()) {
			current_row++;
			current_col = 0;
		}
		return to_ret;
	}
	const T& operator *() {
		return ref(current_row, current_col);
	}
	bool operator== (const this_type& oth_iter) const {
		return current_row == oth_iter.current_row && current_col == oth_iter.current_col;
	}
	bool operator!= (const this_type& oth_iter) const {
		return !operator==(oth_iter);
	}
};

