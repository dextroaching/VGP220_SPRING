#pragma once
#define SIZE 5;

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue
{
private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
	T* arr;

public:

	Queue(T size)
	{
		arr = new T[size];
		mCapacity = size;
		front = 0;
		rear = -1;
		mCurrentSize = 0;
	}
	
	~Queue()
	{
		delete[] arr;
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (isFull())
		{
			std::cout << "Queue is full";
		}
		else
		{
			if (front == -1)front = 0;
			rear++;
			arr[rear] = data;
		}
	}

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (isFull())
		{
			std::cout << "Overflow";
		}
		std::cout << "Isnerting " << output << std::endl;
		rear = (rear + 1) % mCapacity;
		arr[rear] = output;
		mCapacity++;
	}
	int size()
	{
		return mCurrentSize;
	}
	bool isFull()
	{
		return (size() == mCapacity);
	}

	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		if (front == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{
		int i;
		if (isEmpty())
		{
			std::cout << "Empty Queue";
		}
		else
		{
			std::cout << "Front index: " << front;
			std::cout << "Items: ";
			for (i = front; i <= rear; i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "Rear index: " << rear;
		}

		
	}

};


