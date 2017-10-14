#include "parser.c"

//#include "splay.c"


int main(int argc, char** argv){
    printf("Starting program\n");
    parseFile("tests/simple_test.txt");
    
    // tree_node_ptr root = NULL;
    // insert_node(&root, 10);
    // insert_node(&root, 15);
    // insert_node(&root, 5);
    // insert_node(&root, 2);
    // insert_node(&root, 7);
    // insert_node(&root, 6);
    // insert_node(&root, 8);
    // preorder_traverse_recursive(root, &print_node);
    // printf("Rotating...\n");
    // zigzag(root->left->right, &root);
    // preorder_traverse_recursive(root, &print_node);
    // printf("Press key to delete tree...\n");
    // getchar();
    // destroy_tree(root); //fix root, leaking memory


    // tree_node_ptr root = NULL;
    // insert_node(&root, 2);
    // insert_node(&root, 1);
    // insert_node(&root, 4);
    // insert_node(&root, 3);
    // insert_node(&root, 5);
    // preorder_traverse_recursive(root, &print_node);
    // printf("Rotating...\n");
    // getchar();
    // zag(root->right->right, &root);
    // preorder_traverse_recursive(root, &print_node);
    // printf("Press key to delete tree...\n");
}