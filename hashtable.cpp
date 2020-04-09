#include "Hashtable.h"

bool Hashtable::Build(std::string filename)
{
	std::fstream data(filename, std::ios::in);
	if (!data)
		return false;

	// Count the number of elements
	std::string number = "";
	while (std::getline(data, number))
		elements++;

	capacity = 2 * elements + 100;
	delete[] table; // delete for safety
	table = new cell[capacity];

	// Go to the start of the file
	data.clear();
	data.seekg(0, std::ios_base::beg);

	while (std::getline(data, number))
	{
		int value = stoi(number);
		Insert(value, table);
	}
	return true;
}

bool Hashtable::Insert(int number)
{
	double a = (elements + 1) / capacity;
	if (a > 0.5)
		ResizeTable();
	if (Insert(number, table))
	{
		elements++;
		return true;
	}
	return false;
}

bool Hashtable::Insert(int value, cell* t)
{
	int index = HashFunction(value, capacity);
	if (t[index].right == nullptr)
		t[index].right = new cell{ value, nullptr };
	else
	{
		cell* currentCell = t[index].right;
		while (currentCell != nullptr)
		{
			if (currentCell->value == value)
				return false;
			currentCell = currentCell->right;
		}
		currentCell = new cell{ value, nullptr };
	}
	return true;
}

bool Hashtable::Delete(int number)
{
	// Going down the chain of numbers at a particular
	// index, we check if there is the number we are
	// looking for. If so, we remove it from the chain.
	int index = HashFunction(number, capacity);
	cell* currentCell = &table[index];
	cell* nextCell = currentCell->right;
	while (nextCell != nullptr)
	{
		if (nextCell->value == number)
		{
			elements--;
			currentCell->right = nextCell->right;
			delete nextCell;
			return true;
		}
		currentCell = nextCell->right;
		nextCell = currentCell->right;
	}
	return false;
}

bool Hashtable::Search(int number) const
{
	// Going down the chain of numbers at a particular
	// index, we check if there is the number we are
	// looking for.
	int index = HashFunction(number, capacity);
	cell* currentCell = table[index].right;
	while (currentCell != nullptr)
	{
		if (currentCell->value == number)
			return true;
		currentCell = currentCell->right;
	}
	return false;
}

int Hashtable::GetSize() const
{
	return elements;
}

int Hashtable::HashFunction(int x, int cap) const
{
	int i = ((17 * x + 55) % bucket) % cap;
	return i;
}

void Hashtable::ResizeTable()
{
	// For every element in the original table we insert
	// it in a new table using the new capacity and hence
	// the new result of the hash function
	int oldCapacity = capacity;
	capacity *= 2;
	cell *temp = new cell[capacity];
	for (int i = 0; i < oldCapacity; i++)
	{
		cell* currentCell = table[i].right;
		while (currentCell != nullptr)
		{
			int value = currentCell->value;
			Insert(value, temp);
			currentCell = currentCell->right;
		}
	}
	delete[] table;
	table = temp;
}
