#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"


void print_node( tree_node_ptr );

// Insert
void insert_node(tree_node_ptr *root, int key){

    if(*root == NULL){
        tree_node_ptr node = (tree_node_ptr) malloc(sizeof(tree_node));
        node->key = key;
        node->left = node->right = node->parent = NULL;
        *root = node;
        return;
    }
    if(key < (*root)->key){
        return insert_node(&(*root)->left, key);
    }
    if(key > (*root)->key){
        return insert_node(&(*root)->right, key);
    }
    //if equal, do nothing
}

// delete

// traversal
void inorder_traverse_recursive(tree_node_ptr root, void (*f)(tree_node_ptr) ){
    if(root == NULL){
        return;
    }
    // left
    inorder_traverse_recursive(root->left, f);
    // root
    f(root);
    // right
    inorder_traverse_recursive(root->right, f);
}

void preorder_traverse_recursive(tree_node_ptr root, void (*f)(tree_node_ptr) ){
    if(root == NULL){
        return;
    }
    
    // root
    f(root);

    // left
    preorder_traverse_recursive(root->left, f);

    // right
    preorder_traverse_recursive(root->right, f);
}

void destroy_tree(tree_node_ptr root){
    if( root != NULL )
    {
        destroy_tree(root->right);
        destroy_tree(root->left);
        free(root);
    }
}

// rotations

tree_node_ptr zig_left(tree_node_ptr searched_node, tree_node_ptr parent){ //maybe *tree_node_ptr?
    tree_node_ptr temp = searched_node->right;
    searched_node->right = parent;
    parent->left = temp;
    return searched_node;
}

tree_node_ptr zig_right(tree_node_ptr searched_node, tree_node_ptr parent){ //maybe *tree_node_ptr?
    tree_node_ptr temp = searched_node->left;
    searched_node->left = parent;
    parent->right = temp;
    return searched_node;
}

// print
void print_node(tree_node_ptr node){
    printf("Key: %d\n", node->key);
}





int main(int argc, char** argv){
    printf("Starting program\n");

    printf("Testing zig_left\n");
    tree_node_ptr root = NULL;
    insert_node(&root, 4);
    insert_node(&root, 2);
    insert_node(&root, 1);
    insert_node(&root, 3);
    insert_node(&root, 5);
    preorder_traverse_recursive(root, &print_node);
    printf("Rotating...\n");
    root = zig_left(root->left, root);
    preorder_traverse_recursive(root, &print_node);
    destroy_tree(root);

    printf("Testing zig_right\n");
    root = NULL;
    insert_node(&root, 2);
    insert_node(&root, 1);
    insert_node(&root, 4);
    insert_node(&root, 3);
    insert_node(&root, 5);
    preorder_traverse_recursive(root, &print_node);
    printf("Rotating...\n");
    root = zig_right(root->right, root);
    preorder_traverse_recursive(root, &print_node);
    destroy_tree(root);
    
}