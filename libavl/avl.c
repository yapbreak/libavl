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
#include <string.h>
#include <assert.h>

#include "config.h"
#include "avl.h"
#include "syslog.h"

// ========================================================
// Internal API definition
// ========================================================
/** \fn int is_present_recur(node n, void *d, int (*data_cmp) (void *, void *));
 * \brief Recursive function to check if a given data is present in tree.
 *
 * \return 1 if data is present, 0 if not.
 * \param n Node of subtree to analyze.
 * \param d Pointer to data.
 * \param data_cmp Function to compare two nodes.
 *
 * \warning If you use this function you probably make a mistake.
 */
static int is_present_recur(node n, void *d, int (*data_cmp) (void *, void *));

/** \fn int height_tree(node tree);
 * \brief Give the height of tree.
 *
 * \return Height of tree
 * \param tree Root of tree to analyze
 *
 * If there is no son, height of node is 1. Else, the height is maximum
 * height of subtrees plus 1.
 *
 * \warning If you use this function you probably make a mistake.
 */
static unsigned int height_tree(node n);

/** \fn void adjust_tree_height(node n);
 * \brief Update height field of tree.
 *
 * \param n Calculate new height of tree pointed by \c tree.
 *
 * For the height calculation rules, see \c height_tree function.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void adjust_tree_height(node n);

/** \fn void adjust_tree_height(node n);
 * \brief Update height field of tree.
 *
 * \param n Calculate new height of tree pointed by \c tree.
 *
 * For the height calculation rules, see \c height_tree function.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void adjust_tree_height(node n);

/** \fn node rotate_tree_right(node n);
 * \brief Proceed right rotation to tree pointed by \c n.
 *
 * \return New root of right rotated tree.
 * \param n Pointer to root of tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
static node rotate_tree_right(node n);

/** \fn node rotate_tree_left(node n);
 * \brief Proceed left rotation to tree pointed by \c n.
 *
 * \return New root of left rotated tree.
 * \param n Pointer to root of tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
static node rotate_tree_left(node n);

/** \fn node equi_left(node n);
 * \brief Balance left tree.
 *
 * \return New root of left-balanced tree.
 * \param n Pointer to root of tree.
 *
 * This function make rotation and update height if necessary.
 *
 * \warning If you use this function you probably make a mistake.
 */
static node equi_left(node n);

/** \fn node equi_left(node n);
 * \brief Balance left tree.
 *
 * \return New root of left-balanced tree.
 * \param n Pointer to root of tree.
 *
 * This function make rotation and update height if necessary.
 *
 * \warning If you use this function you probably make a mistake.
 */
static node equi_left(node n);

/** \fn node equi_right(node n);
 * \brief Balance right tree.
 *
 * \return New root of right-balanced tree.
 * \param n Pointer to root of tree.
 *
 * This function make rotation and update height if necessary.
 *
 * \warning If you use this function you probably make a mistake.
 */
static node equi_right(node n);

/** \fn int delete_node_min_recur(node *n, void (*data_delete) (void *));
 * \brief Recursive deletion of minimum element.
 *
 * \return True if element is deleted, false if not.
 * \param n Root of tree where minimum element must be deleted.
 * \param data_delete Fonction to delete a node in tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
static int delete_node_min_recur(node *n, void (*data_delete) (void *));

/** \fn node delete_node_recur(node *root, void *data,
 *                             int (*data_cmp) (void *, void *),
 *                             void (*data_delete) (void *));
 * \brief Recursive deletion of the a node.
 *
 * \param root Pointer of pointer to subtree.
 * \param data Data to delete. Only field used in \c avl_data_cmp
 * must be filled.
 * \param data_cmp Function use to compare node.
 * \param data_delete Function use to delete node.
 * \return True if node is deleted, false else.
 *
 * \warning If you use this function you probably make a mistake.
 */
static int delete_node_recur(node *root, void *data,
                             int (*data_cmp) (void *, void *),
                             void (*data_delete) (void *));

/** \fn int insert_elmt_recur(node *n, node add_node,
 *                            int (*data_cmp) (void *, void *),
 *                            void (*data_delete) (void *));
 * \brief Recursive function too add element in tree.
 *
 * \return Number of element inserted.
 * \param n Root of tree where element must be inserted.
 * \param add_node Element to be added in tree.
 * \param data_cmp Function to compare nodes.
 * \param data_delete Function to delete a node.
 *
 * \warning If you use this function you probably make a mistake.
 */
static int insert_elmt_recur(node *n,
                             node add_node,
                             int (*data_cmp) (void *, void *),
                             void (*data_delete) (void *));

/** \fn void delete_tree_recur(node n, void (*data_delete) (void *));
 * \brief Recursively delete all node in tree.
 *
 * \param n Root node of tree to delete.
 * \param data_delete Function use to delete a node.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void delete_tree_recur(node n, void (*data_delete) (void *));

/** \fn void print_tree_recur(node t, void (*data_print) (void *));
 * \brief Recursive function to print tree. Use for debug.
 *
 * \param t Pointer to root of tree.
 * \param data_print Function to display a node.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void print_tree_recur(node t, void (*data_print) (void *));

/** \fn void explore_tree_recur(node t, void (*treatement)(void *, void *),
 *                              void *param);
 * \brief Recursive exploration of tree.
 *
 * \param t Pointer to subtree.
 * \param treatement Function apply to each node of tree.
 * \param param Pointer to data to pass to \c treatement function.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void explore_tree_recur(node t, void (*treatement)(void *, void *), void *param);

/** \fn int explore_restrain_tree_recur(node t, int (*check)(void *, void *),
 *                                      void *param, void *data_min,
 *                                      void *data_max,
 *                                      int (*data_cmp) (void *, void *));
 * \brief Recursive and restrain exploration of tree.
 *
 * \return Accumulation of return value of \c check function.
 * \param t Pointer to root of tree.
 * \param check Function apply to each node of tree between \c data_min and
 * \c data_max.
 * \param param Pointer to data to pass to \c check function
 * \param data_min All treated node are greater than \c data_min
 * \param data_max All treated node are smaller than \c data_max
 * \param data_cmp Function to compare nodes.
 *
 * \warning If you use this function you probably make a mistake.
 */
static int explore_restrain_tree_recur(node t,
                                       int (*check)(void *, void *),
                                       void *param,
                                       void *data_min, void *data_max,
                                       int (*data_cmp) (void *, void *));

/** \fn int get_data_recur(node n, void *data, size_t data_size,
 *                         int (*data_cmp) (void *, void *))
 * \brief Recursively get of a single data.
 *
 * \param n Root of tree to analyze.
 * \param data Pointer to the asked data. At the begining of the function,
 * only field used in \c avl_data_cmp must be filled, at the end (and if
 * data exist in tree), all filled will be filled.
 * \param data_size Size of the data structure (need to copy data).
 * \param data_cmp Function to compare nodes.
 * \return 1 if data was found, 0 if not.
 *
 * \warning If you use this function, you probably make a mistake.
 */
static int get_data_recur(node n, void *data, size_t data_size, int (*data_cmp) (void *, void *));

/** \fn void verif_avl(node n, int tree_min, int tree_max,
 *                      void *data_min, void *data_max,
 *                      int (*data_cmp) (void *, void *));
 * \brief Recursive deffensive function to check if tree is an AVL tree.
 *
 * \param n Pointer to root of tree.
 * \param tree_min Boolean must be true if \c tree is the minimum node.
 * \param tree_max Boolean must be true if \c tree is the maximum node.
 * \param data_min Pointer to the minimum element of sub-tree.
 * \param data_max Pointer to the maximum element of sub-tree.
 * \param data_cmp Fonction to compare nodes.
 *
 * \warning If you use this function you probably make a mistake.
 */
static void verif_avl(node n,
                      int tree_min,
                      int tree_max,
                      void *data_min,
                      void *data_max,
                      int (*data_cmp) (void *, void *));

/* ************************************************************************* *\
   |*                         STUB FUNCTIONS                                    *|
   \* ************************************************************************* */

/** \fn int stub__data_cmp(void *a, void *b)
 * \brief Stub function used if no data_cmp functio is provided.
 *
 * \param a First node to compare.
 * \param b Second node to compare.
 * \return Difference of pointer nodes.
 *
 * \warning This function is just a stub and shall never be used
 * in your production project.
 */
int stub__data_cmp(void *a, void *b)
{
    return (int) ((ptrdiff_t) a - (ptrdiff_t) b);
}

/** \fn void stub__data_print(void *d)
 * \brief Stub function used if no data_print function is provided.
 *
 * \param d Data to print.
 *
 * Print to \c stdout the pointer of data.
 *
 * \warning This function is just a stub and shall never be used
 * in your production project.
 */
void stub__data_print(void *d)
{
    printf("0x%p", d);
}

/** \fn void stub__data_delete(void *d)
 * \brief Stub function used if no data_delete function is provided.
 *
 * \param d Data to delete.
 *
 * This fonction call \c free on \c d.
 *
 * \warning This function is just a stub. If your data is more
 * complicated than a single static structure, you must provide
 * your \c data_delete implementation. If not your program will
 * cause memory leaks on tree deletion.
 */
void stub__data_delete(void *d)
{
    free(d);
}

/** \fn void stub__data_copy(void *src, void *dst, size_t len)
 * \brief Stub function used if no data_copy function is provided.
 *
 * \param src Data source
 * \param dst Data destination
 * \param len Size of data to copy
 *
 * This function call \c memcpy to copy \c src into \c dst.
 *
 * \warning This function is just a stub. If your data is more complicated
 * than a single static structure, you must provide your \c data_copy
 * implementation.
 */
void stub__data_copy(void *src, void *dst, size_t len)
{
    memcpy(dst, src, len);
}

/* ************************************************************************* *\
   |*                      EXTERNAL FUNCTION                                    *|
   \* ************************************************************************* */

tree *init_dictionnary(int (*data_cmp)(void *, void *),
                       void (*data_print)(void *),
                       void (*data_delete)(void *),
                       void (*data_copy)(void *, void *, size_t len))
{
    // New tree allocation
    tree *t = malloc(sizeof(tree));

    // Initialized field
    t->count = 0;
    t->root = NULL;
    t->data_cmp = data_cmp ? data_cmp : stub__data_cmp;
    t->data_print = data_print ? data_print : stub__data_print;
    t->data_delete = data_delete ? data_delete : stub__data_delete;
    t->data_copy = data_copy ? data_copy : stub__data_copy;

    return t;
}

unsigned int insert_elmt(tree *t, void *data, size_t datasize)
{
    node to_add;
    int present = 0;

    // Allocate memory for the new data and copy data.
    to_add = malloc(sizeof(struct _node));
    to_add->data = malloc(datasize);
    t->data_copy(data, to_add->data, datasize);
    to_add->height = 0;
    to_add->left = to_add->right = NULL;

    // recursively insert data in tree.
    present = insert_elmt_recur(&(t->root), to_add, t->data_cmp, t->data_delete);

    // increment counter of element if so.
    if (!present) {
        DLOG("New data was added.");
        return ++t->count;
    } else {
        DLOG("Data was updated.");
        return t->count;
    }
}

void verif_tree(tree *t)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively check of avl tree.
    verif_avl(t->root, 0, 0, t->root->data, t->root->data, t->data_cmp);
}

void delete_tree(tree *t)
{
    if (t == NULL)
        return;

    delete_tree_recur(t->root, t->data_delete);
    free(t);
}

void print_tree(tree *t)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively print the tree.
    print_tree_recur(t->root, t->data_print);
}

void explore_tree(tree *t, void (*treatement)(void *, void *), void *param)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively explore the whole tree.
    explore_tree_recur(t->root, treatement, param);
}

int explore_restrain_tree(tree *t, int (*check)(void *, void *), void *param,
                          void *data_min, void *data_max)
{
    if (t == NULL)
        return 0;
    if (t->root == NULL)
        return 0;

    // recursively explore part of tree.
    return explore_restrain_tree_recur(t->root, check, param,
                                       data_min, data_max,
                                       t->data_cmp);
}

int is_present(tree *t, void *d)
{
    if (t == NULL)
        return 0;

    // Return result of a recursive exploration
    return is_present_recur(t->root, d, t->data_cmp);
}

void delete_node_min(tree *t)
{
    if (t == NULL || t->root == NULL)
        return;

    // go recursively in tree to delete minimum node
    if (delete_node_min_recur(&(t->root), t->data_delete))
        t->count--;
}

void delete_node(tree *t, void *data)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;
    // explore tree recursively to delete node
    if (delete_node_recur(&(t->root), data, t->data_cmp, t->data_delete))
        t->count--;
}

int get_data(tree *t, void *data, size_t data_size)
{
    if (t == NULL)
        return 0;
    if (t->root == NULL)
        return 0;

    return get_data_recur(t->root, data, data_size, t->data_cmp);
}

// ========================================================
// Internal API implementation
// ========================================================
static int is_present_recur(node n, void *d, int (*data_cmp) (void *, void *))
{
    int cmp = 0;

    // Prevent analyze of a Null node
    if (n == NULL)
        return 0;

    // Compare data
    cmp = data_cmp(n->data, d);

    if (cmp == 0)
        // Node found, return true
        return 1;
    else if (cmp > 0)
        // Current node is higher than data to look for,
        // need to go to left subtree.
        return is_present_recur(n->left, d, data_cmp);
    else
        // Current node is smaller than data to look for,
        // need to go to right subtree.
        return is_present_recur(n->right, d, data_cmp);
}

/** Use for debug only. Print recursive level of inserted element */
#if LOGLEVEL > 3
static int level_insert = 0;
#endif

static unsigned int height_tree(node n)
{
    if (n == NULL)
        return 0;

    return n->height;
}

static void adjust_tree_height(node n)
{
    unsigned int h1;
    unsigned int h2;

    h1 = height_tree(n->left);
    h2 = height_tree(n->right);

    if (h1 > h2)
        n->height = h1 + 1;
    else
        n->height = h2 + 1;
}

static node rotate_tree_right(node n)
{
    node temp = n->left;
    n->left = temp->right;
    adjust_tree_height(n);
    temp->right = n;
    adjust_tree_height(temp);
    return temp;
}

static node rotate_tree_left(node n)
{
    node temp = n->right;
    n->right = temp->left;
    adjust_tree_height(n);
    temp->left = n;
    adjust_tree_height(temp);
    return temp;
}

static node equi_left(node n)
{
    node son = n->left;

    DLOG("height tree: tree(%d) | left (%d) | right (%d) | son (%d)",
         height_tree(n),
         height_tree(n->left),
         height_tree(n->right),
         height_tree(son));
    if (height_tree(son) > height_tree(n->right) + 1) {
        if (height_tree(son->right) > height_tree(son->left)) {
            DLOG("Need rotate left");
            n->left = rotate_tree_left(n->left);
        }
        DLOG("Need rotate right");
        n = rotate_tree_right(n);
    } else {
        DLOG("No rotate");
        adjust_tree_height(n);
    }
    return n;
}

static node equi_right(node n)
{
    node son = n->right;

    if (height_tree(son) > height_tree(n->left) + 1) {
        if (height_tree(son->left) > height_tree(son->right))
            n->right = rotate_tree_right(n->right);
        n = rotate_tree_left(n);
    } else {
        adjust_tree_height(n);
    }
    return n;
}

static int delete_node_min_recur(node *n, void (*data_delete) (void *))
{
    int result;

    if (*n == NULL)
        return 0;

    if ((*n)->left == NULL) {
        node aux = *n;
        // No node in left subtree, this means that the current node
        // is the minimum node stored in tree.
        *n = aux->right;
        data_delete(aux->data);
        free(aux);
        return 1;
    } else {
        // not the minimum, go deep
        result = delete_node_min_recur(&((*n)->left), data_delete);
        // balance resulting tree
        *n = equi_right(*n);
    }

    return result;
}

static int delete_node_recur(node *root, void *data,
                             int (*data_cmp) (void *, void *),
                             void (*data_delete) (void *))
{
    int cmp = 0;
    int result = 0;

    if (*root == NULL) {
        WLOG("Node does not exist");
        return 0;
    }

    cmp = data_cmp(data, (*root)->data);
    if (cmp == 0) {
        // Current node is the node to delete.
        if ((*root)->right == NULL) {
            node aux = *root;
            // simple deletion because there is no right subtree.
            // attach the left subtree instead of the deleted node
            *root = (*root)->left;

            // release memory used in node.
            data_delete(aux->data);
            free(aux);
        } else {
            // There is a right subtree.
            // swap minimun element of right subtree and
            // the deleted data, efectively delete data
            // and re balance right subtree.
            void *d;
            node temp = (*root)->right;

            // look for the minimum element of right subtree.
            while (temp->left != NULL)
                temp = temp->left;

            // swap data
            d = (*root)->data;
            (*root)->data = temp->data;
            temp->data = d;

            // delete minimum node.
            delete_node_min_recur(&((*root)->right), data_delete);
            // rebalance subtree.
            *root = equi_left(*root);
        }
        return 1;
    } else if (cmp > 0) {
        // current node is smaller than node to delete
        // go down into right subtree.
        result = delete_node_recur(&((*root)->right), data, data_cmp, data_delete);
        // rebalance subtree.
        *root = equi_left(*root);
    } else {
        // current node is higher than node to delete
        // go down into left subtree.
        result = delete_node_recur(&((*root)->left), data, data_cmp, data_delete);
        // rebalance subtree.
        *root = equi_right(*root);
    }

    return result;
}

static int insert_elmt_recur(node *n, node add_node,
                             int (*data_cmp) (void *, void *),
                             void (*data_delete) (void *))
{
    int present = 0; // 1 means that data already present
    int cmp;

    // Here is the end of a tree. It must create new node here
    DLOG("Insert %p at level %d", add_node, level_insert);
    if (*n == NULL) {
        (*n) = add_node;
        (*n)->height = 1;
        (*n)->left = NULL;
        (*n)->right = NULL;

        return 0;
    }

    cmp = data_cmp((*n)->data, add_node->data);

    // Check if current node is the node you want to add
    if (cmp == 0) {
        // node already exist, update it.
        node old_n = *n;
        (*n) = add_node;
        (*n)->height = old_n->height;
        (*n)->left = old_n->left;
        (*n)->right = old_n->right;
        data_delete(old_n->data);
        free(old_n);

        return 1;
    }

    if (cmp > 0) {
        // Current node is higher that node you want to add
        // Insert it on left subtree.
        DLOG("Down into left level %d", ++level_insert);
        present = insert_elmt_recur(&(*n)->left, add_node, data_cmp, data_delete);
        DLOG("Out of level %d", level_insert--);

        if (!present) {
            // node was really inserted, need to re-balance tree
            *n = equi_left(*n);
            return 0;
        } else
            // node not inserted in subtree
            return 1;
    } else {
        // Current node is smaller that node you want to add
        // Insert it on right subtree.
        DLOG("Down into right level %d", ++level_insert);
        present = insert_elmt_recur(&(*n)->right, add_node, data_cmp, data_delete);
        DLOG("Out of level %d", level_insert--);

        if (!present) {
            // node was really inserted, need to re-balance tree
            *n = equi_right(*n);
            return 0;
        } else
            // node not inserted in subtree
            return 1;
    }

}

static void delete_tree_recur(node n, void (*data_delete) (void *))
{
    if (n == NULL)
        return;

    if (n->left != NULL)
        delete_tree_recur(n->left, data_delete);
    if (n->right != NULL)
        delete_tree_recur(n->right, data_delete);

    data_delete(n->data);
    free(n);
}

static void print_tree_recur(node t, void (*data_print) (void *))
{
    if (t == NULL)
        return;

    // recursively print left subtree.
    print_tree_recur(t->left, data_print);
    {
        // print current node with debug information.
        unsigned i = 0;
        for (i = 0; i < t->height; i++)
            printf("            ");
        printf("[%u|%p]", t->height, t);
        data_print(t->data);
        printf("\n");
    }
    // recursively print right subtree.
    print_tree_recur(t->right, data_print);
}

static void explore_tree_recur(node t, void (*treatement)(void *, void *),
                               void *param)
{
    if (t == NULL)
        return;

    // recursively treat left subtree.
    explore_tree_recur(t->left, treatement, param);
    // treat current node.
    treatement(t->data, param);
    // recursively treat right subtree.
    explore_tree_recur(t->right, treatement, param);
}

static int explore_restrain_tree_recur(node t,
                                       int (*check)(void *, void *),
                                       void *param,
                                       void *data_min, void *data_max,
                                       int (*data_cmp) (void *, void *))
{
    if (t == NULL)
        return 0;

    if (data_cmp(t->data, data_max) > 0)
        // current data is not in the asked range.
        return explore_restrain_tree_recur(t->left, check, param,
                                           data_min, data_max,
                                           data_cmp);
    else if (data_cmp(t->data, data_min) < 0)
        // current data is not in the asked range.
        return explore_restrain_tree_recur(t->right, check, param,
                                           data_min, data_max,
                                           data_cmp);
    else {
        // current data is in the range.
        int accu = 0;
        // treat recursively left subtree.
        accu += explore_restrain_tree_recur(t->left, check, param,
                                            data_min, data_max,
                                            data_cmp);
        // treat current node.
        accu += check(t->data, param);
        // treat recursively right subtree.
        accu += explore_restrain_tree_recur(t->right, check, param,
                                            data_min, data_max,
                                            data_cmp);
        return accu;
    }
}

static int get_data_recur(node n, void *data, size_t data_size,
                          int (*data_cmp) (void *, void *))
{
    int cmp = 0;

    if (n == NULL)
        return 0;

    cmp = data_cmp(n->data, data);
    if (cmp == 0) {
        // Current node is the good node, copy it.
        memcpy(data, n->data, data_size);
        return 1;
    } else if (cmp > 0) {
        // Need to go deep in the left subtree.
        return get_data_recur(n->left, data, data_size, data_cmp);
    } else {
        // Need to go deep in the right subtree.
        return get_data_recur(n->right, data, data_size, data_cmp);
    }

}

static void verif_avl(node n,
                      int tree_min,
                      int tree_max,
                      void *data_min,
                      void *data_max,
                      int (*data_cmp) (void *, void *))
{
    unsigned hg;
    unsigned hd;

    // Check order of data.
    assert(!tree_min || data_cmp(n->data, data_min) >= 0);
    assert(!tree_max || data_cmp(n->data, data_max) <= 0);

    // Check avl left subtree.
    if (n->left != NULL) {
        verif_avl(n->left,
                  tree_min,
                  1,
                  data_min,
                  n->data,
                  data_cmp);
        hg = n->left->height;
    } else {
        hg = 0;
    }

    // Check avl right subtree.
    if (n->right != NULL) {
        verif_avl(n->right,
                  1,
                  tree_max,
                  n->data,
                  data_max,
                  data_cmp);
        hd = n->right->height;
    } else {
        hd = 0;
    }

    // Check height consistency of each subtree
    if (hg <= hd) {
        assert(hd + 1 == n->height && hg + 2 >= n->height);
    } else {
        assert(hg + 1 == n->height && hg + 2 >= n->height);
    }
}

