/*
 *   Libavl is a library to manage AVL structure to store and organize
 *   everykind of data. You just need to implement function to compare,
 *   to desallocate and to print your structure.
 *
 *       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *                   Version 2, December 2004 
 *
 *   Copyright (C) 2013 Adrien Oliva <adrien.oliva@yapbreak.fr>
 *
 *   Everyone is permitted to copy and distribute verbatim or modified 
 *   copies of this license document, and changing it is allowed as long 
 *   as the name is changed. 
 *
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../syslog.h"
#include "../avl.h"

struct _tree_data {
    int key;
    int value;
};

#define MAX_ELEMENT 10000

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data tmp_elmnt;
    unsigned int result;
    unsigned int element_in_tree = 0;
    int i = 0;

    unsigned long rand_seed = (unsigned long) time(NULL);
    printf("Random seed: %lu\n", rand_seed);
    srand(rand_seed);

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].key = rand();
        data[i].value = rand();
    }


    verif_tree(first);
    // Try to print an null tree.
    print_tree(first);

    // Try to allocate a new tree.
    first = init_dictionnary(NULL, NULL, NULL, NULL);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // Add data
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        tmp_elmnt.key = data[i].key;
        if (!is_present(first, &(tmp_elmnt))) {
            element_in_tree++;
        }
        result = insert_elmt(first, &(data[i]), sizeof(struct _tree_data));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    print_tree(first);

    // Try to delete it
    delete_tree(first);

    return EXIT_SUCCESS;
}
