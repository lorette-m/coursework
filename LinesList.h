#ifndef LINESLIST_H
#define LINESLIST_H

#include <iostream>
#include <string>

class LinesList
{
public:
	
	LinesList() :
		head_(nullptr),
		tail_(nullptr),
		size_(0)
	{}

	virtual ~LinesList() {}

	bool insertLLNode(int number);

	int searchListNumber(int number);

	bool deleteLLNode(int number);

	int firstLayerProcessingOut();

	bool linesListOut();


private:

	struct LLNode
	{
		int number_;
		LLNode* prev_;
		LLNode* next_;
		LLNode(int number, LLNode* prev = nullptr, LLNode* next = nullptr) :
			number_(number), prev_(prev), next_(next)
		{ }
	};

	LLNode* head_;
	LLNode* tail_;
	size_t size_;

	LLNode* searchLLNode(int number) const
	{
		LLNode* current = head_;
		while (current != nullptr and current->number_ != number)
		{
			current = current->next_;
		}
		return current;
	}
};

#endif