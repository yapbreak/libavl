#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "syslog.h"
#include "avl.h"

struct _tree_data {
    int key;
    int value;
};

int data_cmp(void *a, void *b)
{
    struct _tree_data aa = *((struct _tree_data *) a);
    struct _tree_data bb = *((struct _tree_data *) b);

    return aa.key - bb.key;
}

void data_print(void *d)
{
    printf("%p|%d-%d", d,
            ((struct _tree_data *) d)->key, ((struct _tree_data *) d)->value);
}

void data_delete(void *d)
{
    free(d);
}

#define MAX_ELEMENT 10000

int main(int argc, char *argv[])
{
    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data tmp_elmnt;
    struct _tree_data current_min;
    unsigned int result;
    unsigned int element_in_tree = 0;
    int i = 0;
    int j = 0;


    (void) argc;
    (void) argv;

    srand(time(NULL));

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].key = rand();
        data[i].value = rand();
    }


    verif_tree(first);

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete);
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

    current_min.key     = (int) 0x80000000;
    current_min.value   = (int) 0x80000000;

    for (i = 0; i < MAX_ELEMENT && element_in_tree != 0; i++) {
        tmp_elmnt.key       = (int) 0x7fffffff;
        tmp_elmnt.value     = (int) 0x7fffffff;
        // Get minimum data
        for (j = 0; j < MAX_ELEMENT; j++) {
            if (    data[j].key < tmp_elmnt.key
                &&  data[j].key > current_min.key) {
                tmp_elmnt.key   = data[j].key;
                tmp_elmnt.value = data[j].value;
            }

        }

        current_min.key     = tmp_elmnt.key;
        current_min.value   = tmp_elmnt.value;

        if (!is_present(first, &tmp_elmnt)) {
            ELOG("Minimum data not in tree");
            return -2;
        }
        delete_node_min(first);
        if (is_present(first, &tmp_elmnt)) {
            ELOG("Minimum element deleted");
            return -3;
        }
        element_in_tree--;
        verif_tree(first);
    }

    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}