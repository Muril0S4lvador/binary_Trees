#include "binary_tree.h"

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *item = malloc(sizeof(KeyValPair));
    item->key = key;
    item->value = val;
    return item;
}

void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){

    key_destroy_fn(kvp->key);
    val_destroy_fn(kvp->value);
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *n = malloc(sizeof(Node));

    n->pair = key_val_pair_construct(key, value);
    n->left = left;
    n->right = right;

    return n;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    key_val_pair_destroy(node->pair, key_destroy_fn, val_destroy_fn);
    free(node);

}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn){

    BinaryTree *bt = malloc(sizeof(BinaryTree));
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    bt->root = NULL;
    
    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){

    Node *n = bt->root, *parent = NULL;
    int left = 0;

    if(!n){
        bt->root = node_construct(key, value, NULL, NULL);
        return;
    }

    while(n){
        KeyValPair *pair = n->pair;
        left = 0;
        parent = n;

        if(bt->cmp_fn(pair->key, key) < 0){
            // Caso a chave 2 seja maior que node, direita
            n = n->right;

        } else if( bt->cmp_fn(pair->key, key) > 0 ){
            // Caso a chave 2 seja menor que node, esquerda
            n = n->left;
            left++;

        } else{

            bt->val_destroy_fn(pair->value);
            bt->key_destroy_fn(key);
            pair->value = value;
            return;
        }
    }

    n = node_construct(key, value, NULL, NULL);

    if(left)
        parent->left = n;
    else
        parent->right = n;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value){
    bt->root = _node_add_recursive(bt->root, key, value, bt->key_destroy_fn, bt->val_destroy_fn);
}

Node *_node_add_recursive(Node *n, void *key, void *value, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    if(!n){
        n = node_construct(key, value, NULL, NULL);

    } else if( strcmp(n->pair->key, key) < 0 ){
        // n->pair->key menor que key || key maior que n->pair->key
        n->right = _node_add_recursive(n->right, key, value, key_destroy_fn, val_destroy_fn);

    } else if( strcmp(n->pair->key, key) > 0 ){
        // n->pair->key maior que key || key menor que n->pair->key
        n->left = _node_add_recursive(n->left, key, value, key_destroy_fn, val_destroy_fn);

    } else{
        // chaves iguais
        val_destroy_fn(n->pair->value);
        key_destroy_fn(key);
        n->pair->value = value;
    }

    return n;
}

int binary_tree_empty(BinaryTree *bt){
    return !bt->root;
}

void binary_tree_remove(BinaryTree *bt, void *key){
    Node *n = bt->root, *parent = NULL;
    int left = 0;
    
    // Pego o node que procuro
    while(n){
        KeyValPair *pair = n->pair;

        if(bt->cmp_fn(pair->key, key) < 0){
            // Caso a chave 2 seja maior que node, direita
            parent = n;
            n = n->right;
            left = 0;

        } else if( bt->cmp_fn(pair->key, key) > 0 ){
            // Caso a chave 2 seja menor que node, esquerda
            parent = n;
            n = n->left;
            left = 1;

        } else{
            break;

        }
    }

    if(!n){
        return;

    } else if(n == bt->root){
        bt->root = NULL;

    } else if( !n->left && !n->right ){
        // Caso nao tenha filhos
        if(left)
            parent->left = NULL;
        else
            parent->right = NULL;
        
    } else if( !n->left ){
        // Caso tenha apenas filho a direita
        if(left)
            parent->left = n->right;
        else
            parent->right = n->right;

    } else if( !n->right ){
        // Caso tenha apenas filho a esquerda
        if(left)
            parent->left = n->left;
        else
            parent->right = n->left;

    } else{
        Node *sucessor = NULL, *n2 = n->right;

        while( n2 ){
            sucessor = n2;
            n2 = n2->left;
        }
    }
}

KeyValPair binary_tree_min(BinaryTree *bt){
    Node *n = bt->root, *parent = NULL;

    while(n){
        parent = n;
        n = n->left;
    }
    KeyValPair kvp = {parent->pair->key, parent->pair->value};
    return kvp;
}

KeyValPair binary_tree_max(BinaryTree *bt){
    Node *n = bt->root, *parent = NULL;

    while(n){
        parent = n;
        n = n->right;
    }
    KeyValPair kvp = {parent->pair->key, parent->pair->value};
    return kvp;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    Node *n = bt->root, *parent = NULL;
    if(!n)
        return NULL;

    while(n->left){
        parent = n;
        n = n->left;
    }
    if(parent)
        parent->left = n->left;
    else
        bt->root = n->right;
    KeyValPair *kvp = n->pair;
    free(n);
    return kvp;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
    Node *n = bt->root, *parent = NULL;
    if(!n)
        return NULL;

    while(n->right){
        parent = n;
        n = n->right;
    }
    if(parent)
        parent->right = n->left;
    else
        bt->root = n->left;
    KeyValPair *kvp = n->pair;
    free(n);
    return kvp;
}

void *binary_tree_get(BinaryTree *bt, void *key){
    Node *n = bt->root;

    while( n ){
        KeyValPair *pair = n->pair;

        if(bt->cmp_fn(pair->key, key) < 0){
            // Caso a chave 2 seja maior que node, direita
            n = n->right;

        } else if( bt->cmp_fn(pair->key, key) > 0 ){
            // Caso a chave 2 seja menor que node, esquerda
            n = n->left;

        } else{
            
            return pair->value;
        }
    }

    return NULL;
}

void binary_tree_destroy(BinaryTree *bt){
    bt->root = _node_destroy_recursive(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
}

Node *_node_destroy_recursive(Node *n, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    if(n){
        n->left = _node_destroy_recursive(n->left, key_destroy_fn, val_destroy_fn);
        n->right = _node_destroy_recursive(n->right, key_destroy_fn, val_destroy_fn);

        if( !n->left && !n->right )
            node_destroy(n, key_destroy_fn, val_destroy_fn);
    }
    return NULL;
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt){
    Vector *v = vector_construct();
    Stack *s = stack_construct();

    Node *act = bt->root, *pop;

    while( 1 ){

        while(act){
            stack_push(s, act);
            act = act->left;
        }

        if(stack_empty(s)){
            stack_destroy(s);
            break;
        } else {
            pop = stack_pop(s);
            vector_push_back(v, pop->pair);
            act = pop->right;
        }
    }

    return v;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt){
    Vector *v = vector_construct();
    Stack *s = stack_construct();
    Node *pop;
    
    stack_push(s, bt->root);

    while(!stack_empty(s)){
        pop = stack_pop(s);
        vector_push_back(v, pop->pair);
        if(pop->right) stack_push(s, pop->right);
        if(pop->left) stack_push(s, pop->left);
    }
    stack_destroy(s);

    return v;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt){
    Vector *v = vector_construct();
    Stack *q1 = stack_construct(), *q2 = stack_construct();
    Node *n;

    stack_push(q1, bt->root);

    while(!stack_empty(q1)){
        n = stack_pop(q1);
        if(n->left) stack_push(q1, n->left);
        if(n->right) stack_push(q1, n->right);
        stack_push(q2, n);
    }
    while(!stack_empty(q2)){
        n = stack_pop(q2);
        vector_push_back(v, n->pair);
    }

    stack_destroy(q1);
    stack_destroy(q2);
    return v;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt){
    Vector *v = vector_construct();
    Queue *q = queue_construct();
    Node *n;

    queue_push(q, bt->root);

    while(!queue_empty(q)){
        n = queue_pop(q);
        if(n){
            vector_push_back(v, n->pair);
            if(n->left) queue_push(q, n->left);
            if(n->right) queue_push(q, n->right);
        }
    }
    queue_destroy(q);

    return v;
}