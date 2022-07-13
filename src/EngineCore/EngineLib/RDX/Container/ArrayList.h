#pragma once


template<typename T>
class ArrayList
{
protected:
	T* buffer;
	std::size_t size;
	std::size_t capacity;

public:
	ArrayList()
		: buffer(nullptr)
		, size(0)
		, capacity(0)
	{}

public:
	void PushBack()
	{
	}

	void PopBack()
	{
	}

public:
	void Reserve(std::size_t newCapacity)
	{
	}

};

