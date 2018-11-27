#pragma once
#include<vector>
#include<memory>
#include "matrix_types.h"
#include "iterators.h"
#include <stdexcept>

template<typename T> class matrix_decorated<T, standard> {
	protected:

		size_t rows, cols;
		std::shared_ptr<std::vector<T>> data;
		matrix_decorated () {} // not visible from outside, available to subclasses

	public:

		T& operator() (size_t i, size_t j) {
			if (i >= rows || j >= cols) throw std::out_of_range("out of bound access");
			return data->operator[] ( j + i * cols);
		}

		const T& operator() (size_t i, size_t j) const {
			if ( i >= rows || j >= cols) throw std::out_of_range("out of bound access");
			return data->operator[] (j + i * cols);
		}

		size_t get_cols () const { 
			return cols; 
		}

		size_t get_rows () const { 
			return rows; 
		}

		matrix_decorated<T, transposed<standard>> transpose () const{
			return matrix_decorated<T, transposed<standard>> (*this);

		}

		matrix_decorated<T, vectorized<standard>> vectorize () const {
			return matrix_decorated<T, vectorized<standard>> (*this);
		}

		matrix_decorated<T, partitioned<standard>> submatrix(size_t start_row, size_t end_row, size_t start_col, size_t end_col) const {
			return matrix_decorated<T, partitioned<standard>>(*this, start_row, end_row, start_col, end_col);
		}

		const matrix_decorated<T, expanded<standard>> expand () const {
			return matrix_decorated<T, expanded<standard>> (*this);
		}

		//iterators
		using  iterator = template_row_iterator<T,standard>;
		using  const_iterator = const_template_row_iterator<T, standard>;
		using  row_iterator = template_row_iterator<T, standard>;
		using  const_row_iterator = const_template_row_iterator<T, standard>;
		using  col_iterator = template_col_iterator<T, standard>;
		using  const_col_iterator = const_template_col_iterator<T, standard>;

		iterator begin() {
			return iterator(*this,0,0);
		}
		iterator end() {
			return iterator(*this,rows, 0);
		}

		const_iterator begin() const {
			return data -> begin ();
		}
		const_iterator end() const {
			return data -> end ();
		}
		
		row_iterator row_begin (size_t i) {
			return row_iterator (*this, i, 0);
		}

		row_iterator row_end (size_t i) {
			return row_iterator(*this, i + 1, 0);
		}

		const_row_iterator row_begin (size_t i) const {
			return const_row_iterator(*this, i, 0);
		}

		const_row_iterator row_end (size_t i) const {
			return const_row_iterator(*this, i + 1, 0);
		}

		col_iterator col_begin (size_t i) {
			return col_iterator(*this, 0, i);
		}

		col_iterator col_end (size_t i) {
			return col_iterator(*this, 0, i + 1);
		}

		const_col_iterator col_begin (size_t i) const {
			return const_col_iterator(*this, 0, i);
		}

		const_col_iterator col_end (size_t i)  const {
			return const_col_iterator(*this, 0, i + 1);
		}
};
template<typename T, class type> class matrix_decorated<T, transposed<type>> : matrix_decorated<T, type> {

	typedef matrix_decorated<T, type> super;
	typedef transposed<type> this_type;
	friend class super;

	private:

		matrix_decorated(const super& b) : super (b) {}

	public:

		T& operator() (size_t i, size_t j) {
			return super::operator() (j, i);
		}

		const T& operator() (size_t i, size_t j) const {
			return super::operator() (j, i);
		}

		matrix_decorated<T, transposed<this_type>> transpose () const{
			return matrix_decorated<T, transposed<this_type>> (*this);
		}

		matrix_decorated<T, vectorized<this_type>> vectorize () const {
			return matrix_decorated<T, vectorized<this_type>> (*this);
		}

		matrix_decorated<T, partitioned<this_type>> submatrix(size_t start_row, size_t end_row, size_t start_col, size_t end_col) const {
			if (start_row > end_row || start_col > end_col) throw std::invalid_argument("end indexes cannot be smaller than start ones");
			if (end_row > super::get_rows() || start_col > super::get_rows()) throw std::invalid_argument(" submatrix must be inside original matrix");
			return matrix_decorated<T, partitioned<this_type>>(*this, start_row, end_row, start_col, end_col);
		}

		const matrix_decorated<T, expanded<this_type>> expand () const {
			return matrix_decorated<T, expanded<this_type>>(*this);
		}

		size_t get_cols () const { 
			return super::get_rows ();
		}

		size_t get_rows () const { 
			return super::get_cols ();
		}
		
		//iterators
		using col_iterator = typename template_col_iterator<T, this_type>;
		using const_col_iterator = typename const_template_col_iterator<T, this_type>;
		using row_iterator = typename template_row_iterator<T, this_type>;
		using const_row_iterator = typename const_template_row_iterator<T, this_type>;
		using  iterator = typename template_row_iterator<T, this_type>;
		using  const_iterator = typename const_template_row_iterator<T, this_type>;

		iterator begin() {
			return iterator(*this, 0, 0);
		}

		iterator end() {
			return iterator(*this, get_rows(), 0);
		}

		const_iterator begin() const {
			return const_iterator(*this, 0, 0);
		}

		const_iterator end() const {
			return const_iterator(*this, get_rows(), 0);
		}

		row_iterator row_begin(size_t i) {
			return row_iterator(*this, i, 0);
		}

		row_iterator row_end(size_t i) {
			return row_iterator(*this, i + 1, 0);
		}

		const_row_iterator row_begin(size_t i) const {
			return row_iterator(*this, i, 0);
		}

		const_row_iterator row_end(size_t i) const {
			return row_iterator(*this, i + 1, 0);
		}

		const_col_iterator col_begin(size_t i) const {
			return const_col_iterator(*this, 0, i);
		}

		const_col_iterator col_end(size_t i) const {
			return const_col_iterator(*this, 0, i + 1);
		}

		col_iterator col_begin(size_t i) {
			return col_iterator(*this, 0, i);
		}

		col_iterator col_end(size_t i) {
			return col_iterator(*this, 0, i + 1);
		}
};
template<typename T, class type> class matrix_decorated<T, vectorized<type>> : matrix_decorated<T, type> {
	
	typedef matrix_decorated<T, type> super;
	typedef vectorized<type> this_type;
	friend class super;

	private:

		matrix_decorated(const super& b) : super (b) {}
	
	public:
		size_t get_cols () const { 
			return 1; 
		}

		size_t get_rows () const { 
			if (super::get_cols () < super::get_rows ()) 
				return super::get_cols (); 
			else 
				return super::get_rows (); 
		}

		T& operator() (size_t i, size_t j = 0) {
			return super::operator() (i, i);
		}

		const T& operator() (size_t i, size_t j = 0) const {
			return super::operator() (i, i);
		}

		matrix_decorated<T, transposed<this_type>> transpose () const {
			return matrix_decorated<T, transposed<this_type>> (*this);
		}

		matrix_decorated<T, vectorized<this_type>> vectorize () const{
			return matrix_decorated<T, vectorized<this_type>> (*this);
		}

		matrix_decorated<T, partitioned<this_type>> submatrix(size_t start_row, size_t end_row, size_t start_col, size_t end_col) const {
			return matrix_decorated<T, partitioned<this_type>>(*this, start_row, end_row, start_col, end_col);
		}

		const matrix_decorated<T, expanded<this_type>> expand () const {
			return matrix_decorated<T, expanded<this_type>> (*this);
		}

		//iterators
		using col_iterator = typename template_col_iterator<T,this_type>;
		using const_col_iterator = typename const_template_col_iterator<T, this_type>;
		using row_iterator = typename template_row_iterator<T, this_type>;
		using const_row_iterator = typename const_template_row_iterator<T, this_type>;
		using  iterator = typename template_row_iterator<T,this_type>;
		using  const_iterator = typename const_template_row_iterator<T, this_type>;

		iterator begin() {
			return iterator(*this, 0, 0);
		}

		iterator end() {
			return iterator(*this, get_rows(), 0);
		}

		const_iterator begin() const {
			return const_iterator(*this, 0, 0);
		}

		const_iterator end() const {
			return const_iterator(*this, get_rows(), 0);
		}

		row_iterator row_begin (size_t i) {
			return row_iterator (*this, i, 0);
		}

		row_iterator row_end (size_t i) {
			return row_iterator (*this, i + 1, 0);
		}

		const_row_iterator row_begin (size_t i) const {
			return row_iterator (*this, i, 0);
		}

		const_row_iterator row_end (size_t i) const {
			return row_iterator(*this, i + 1, 0);
		}

		const_col_iterator col_begin (size_t i) const {
			return const_col_iterator (*this, 0, i);
		}

		const_col_iterator col_end (size_t i) const {
			return const_col_iterator (*this, 0, i + 1);
		}

		col_iterator col_begin (size_t i) {
			return col_iterator (*this, 0, i);
		}

		col_iterator col_end (size_t i) {
			return col_iterator (*this, 0, i + 1);
		}
};

template<typename T, class type> class matrix_decorated<T, partitioned<type>> : matrix_decorated<T, type> {
	
	typedef matrix_decorated<T, type> super;
	typedef partitioned<type> this_type;
	friend class super;

	private:

		size_t start_row, end_row; 
		size_t start_col, end_col;
		matrix_decorated(const super& b, size_t rs, size_t re, size_t cs, size_t ce) : super (b), 
			start_row(rs), end_row(re), start_col(cs), end_col(ce) {}

	public:

		size_t get_cols () const { 
			return (end_col - start_col); 
		}

		size_t get_rows () const { 
			return (end_row - start_row);
		}

		T& operator() (size_t i, size_t j ) {
			return super::operator() (i + start_row, j + start_col);
		}

		const T& operator() (size_t i, size_t j) const {
			return super::operator() (i + start_row, j + start_col);
		}

		matrix_decorated<T, transposed<this_type>> transpose () const {
			return matrix_decorated<T, transposed<this_type>> (*this);
		}

		matrix_decorated<T, vectorized<this_type>> vectorize () const {
			return matrix_decorated<T, vectorized<this_type>> (*this);
		}

		matrix_decorated<T, partitioned<this_type>> submatrix (size_t st_row, size_t e_row, size_t st_col, size_t e_col) const {
			return matrix_decorated<T, partitioned<this_type>>(*this,
				start_row + st_row,
				end_row + e_row,
				start_col + st_col,
				end_col + e_col
			);
		}

		const matrix_decorated<T, expanded<this_type>> expand () const {
			return matrix_decorated<T, expanded<this_type>> (*this);
		}

		using col_iterator = typename template_col_iterator<T, this_type>;
		using const_col_iterator = typename const_template_col_iterator<T, this_type>;
		using row_iterator = typename template_row_iterator<T, partitioned<this_type>>;
		using const_row_iterator = typename const_template_row_iterator<T, this_type>;
		using iterator = typename template_row_iterator<T, this_type>;
		using const_iterator = typename const_template_row_iterator<T, this_type>;

		iterator begin() {
			return iterator(*this, 0, 0);
		}

		iterator end() {
			return iterator(*this, get_rows(), 0);
		}

		const_iterator begin() const {
			return const_iterator(*this, start_row, start_col);
		}

		const_iterator end() const {
			return const_iterator(*this, end_row, 0);
		}

		row_iterator row_begin (size_t i) {
			return row_iterator (*this, i, 0);
		}

		row_iterator row_end (size_t i) {
			return row_iterator (*this, i + 1, 0);
		}

		const_row_iterator row_begin (size_t i) const {
			return row_iterator(*this, i, 0);
		}

		const_row_iterator row_end (size_t i) const {
			return row_iterator(*this, i + 1, 0);
		}

		const_col_iterator col_begin (size_t i) const {
			return const_col_iterator(*this, 0, i);
		}

		const_col_iterator col_end (size_t i) const {
			return const_col_iterator(*this, 0, i + 1);
		}

		col_iterator col_begin (size_t i) {
			return col_iterator(*this, 0, i);
		}

		col_iterator col_end (size_t i) {
			return col_iterator(*this, 0, i + 1);
		}
};

template<typename T, class type> class matrix_decorated<T, expanded<type>> : matrix_decorated<T, type> {
		
	typedef matrix_decorated<T, type> super;
	typedef expanded<type> this_type;	
	friend class super;
	
	private:
		
		T neutral_value;
		matrix_decorated(const super& b) : super (b), neutral_value(0) {}
	
	public:

		// always n x n matrix
		size_t get_cols () const { 
			return super::get_rows();
		}

		size_t get_rows () const { 
			return super::get_rows();
		}

		const T& operator () (size_t i, size_t j) const {
			if (i != j) return neutral_value;					
			return super::operator () (i, 0);		// we suppose that super is a vector, thus we only need its first col.
		}
		matrix_decorated<T, transposed<this_type>> transpose () const {
			return matrix_decorated<T, transposed<this_type>> (*this);
		}

		matrix_decorated<T, vectorized<this_type>> vectorize () const {
			return matrix_decorated<T, vectorized<this_type>> (*this);
		}

		matrix_decorated<T, partitioned<this_type>> submatrix(size_t start_row, size_t end_row, size_t start_col, size_t end_col) const {
			return matrix_decorated<T, partitioned<this_type>>(*this, start_row, end_row, start_col, end_col);
		}

		const matrix_decorated<T, expanded<this_type>> expand () const {
			return (*this);							// a diagonal diagonal matrix is itself, 
													// do not  add a decoration, tricky bit 
		}

		//iterators
		using const_col_iterator = typename const_template_col_iterator<T, this_type>;
		using const_row_iterator = typename const_template_row_iterator<T, this_type>;
		using const_iterator = typename const_template_row_iterator<T,this_type>;

		const_iterator begin() const {
			return const_iterator(*this, 0, 0);
		}

		const_iterator end() const {
			return const_iterator(*this, get_rows(), 0);
		}

		const_row_iterator row_begin (size_t i) const {
			return const_row_iterator(*this, i, 0);
		}

		const_row_iterator row_end (size_t i) const {
			return const_row_iterator(*this, i + 1, 0);
		}

		const_col_iterator col_begin (size_t i) const {
			return const_col_iterator (*this, 0, i);
		}

		const_col_iterator col_end (size_t i) const {
			return const_col_iterator (*this, 0, i + 1);
		}
};

template<typename T> class matrix : public matrix_decorated<T, standard> {
	
	typedef matrix_decorated<T, standard> super;
		
	public:
		
		matrix (size_t r, size_t c){
			super::rows = r;
			super::cols = c;
			super::data = std::make_shared<std::vector<T>> (r * c);
		}

		template<class type> matrix (const matrix_decorated<T, type>& oth) {
			size_t r = oth.get_rows();
			size_t c = oth.get_cols();
			super::rows = r;
			super::cols = c;
			super::data = std::make_shared<std::vector<T>>(r * c);
			auto current = oth.data->begin();
			auto last = oth.data->end();
			auto target = super::data->begin();
			while (current != last) {
				*target = *current;
				++current;
				++target;
			}
		}

		matrix (const matrix<T>& oth) {
			size_t r = oth.get_rows ();
			size_t c = oth.get_cols ();
			super::rows = r;
			super::cols = c;
			super::data = std::make_shared<std::vector<T>> (r * c);
			auto current = oth.data -> begin ();
			auto last = oth.data -> end ();
			auto target = super::data -> begin ();
			while (current != last) {
				*target = *current;
				++current;
				++target;
			}
		}
};