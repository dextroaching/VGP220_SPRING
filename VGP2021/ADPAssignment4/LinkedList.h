#pragma once

#include <iostream>

template<typename T>
class LinkedList
{
	

private:
	struct Node
	{
		T data;
		Node* next = nullptr;
	};

	Node* mHead;

	Node* CreateNode(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		return newNode;
	}


public:
	LinkedList()
		: mHead(nullptr)
	{}

	~LinkedList()
	{
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}

	void Insert(T data)
	{
		Node* newNode = CreateNode(data);
		if (IsEmpty())
		{
			mHead = newNode;
			return;
		}

		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->next == nullptr)
			{
				currentNode->next = newNode;
				currentNode = nullptr;
				break;
			}
			currentNode = currentNode->next;
		}
	}

	void Remove(T data)
	{
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		if (mHead->data == data)
		{
			Node* temp = mHead->next;
			delete mHead;
			mHead = temp;
			temp = nullptr;
			return;
		}

		Node* currentNode = mHead->next;

		while (currentNode->next->data != data && currentNode != nullptr)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			std::cout << "The element is not in the list.\n";
			return;
		}
		Node* temp = currentNode->next;
		currentNode->next = temp->next;
		delete temp;
		temp = nullptr;

	}

	bool IsEmpty()
	{
		return mHead == nullptr;
	}

	//Displays all the elements of the linked list
	void DisplayList()
	{

		
		// TODO: 1
		Node* mCurrent = mHead;
		if (mHead == nullptr)
		{
			std::cout << "List is empty";
			return;
			
		}
		while (mCurrent != nullptr)
		{
			std::cout << mCurrent->data << std::endl;
			mCurrent = mCurrent->next;
		}
		

	

	}

	//ERROR: -5. A display function, should not modify the current data. a good way to approach this problem is with a recursive function:
	/*void printReverse(Node* node)
	{
		if (node->next != nullptr)
		{
			printReverse(node->next);
		}

		std::cout << node->data << " ";
	}*/
	//then, inside your DisplayReverseList, you call printReverse(mHead).

	//Displays all the elements of the linked list in reverse order
	void DisplayReverseList()
	{
		// TODO: 2
		Node* mCurrent = mHead;
		Node* mPrev = nullptr;
		Node* next = nullptr;
	

		while (mCurrent != nullptr)
		{
			next = mCurrent->next;
			mCurrent->next = mPrev;
			mPrev = mCurrent;
			mCurrent = next;
		}
		mHead = mPrev;
		DisplayList();
	}

	//This function allows the user to modify an existance data
	//Returns true if the conten was modified and false if it wasn't.
	bool ModifyContent(T content, T newContent)
	{
		// TODO: 3
		
		Node* mCurrent = mHead;
		while (mCurrent->next != nullptr)
		{
			if (mCurrent->data == content)
			{
				mCurrent->data = newContent;
				return true;
			}
			mCurrent = mCurrent->next;
		}
	}

	//Clear all the data from the linked list
	void ClearList()
	{
		// TODO: 4
		Node* mCurrent = mHead;
		Node* mNext = nullptr;

		while (mCurrent != nullptr)
		{
			mNext = mCurrent->next;
			free(mCurrent);
			mCurrent = mNext;

		}
		mHead = nullptr;
	}


};
