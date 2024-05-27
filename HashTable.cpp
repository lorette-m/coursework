#include "HashTable.h"

void HashTable::insert(std::string& key, int number) 
{
	const double LOAD_FACTOR_NUMBER = 0.75;
	if (numElements > tableSize * LOAD_FACTOR_NUMBER) 
	{
		rehash();
	}
	int index = hashFunction(key);
	HashNode* newNode = new HashNode(key, number);
	if (!table[index]) 
	{
		table[index] = newNode;
	}
	else 
	{
		HashNode* current = table[index];
		while (current->nextByChain_) 
		{
			current = current->nextByChain_;
		}
		current->nextByChain_ = newNode;
	}
	insertSorted(newNode);
	++numElements;
}

LinesList* HashTable::search(std::string& key) 
{
	int index = hashFunction(key);
	HashNode* current = table[index];
	while (current) 
	{
		if (current->key_ == key) 
		{
			return current->lines_;
		}
		current = current->nextByChain_;
	}
	return nullptr;
}

bool HashTable::remove(std::string& key) 
{
	int index = hashFunction(key);
	HashNode* current = table[index];
	HashNode* preCurrent = nullptr;

	while (current and current->key_ != key) 
	{
		preCurrent = current;
		current = current->nextByChain_;
	}

	if (!current)
	{
		return false;
	}

	if (preCurrent) 
	{
		preCurrent->nextByChain_ = current->nextByChain_;
	}
	else 
	{
		table[index] = current->nextByChain_;
	}

	if (tableHead == current) 
	{
		tableHead = current->nextByTable_;
	}
	else 
	{
		HashNode* tablePreCurrent = tableHead;
		while (tablePreCurrent->nextByTable_ and tablePreCurrent->nextByTable_ != current) {
			tablePreCurrent = tablePreCurrent->nextByTable_;
		}
		if (tablePreCurrent->nextByTable_ == current) {
			tablePreCurrent->nextByTable_ = current->nextByTable_;
		}
	}

	current->nextByChain_ = nullptr;
	current->nextByTable_ = nullptr;
	delete current;
	--numElements;
}

void HashTable::display() {
	std::cout << "Хэш-таблица: " << std::endl;
	HashNode* current = tableHead;
	int tableLineCounter = 0;
	while (current) {
		std::cout << "Строка " << ++tableLineCounter << std::endl;
		std::cout << "    Ключ: " << current->key_ << "\n    ";
		current->lines_->linesListOut();
		current = current->nextByTable_;
	}
	std::cout << std::endl;
}