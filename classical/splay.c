#include <stdio.h>
#include <stdlib.h>
#include "../tree_node.h"



// BASIC OPERATIONS
void insert_node(tree_node_ptr *root, int key){
    
    if(!(*root)){ // Case empty tree
        tree_node_ptr node = (tree_node_ptr) malloc(sizeof(tree_node));
        node->key = key;
        node->left = node->right = node->parent = NULL;
        *root = node;
        return;
    }else{ //traverse tree till right position
        tree_node_ptr iter = (*root);
        tree_node_ptr iter_papa = NULL;
        while(iter){
            if(key < iter->key){
                iter_papa = iter;
                iter = iter->left;
                continue;
            }else{
                if(key > iter->key){
                    iter_papa = iter;
                    iter = iter->right; 
                    continue;
                }else{
                    //equal do nothin
                    splay(iter, root);
                    return; //still should splay
                }
            }
        }
        //insert, set parent and splay
        tree_node_ptr node = (tree_node_ptr) malloc(sizeof(tree_node));
        node->key = key;
        node->left = node->right = NULL;
        node->parent = iter_papa;

        if(key < iter_papa->key){
            iter_papa->left = node;
        }else{
            if(key > iter_papa->key){
                iter_papa->right = node;
            }   
        }

        //Splay
        splay(node, root);
    }
}

// Find
find_result find(tree_node_ptr* root, int key){
    tree_node_ptr iter = *root;
    tree_node_ptr iter_papa = NULL;
    find_result result;
    int depth = 0;
    while(iter){ // root not null
        if(iter->key == key){
            result.depth = depth;
            result.node = iter;
            splay(iter, root);
            return result;
        }else{
            if(key < iter->key){
                iter_papa = iter;
                iter = iter->left;
                depth++;
                continue;
            }else{
                iter_papa = iter;
                iter = iter->right;
                depth++;
                continue;
            }
        }
    }
    // splay closest node if node was not found
    splay(iter_papa, root);
    result.depth = depth;
    result.node = NULL;
    return result;
}
// Destroy whole tree
// Traverses tree in postorder, deleting element
void destroy_tree_recursive(tree_node_ptr root){
    if(!root)
    {
        destroy_tree_recursive(root->right);
        destroy_tree_recursive(root->left);
        free(root);
    }
}

void destroy_tree(tree_node_ptr* root){
    tree_node_ptr iter = *root;
    tree_node_ptr iter_papa = NULL;
    while(iter){ // iter not null
        // if has no child
        if(!(iter->left || iter->right)){
            if(iter_papa){ //if leave
                if(iter->key < iter_papa->key){
                    iter_papa->left = NULL;
                }else{
                    iter_papa->right = NULL;
                }
            }else{ // root of tree and no children
                free(iter);
                *root = NULL;
                return;
            }
            free(iter);
            iter = iter_papa;
            iter_papa = iter_papa->parent;
            continue;
        }
        if(iter->left){
            iter_papa = iter;
            iter = iter->left;
            continue;
        }
        if(iter->right){
            iter_papa = iter;
            iter = iter->right;
            continue;
        }
        iter = iter->parent;
        free(iter);
    }
}

// splay
void splay(tree_node_ptr target_node, tree_node_ptr *root){ 
    while(target_node->parent){ // Stop when target_node is the root of tree
        // find rotation

        // Make single last rotation to get to the root
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
            tree_node_ptr grandpa = target_node->parent->parent; 
            if(grandpa->left){
                if(grandpa->left->left == target_node){
                    zigzig(target_node, root);
                    continue;
                }
    
                if(grandpa->left->right == target_node){
                    zigzag(target_node, root);
                    continue;
                }
            }
            
            if(grandpa->right){
                if(grandpa->right->right == target_node){
                    zagzag(target_node, root);
                    continue;
                }
    
                if(grandpa->right->left == target_node){
                    zagzig(target_node, root);
                    continue;
                }
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
    parent->parent = target_node;
    if(target_node->right){ 
        target_node->right->parent = parent;
    }
    parent->left = target_node->right;
    target_node->right = parent;

    // updating root
    tree_node_ptr it = *root;
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
    parent->parent = target_node;
    if(target_node->left){ 
        target_node->left->parent = parent;
    }
    parent->right = target_node->left;
    target_node->left = parent;

    // updating root
    tree_node_ptr it = *root;
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
    zag(target_node->parent, root);
    zag(target_node, root);
}

void zigzig(tree_node_ptr target_node, tree_node_ptr* root){
    zig(target_node->parent, root);
    zig(target_node, root);
}

// MISCELLANEOUS

// Print a node
void print_node(tree_node_ptr node){
    printf("Key: %d\tParent key: %d\n", node->key, node->parent == NULL ? -1 : node->parent->key);
}