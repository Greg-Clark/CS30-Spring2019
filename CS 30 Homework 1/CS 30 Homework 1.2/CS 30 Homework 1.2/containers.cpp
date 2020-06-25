//
//  containers.cpp
//  CS 30 Homework 1.2
//
//  Created by Gregory Clark on 4/27/19.
//  Copyright © 2019 Gregory Clark. All rights reserved.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
	for(list<int>::iterator p = li.begin(); p != li.end(); p++)
	{
		if(*p % 2 != 0)			//checks for odd numbers
		{
			list<int>::iterator q = p;		//sets another list iterator q equal to p
			li.erase(q);					//erases q
			p--;							//decreases the size of the list so p needs to also decrease
		}
	}
}


void test1()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a+8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end());  // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i] % 2 != 0)	//checks for odd numbers
		{
			v.erase(v.begin() + i);
			i--;	//after the odd number gets deleted the size decreases so i needs to also decrease
		}
	}
}

void test2()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a+8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

vector<int> destroyedOnes3;

class Movie
{
public:
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes3.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in li with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
	for(list<Movie*>::iterator p = li.begin(); p != li.end(); p++)
	{
		Movie* mp = *p;
		if(mp->rating() < 50)
		{
			list<Movie*>::iterator q = p;			//creates an iterator at position p to be deleted
			li.erase(q);							//deletes the rating that is less than 50
			p--;									//accounts for decrease in size
			destroyedOnes3.push_back(mp->rating());	//pushes rating onto destroyed vector
		}
	}
}

void test3()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes3.size() == 4);
	vector<int> v;
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie* mp = *p;
		v.push_back(mp->rating());
	}
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes3.begin(), destroyedOnes3.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes3[k] == expectGone[k]);
}

vector<int> destroyedOnes4;

class Movie2
{
public:
	Movie2(int r) : m_rating(r) {}
	~Movie2() { destroyedOnes4.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBad(vector<Movie2*>& v)
{
	for(int i = 0; i < v.size(); i++)
	{
		Movie2* mp = v[i];		//creates a pointer to the movie
		if(mp->rating() < 50)
		{
			v.erase(v.begin() + i);		//erases the movie with the bad rating
			i--;						//decreases i to account for the size decreasing
			destroyedOnes4.push_back(mp->rating());	//pushes the bad rating onto the destroyed vector
		}
	}
}

void test4()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	vector<Movie2*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie2(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes4.size() == 4);
	vector<int> v;
	for (int k = 0; k < 4; k++)
		v.push_back(x[k]->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes4.begin(), destroyedOnes4.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes4[k] == expectGone[k]);
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	cout << "Passed" << endl;
}
