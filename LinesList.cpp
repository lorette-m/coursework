#include "LinesList.h"

bool LinesList::insertLLNode(int number)
{
	if (head_ == nullptr)
	{
		head_ = new LLNode(number);
		return true;
	}
	if (tail_ == nullptr)
	{
		if (head_->number_ == number)
		{
			return false;
		}
		tail_ = new LLNode(number);
		head_->next_ = tail_;
		tail_->prev_ = head_;
		return true;
	}
	LLNode* preCurrent = nullptr;
	LLNode* current = head_;
	while ((current->number_ < number) and (current->next_ != nullptr))
	{
		preCurrent = current;
		current = current->next_;
	}
	if (current->number_ == number)
	{
		return false;
	}
	if (current->number_ > number)
	{
		LLNode* newLLNode = new LLNode(number);
		preCurrent->next_ = newLLNode;
		newLLNode->prev_ = preCurrent;
		current->prev_ = newLLNode;
		newLLNode->next_ = current;
		return true;
	}
	if ((current == tail_) and (current->number_ < number))
	{
		tail_ = new LLNode(number);
		current->next_ = tail_;
		tail_->prev_ = current;
		return true;
	}
	return false;
}

int LinesList::searchListNumber(int number)
{
	return (searchLLNode(number) == nullptr ? 0 : searchLLNode(number)->number_);
}

bool LinesList::deleteLLNode(int number)
{
	if ((head_ == nullptr) or (searchListNumber(number) == 0))
	{
		return false;
	}
	LLNode* current = searchLLNode(number);
	if (current == head_)
	{
		head_ = current->next_;
		head_->prev_ = nullptr;
		return true;
	}
	if (current == tail_)
	{
		tail_ = current->prev_;
		tail_->next_ = nullptr;
		return true;
	}
	LLNode* preCurrent = current->prev_;
	preCurrent->next_ = current->next_;
	current = current->next_;
	current->prev_ = preCurrent;
	return true;
}

int LinesList::firstLayerProcessingOut()
{
	if (head_ == nullptr)
	{
		return 0;
	}
	return head_->number_;
}

bool LinesList::linesListOut()
{
	const std::string EMPTY_LINES_LIST = "Список строк пуст";
	const std::string STANDARD_OUT_PHRASE = "Слово встречается в строках: ";
	if (head_ == nullptr)
	{
		std::cout << EMPTY_LINES_LIST << std::endl;
		return false;
	}
	LLNode* current = head_;
	std::cout << STANDARD_OUT_PHRASE;
	while (current != nullptr)
	{
		std::cout << current->number_ << " ";
		current = current->next_;
	}
	std::cout << std::endl;
}