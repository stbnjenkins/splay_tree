
typedef struct TREE_NODE{
    int key;
    struct TREE_NODE *left, *right, *parent;
}tree_node, *tree_node_ptr;