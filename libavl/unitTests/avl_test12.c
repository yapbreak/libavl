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

static int data_cmp(void *a, void *b)
{
    struct _tree_data aa = *((struct _tree_data *) a);
    struct _tree_data bb = *((struct _tree_data *) b);

    return aa.key - bb.key;
}

static void data_delete(void *d)
{
    free(d);
}

#define MAX_ELEMENT 10000

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data look_for_data;
    unsigned int result;
    int bool_result;
    unsigned int element_in_tree = 0;
    int i = 0;

    unsigned long rand_seed = (unsigned long) time(NULL);
    printf("Random seed: %lu\n", rand_seed);
    srand(rand_seed);

    verif_tree(first);

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, NULL, data_delete, NULL);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // Add data
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        // [RMID #67] My keys need to be unique
        do {
            data[i].key = rand();
            look_for_data.key = data[i].key;
        } while (is_present(first, &(look_for_data)));
        data[i].value = rand();
        element_in_tree++;

        ILOG("Insert <%d, %d>", data[i].key, data[i].value);
        result = insert_elmt(first, &(data[i]), sizeof(struct _tree_data));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Get data
    for (i = MAX_ELEMENT - 1; i >= 0; i--) {
        look_for_data.key = data[i].key;
        bool_result = get_data(first, &(look_for_data), sizeof(struct _tree_data));
        if (!bool_result) {
            ELOG("Data not found");
            return EXIT_FAILURE;
        }
        ILOG("Get <%d, %d>", look_for_data.key, look_for_data.value);
        if (look_for_data.key != data[i].key || look_for_data.value != data[i].value) {
            ELOG("Not the good data retrieve.");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Update data with new values
    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].value = rand();
    }

    // Re-Add data with new values
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        look_for_data.key = data[i].key;
        if (!is_present(first, &(look_for_data))) {
            ELOG("Element not found in tree.");
            return EXIT_FAILURE;
        }
        ILOG("Insert <%d, %d>", data[i].key, data[i].value);
        result = insert_elmt(first, &(data[i]), sizeof(struct _tree_data));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Get data
    for (i = MAX_ELEMENT - 1; i >= 0; i--) {
        look_for_data.key = data[i].key;
        bool_result = get_data(first, &(look_for_data), sizeof(struct _tree_data));
        if (!bool_result) {
            ELOG("Data not found");
            return EXIT_FAILURE;
        }
        ILOG("Get <%d, %d>", look_for_data.key, look_for_data.value);
        if (look_for_data.key != data[i].key || look_for_data.value != data[i].value) {
            ELOG("Not the good data retrieve.");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Try to delete it
    delete_tree(first);

    return EXIT_SUCCESS;
}
