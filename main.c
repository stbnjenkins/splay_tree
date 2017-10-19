#include <time.h>
#include <stdio.h>
#include "splay.c"


int main(int argc, char** argv){
    time_t start_t, end_t;
    double diff_t;
    time(&start_t);
    printf("Starting program\n");
    /***********************************************/
    
    // Variable definitions
    FILE *csv;
    int avg_depth_of_search, number_of_nodes, find_ops;
    tree_node_ptr root = NULL;
    find_result r;    
    char command;
    int key;

    // Opening file
    csv = fopen("result_t10000_s58_l.csv","w+");
    if (!csv) { //If error opening file
        fprintf(stderr, "Can't create output file result.csv\n");
        exit(1);
    }
    printf("Files opened succesfully.\n");
    fprintf(csv,"n,t,avg_path_length\n");

    while(!feof(stdin) && scanf("%c %d\n", &command, &key) == 2){
        switch(command){
            case '#':
                if(root){
                    fprintf(csv,"%d,%d,%d\n", number_of_nodes, find_ops, avg_depth_of_search/find_ops);
                    destroy_tree(&root); // Free memory for next tree
                }
                root = NULL;
                // Set up number of nodes, and other stuff
                number_of_nodes = key;
                find_ops = 0; //counter of find operations to take average at the end
                avg_depth_of_search = 0;
                break;

            case 'F':
                // find
                r = find(&root, key);
                avg_depth_of_search += r.depth;
                find_ops++;                
                break;

            case 'I':
                insert_node(&root, key);
                break;

            default:
                fprintf(stderr, "Invalid file format. Exiting...\n");
                exit(1);
        }
    }
    // end of file process last tree data
    if(root){
        fprintf(csv,"%d,%d,%d\n", number_of_nodes, find_ops, avg_depth_of_search/find_ops);
        destroy_tree(&root);
    }

    printf("Closing file...");
    fclose(csv);
    printf("File closed\n");

    /***********************************************/
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    printf("Total execution time = %f\n", diff_t);
}