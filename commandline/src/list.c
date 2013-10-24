#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "emalloc.h"

#include "list.h"

struct list_node_impl_t
{
    struct list_node_impl_t *next;
    void* data;
};

struct list_impl_t
{
    struct list_node_impl_t *head;
    comparator        comp_func; // die Funktion zum vergleichen
    printer           printer_func; // die Funktion zum ausgeben
    disposer          dispose_func; // die Funktion zum löschen
    int               freed;
};

list_t list_new(comparator comp_func, printer printer_func,
                disposer dispose_func)
{
    list_t new_list; /* erstellen einer neuen liste */

    new_list               = (list_t)emalloc(sizeof(*new_list)); /* sie mit der größe initialisieren*/
    new_list->head         = NULL; /* es gibt am Anfang keine Liste*/

    new_list->comp_func    = comp_func; // wir speichern uns die comperator funktion
    new_list->printer_func = printer_func; // wir speichern uns die printer funktion
    new_list->dispose_func = dispose_func; // wir speichern uns die dispose funktion
    new_list->freed = 0;
    return new_list; /* wir geben die neue liste wieder */

}

/* Prepends a node with @data to the list. */
void list_prepend(list_t list,void *data)
{
    if( list != NULL)
    {
        list_node_t new_node = (list_node_t)emalloc(sizeof(*new_node)); /* erstellen eines neun Knoten*/

        new_node->next = list->head; /* damit wir es vor dem anfang erstellen setzen wir den aktuellen Kopf hinter das neue Element*/
        new_node->data = data; /* fügen den Inhalt in den neuen Knoten*/

        list->head = new_node; /* setzen den Kopf auf das neue element*/
    }
}

/* Appends a node with @data to the list. */
void list_append(list_t list,void* data)
{
    if( list != NULL)
    {
        list_node_t it = list->head; /* Wir werden zum ende laufen dafür müssen wir am Kopf starten*/
        list_node_t new_node = (list_node_t)emalloc(sizeof(*new_node)); /* ersellen den Speicher für das neue element*/
        new_node->next = NULL; /* wir initialiseiern das neue element*/
        new_node->data = data;
        if( it == NULL)
        {
            list->head = new_node;
        }
        else
        {
            while(it->next != NULL) /* solange noch nachfolger existieren laufen wir weiter drüber*/
                it = it->next;
            it->next = new_node; /* und fügen es am ende ein*/
        }
    }
}

/* Removes the first node, starting from the list head, with @data.
 * Returns 1, if found otherwise 0. */
int list_remove(list_t list,void* data)      /* OPTIONAL */
{
    if( list != NULL)
    {
        list_node_t it = list->head; /* zeigt auf das aktuelle element*/
        list_node_t jt = list->head; /* zeigt auf das element vor dem aktuellen*/
        for( ; it != NULL; jt = it, it = it->next) /* wir laufen über alle elmente drüber*/
        {
            if( list->comp_func(it->data, data)) /* wenn wir das zu löschende Element gefunden haben*/
            {
                if( it == list->head) /* und it auf den Kopf zeigt*/
                    list->head = it->next; /* müssen wir den nachfolger zum kopf machen*/
                else
                    jt->next = it->next; /* sonst müssen wir vom Vorgänger den nachfolger auf den nachfolger des gefundenen zeigen lassen*/
                list->dispose_func(it->data);// dann noch das element frei geben und
                free(it);
                return 1; /* 1 zurück geben*/
            }
        }
    }
    return 0; /* wenn das zu löschende nicht gefunden wurde einfach 0 zurück geben*/
}

/* Returns a node with @data, if found, otherwise NULL. */
list_node_t list_find(list_t list,void *data)
{
    if( list != NULL)
    {
        /* wir gehen über die liste vom Kopf her*/
        list_node_t it = list->head;
        for( ; it != NULL; it = it->next)
        {
            if( list->comp_func(it->data, data)) /* Wenn wir die gesuchte data variable gefunden haben,*/
                return it; /* geben wir sie zurück*/
        }
    }
    return NULL; /* ansonsten geben wir NULL wieder*/
}

/* Returns data saved in a @node. */
void* node_get_data(list_node_t node)
{
    if( node != NULL)
        return node->data; /* extrahieren der data von einem node und zurück geben*/
    return NULL;
}

/* Frees all list data items using a disposer,
 * then frees the list itself. */
void list_dispose(list_t list)
{
    if( list != NULL && !list->freed)
    {
        list_node_t it = list->head;
        list_node_t temp;
        for( ; it != NULL; it = temp) /* Zum löschen laufen wir über die liste*/
        {
            temp = it->next; /* merken uns den nachfolger temporär*/
            if( list->dispose_func != NULL)
                list->dispose_func(it->data); /* löschen den inhalt*/
            free(it); /* und das aktuelle element*/
        }
        list->dispose_func = NULL;
        list->head = NULL;
        list->freed = 1;
        free(list); /* zum schluss machen wir noch die liste platt.*/
        list = NULL;
    }
}

/*
* Returns the head of the list
*/
list_node_t list_head(list_t list)
{
    if( list != NULL)
        return list->head;
    return NULL;
}

/*
* Returns the next node after @node or NULL
*/
list_node_t node_next(list_node_t node)
{
    if( node != NULL)
        return node->next;
    return NULL;
}

/*
 * Returns the length of a list
*/
int list_length(list_t list)
{
    int leng = 0;

    list_node_t it = list->head;
    while(it != NULL)
    {
        it = it->next;
        leng++;
    }

    return leng;
}

/*
* Returns 0 if head of list is not NULL
*/
int list_empty(list_t list)
{
    if( node_get_data(list->head) == NULL)
        return 1;
    return 0;
}

/* Prints the list using a printer for each data item. */
void list_print(list_t list)
{
    if( list != NULL)
    {
        list_node_t it;
        for( it = list->head; it != NULL; it = it->next) /* für jedes Element in der Liste rufen wir die print funktion auf*/
        {
            if( it != NULL && it->data != NULL)
                list->printer_func(it->data);
        }
        list->printer_func(NULL);
    }
}

void list_sort(list_t list)
{

    list_node_t start = list->head;
    list_node_t help;
    if( list->comp_func == NULL || list == NULL)
        return ;
    for( ; start != NULL; start = start->next)
    {
        for( help = start->next; help != NULL; help = help->next)
        {
            if( list->comp_func(start->data, help->data) > 0)
            {
                void* temp = start->data;
                start->data = help->data;
                help->data = temp;
            }
        }
    }
}

void list_insert_sort(list_t list, void* data)
{
    if( list == NULL)
        return ;
    if( list->comp_func == NULL)
        list_append(list, data);

    list_node_t it = list->head; /* Wir werden zum ende laufen dafür müssen wir am Kopf starten*/
    list_node_t new_node = (list_node_t)emalloc(sizeof(*new_node)); /* ersellen den Speicher für das neue element*/
    new_node->next = NULL; /* wir initialiseiern das neue element*/
    new_node->data = data;
    if( it == NULL)
    {
        list->head = new_node;
    }
    else
    {
        list_node_t temp = it;
        int found = 0;
        for( ; it != NULL; it = it->next)
        {
            if(list->comp_func(it->data, new_node->data) > 0)
            {
                if( it == list->head)
                    list->head = new_node;
                else
                    temp->next = new_node;

                new_node->next = it;
                found = 1;
                break;
            }
            temp = it;
        }

        if( found == 0)
        {
            it->next = new_node;
        }
    }
}

int node_has_next(list_node_t node)
{
    if( node == NULL)
        return 0;
    else if( node->next == NULL)
        return 0;
    return 1;
}
