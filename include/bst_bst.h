#if !defined(BST_BST_H)
#define BST_BST_H

#include "bst_utils.h"
#include "bst_uniqueKey.h"
#include "bst_storage.h"

typedef struct nodeBst NodeBst;
typedef struct bst Bst;
typedef NodeBst* nodebstptr_t;
typedef Bst* bstptr_t;

typedef void (*funAdd)(bstptr_t, voidptr_t, UniqueKey);
typedef void (*funDtor)(bstptr_t, StorageType);
typedef void (*funGet)(nodebstptr_t*, voidptr_t, UniqueKey);
typedef void (*funDel)(bstptr_t, voidptr_t, UniqueKey, StorageType);

struct bst
{
    struct nodeBst
    {
        voidptr_t object;
        nodebstptr_t left, right;
    }*root;
    
    funAdd add;
    funDtor dtor;
    funDel del;
    funGet get;
};

extern bstptr_t initBst();

#endif // BST_BST_H
