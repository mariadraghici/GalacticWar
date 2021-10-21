/*Copyright [2021] <Maria Draghici>*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"

static void
error(int a) {
    if (a == 1)
		printf("Not a valid n\n");
	if(a == 2)
		printf("List non-existent\n");
	if (a == 3)
		printf("Malloc failed\n");
}
/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* list;
    list =  calloc(1, sizeof(doubly_linked_list_t));

    if (list == NULL) {
        error(3);
        return NULL;
                    }
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;
    return list;
}
/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	dll_node_t *p = list->head;

	if (n < 0) {
        error(1);
        return NULL;
                }

    if (n >= list->size)
        n = n % list->size;
    while (n) {
        p = p->next;
        n--;
            }
    return p;
}
/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    dll_node_t *new_node = malloc(sizeof(dll_node_t));

    if (new_node == NULL) {
        error(3);
        return;
                    }

    dll_node_t *p = list->head;

    if (list == NULL) {
        error(2);
        return;
                    }

    if (n < 0) {
        error(1);
        return;
                }

    new_node->data = malloc(list->data_size);

    if (new_node->data == NULL) {
        error(3);
        return;
                    }

    memcpy(new_node->data, data, list->data_size);
    if (n >= list->size)
    {
        if (list->size == 0)
        {
            list->head = new_node;
        } else {
            n = list->size - 1;
            while (n) {
                p = p->next;
                n--;
                    }
            p->next = new_node;
            new_node->prev = p;
            new_node->next = list->head;
            list->head->prev = new_node;
                }
    } else {
        if (n == 0) {
            new_node->prev = list->head->prev;
            new_node->next = list->head;
            list->head->prev->next = new_node;
            list->head->prev = new_node;
            list->head = new_node;
                    } else {
                        n--;
                        while (n) {
                            p = p->next;
                            n--;
                                    }
                            new_node->next = p->next;
                            p->next = new_node;
                            p->next->prev = new_node;
                            new_node->prev = p;
                            }
            }
    list->size++;
}
/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (!list || !list->head) {
        error(2);
        return NULL;
                            }

    dll_node_t *p = list->head, *deleted_node = NULL;

    if (n < 0) {
        error(1);
        return NULL;
                }

    if (n == 0)
    {
        deleted_node = list->head;
        list->head->next->prev = list->head->prev;
        list->head->prev->next = list->head->next;
        list->head = list->head->next;
    } else if (n >= list->size - 1) {
            n = list->size - 2;
            while (n) {
                p = p->next;
                n--;
                        }
            deleted_node = p->next;
            p->next = list->head;
            list->head->prev = p;
                                    } else {
                                        n--;
                                        while (n) {
                                            p = p->next;
                                            n--;
                                                }
                                        deleted_node = p->next;
                                        p->next->next->prev = p;
                                        p->next = p->next->next;
                                            }
	list->size--;
	return deleted_node;
}
/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    if (!list) {
        error(2);
        return -1;
                            }
    return list->size;
}
/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    unsigned int i;
    dll_node_t *p = (*pp_list)->head, *tmp;
    for (i = 0; i < (*pp_list)->size; i++) {
        tmp = p;
        p = p->next;
        free(tmp->data);
        free(tmp);
                                        }
    free(*pp_list);
    pp_list = NULL;
}
/*
 * Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    unsigned int i;
    dll_node_t *p = list->head;

    for (i = 0; i < list->size; i++) {
    	printf("%d ", (*(int *)(p->data)));
    	p = p->next;
    }
    printf("\n");
}
/*
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate 
 * printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	unsigned int i;
    dll_node_t *p = list->head;

    for (i = 0; i < list->size; i++) {
        printf("%s ", (char *)p->data);
    	p = p->next;
    }
    printf("\n");
}
