#if !defined(BST_TEST_H)
#define BST_TEST_H
#include <bst_bst.h>
typedef struct person{
    int age;
    char name[15];
}Person;

Person *initPerson(const char *name, int age){
    Person *p = memAllocM(Person, 1);
    strcpy_s(p->name, 15, name);
    p->age = age;
    return p;
}

#endif // BST_TEST_H
