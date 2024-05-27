#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinesList.h"

#include <cmath>

class HashTable
{
public:

	HashTable() :
		tableSize(100), 
		numElements(0) 
	{
		table = new HashNode * [tableSize]();
	}

	~HashTable() {
		for (size_t i = 0; i < tableSize; ++i) {
			HashNode* current = table[i];
			while (current) {
				HashNode* toDelete = current;
				current = current->next_;
				delete toDelete;
			}
		}
		delete[] table;
	}

	void insert(std::string& key, int number);
	LinesList* search(std::string& key);
	bool remove(std::string& key);
	void display();

private:
	struct HashNode {
		std::string key_;
		LinesList* lines_;
		HashNode* next_;
		// Конструктор узла
		HashNode(std::string key, int number, HashNode* next = nullptr) :
			key_(key), next_(next)
		{
			lines_ = new LinesList();
			lines_->insertLLNode(number);
		}
	};

	int hashFunction(const std::string& key) {
		int hash = 0;
		for (char c : key) {
			hash = (hash * 31 + c);
		}
		return std::fabs(hash % tableSize);
	}

	void insertSorted(HashNode*& head, HashNode* newNode) {
		if (!head or head->key_ > newNode->key_) {
			newNode->next_ = head;
			head = newNode;
			return;
		}

		HashNode* current = head;
		while (current->next_ and current->next_->key_ <= newNode->key_) {
			current = current->next_;
		}
		if (current->key_ == newNode->key_)
		{
			current->lines_->insertLLNode(newNode->lines_->firstLayerProcessingOut());
		}
		else if (current->next_ and current->next_->key_ == newNode->key_)
		{
			current->next_->lines_->insertLLNode(newNode->lines_->firstLayerProcessingOut());
		}
		else
		{
			newNode->next_ = current->next_;
			current->next_ = newNode;
		}
	}

	void rehash() {
		size_t oldTableSize = tableSize;
		tableSize *= 2;
		HashNode** newTable = new HashNode * [tableSize]();

		for (size_t i = 0; i < oldTableSize; ++i) {
			HashNode* current = table[i];
			while (current) {
				HashNode* nextNode = current->next_;
				int newIndex = hashFunction(current->key_);
				insertSorted(newTable[newIndex], current);
				current = nextNode;
			}
		}

		delete[] table;
		table = newTable;
	}


	HashNode** table;
	size_t tableSize;
	size_t numElements;
};

#endif