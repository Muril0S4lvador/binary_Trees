
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "person.h"
// #include "vector.h"

/*
A entrada do problema consiste em uma sequência de operações de atribuição e leitura de pares chave-valor 
em uma árvore binária genérica. A primeira linha da entrada informa o número de operações. 
Para cada operação de atribuição (set), são dados 4 valores representando o CPF de uma pessoa (string), 
seu nome (assuma que sempre contém apenas uma palavra), idade (int) e altura (float). O CPF será a chave da árvore. 
Os demais valores devem ser usados para criar uma variável do tipo Pessoa que será o valor associado à chave na árvore. 
Para cada operação de leitura (get), é dado o CPF de uma pessoa e o programa deve mostrar na tela os dados da 
pessoa que possui aquele CPF. A altura deve ser exibida com 2 casas depois da vírgula
*/

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

typedef struct
{
    void *key;
    void *value;
} KeyValPair;

typedef struct Node
{
    KeyValPair *pair;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
} BinaryTree;

KeyValPair *key_val_pair_construct(void *key, void *val);
void key_val_pair_destroy(KeyValPair *kvp);

Node *node_construct(void *key, void *value, Node *left, Node *right);
void node_destroy(Node *node);
Node *_node_add_recursive(Node *n, void *key, void *value);

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn);
void binary_tree_add(BinaryTree *bt, void *key, void *value);
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair binary_tree_min(BinaryTree *bt);
KeyValPair binary_tree_max(BinaryTree *bt);
KeyValPair binary_tree_pop_min(BinaryTree *bt);
KeyValPair binary_tree_pop_max(BinaryTree *bt);
void *binary_tree_get(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);
/*
Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);
*/

#endif