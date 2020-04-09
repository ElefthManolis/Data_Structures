#pragma once
#include <fstream>
#include <string>

struct cell
{
	int value = -1;
	cell *right = nullptr;
};

class Hashtable
{
public:
	bool Build(std::string filename);
    bool Insert(int number);
    bool Delete(int number);
	bool Search(int number) const;
	int GetSize() const;

private:
	bool Insert(int value, cell* t);
	int HashFunction(int x, int cap) const;
	void ResizeTable();

private:
	cell *table = nullptr;
	int elements = 0;
	int capacity = 0;
    int bucket = 1572869;
};
