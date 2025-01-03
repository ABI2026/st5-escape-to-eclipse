#pragma once

#include <string>

namespace DevUtils
{
	template <typename Type>
	class DynamicArray {
		public:
			DynamicArray();
			~DynamicArray();
			Type operator[](int indexOf) {
				if (indexOf > this->m_currentSize) const {
					std::_Xout_of_range("Index is out of range");
				}
				return *(m_memory + indexOf);
			}
			const Type operator[](int indexOf) const {
				if (indexOf > this->m_currentSize) {
					std::_Xout_of_range("Index is out of range");
				}
				return *(m_memory + indexOf);
			}
			DynamicArray operator+(DynamicArray& arr_0, DynamicArray& arr_1) const {

			}
			void push_back(Type element);
		private:
			size_t m_currentCapacity{};
			size_t m_currentSize{};
			Type* m_memory;

			void combine_arrays(DynamicArray&, DynamicArray&);
	};
	template <typename Type>
	DevUtils::DynamicArray<Type>::DynamicArray() {
		this->m_currentCapacity = 4;
		this->m_currentSize = 0;
		this->m_memory = new Type[this->m_currentCapacity]; // no use of std::malloc, because of the requirement to call the constructor in case of default types like std::string
	}

	template <typename Type>
	DevUtils::DynamicArray<Type>::~DynamicArray() {
		delete[] this->m_memory;
	}

	template <typename Type>
	void DevUtils::DynamicArray<Type>::push_back(Type element) {
		if (!((this->m_currentSize+1) > this->m_currentCapacity)) {
			*(this->m_memory + this->m_currentSize) = element;
			this->m_currentSize += 1;
		}
		else {
			Type* tmp_memory = new Type[this->m_currentCapacity];
			std::memcpy(tmp_memory, this->m_memory, this->m_currentCapacity * sizeof(Type));
			this->m_currentCapacity *= 2;
			delete[] this->m_memory;
			this->m_memory = new Type[this->m_currentCapacity];
			for (size_t index = 0; index < this->m_currentSize; index++) {
				*(m_memory + index) = *(tmp_memory + index);
			}
			push_back(element);
		}
	}
}

