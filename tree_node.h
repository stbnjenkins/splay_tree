#ifndef TREE_NODE_H
#define TREE_NODE_H

typedef struct TREE_NODE{
    int key;
    struct TREE_NODE *left, *right, *parent;
}tree_node, *tree_node_ptr;

typedef struct FIND_RESULT{
    int depth;
    tree_node_ptr node; // NULL if doesnt belong to tree
} find_result;


// Functions
void insert_node(tree_node_ptr*, int);
void inorder_traverse_recursive(tree_node_ptr, void (*f)(tree_node_ptr));
void preorder_traverse_recursive(tree_node_ptr, void (*f)(tree_node_ptr));
void print_node(tree_node_ptr);
// Rotations
void zig(tree_node_ptr, tree_node_ptr*);
void zag(tree_node_ptr, tree_node_ptr*);
void zigzag(tree_node_ptr, tree_node_ptr*);
void zagzig(tree_node_ptr, tree_node_ptr*);
void zagzag(tree_node_ptr, tree_node_ptr*);
void zigzig(tree_node_ptr, tree_node_ptr*);
void splay(tree_node_ptr, tree_node_ptr*);

#endif //TREE_NODE_H