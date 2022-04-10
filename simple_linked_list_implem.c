#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_STRING_SIZE 64

typedef struct ll_node_t
{
    void* data;
    struct ll_node_t* next;
} ll_node_t;

typedef struct linked_list_t
{
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
} linked_list_t;

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t *my_list = malloc(sizeof(*my_list));
    if (!my_list) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    }
    my_list->head = NULL;
    my_list->data_size = data_size;
    my_list->size = 0;
    return my_list;
}


void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    int nodes_no = list->size;

    if (!list)
        return;

    if (n >= nodes_no) {

        //I allocated space in memory to make a node

        ll_node_t *node_to_add = malloc(sizeof(*node_to_add));
        if (!node_to_add) {
            fprintf(stderr, "Malloc failed\n");
            return;
        }
        node_to_add->data = malloc(list->data_size);
        if (!(node_to_add->data)) {
            fprintf(stderr, "Malloc failed\n");
            return;
        }

        //Copy the value of new_data depending of data size
        //and send the next pointer to the NULL cause it's the last

        memcpy(node_to_add->data, new_data, list->data_size);
        node_to_add->next = NULL;
        
        //pointer to what head points and going until NULL
        //to append the node_to_add

        ll_node_t *ptr_current = list->head;
        /*I think that if the ptr_current is null the list is empty
        and while in that case will do that Null pointer goes on next with an
        address*/
        if (!(ptr_current)) {
            list->head = node_to_add;
            list->size++;
            return;
        }
        while ((ptr_current->next) != NULL)
            ptr_current = ptr_current->next;
        ptr_current->next = node_to_add;
        list->size++;
        return;

    }

    if (n < nodes_no) {

        //allocate the memory for a new node

        ll_node_t *new = malloc(sizeof(*new));
        if (!new) {
            fprintf(stderr, "Malloc failed\n");
            return;
        }
        new->data = malloc(list->data_size);
        if (!(new->data)) {
            fprintf(stderr, "Malloc failed\n");
            return;
        }

        //Copy the value of new_data

        memcpy(new->data, new_data, list->data_size);

        //initialise two pointers
        
        ll_node_t *prev, *next_n;
        prev = NULL;
        next_n = list->head;
        while (n > 0) {
            prev = next_n;
            next_n = next_n->next;
            --n;
        }

        //if prev is NULL, we want the pos 0, so list->head to new and new->next to next_n

        if (!prev) {
            list->head = new;
            new->next = next_n;
            list->size++;
            return;
        }

        prev->next = new;
        new->next = next_n;
        list->size++;
        return;
    }
}


ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{

    if (!list)
        return NULL;
     /*NU are sens comparatia cu zero deoarece este de tip unsigned n-ul*/
    int condition = list->size - 1;

    if (n >= condition) {

        ll_node_t *prev, *next;
        prev = NULL;
        next = list->head;

        while ((next->next) != NULL) {
            prev = next;
            next = next->next;
        }

        if (!prev) {
            list->head = NULL;
            (list->size)--;
            return next;
        }

        prev->next = NULL;
        (list->size)--;
        return next;

    }

    if (n < condition) {

        ll_node_t *prev, *next;
        prev = NULL;
        next = list->head;

        while(n > 0) {
            prev = next;
            next = next->next;
            n--;
        }

        if (!prev) {
            list->head = next->next;
            (list->size)--;
            return next;
        }

        prev->next = next->next;
        (list->size)--;
        return next;

    }

}


unsigned int
ll_get_size(linked_list_t* list)
{
    unsigned int a = list->size;
    return a;
}


void
ll_free(linked_list_t** pp_list)
{

    ll_node_t *ptr_current = (*pp_list)->head;

    for (int i = 0;  i < (*pp_list)->size; ++i) {
        free(ptr_current->data);
        ll_node_t *del_that = ptr_current;
        ptr_current = ptr_current->next;
        free(del_that);
    }

    free((*pp_list));

}

void
ll_print_int(linked_list_t* list)
{
    // int *p = (int *) list->head->data;
    // printf("%d", (*p));
    ll_node_t *ptr_current = list->head;
    int *ptr_for_display;

    for(int i = 0; i < (list->size); ++i) {
        ptr_for_display = (int *) ptr_current->data;
         printf("%d ", (*ptr_for_display));
         ptr_current = ptr_current->next;
    }

    printf("\n");
}

void
ll_print_string(linked_list_t* list)
{
    ll_node_t *ptr_current = list->head;
    char *ptr_for_display;

    for (int i = 0; i < (list->size); ++i) {
        ptr_for_display = (char *) ptr_current->data;
        printf("%s ", ptr_for_display);
        ptr_current = ptr_current->next;
    }

    printf("\n");
}

int main()
{
    linked_list_t* linkedList;
    int is_int = 0;
    int is_string = 0;

    while (1) {
        char command[16], added_elem[64], *end_ptr;
        long nr, pos;

        scanf("%s", command);

        if (strcmp(command, "create_str") == 0) {
            linkedList = ll_create(MAX_STRING_SIZE);
            is_string = 1;
            //printf("%u", linkedList->data_size);
        }

        if (strcmp(command, "create_int") == 0) {
            linkedList = ll_create(sizeof(int));
            is_int = 1;
            //printf("%u", linkedList->data_size);
        }

        if (strcmp(command, "add") == 0) {
            scanf("%ld", &pos);
            scanf("%s", added_elem);

            nr = strtol(added_elem, &end_ptr, 10);
            if (nr != 0) {
                ll_add_nth_node(linkedList, pos, &nr);
            } else {
                ll_add_nth_node(linkedList, pos, end_ptr);
            }
        }

        if (strcmp(command, "remove") == 0) {
            scanf("%ld", &pos);
            ll_node_t *removed = ll_remove_nth_node(linkedList, pos);
            free(removed->data);
            free(removed);
        }

        if (strcmp(command, "print") == 0) {
            if (is_int == 1) {
                ll_print_int(linkedList);
            }

            if (is_string == 1) {
                ll_print_string(linkedList);
            }
        }

        if (strcmp(command, "free") == 0) {
            ll_free(&linkedList);
            break;
        }
    }

    return 0;
}