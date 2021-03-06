#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:
	Inventory()
		:mMaxSlots(5)
		,mSlotsOccupied(0)
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mInventory = new Item[5];
	}
	Inventory(uint32_t capacity)
		:mMaxSlots(capacity)
		,mSlotsOccupied(0)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mInventory = new Item[capacity]; 
	}
	Inventory(const Inventory& other)
	{
		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;
		delete[] mInventory;
		mInventory = new Item[mMaxSlots];
		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = other.mInventory[i];
		}
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
	}
	Inventory(Inventory&& other)
	{
		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;
		delete[] mInventory;
		mInventory = other.mInventory;
		other.mInventory = nullptr;
		other.mMaxSlots = 0;
		other.mSlotsOccupied = 0;

		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
	}
	~Inventory()
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
		mInventory = nullptr;
	}

	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& rhs)
	{
		if (&rhs != this)
		{
			mMaxSlots = rhs.mMaxSlots;
			mSlotsOccupied = rhs.mSlotsOccupied;
			delete[]mInventory;
			mInventory = new Item[mMaxSlots];
			for (int i = 0; i < mSlotsOccupied; ++i)
			{
				mInventory[i] = rhs.mInventory[i];
			}
		}
	}
	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& rhs)
	{
		if (&rhs != this)
		{
			mMaxSlots = rhs.mMaxSlots;
			mSlotsOccupied = rhs.mSlotsOccupied;
			delete[]mInventory;
			mInventory = rhs.mInventory;
			rhs.mInventory = nullptr;
			rhs.mMaxSlots = 0;
			rhs.mSlotsOccupied = 0;

		}
	}

	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;

		//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
		//should expand adding 5 more empty slots for the user.
		if (!isFullForItem(&newItem))
		{
			int slot = SearchItemByNameLessThan50(newItem.name);
			if (slot != -1)
			{
				int nextQ = mInventory[slot].quantity + newItem.quantity;
				if (nextQ > 50)
				{
					newItem.quantity = nextQ - 50;
					mInventory[slot].quantity = 50;
					mInventory[mSlotsOccupied] = newItem;
					mSlotsOccupied++;
					return;
				}
				mInventory[slot].quantity += newItem.quantity;
				return;
			}
			else
			{
				if ((newItem.type == ItemType::Armor) && (newItem.name.compare("Expansion") == 0))
				{
					Item* temp = mInventory;
					mMaxSlots += 5;
					mInventory = new Item[mMaxSlots];
					for (int i = 0; i < mSlotsOccupied; ++i)
					{
						mInventory[i] = temp[i];
					}
					delete[] temp;
					temp = nullptr;
				}
				mInventory[mSlotsOccupied] = newItem;
				mSlotsOccupied++;
			}
		}

		std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	}

	void RemoveItem(std::string itemName, int quantity)
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.
		bool isExpansion = itemName.compare("Expansion") == 0;
		if (mSlotsOccupied != 0)
		{
			int slotIndex = SearchItemByName(itemName);
			if (slotIndex == -1)
			{
				std::cout << "Non-Existent Item";
				return;
			}

			if (quantity >= mInventory[slotIndex].quantity)
			{
				for (int i = slotIndex; i < mSlotsOccupied - 1; ++i)
				{
					mInventory[i] = mInventory[i + 1];
				}
				mSlotsOccupied--;

				//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
				//should reduce the number of slots in 5, discarting all the items from the removed slots.
				if (isExpansion && (SearchItemByName(itemName) == -1))
				{
					mSlotsOccupied -= 5;
				}
			}
			else
			{
				mInventory[slotIndex].quantity -= quantity;
			}
		}
		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

	}

	Item* UseItem(std::string itemName)
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.

		int index = SearchItemByName(itemName);
		if (index < 0)
		{
			Item* item = &mInventory[index];
			RemoveItem(itemName, 1);
			return item;
		}
		std::cout << "Using " << itemName << "\n";
	}
private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;


	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};