#include "list.h"

List::List()
{
	head.next = head.previous = 0; 
}

void List::initialize()
{
	head.next = head.previous = 0; 
}

int List::size()
{
	ListItem *temp = head.next; 
	int cnt = 0; 

	while(temp)
	{
		temp = temp->next; 
		++cnt; 
	}
	return cnt; 
}

bool List::empty()
{
	return size()==0; 
}

ListItem *List::back()
{
	ListItem *tmp = head.next; 
	if(tmp == 0)
		return nullptr; 

	while(tmp->next)
	{
		tmp = tmp ->next; 
	}

	return tmp; 
}

void List::push_back(ListItem * itemPtr)
{
	ListItem * tmp = back(); 
	if(tmp == nullptr) 
		tmp = &head; 
	tmp->next = itemPtr; 
	itemPtr->previous = tmp; 
	itemPtr->next = nullptr; 
}

void List::pop_back()
{
	ListItem *tmp = back(); 
	if(tmp)
	{
		tmp->previous->next = nullptr; 
		tmp->previous = tmp->next = nullptr; 
	}
}

ListItem *List::front()
{
	return head.next; 
}

void List::push_front(ListItem *itemPtr)
{
	ListItem *tmp = head.next; 
	if(tmp) tmp->previous = itemPtr; 
	head.next = itemPtr; 
	itemPtr->previous = &head; 
	itemPtr->next = tmp; 
}

void List::pop_front()
{
	ListItem *tmp = head.next;
	if(tmp)
	{
		if(tmp->next) tmp->next->previous = &head; 
		head.next = tmp->next; 
		tmp->previous = tmp->next = nullptr; 
			
	}
}

void List::insert(int pos, ListItem *itemPtr)
{
	if (pos == 0) push_front(itemPtr);
    	else
    	{
        	int length = size();
        	if (pos == length) push_back(itemPtr);
        	else if (pos < length)
        	{
            		ListItem *temp = at(pos);
            		itemPtr->previous = temp->previous;
            		itemPtr->next = temp;
            		temp->previous->next = itemPtr;
            		temp->previous = itemPtr;
        	}
    	}
}

void List::erase(int pos)
{
	if(pos == 0) pop_front(); 
	else
	{
		int len = size(); 
		if(pos < len)
		{
			ListItem *tmp = at(pos); 

			tmp->previous->next = tmp->next; 
			if(tmp->next) tmp->next->previous = tmp->previous; 
		}
	}
}

void List::erase(ListItem *itemPtr)
{
	ListItem *tmp = head.next; 
	while(tmp && tmp != itemPtr) tmp = tmp->next; 
	if(tmp)
	{
		tmp->previous->next = tmp->next; 
		if(tmp->next) tmp->next->previous = tmp->previous; 
	}
}

ListItem *List::at(int pos)
{
	ListItem *tmp = head.next; 
	for(int i = 0;(i<pos)&& tmp; ++i,tmp = tmp->next)
	{
	}
	return tmp; 
}

int List::find(ListItem *itemPtr)
{
	int pos = 0; 
	ListItem *tmp = head.next; 
	while(tmp && tmp != itemPtr)
	{
		tmp = tmp->next; 
		++pos; 
	}
	if(tmp && tmp == itemPtr) return pos; 
	else return -1; 
}
