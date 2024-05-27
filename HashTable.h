#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinesList.h"

#include <cmath>

class HashTable
{
public:

	HashTable() :
		tableSize(100), 
		numElements(0),
		tableHead(nullptr)
	{
		table = new HashNode * [tableSize]();
	}

	~HashTable() {
		for (size_t i = 0; i < tableSize; ++i) {
			delete table[i];
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
		HashNode* nextByChain_;
		HashNode* nextByTable_;

		HashNode(std::string key, int number, HashNode* nextByChain = nullptr, HashNode* nextByTable = nullptr) :
			key_(key), nextByChain_(nextByChain), nextByTable_(nextByTable)
		{
			lines_ = new LinesList();
			lines_->insertLLNode(number);
		}

		~HashNode() 
		{
			delete nextByChain_;
		}
	};

	HashNode** table;
	HashNode* tableHead;
	size_t tableSize;
	size_t numElements;

	int hashFunction(const std::string& key) const 
	{
		std::hash<std::string> hashFunc;
		return hashFunc(key) % tableSize;
	}

	void insertSorted(HashNode* newNode) 
	{
		if (!tableHead or tableHead->key_ > newNode->key_) 
		{
			newNode->nextByTable_ = tableHead;
			tableHead = newNode;
			return;
		}

		HashNode* current = tableHead;
		while (current->nextByTable_ and current->nextByTable_->key_ <= newNode->key_) 
		{
			current = current->nextByTable_;
		}
		if (current->key_ == newNode->key_)
		{
			current->lines_->insertLLNode(newNode->lines_->firstLayerProcessingOut());
		}
		else if (current->nextByTable_ and current->nextByTable_->key_ == newNode->key_)
		{
			current->nextByTable_->lines_->insertLLNode(newNode->lines_->firstLayerProcessingOut());
		}
		else
		{
			newNode->nextByTable_ = current->nextByTable_;
			current->nextByTable_ = newNode;
		}
	}

	void rehash() 
	{
		size_t oldTableSize = tableSize;
		tableSize *= 2;
		HashNode** newTable = new HashNode * [tableSize]();
		tableHead = nullptr;

		for (size_t i = 0; i < oldTableSize; ++i) 
		{
			HashNode* current = table[i];
			while (current) 
			{
				HashNode* nextNode = current->nextByChain_;
				current->nextByChain_ = nullptr;
				int newIndex = hashFunction(current->key_);
				if (!newTable[newIndex]) 
				{
					newTable[newIndex] = current;
				}
				else {
					HashNode* chainCurrent = newTable[newIndex];
					while (chainCurrent->nextByChain_) {
						chainCurrent = chainCurrent->nextByChain_;
					}
					chainCurrent->nextByChain_ = current;
				}
				insertSorted(current);
				current = nextNode;
			}
		}

		delete[] table;
		table = newTable;
	}
};

#endif