//
////  main.cpp
////  Project 1
////
////  Created by Gregory Clark on 3/11/19.
////  Copyright © 2019 Gregory Clark. All rights reserved.
//
//
//#include "Map.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main() {
//	//test for compare/insert/contains function
//	Map m1, m2, result;
//	m1.insert("Fred", 123);
//	m1.insert("Ethel", 456);
//	m1.insert("Lucy", 789);
//	m2.insert("Lucy", 789);
//	m2.insert("Ricky", 321);
//	combine(m1, m2, result);
//
//	assert(result.size() == 4 && result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel"));
//
//	//test for subtract function
//	Map m3, m4, result2;
//	m3.insert("Fred", 123);
//	m3.insert("Ethel", 456);
//	m3.insert("Lucy", 789);
//	m4.insert("Lucy", 789);
//	m4.insert("Ricky", 321);
//	m4.insert("Ethel", 654);
//	subtract(m3, m4, result2);
//
//	assert(result2.size() == 1 && result2.contains("Fred") && !(result2.contains("Ethel")));
//
//	//test for 3 argument get function
//	Map gpas;
//	gpas.insert("Fred", 2.956);
//	gpas.insert("Ethel", 3.538);
//	double v;
//	std::string k1;
//	assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
//	std::string k2;
//	assert(gpas.get(1,k2,v)  &&  k2 == k1);
//
//	//test for swap function
//	Map m5;
//	m5.insert("Fred", 2.956);
//	Map m6;
//	m6.insert("Ethel", 3.538);
//	m6.insert("Lucy", 2.956);
//	m5.swap(m6);
//	assert(m5.size() == 2  &&  m5.contains("Ethel")  &&  m5.contains("Lucy")  &&
//		   m6.size() == 1  &&  m6.contains("Fred"));
//
//	//tests copy constructor
//	Map original;
//	original.insert("Fred", 123);
//	original.insert("Ethel", 456);
//	original.insert("Lucy", 789);
//	Map copy(original);
//	assert(copy.size() == original.size() && copy.contains("Fred") && copy.contains("Ethel") && copy.contains("Lucy"));
//
//	//tests assignment oporator and erase function
//	original.erase("Fred");
//	copy = original;
//	assert(copy.size() == original.size() && !(copy.contains("Fred")) && copy.contains("Ethel") && copy.contains("Lucy"));
//
//	//test for update function and 2 argument get function
//	ValueType ofred;
//	ValueType cfred;
//	assert(original.get("Ethel", ofred) && copy.update("Ethel", 321) && copy.get("Ethel", cfred) && cfred == 321);
//
//	Map m;
//	// For an empty map:
//	assert(m.size() == 0);      // test size
//	assert(m.empty());          // test empty
//	assert(!m.erase("Ricky"));  // nothing to erase
//
//	cout << "Passed\n";
//	return 0;
//}

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	// Basic Map operations
	Map* ops = new Map;
	assert(ops->empty() && ops->size() == 0);
	assert(ops->insert("Key", 1) && ops->contains("Key") && ops->size() == 1);
	assert(ops->insertOrUpdate("newKey", 2) && ops->size() == 2);
	assert(ops->insert("", -1) && ops->contains("") && ops->erase(""));
	assert(!ops->contains("thiskeydoesn'texist"));
	ValueType opsVal;
	assert(ops->get("Key", opsVal) && opsVal == 1);
	assert(ops->insertOrUpdate("Key", 2) && ops->size() == 2
		   && (ops->get("Key", opsVal) && opsVal == 2));
	assert(ops->erase("newKey") && ops->size() == 1);
	assert(!ops->erase("thiskeydoesn'texist"));
	assert(ops->erase("Key") && ops->size() == 0 && ops->empty());
	delete ops;
	
	// Copy Constructor and Assignment Operator
	Map* original = new Map;
	original->insert("A", 1);
	Map* cc = new Map(*original);
	assert(!cc->empty() && cc->contains("A") && cc->size() == 1);
	Map* ao = new Map;
	*ao = *original;
	assert(!ao->empty() && ao->contains("A") && ao->size() == 1);
	delete original;
	delete cc;
	delete ao;
	
	// 3 Argument Get
	Map* threeGet = new Map;
	threeGet->insert("A", 1);
	threeGet->insert("B", 2);
	threeGet->insert("C", 3);
	KeyType k;
	ValueType v;
	assert(threeGet->get(0, k, v) &&
		   ((k == "A"  && v == 1) || (k == "B" && v == 2) || (k == "C" && v == 3)));
	delete threeGet;
	
	// Swap function
	Map* swap1 = new Map;
	swap1->insert("FirstMap", 1);
	Map* swap2 = new Map;
	swap2->insert("SecondMap", 2);
	swap2->insert("AnotherKey", 3);
	swap1->swap(*swap2);
	assert(swap1->size() == 2  &&  swap1->contains("SecondMap")  &&  swap1->contains("AnotherKey")  &&
		   swap2->size() == 1  &&  swap2->contains("FirstMap"));
	delete swap1;
	delete swap2;
	
		//test for compare/insert/contains function
		Map m1, m2, result;
		m1.insert("Fred", 123);
		m1.insert("Ethel", 456);
		m1.insert("Lucy", 789);
		m2.insert("Lucy", 789);
		m2.insert("Ricky", 321);
		combine(m1, m2, result);
	
		assert(result.size() == 4 && result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel"));
	
	// Combine //
	// Into new map
	Map* c1 = new Map;
	c1->insert("Fred", 123);
	c1->insert("Ethel", 456);
	c1->insert("Lucy", 789);
	Map* c2 = new Map;
	c2->insert("Lucy", 789);
	c2->insert("Ricky", 321);
	Map* cR = c1;
	assert(combine(*c1, *c2, *cR) && cR->size() == 4 && c2->size() == 2);
	delete c1;
	delete c2;
	
	// Into first map passed in
	c1 = new Map;
	c1->insert("Fred", 123);
	c1->insert("Ethel", 456);
	c1->insert("Lucy", 789);
	c2 = new Map;
	c2->insert("Lucy", 789);
	c2->insert("Ricky", 321);
	assert(combine(*c1, *c2, *c1) && c1->size() == 4 && c2->size() == 2);
	delete c1;
	delete c2;
	
	// Into second map passed in
	c1 = new Map;
	c1->insert("Fred", 123);
	c1->insert("Ethel", 456);
	c1->insert("Lucy", 789);
	c2 = new Map;
	c2->insert("Lucy", 789);
	c2->insert("Ricky", 321);
	assert(combine(*c1, *c2, *c2) && c2->size() == 4 && c1->size() == 3);
	delete c1;
	delete c2;
	
	// Subtract //
	// Into new map
	Map* s1 = new Map;
	s1->insert("Fred", 123);
	s1->insert("Ethel", 456);
	s1->insert("Lucy", 456);
	Map* s2 = new Map;
	s2->insert("Lucy", 789);
	s2->insert("Ricky", 321);
	s2->insert("Ethel", 654);
	Map* sR = new Map;
	subtract(*s1, *s2, *sR);
	ValueType fredVal = -1;
	assert(!sR->empty() && sR->size() == 1 && sR->contains("Fred") &&
		   (sR->get("Fred", fredVal) && fredVal == 123));
	assert(s1->size() == 3 && s2->size() == 3);
	delete s1;
	delete s2;
	delete sR;
	
	// Into first map passed in
	s1 = new Map;
	s1->insert("Fred", 123);
	s1->insert("Ethel", 456);
	s1->insert("Lucy", 456);
	s2 = new Map;
	s2->insert("Lucy", 789);
	s2->insert("Ricky", 321);
	s2->insert("Ethel", 654);
	subtract(*s1, *s2, *s1);
	fredVal = -1;
	assert(!s1->empty() && s1->size() == 1 && s1->contains("Fred") &&
		   (s1->get("Fred", fredVal) && fredVal == 123));
	assert(s2->size() == 3);
	delete s1;
	delete s2;
	
	// Into second map passed in
	s1 = new Map;
	s1->insert("Fred", 123);
	s1->insert("Ethel", 456);
	s1->insert("Lucy", 456);
	s2 = new Map;
	s2->insert("Lucy", 789);
	s2->insert("Ricky", 321);
	s2->insert("Ethel", 654);
	subtract(*s1, *s2, *s2);
	fredVal = -1;
	assert(!s2->empty() && s2->size() == 1 && s2->contains("Fred") &&
		   (s2->get("Fred", fredVal) && fredVal == 123));
	assert(s1->size() == 3);
	delete s1;
	delete s2;
	
	
	Map M1;
	M1.insert("Fred", 123);
	M1.insert("Ethel", 456);
	M1.insert("Lucy", 789);
	Map M2;
	M2.insert("Lucy", 789);
	M2.insert("Ricky", 321);
	Map M3;
	bool tru = combine(M1, M2, M3);
	assert(tru == true && M3.size() == 4);
	
	Map N1;
	N1.insert("Fred", 123);
	N1.insert("Ethel", 456);
	N1.insert("Lucy", 789);
	Map N2;
	N2.insert("Lucy", 654);
	N2.insert("Ricky", 321);
	Map N3;
	bool tru2 = combine(N1, N2, N3);
	assert(tru2 == false && N3.size() == 3);
	
	cout << "PASSED ALL TESTS" << endl;
	return 0;
}
