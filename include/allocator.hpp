#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <limits>

namespace stl {

	template <typename T>
	class default_allocator {

		typedef T data_type;

	public:

		data_type* allocate(std::size_t size) {
			data_type* ptr = new data_type[size * sizeof(data_type)];
			return ptr;
		}

		data_type* construct(std::size_t size, data_type value) {
			data_type* ptr = new data_type[size * sizeof(data_type)];
			std::size_t itr = 0;
			while (itr < size) {
				ptr[itr] = value;
				++itr;
			}
			return ptr;
		}
		
	};

};




#endif