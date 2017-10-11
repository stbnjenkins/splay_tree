#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"



// BASIC OPERATIONS

// Insert
void insert_node(tree_node_ptr *root, int key){

    if(!*root){
        tree_node_ptr node = (tree_node_ptr) malloc(sizeof(tree_node));
        node->key = key;
        node->left = node->right = node->parent = NULL;
        *root = node;
        return;
    }else{
        if(key < (*root)->key){
            insert_node(&(*root)->left, key);
        }else{
            if(key > (*root)->key){
                insert_node(&(*root)->right, key);
            }
        }
        // Set up parent nodes
        tree_node_ptr parent = (*root);
        while(parent){
            if(key < parent->key){
                if(key == parent->left->key){
                    parent->left->parent = parent;
                    return;
                }
                parent = parent->left;
                continue;
            }else{
                if(key > parent->key){
                    if(key == parent->right->key){
                        parent->right->parent = parent;
                        return;
                    }
                    parent = parent->right;
                    continue;
                }
            }
        }
    }

    //if equal, do nothing
}

// Destroy
void destroy_tree(tree_node_ptr root){
    if(!root)
    {
        destroy_tree(root->right);
        destroy_tree(root->left);
        free(root);
    }
}

// delete
//




// TRAVERSAL
void inorder_traverse_recursive(tree_node_ptr root, void (*f)(tree_node_ptr) ){
    if(!root)return;
    inorder_traverse_recursive(root->left, f);      // left
    f(root);                                        // root
    inorder_traverse_recursive(root->right, f);     // right
}

void preorder_traverse_recursive(tree_node_ptr root, void (*f)(tree_node_ptr) ){
    if(!root)return;
    f(root);                                        // root
    preorder_traverse_recursive(root->left, f);     // left
    preorder_traverse_recursive(root->right, f);    // right
}






// ROTATIONS

void zig(tree_node_ptr target_node){ // still can reduce mem footprint
    tree_node_ptr temp = target_node->right; 
    tree_node_ptr parent = target_node->parent;
    target_node->parent = parent->parent;
    target_node->right = parent;
    if(parent->parent) parent->parent->right = target_node; // check 4 null
    temp->parent = parent;
    parent->left = temp;
    parent->parent = target_node;   
    return;
}

void zag(tree_node_ptr target_node){ // still can reduce mem footprint
    tree_node_ptr temp = target_node->left; 
    tree_node_ptr parent = target_node->parent;
    target_node->parent = parent->parent;
    target_node->left = parent;
    if(parent->parent) parent->parent->left = target_node;
    parent->parent->left = target_node;
    temp->parent = parent;
    parent->right = temp;
    parent->parent = target_node;   
    return;
}

void zigzag(tree_node_ptr target_node){
    zag(target_node);
    zig(target_node);
}

void zagzig(tree_node_ptr target_node){
    zig(target_node);
    zag(target_node);
}

void zagzag(tree_node_ptr target_node){
    zag(target_node);
    zag(target_node);
}

void zigzig(tree_node_ptr target_node){
    zig(target_node);
    zig(target_node);
}



// MISCELLANEOUS

// print a node
void print_node(tree_node_ptr node){
    printf("Key: %d\tParent key: %d\n", node->key, node->parent == NULL ? -1 : node->parent->key);
}