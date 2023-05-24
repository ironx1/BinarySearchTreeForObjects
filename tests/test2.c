#include "test.h"
#include <stdio.h>
int main(void){
    Person *p1, *p2, *p3, *p4, *p5, *p6, *p7;
    bstptr_t tree = initBst();
    p1 = initPerson("kaan", 23);
    p2 = initPerson("ali", 26);
    p3 = initPerson("melih", 29);
    p4 = initPerson("xyz", 15);
    p5 = initPerson("abc", 21);
    p6 = initPerson("abcd", 24);
    p7 = initPerson("abcree", 19);
    tree->add(tree, p1, INTEGER);
    tree->add(tree, p2, INTEGER);
    tree->add(tree, p3, INTEGER);
    tree->add(tree, p4, INTEGER);
    tree->add(tree, p5, INTEGER);
    tree->add(tree, p6, INTEGER);
    tree->add(tree, p7, INTEGER);
    tree->del(tree, p1, INTEGER, HEAP);
    tree->del(tree, p2, INTEGER, HEAP);
    tree->del(tree, p3, INTEGER, HEAP);
    tree->del(tree, p4, INTEGER, HEAP);
    tree->del(tree, p5, INTEGER, HEAP);
    tree->del(tree, p6, INTEGER, HEAP);
    tree->del(tree, p7, INTEGER, HEAP);
    tree->dtor(tree, HEAP);
}