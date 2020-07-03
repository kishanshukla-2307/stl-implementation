#ifndef	VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <allocator.hpp>


namespace stl {

	template < typename T, class allocator = stl::default_allocator<T> >
	class vector {
		// typedefs
		typedef T data_type_;
		// typedef std::size_t size_;

	private:
		data_type_* dynamic_array_;
		std::size_t buffer_ = 0;
		std::size_t size_ = 0;
		constexpr static float buffer_to_size_ratio_ = 1;
		allocator allocator_;

	public:
		/***************** CONSTRUCTORS ******************/

		// default constructor
		vector () {};

		// vector<T> v(size, value)
		vector (std::size_t size, data_type_ value = 0): size_(size), buffer_(0) {
			dynamic_array_ = allocator_.construct(size_, value);
		}

		void operator=(const vector<data_type_>& other) {
			dynamic_array_= allocator_.allocate(other.size_ + other.buffer_);
			size_ = other.size_;
			buffer_ = other.buffer_;
			std::size_t itr = 0;
			while (itr < size_) {
				dynamic_array_[itr] = other.dynamic_array_[itr];
				++itr;
			}
		} 

		/************ MODIFIERS ************/

		void pop_back() {
			--size_;
			++buffer_;
		}

		void push_back(data_type_ value) {
			if (buffer_ == 0) {
				++size_;
				buffer_ = buffer_to_size_ratio_ * size_;
				data_type_* old_array = dynamic_array_;
				dynamic_array_ = allocator_.allocate(buffer_ + size_);
				std::size_t itr = 0;
				while (itr < size_ - 1) {
					dynamic_array_[itr] = old_array[itr];
					++itr;
				}
				dynamic_array_[itr] = value;
				delete[] old_array;
			} else {
				dynamic_array_[size_] = value;
				++size_;
				--buffer_;
			}
		}

		/*********** CAPACITY ************/

		// const complexity
		std::size_t size() {
			return size_;
		}

		// const complexity
		std::size_t capacity() {
			return size_ + buffer_;
		}

		// linear complexity (worst case)
		void resize(std::size_t new_size) {
			// decrease size
			if (new_size <= size_ + buffer_) {
				std::size_t capacity = size_ + buffer_;
				size_ = new_size;
				buffer_ = capacity - size_;
			}
			// increase size and append zeroes
			else {
				data_type_* old_array = dynamic_array_;
				std::size_t old_size = size_;
				size_ = new_size;
				buffer_ = 0;
				dynamic_array_ = allocator_.allocate(size_);
				std::size_t itr = 0;
				while (itr < new_size) {
					if (itr < old_size){
						dynamic_array_[itr] = old_array[itr];
					} else {
						dynamic_array_[itr] = 0;
					}
					++itr;
				}
				delete[] old_array;
			}
		}

		// const complexity
		bool empty() {
			return (size_ == 0);
		}

		// linear complexity (worst case)
		void reserve(std::size_t n) {
			if (n > size_ + buffer_) {
				data_type_* old_array = dynamic_array_;
				buffer_ = n - size_;
				dynamic_array_ = allocator_.allocate(n);
				std::size_t itr = 0;
				while (itr < size_) {
					dynamic_array_[itr] = old_array[itr];
					++itr;
				}
				delete[] old_array;
			}
		}


		/*********** ELEMENT ACCESS ***********/

		data_type_ operator[](std::size_t n) {
			return dynamic_array_[n];
		}

		data_type_ back() {
			return dynamic_array_[size];
		}

		data_type_ front() {
			return dynamic_array_[0];
		}

		data_type_ at(std::size_t n) {
			// if (n < 0 || n >= size) {
			// 	throw out_of_bound_exception();
			// }
			return dynamic_array_[n];
		}

		data_type_* data() {
			return dynamic_array_;
		}

	};

};

#endif