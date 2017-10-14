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
                if(key == parent->right->key){
                    parent->right->parent = parent;
                    return;
                }
                parent = parent->right;
                continue;
            }
        }
    }

    //if equal, do nothing
}

// Find
find_result* find(tree_node_ptr root, int key){
    find_result* result = (find_result*) malloc(sizeof(find_result));
    int depth = 0;
    while(root){ // root not null
        if(root->key == key){
            result->depth = depth;
            result->node = root;
            return result;
        }else{
            if(key < root->key){
                root = root->left;
                depth++;
                continue;
            }else{
                root = root->right;
                depth++;
                continue;
            }
        }
    }
    return NULL;
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

// splay
/*
    at the end should update root.

 /   params: target_node, tree_node_ptr *root

    ehile target_node not root, do splaysplay.c:152:39: error: expect
*/
void splay(tree_node_ptr target_node, tree_node_ptr *root){ 
    while(target_node->parent){ //When is 0 (NULL) cycle will stop
        // find rotation
        if(!(target_node->parent->parent)){ 
            
            //if parent is root
            if(target_node->parent->left == target_node){
                zig(target_node, root);
                return;
            }else{
                zag(target_node, root);
                return;
            }
        }else{
            // decide which rotation
            /// else
            //zigzag(root->left->right, &root);
            tree_node_ptr grandpa = target_node->parent->parent; 
            
            if(grandpa->left->left == target_node){
                zigzig(target_node, root);
                continue;
            }

            if(grandpa->left->right == target_node){
                zigzag(target_node, root);
                continue;
            }

            if(grandpa->right->right == target_node){
                zagzag(target_node, root);
                continue;
            }

            if(grandpa->right->left == target_node){
                zagzig(target_node, root);
                continue;
            }
        }
    } // end while
}


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
// Assumes no duplicates keys. Unpredictable behavior if there are.

void zig(tree_node_ptr target_node, tree_node_ptr *root){
    // If target_node is NULL, or already root, do nothing
    if(!target_node || !(target_node->parent))return;

    // If target_node's parent is root, set target_node's parent to NULL
    // else, setup the corresponding parent.
    tree_node_ptr parent = target_node->parent;
    if(!(target_node->parent->parent)){
        target_node->parent = NULL;
    }else{
        // means have grandfather
        if(target_node->key < parent->parent->key){
            parent->parent->left = target_node;
        }else{
            parent->parent->right = target_node;
        }
        target_node->parent = parent->parent;
    }
    parent->parent = target_node; //ok
    if(target_node->right){  //err, check if null
        target_node->right->parent = parent;
    }
    parent->left = target_node->right;
    target_node->right = parent;

    // updating root
    tree_node_ptr it = target_node;
    while(it->parent){
        it = it->parent;
    }
    *root = it;
}

void zag(tree_node_ptr target_node, tree_node_ptr *root){
    // If target_node is NULL, or already root, do nothing
    if(!target_node || !(target_node->parent))return;

    // If target_node's parent is root, set target_node's parent to NULL
    // else, setup the corresponding parent.
    tree_node_ptr parent = target_node->parent;
    if(!(target_node->parent->parent)){
        target_node->parent = NULL;
    }else{
        // means have grandfather
        if(target_node->key < parent->parent->key){
            parent->parent->left = target_node;
        }else{
            parent->parent->right = target_node;
        }
        target_node->parent = parent->parent;
    }
    parent->parent = target_node; //ok
    if(target_node->left){  //err, check if null
        target_node->left->parent = parent;
    }
    parent->right = target_node->left;
    target_node->left = parent;

    // updating root
    tree_node_ptr it = target_node;
    while(it->parent){
        it = it->parent;
    }
    *root = it;
}


void zigzag(tree_node_ptr target_node, tree_node_ptr* root){
    zag(target_node, root);
    zig(target_node, root);
}

void zagzig(tree_node_ptr target_node, tree_node_ptr* root){
    zig(target_node, root);
    zag(target_node, root);
}

void zagzag(tree_node_ptr target_node, tree_node_ptr* root){
    zag(target_node, root);
    zag(target_node, root);
}

void zigzig(tree_node_ptr target_node, tree_node_ptr* root){
    zig(target_node, root);
    zig(target_node, root);
}


// MISCELLANEOUS

// print a node
void print_node(tree_node_ptr node){
    printf("Key: %d\tParent key: %d\n", node->key, node->parent == NULL ? -1 : node->parent->key);
}