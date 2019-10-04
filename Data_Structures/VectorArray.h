#pragma once
#include "Framework.h"
#include <iterator> //haven't created my own iterator yet

template <typename Object>
class VectorArray : public std::iterator<std::input_iterator_tag, Object>
{
public:

	VectorArray() : mArray(nullptr), mSize(NULL), mCapacity(NULL) {}
	~VectorArray() { 
		SafeDeleteArray(mArray); 
	}
	VectorArray(VectorArray& _cpy) : mArray(nullptr), mSize(NULL) {
		this->mSize = _cpy.mSize;
		this->mCapacity = _cpy.mCapacity;
		this->mArray = new Ojbect[this->mCapacity];
		for (size_t i = 0; i < this->mSize; i++)
		{
			this->mArray[i] = _cpy.mArray[i];
		}
	}
	VectorArray& operator=(VectorArray& _assign) {
		if (this != &_assign)
		{
			this->mSize = _assign.mSize;
			this->mCapacity = _assign.mCapacity;
			SafeDeleteArray(this->mArray);
			this->mArray = new Ojbect[this->mSize];
			for (size_t i = 0; i < this->mSize; i++)
			{
				this->mArray[i] = _assign.mArray[i];
			}
		}
		return *this;
	}

	//Accessors

	Object& operator[](size_t _index) const {
		if (_index >= mCapacity || _index < NULL)
			return NULL;
		return mArray[_index];
	}
	size_t ArraySize() const { 
		return this->mSize; 
	}
	size_t ArrayCapacity() const {
		return this->mCapacity;
	}
	Object& GetAt(size_t _index) const {
		return this->mArray[_index];
	}
	Object& GetFront() const {
		return this->mArray[ARRAY_FRONT_INDEX];
	}
	Object& GetBack() const {
		return this->mArray[ARRAY_BACK_INDEX];
	}
	std::iterator<std::output_iterator_tag, Object> GetBegin() const {
		return std::begin(mArray[ARRAY_FRONT_INDEX]);
	}
	std::iterator<std::output_iterator_tag, Object> const GetCBegin() const {
		return std::cbegin(mArray[ARRAY_FRONT_INDEX]);
	}

	//Mutators

	void SetArrayCapacity(UINT _new_size) {
		//First See if mArray exists. If not just create it w/ the new size and return.
		if (mArray)
		{
			mArray = new Object[_new_size];
			return;
		}

		//Trying to find the smallest size, I'm allowing the code to concatenate the array.
		UINT smallest_size = min(_new_size, mSize);
		Object* newArray = new Object[_new_size];

		for (size_t i = 0; i < smallest_size; i++)
		{
			newArray[i] = this->mArray[i];
		}

		//delete current array and replace it w/ the new size;
		SafeDeleteArray(mArray);

		mArray = newArray;
		mSize = smallest_size;
		mCapacity = _new_size;
	}

	void Swap(size_t _index_a, size_t _index_b) {
		Object tempp_obj = mArray[_index_a];
		mArray[_index_a] = mArray[_index_b];
		mArray[_index_b] = temp_obj;
	}

	void Insert(_insert_index, const Object& _data) {
		
	}
	void Insert(Object)

	//Methods


private:

	Object* mArray;
	size_t mSize;
	size_t mCapacity;
};