#include <iostream>

class CustomIntVector {

public:
	CustomIntVector()
		: mMaxSize(10)
		, mCurrentSize(0)
		, mCurrentErasedSize(0)
	{
		mData = new int[10];
		mErasedData = new int[10];
	}

	~CustomIntVector() {
		delete[] mData;
		mErasedData = nullptr;
		mData = nullptr; // corrected 
	}

	//Copy constructor
	CustomIntVector(const CustomIntVector& other) {

		delete[]mData;
		delete[] mErasedData;
		mMaxSize = other.mMaxSize;
		mCurrentSize = other.mCurrentSize;
		mCurrentErasedSize = other.mCurrentErasedSize;
		mData = nullptr;
		mErasedData = nullptr;
		
		for (auto i = 0; i < other.mCurrentSize; ++i)
		{
			mData[i] = other.mData[i];
		}
	}

	CustomIntVector(CustomIntVector&& other) {
		delete[] mData;
		delete[] mErasedData;
		mMaxSize = other.mMaxSize;
		mCurrentSize = other.mCurrentSize;
		mCurrentErasedSize = other.mCurrentErasedSize;
		other.mMaxSize = 0;
		other.mCurrentSize = 0;
		other.mCurrentErasedSize = 0;
		mData = other.mData;
		mErasedData = other.mErasedData;
		other.mData = nullptr;
		other.mErasedData = nullptr;
	}

	void erase(int index)
	{
		//Using it like a node from linked list.
		mErasedData[mCurrentErasedSize] = mData[index];
		mCurrentErasedSize += 1;

		for (int x = index; x < mCurrentSize; x++)
		{
			mData[x] = mData[x + 1];
		}
		mCurrentSize -= 1;
	}

	void Push(int n)
	{
		if (mCurrentSize > mMaxSize)
		{
			mCurrentSize++;
			mData[mCurrentSize] = n;
		}
		else
		{

			std::cout << "Stack Overflow";
		}

	}
	void Pop()
	{
		if (mCurrentSize == 0)
		{
			std::cout << "Stack is empty";
		}
		else
		{
			mData[mCurrentSize]=0;
			--mCurrentSize;
		}
	}
	void Enqueue(int n)
	{
		if (mCurrentSize == 0)
		{
			mData[mCurrentSize] = n;
			mCurrentSize++;
		}
		else
		{
			std::cout << "Overflow!";
		}
	}
	void Dequeue()
	{
		if (mCurrentSize != 0)
		{
			mData[mCurrentSize] = 0;
			--mCurrentErasedSize;
		}
		else
		{
			std::cout << "Underflow";
		}
	}
private:
	int* mData;
	int* mErasedData;
	int mMaxSize;
	int mCurrentSize;
	int mCurrentErasedSize;
};

