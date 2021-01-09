#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace votes
{
	template <class T>
	class DynamicArray
	{
	private:
		T* _array;
		int _logical;
		int _physical;


	public:
		DynamicArray(int size = 2) : _logical(0), _physical(size)
		{
			string errorName;
			if (size > 0)
			{
				_array = new T[size];
					if (!_array)
						throw (errorName = "Memory Allocation failed.");
			}
			else
				_array = nullptr;

		}

		DynamicArray(const DynamicArray& other) : _array(nullptr)
		{
			*this = other;
		}
		~DynamicArray()
		{
			delete[] _array;
		}

		const DynamicArray& operator=(const DynamicArray& other)
		{
			string errorName;
			if (this != &other)
			{
				_logical = other._logical;
				_physical = other._physical;
				delete[] _array;
				_array = new T[_physical];
				if (!_array)
					throw (errorName = "Memory Allocation failed.");
				for (int i = 0; i < _logical; i++)
					_array[i] = other._array[i];
			}
			return *this;
		}
		const T& operator[](int i) const { return _array[i]; }
		T& operator[](int i) { return _array[i]; }

		void push_back(const T& value)
		{
			if (_logical == _physical)
				resize();
			_array[_logical++] = value;
		}

		const T& front()    const { return _array[0]; }
		int      size()     const { return _logical; }
		int      capacity() const { return _physical; }
		bool     empty()    const { return _logical == 0; }
		void     clear() { _logical = 0; }

		class iterator
		{
		private:
			DynamicArray* _dynamicarr;
			int	_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(DynamicArray& array, int i) : _dynamicarr(&array), _i(i) {}
			iterator(const iterator& other) : _dynamicarr(other._dynamicarr), _i(other._i) {}
			friend class const_iterator;

			const iterator& operator=(const iterator& other)
			{
				_dynamicarr = other._dynamicarr;
				_i = other._i;
				return *this;
			}

			bool operator==(const iterator& other) const
			{
				return (_dynamicarr == other._dynamicarr) && (_i == other._i);
			}
			bool operator!=(const iterator& other) const
			{
				return !(*this == other);
			}

			T& operator*()
			{
				return _dynamicarr->_array[_i];
			}
			T* operator->()
			{
				return &_dynamicarr->_array[_i];
			}

			iterator& operator++()
			{
				++_i;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp(*this);
				++_i;
				return temp;
			}
			iterator& operator--()
			{
				--_i;
				return *this;
			}
			iterator operator--(int)
			{
				iterator temp(*this);
				--_i;
				return temp;
			}
		};

		//------------------------------------------------------------------------------------------
		class const_iterator
		{
		private:
			const DynamicArray* _dynamicarr;
			int	_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = const T;
			using pointer = T*;
			using reference = const T&;

			const_iterator(const DynamicArray& array, int i) : _dynamicarr(&array), _i(i) {}
			const_iterator(const const_iterator& other) : _dynamicarr(other._dynamicarr), _i(other._i) {}
			const_iterator(const iterator& other) : _dynamicarr(other._da), _i(other._i) {}

			const const_iterator& operator=(const iterator& other)
			{
				_dynamicarr = other._dynamicarr;
				_i = other._i;
				return *this;
			}
			const const_iterator& operator=(const const_iterator& other)
			{
				_dynamicarr = other._dynamicarr;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const const_iterator& other) const
			{
				return (_dynamicarr == other._dynamicarr) && (_i == other._i);
			}
			bool operator!=(const const_iterator& other) const
			{
				return !(*this == other);
			}

			// smart-pointer iterator methods
			const T& operator*()
			{
				return _dynamicarr->_array[_i];
			}
			T* operator->()
			{
				return &_dynamicarr->_array[_i];
			}

			// increment-decrement iterator methods
			const_iterator& operator++()
			{
				++_i;
				return *this;
			}
			const_iterator operator++(int)
			{
				const_iterator temp(*this);
				++_i;
				return temp;
			}
			const_iterator& operator--()
			{
				--_i;
				return *this;
			}
			const_iterator operator--(int)
			{
				const_iterator temp(*this);
				--_i;
				return temp;
			}
		};


		//------------------------------------------------------------------------------------------

		class reverse_iterator
		{
		private:
			DynamicArray* _dynamicarr;
			int	_i;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			reverse_iterator(DynamicArray& array, int i) : _dynamicarr(&array), _i(i) {}
			reverse_iterator(const reverse_iterator& other) : _dynamicarr(other._dynamicarr), _i(other._i) {}



			const reverse_iterator& operator=(const reverse_iterator& other)
			{
				_dynamicarr = other._dynamicarr;
				_i = other._i;
				return *this;
			}

			// comparison with another iterator
			bool operator==(const reverse_iterator& other) const
			{
				return (_dynamicarr == other._dynamicarr) && (_i == other._i);
			}
			bool operator!=(const reverse_iterator& other) const
			{
				return !(*this == other);
			}

			// smart-pointer iterator methods
			T& operator*()
			{
				return _dynamicarr->_array[_i];
			}
			T* operator->() {
				return &_dynamicarr->_array[_i];
			}

			// increment-decrement iterator methods
			reverse_iterator& operator++()
			{
				--_i;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator temp(*this);
				--_i;
				return temp;
			}
			reverse_iterator& operator--()
			{
				++_i;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator temp(*this);
				++_i;
				return temp;
			}

		};

		//------------------------------------------------------------------------------------------

		void print() const
		{
			for (int i = 0; i < _logical; i++)
				cout << _array[i] << " ";
			cout << endl;
		}
		friend ostream& operator<<(ostream& os, const DynamicArray& arr)
		{
			for (int i = 0; i < arr.size(); i++)
				os << i << "." << arr[i] << endl;
			return os;
		}
		void insert(const iterator& pos, const T& val)
		{
			if (_logical == _physical)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logical;
		}

		const iterator& erase(const iterator& iter)
		{

			iterator itrbeg = begin();
			iterator itrnext = ++begin();

			while (itrbeg != iter && itrbeg != end())
			{
				itrbeg = itrnext++;
			}
			if (itrbeg == iter)
			{
				while (itrnext != end())
				{
					*itrbeg = *itrnext;
					itrbeg++;
					itrnext++;
				}
				_logical--;
			}
			else
			{
				return begin();
			}
			itrbeg = iter;
			itrbeg--;
			return (itrbeg);
		}
		const iterator& erase(const iterator& first, const iterator& last)
		{
			int counter = 0;
			iterator itrfirst = first;
			iterator itrlast = last;
			while (itrlast != end())
			{

				*itrfirst = *itrlast;
				++itrfirst;
				++itrlast;
			}
			for (iterator itr = first; itr != last; itr++)
				counter++;
			_logical = _logical - counter;
			itrfirst = first;
			itrfirst--;
			return (itrfirst);
		}


	private:
		void resize() {
			string errorName;
			_physical *= 2;
			T* temp = new T[_physical];
			if (!temp)
				throw (errorName = "Memory Allocation failed.");
			for (int i = 0; i < _logical; i++)
				temp[i] = _array[i];

			delete[] _array;
			_array = temp;
		}
	public:
		iterator begin()  const 
		{
			return iterator(*this, 0);
		}
		iterator end() 
		{
			return iterator(*this, _logical);
		}
		reverse_iterator rbegin() 
		{
			return reverse_iterator(*this, _logical);
		}
		reverse_iterator rend() 
		{
			return reverse_iterator(*this, 0);
		}
		iterator cbegin() 
		{
			return  const_iterator(*this, 0);
		}
		iterator cend() 
		{
			return  const_iterator(*this, _logical);
		}
	};
}