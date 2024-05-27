#include "HashTable.h"

void HashTable::insert(std::string& key, int number)
{
	const double LOAD_FACTOR_NUMBER = 0.75;
	if (numElements > tableSize * LOAD_FACTOR_NUMBER) {
		rehash();
	}
	int index = hashFunction(key);
	HashNode* newNode = new HashNode(key, number);
	insertSorted(table[index], newNode);
	++numElements;
}

LinesList* HashTable::search(std::string& key)
{
	int index = hashFunction(key);
	HashNode* current = table[index];
	while (current) {
		if (current->key_ == key) {
			return current->lines_;
		}
		current = current->next_;
	}
	return nullptr;
}

bool HashTable::remove(std::string& key) {
	int index = hashFunction(key);
	HashNode* current = table[index];
	HashNode* preCurrent = nullptr;

	while (current && current->key_ != key) {
		preCurrent = current;
		current = current->next_;
	}

	if (!current)
	{
		return false;
	}

	if (preCurrent) 
	{
		preCurrent->next_ = current->next_;
	}
	else 
	{
		table[index] = current->next_;
	}

	delete current;
	--numElements;
}

void HashTable::display() {
	for (size_t i = 0; i < tableSize; ++i) {
		std::cout << "Строка " << i << ": ";
		HashNode* current = table[i];
		while (current) {
			std::cout << "    Ключ: " << current->key_ << "\n    ";
			current->lines_->linesListOut();
			current = current->next_;
		}
		std::cout << std::endl;
	}
}