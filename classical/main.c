#include <time.h>
#include <stdio.h>
#include <string.h>
#include "splay.c"


int main(int argc, char** argv){
    printf("Starting classical splay tree program\n");
    time_t start_t, end_t;
    double diff_t;
    time(&start_t);
    if(argc != 2){
        printf("Usage: $ program <result_filename>\n");
        exit(1);
    }
    char* filename = argv[1];

    // Variable definitions
    FILE *csv;
    int avg_depth_of_search, number_of_nodes, find_ops; // For tracking stats
    tree_node_ptr root = NULL;
    find_result r;    
    char command;
    int key;

    // Create CSV for results
    csv = fopen(filename, "w+");
    if (!csv) { //If error opening file
        fprintf(stderr, "Can't create output file result.csv\n");
        exit(1);
    }
    printf("Files created succesfully.\n");
    fprintf(csv,"n,depth\n");

    // Read from std input until the end. Expects each line to be
    // as <char> <int>
    while(!feof(stdin) && scanf("%c %d\n", &command, &key) == 2){
        switch(command){
            case '#': // Save stats of last tree, and reset everything for new test run
                if(root){
                    fprintf(csv,"%d,%.4lf\n", number_of_nodes, (double)avg_depth_of_search/find_ops);
                    destroy_tree(&root); // Free memory for next tree
                }
                root = NULL;
                // Set up number of nodes, and other stuff
                number_of_nodes = key;
                // Maybe take out this parameter and fix it?
                find_ops = 0; //counter of find operations to take average at the end
                avg_depth_of_search = 0;
                break;

            case 'F': // Find operation
                r = find(&root, key);
                avg_depth_of_search += r.depth;
                find_ops++;                
                break;

            case 'I': // Insert operation
                insert_node(&root, key);
                break;

            default:
                fprintf(stderr, "Invalid file format. Exiting...\n");
                exit(1);
        }
    }
    // end of file process last tree data
    if(root){
        fprintf(csv,"%d,%.4lf\n", number_of_nodes, (double)avg_depth_of_search/find_ops);
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