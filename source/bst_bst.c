#include <bst_bst.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
static nodebstptr_t initNodeBst(voidptr_t object)
{
    nodebstptr_t node = memAllocM(NodeBst, 1);
    node->object = object;
    node->left = node->right = NULL;
    return node;
}

static nodebstptr_t bst_addObject(nodebstptr_t root, voidptr_t obj, UniqueKey keyField)
{
    //the unique key must be defined as the first field of the structure
    int flag = 0;
    if (root == NULL)
        return initNodeBst(obj);
    if(keyField == STRING){
        if(strcmp((charptr_t)obj, (charptr_t)root->object) > 0) flag = 1;
        else flag = -1;
    }
    else if(keyField = FLOAT){
        if(*(folatptr_t)obj > *(folatptr_t)root->object) flag = 1;
        else flag = -1;
    }
    else if(keyField == INTEGER){
        if(*(pint_t)obj > *(pint_t)root->object) flag = 1;
        else flag = -1;
    }
    else printf("Error: unknown data type\n"), exit(EXIT_FAILURE);
    
    if(flag > 0) root->right = bst_addObject(root->right, obj, keyField);
    else if(flag < 0) root->left = bst_addObject(root->left, obj, keyField);
    else printf("Error: unknown data type\n"), exit(EXIT_FAILURE);
    return root;
}


void bst_add(bstptr_t bst, voidptr_t obj, UniqueKey keyField){
    bst->root = bst_addObject(bst->root, obj, keyField);
}

static void bst_free(nodebstptr_t root, StorageType storage){
    if(root == NULL) return;
    bst_free(root->left, storage);
    bst_free(root->right, storage);
    if(storage == HEAP) free(root->object);
    free(root);
}

void bst_dtor(bstptr_t bst, StorageType storage){
    if(bst == NULL) return;
    bst_free(bst->root, storage);
    free(bst);
}

nodebstptr_t *bst_getNode(nodebstptr_t *root, voidptr_t obj, UniqueKey key){
    if(obj == (*root)->object) return root;
    int flag = 0;
    if(key == STRING){
        if(strcmp((charptr_t)obj, (charptr_t)(*root)->object) > 0) flag = 1;
        else flag = -1;
    }
    else if(key == INTEGER){
        if(*(pint_t)obj > *(pint_t)(*root)->object) flag = 1;
        else flag = -1;
    }
    else if(key == FLOAT){
        if(*(folatptr_t)obj > *(folatptr_t)(*root)->object) flag = 1;
        else flag = -1;
    }
    else return NULL;
    if(flag == 1) return bst_getNode(&(*root)->right, obj, key);
    else if(flag == -1) return bst_getNode(&(*root)->left, obj, key);
    else return NULL;
    return NULL;
}

nodebstptr_t *bst_maxNode(nodebstptr_t *root){
    if(root == NULL) return NULL;
    if((*root)->right == NULL) return root;
    else return bst_maxNode(&(*root)->right);
}

nodebstptr_t *bst_minNode(nodebstptr_t *root){
    if(root == NULL) return NULL;
    if((*root)->left == NULL) return root;
    else return bst_minNode(&(*root)->left);
}

static void bst_del(nodebstptr_t *root, voidptr_t obj, UniqueKey key, StorageType storage){
    nodebstptr_t *temp = bst_getNode(root, obj, key);
    if(temp == NULL) return;
    if((*temp)->left == NULL && (*temp)->right == NULL){
        if(storage == HEAP) free((*temp)->object);
        free(*temp);
        *temp = NULL;
        return;
    }
    else if((*temp)->left == NULL){
        nodebstptr_t del = *temp;
        *temp = (*temp)->right;
        if(storage == HEAP) free(del->object);
        free(del);
        return;
    }
    else if((*temp)->right == NULL){
        nodebstptr_t del = *temp;
        *temp = (*temp)->left;
        if(storage == HEAP) free(del->object);
        free(del);
        return;
    }
    else{
        nodebstptr_t *leftMax = bst_maxNode(&(*temp)->left);
        if(leftMax == NULL) return;
        voidptr_t tmp = (*temp)->object;
        (*temp)->object = (*leftMax)->object;
        (*leftMax)->object = tmp;
        bst_del(&(*temp)->left, (*leftMax)->object, key, storage);
    }
}

static void bst_delete(bstptr_t bst, voidptr_t obj, UniqueKey key, StorageType storage){
    if(bst == NULL) return;
    bst_del(&bst->root, obj, key, storage);
}

bstptr_t initBst()
{
    bstptr_t b = memAllocM(Bst, 1);
    b->root = NULL;
    b->add = bst_add;
    b->del = bst_delete;
    b->dtor = bst_dtor;
    b->get = bst_getNode;
    return b;
}