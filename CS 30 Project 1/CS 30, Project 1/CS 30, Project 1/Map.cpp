//
//  Map.cpp
//  Project 1
//
//  Created by Gregory Clark on 2/27/19.
//  Copyright © 2019 Gregory Clark. All rights reserved.
//  79, 80, 87, 92

#include "Map.h"

Map::Map() : head(nullptr) { }              // Create an empty map (i.e., one with no key/value pairs)

bool Map::empty() const // Return true if the map is empty, otherwise false.
{
	if(head == nullptr)
		return true;
	return false;
}

int Map::size() const   // Return the number of key/value pairs in the map.
{
	if(this->empty())	//checks to see if map is empty
		return 0;
	int total = 0;
	Node *p = head;
	while(p != nullptr)	//loops through map to get total size
	{
		p = p->next;
		total++;
	}
	return total;	//returns the size of the map
}

Map::~Map()		//deletes all nodes in the map
{
	Node *p;
	while(head != nullptr)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

Map::Map(const Map& other)
{
	Node *q = other.head;
	if(q == nullptr)
	{
		return;
	}
	Node *p = new Node;		//creates first node of map
	p->mapKey = q->mapKey;
	p->mapValue = q->mapValue;
	p->previous = nullptr;
	p->next = nullptr;
	head = p;
	q = q->next;
	while(q != nullptr)		//creates the rest of the nodes in map
	{
		Node *w = new Node;
		p->next = w;
		w->previous = p;
		w->next = nullptr;
		w->mapKey = q->mapKey;
		w->mapValue = q->mapValue;
		p = p->next;
		q = q->next;
	}
}

const Map& Map::operator=(const Map& other)
{
	if(this == &other)
		return (*this);
	if(other.head == nullptr)
		return (*this);
	Node *o = other.head;
	this->~Map();			//deletes all nodes in map
	head = nullptr;
	Node *p = new Node;
	p->previous = nullptr;
	p->next = nullptr;
	p->mapKey = o->mapKey;
	p->mapValue = o->mapValue;
	head = p;
	o = o->next;
	while(o != nullptr)	//copies all the values of other into "this"
	{
		Node *q = new Node;
		p->next = q;
		q->previous = p;
		q->next = nullptr;
		q->mapKey = o->mapKey;
		q->mapValue = o->mapValue;
		p = p->next;
		o = o->next;
	}
	return (*this);
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if(head == nullptr)	//checks to see if map is empty. If it is it creates first node
	{
		Node *p = new Node;
		p->mapKey = key;
		p->mapValue = value;
		p->next = nullptr;
		p->previous = nullptr;
		head = p;
		return true;
	}
	Node *q = head;
	while(q->next != nullptr)
	{
		if(q->mapKey == key)
			return false;	//will return false if key is found
		q = q->next;		//and sets q to the last element in the map
	}
	if(q->mapKey == key)	//checks last node for key
		return false;
	Node *p = new Node;		//creates new node is map if not empty and adds it to the end
	p->mapKey = key;
	p->mapValue = value;
	p->next = nullptr;
	p->previous = q;
	q->next = p;
	return true;
}
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map).

bool Map::update(const KeyType& key, const ValueType& value)
{
	if(head == nullptr)
		return false;
	Node *p = head;
	while(p != nullptr)
	{
		if(p->mapKey == key)
		{
			if(p->mapValue == value)	//if same values are already in then
				return false;				//there is no updated needed
			p->mapValue = value;		//if values are different then change
			return true;					//them and return true
		}
		p = p->next;
	}
	return false;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if(this->update(key, value))
		return true;
	this->insert(key, value);
	return true;
}
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map then add it and
// return true. In fact this function always returns true.

bool Map::erase(const KeyType& key)
{
	Node *p = head;
	while(p != nullptr)
	{
		if(p->mapKey == key)
		{
			if(p->previous == nullptr && p->next == nullptr)	//if there is only one element in the
			{													//list, set head to null, then delete
				head = nullptr;
			}
			else if(p->previous == nullptr)	//if the item being erased is the first object in the
			{							//linked list, head is changed to the next item
				p->next->previous = nullptr;
				head = p->next;
			}
			else if(p->next == nullptr)	//if the item being deleted is the last item element than the
			{							//previous node's next points to null
				p->previous->next = nullptr;
			}
			else						//if the element is not the first or last item rearrange
			{							//the pointers to exclude the node about to be erased
				p->previous->next = p->next;
				p->next->previous = p->previous;
			}
			delete p;					//delete(erase) desired node
			return true;
		}
		p = p->next;
	}
	return false;
}
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const
{
	Node *p = head;
	while(p != nullptr)
	{
		if(p->mapKey == key)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const
{
	Node *p = head;
	while(p != nullptr)
	{
		if(p->mapKey == key)	//if keys match, then set value equal to key's value
		{
			value = p->mapValue;
			return true;
		}
		p = p->next;
	}
	return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if(i < 0 || i >= this->size())
		return false;
	Node *p = head;
	for(int j = 0; j < i; j++)	//sets p equal to the item at position i
	{
		p = p->next;
	}
	key = p->mapKey;
	value = p->mapValue;
	return true;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)

void Map::swap(Map& other)
{
	Node *temp = head;
	head = other.head;
	other.head = temp;
}
// Exchange the contents of this map with the other one.




bool combine(const Map& m1, const Map& m2, Map& result)
{
	KeyType key2;					//key2 for m2
	ValueType value2;				//value2 is for m2
	bool TorF = true;				//used in order to cause function to return true or false
	bool sameAddress = false;
	Map temp(m1);
	if(&m1 == &result){
		sameAddress = true;
	}
	for(int i = 0; i < m2.size(); i++)	//tests all values against one another
	{
		m2.get(i, key2, value2);
		if(temp.update(key2, value2))
		{
			temp.erase(key2);
			TorF = false;
		}
		else
			temp.insert(key2, value2);
		//checks to see if key type is already in result
	}
	if(sameAddress)				//if m1 and result map to the same map
		result.swap(temp);		//then swap the pointers of result and
	else						//temp. Otherwise set result equal to
		result = temp;			//temp

	return TorF;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	KeyType key2;						//key2 for m2
	ValueType value2;				//value2 is for m2
	bool sameAddress = false;
	Map temp(m1);
	if(&m1 == &result)
		sameAddress = true;
	for(int i = 0; i < m2.size(); i++)	//tests all values against one another
	{
		m2.get(i, key2, value2);
		if(temp.contains(key2))
		{
			temp.erase(key2);
			//checks to see if key type is already in result
		}
	}
	if(sameAddress)				//if m1 and result map to the same map
		result.swap(temp);		//then swap the pointers of result and
	else						//temp. Otherwise set result equal to
		result = temp;			//temp
}

