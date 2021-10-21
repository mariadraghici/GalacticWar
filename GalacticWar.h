/*Copyright [2021] <Maria Draghici>*/
#ifndef GALACTICWAR_H_
#define GALACTICWAR_H_

#define MAX_COMMAND_SIZE 200
#define MAX_WORDS 5

/* Structura nod */
typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data;
    dll_node_t *prev, *next;
};

/* Structura lista */
typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

/* Structura planeta */
typedef struct planet_t planet_t;
struct planet_t
{
	char name[MAX_COMMAND_SIZE];
	doubly_linked_list_t *shield_t;
	int kills;
};

void add_last(dll_node_t *new_planet, unsigned int *value);

void add_planet(doubly_linked_list_t* galaxy);

void blh(doubly_linked_list_t* galaxy, unsigned int index_planet,
	unsigned int ok);

void upgrade_shield(doubly_linked_list_t* galaxy);

void exp_shield(doubly_linked_list_t *galaxy);

void rmv_shield(doubly_linked_list_t *galaxy);

void col(doubly_linked_list_t *galaxy);

void rot(doubly_linked_list_t *galaxy);

void shw(doubly_linked_list_t *galaxy);

void galaxy_free(doubly_linked_list_t **galaxy);
#endif  // GALACTICWAR_H_
