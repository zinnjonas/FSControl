#ifndef LIST_H_
#define LIST_H_

/* Node types. */
typedef struct list_node_impl_t* list_node_t;

/* List types. */
typedef struct list_impl_t* list_t;

typedef void (*disposer)(void*);

typedef int (*comparator)(void*, void*);

typedef void (*printer)(void*);

/* Creates a new empty list.*/
list_t list_new(comparator comp_func, printer printer_func,
                disposer dispose_func);

/* Prepends a node with @data to the list. */
void list_prepend(list_t list,void *data);

/* Appends a node with @data to the list. */
void list_append(list_t list,void *data);

/* Removes the first node, starting from the list head, with @data.
 * Returns 1, if found otherwise 0. */
int list_remove(list_t list,void *data);

/* Returns a node with @data, if found, otherwise NULL. */
list_node_t list_find(list_t list,void *data);

/* Returns the head node of the list. */
list_node_t list_head(list_t list);


/* Returns the next node after the @node or NULL. */
list_node_t node_next(list_node_t node);

/* Returns data saved in a @node. */
void* node_get_data(list_node_t node);

/* Prints the list using a printer for each data item. */
void list_print(list_t list);

/* Frees all list data items using a disposer,
 * then frees the list itself. */
 void list_dispose(list_t list);

 /*
 * Returns the length of a list
*/
int list_length(list_t list);

/*
* Returns 0 if head of list is not NULL
*/
int list_empty(list_t list);

/*
* Sorts the given list
*/
void list_sort(list_t list);

/*
* insert a new data to the list, in sorted order
* list should be sorted
*/
void list_insert_sort( list_t list, void* data);

/*
* returns 1 if there is a next node,
* 0 if there is no next node
*/
int node_has_next(list_node_t node);

#endif // LIST_H_
