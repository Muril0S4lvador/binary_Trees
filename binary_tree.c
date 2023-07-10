#include "person.h"
#include "binary_tree.h"

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *item = malloc(sizeof(KeyValPair));
    item->key = key;
    item->value = val;
    return item;
}

void key_val_pair_destroy(KeyValPair *kvp){

    free(kvp->value);
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *n = malloc(sizeof(Node));

    n->pair = key_val_pair_construct(key, value);
    n->left = left;
    n->right = right;

    return n;
}

void node_destroy(Node *node){
    key_val_pair_destroy(node->item);

}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn){

    BinaryTree *bt = malloc(sizeof(BinaryTree));
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    
    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){

    Node *n = bt->root;

    while(n){
        KeyValPair *pair = n->pair;

        if(bt->cmp_fn(pair->key, key) > 0){
            // Caso a chave 2 seja maior que node, direita
            n = n->right

        } else if( bt->cmp_fn(pair->key, key) < 0 ){
            // Caso a chave 2 seja menor que node, esquerda
            n = n->left;

        } else{
            KeValPair *it = n->pair;
            it->value = value;
            return;
        }
    }

    n = node_construct(key, value, NULL, NULL);
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);

int binary_tree_empty(BinaryTree *bt);

void binary_tree_remove(BinaryTree *bt, void *key);

KeyValPair binary_tree_min(BinaryTree *bt);

KeyValPair binary_tree_max(BinaryTree *bt);

KeyValPair binary_tree_pop_min(BinaryTree *bt);

KeyValPair binary_tree_pop_max(BinaryTree *bt);

void *binary_tree_get(BinaryTree *bt, void *key);

void binary_tree_destroy(BinaryTree *bt);