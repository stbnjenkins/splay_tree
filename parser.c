#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "splay.c"

/*
NOTE: for sure not the fastest way for reading such large files. Will make A LOT
of context switches for reading file, but still quicker to implement. Will change 
later if I've time and its worth it.

With own memory manager we request block for all nodes and avoid this system calls
and context switching.

==================
Measuring time:
ck ticks per second) to get processor time, like following.

     #include <time.h>
     
     clock_t start, end;
     double cpu_time_used;
     
     start = clock();
      //Do the work.
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

taken from: http://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
*/
void parseFile(char* filename){
    // Variable definitions
    FILE *fp;
    clock_t start, end;
    double cpu_time_used;
    int depth_of_search, avg_depth_of_search, number_of_nodes, find_ops;
    tree_node_ptr root = NULL;
    find_result* r;

    // Opening file
    printf("Opening file %s...", filename);
    fp = fopen(filename, "r+");
    if (!fp) { //If error opening file
        fprintf(stderr, "Can't open input file %s\n", filename);
        exit(1);
    }
    printf("File opened succesfully.\n");
    

    //first line is #100
    // fscanf(fp, "%c %d %d");

    // Process file
    // while not EOF, read number of lines, 
    char command;
    int key;
    while(!feof(fp)){
        fscanf(fp, "%c %d\n", &command, &key);
        switch(command){
            case '#':
                if(root){
                    // process data
                    printf("Nodes: %d\n", number_of_nodes);
                    printf("Number of find ops: %d\n", find_ops);
                    printf("*****************\n");
                    preorder_traverse_recursive(root, &print_node);
                    printf("*****************\n\n");
                    // free memory for next tree
                    destroy_tree(root);
                }
                root = NULL;
                // start = clock(); // tic-tac
                // Set up number of nodes, and other stuff
                number_of_nodes = key;
                find_ops = 0; //counter of find operations to take average at the end
                break;
            case 'I':
                insert_node(&root, key);
                // printf("Inserting node with key %d\n", key);
                break;
            case 'F':
                // start clock
                // find
                r = find(root, key);
                find_ops++;
                // end clock, report to var
                // printf("Finding node with key %d\n", key);
                break;
            default:
                fprintf(stderr, "Invalid file format. Exiting...\n");
                exit(1);
        }
    }
    // end of file process last tree data
    if(root){
        // process data
        printf("Nodes: %d\n", number_of_nodes);
        printf("Number of find ops: %d\n", find_ops);
        printf("*****************\n");
        preorder_traverse_recursive(root, &print_node);
        printf("*****************\n\n");
        // free memory for next tree
        destroy_tree(root);
    }
    printf("Closing file...");
    fclose(fp);
    printf("File closed\n");
    return;
}