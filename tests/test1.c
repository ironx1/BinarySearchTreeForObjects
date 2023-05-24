#include <bst_bst.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct person{
    char name[15];
    int age;
}Person;

Person *initPerson(const char *name, int age){
    Person *p = memAllocM(Person, 1);
    strcpy_s(p->name, 15, name);
    p->age = age;
    return p;
}

int main(int argc, char const *argv[])
{
    bstptr_t tree = initBst();
    tree->add(tree, initPerson("kaan", 23), STRING);
    tree->add(tree, initPerson("ali",32), STRING);
    Person *getP = tree->root->object;
    printf("%d", getP->age);
    tree->dtor(tree, HEAP);
    return 0;
}
