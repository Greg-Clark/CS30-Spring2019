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

    // Combine //
    // Into new map
    Map* c1 = new Map;
    c1->insert("Fred", 123);
    c1->insert("Ethel", 456);
    c1->insert("Lucy", 789);
    Map* c2 = new Map;
    c2->insert("Lucy", 789);
    c2->insert("Ricky", 321);
    Map* cR = new Map;
    assert(combine(*c1, *c2, *cR) && cR->size() == 4 &&
           (c1->size() == 3 && c2->size() == 2));
    delete c1;
    delete c2;
    delete cR;

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

    cout << "PASSED ALL TESTS" << endl;
    return 0;
}
