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

#include "../syslog.h"
#include "../avl.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    tree *first;

    // Try to allocate a new tree.
    first = init_dictionnary(NULL, NULL, NULL, NULL);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }
    if (sizeof(*first) != sizeof(tree)) {
        ELOG("Wrong returned size");
        return EXIT_FAILURE;
    }

    // Try to delete it
    delete_tree(first);

    // Try to delete a null tree
    delete_tree(NULL);

    return EXIT_SUCCESS;
}
