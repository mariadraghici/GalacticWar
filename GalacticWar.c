/*Copyright [2021] <Maria Draghici>*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"

#define MAX_COMMAND_SIZE 200
#define MAX_WORDS 5

static void
error(int a) {
	if(a == 1)
		printf("Malloc failed!\n");
	if(a == 2)
		printf("List non-existent!\n");
	if (a == 3)
		printf("Planet out of bounds!\n");
	if (a == 4)
		printf("Shield out of bounds!\n");
}
/*
 * Functie pentru shield-uri, care adauga un shield la
 * finalul listei, avand valoarea value.
 */
void
add_last(dll_node_t *new_planet, unsigned int *value)
{
	dll_node_t *new_shield = NULL;
	new_shield = calloc(1, sizeof(dll_node_t));

	if (!new_shield) {
		error(1);
					}
	dll_node_t *p = NULL;
	p = ((planet_t *)(new_planet->data))->shield_t->head;

	new_shield->data = calloc(1, sizeof(int));
	memcpy(new_shield->data, value, sizeof(int));

	if (((planet_t *)(new_planet->data))->shield_t->size == 0) {
		((planet_t *)(new_planet->data))->shield_t->head = new_shield;
		((planet_t *)(new_planet->data))->shield_t->size++;
		return;
			}
	unsigned int n = ((planet_t *)(new_planet->data))->shield_t->size - 1;
	while (n) {
		p = p->next;
		n--;
			}
	p->next = new_shield;
	new_shield->prev = p;
	new_shield->next = ((planet_t *)(new_planet->data))->shield_t->head;
	((planet_t *)(new_planet->data))->shield_t->head->prev = new_shield;
	((planet_t *)(new_planet->data))->shield_t->size++;
}
/*
 * Functie care adauga o noua planeta in galaxie, pe pozitia index_planet.
 * Daca lista galaxy nu exista, atunci va da eroare; daca indexul dat al 
 * planetei e mai mare ca numarul de planete din galaxie, atunci va afisa
 * eroare. In aceasta functie este apelata si add_last, pentru a crea
 * lista de scuturi a planetei respective.
 */
void
add_planet(doubly_linked_list_t* galaxy)
{
	unsigned int i, value = 1, index_planet, shields_number;
	char name[MAX_COMMAND_SIZE];
	scanf("%s", name);
	scanf("%d", &index_planet);
	scanf("%d", &shields_number);

	if (galaxy == NULL) {
		error(2);
		return;
                    }
    if (index_planet > galaxy->size) {
    	error(3);
    	return;
    }
	dll_node_t *new_planet = NULL;
	new_planet = calloc(1, sizeof(dll_node_t));
	dll_node_t *p = galaxy->head;

	if (!new_planet) {
		error(1);
					}

	new_planet->data = NULL;
	new_planet->data = calloc(1, galaxy->data_size);

	if (!new_planet->data) {
		error(1);
					}

	strcpy(((planet_t *)(new_planet->data))->name, name);
	((planet_t *)(new_planet->data))->shield_t = dll_create(sizeof(int));
	((planet_t *)(new_planet->data))->kills = 0;
	/* Creare lista de scuturi. */
	for (i = 0; i < shields_number; ++i)
		add_last(new_planet, &value);

	/* Tratare caz adaugare prima planeta. */
    if (index_planet == galaxy->size && galaxy->size == 0) {
		galaxy->head = new_planet;
		printf("The planet %s has joined the galaxy.\n",
			((planet_t *)(new_planet->data))->name);
		galaxy->size++;
		return;
												}
	/* Tratare caz adaugare planeta pe prima pozitie
	 * cand e o singura planeta in galaxie .
	 */
	if (index_planet == 0 && galaxy->size == 1) {
		new_planet->next = galaxy->head;
		new_planet->prev = galaxy->head;
		galaxy->head->prev = new_planet;
		galaxy->head = new_planet;
		} else if (index_planet == 0) {
			/* Tratare cazuri cand index-ul noii planete
			 * este 0.
			 */
			new_planet->next = galaxy->head;
			new_planet->prev = galaxy->head->prev;
			galaxy->head->prev->next = new_planet;
			galaxy->head->prev = new_planet;
			galaxy->head = new_planet;
			} else if (index_planet == galaxy->size) {
				/* Tratare caz cand planeta este adaugata pe
			 	 * ultima pozitie.
			 	 */
					index_planet--;
					while (index_planet) {
						p = p->next;
						index_planet--;
						    	}
					p->next = new_planet;
					new_planet->next = galaxy->head;
					new_planet->prev = p;
					galaxy->head->prev = new_planet;
						    		} else {
						    			/* Tratare restul cazurilor. */
						    				index_planet--;
						    				while (index_planet) {
						    					p = p->next;
						    					index_planet--;
						    						}
						    				p->next->prev = new_planet;
						    				new_planet->next = p->next;
						    				p->next = new_planet;
						    				new_planet->prev = p;
											}
	printf("The planet %s has joined the galaxy.\n",
		((planet_t *)(new_planet->data))->name);
	galaxy->size++;
}
/*
 * Functie care elimina planeta din galaxie de la indicele index_planet.
 * Daca galaxia nu exista sau nu contine nici o planeta, atunci va afisa
 * eroare. Parametrul ok reprezinta daca functia este accesata direct
 * ca blh, atunci ok = 1 si se afisaza erorile corespunzatoare; daca ok = 0,
 * atunci functia a fost accesata din alta functie, pentru a elibera memoria.
 */
void
blh(doubly_linked_list_t* galaxy, unsigned int index_planet, unsigned int ok)
{
    if ((!galaxy || !galaxy->head || galaxy->size == 0) && ok == 1) {
        error(3);
        return;
                            }
    if (index_planet > galaxy->size - 1 && ok == 1) {
    	error(3);
    	return;
    }
	dll_node_t *p = galaxy->head, *deleted_planet = NULL;
	doubly_linked_list_t *deleted_shields = NULL;

	/*Tratare caz cand exista o singura planeta */
	if (index_planet == 0 && galaxy->size == 1) {
		deleted_planet = galaxy->head;
		deleted_shields = ((planet_t *)(deleted_planet->data))->shield_t;
		dll_free(&deleted_shields);
		if (ok == 1)
			printf("The planet %s has been eaten by the vortex.\n",
				((planet_t *)(deleted_planet->data))->name);
		free(deleted_planet->data);
		free(deleted_planet);
		galaxy->size--;
		return;
	}
	/* Tratare caz cand index-ul este 0*/
	if (index_planet == 0) {
    	deleted_planet = galaxy->head;
    	galaxy->head->next->prev = galaxy->head->prev;
        galaxy->head->prev->next = galaxy->head->next;
        galaxy->head = galaxy->head->next;
    		} else {
    			/* Tratare restul cazurilor */
				index_planet--;
				while(index_planet) {
					p = p->next;
					index_planet--;
				}
				deleted_planet = p->next;
				p->next->next->prev = p;
				p->next = p->next->next;
			}
	if (ok == 1) {
		printf("The planet %s has been eaten by the vortex.\n",
			((planet_t *)(deleted_planet->data))->name);
					}
	deleted_shields = ((planet_t *)(deleted_planet->data))->shield_t;
	dll_free(&deleted_shields);
	free(deleted_planet->data);
	free(deleted_planet);
	galaxy->size--;
}
/*
 * Functie care atribuie scutului de la index_shield al planetei
 * de la index_planet valoarea upg_value.
 */
void
upgrade_shield(doubly_linked_list_t *galaxy)
{
	unsigned int index_planet, index_shield;
	int upg_value;
	scanf("%d%d%d", &index_planet, &index_shield, &upg_value);

	if (!galaxy || !galaxy->head || galaxy->size == 0) {
        error(3);
        return;
    }

	if (index_planet > galaxy->size - 1) {
		error(3);
		return;
	}

	dll_node_t *planet = galaxy->head;

	while (index_planet) {
		planet = planet->next;
		index_planet--;
	}

	if (index_shield > ((planet_t *)(planet->data))->shield_t->size - 1) {
		error(4);
		return;
	}

	dll_node_t *shield = ((planet_t *)(planet->data))->shield_t->head;
	while (index_shield) {
		shield = shield->next;
		index_shield--;
	}
	int new_shield_data = *((int *)(shield->data)) + upg_value;
	memcpy(shield->data, &new_shield_data, sizeof(int));
}
/*
 * Functie care adauga prin add_last scutul cu valoare value
 * la sfarsitul listei de scuturi a planetei de la index_planet
 */
void
exp_shield(doubly_linked_list_t *galaxy)
{
	unsigned int index_planet, value;

	scanf("%d%d", &index_planet, &value);

	if (!galaxy || !galaxy->head || galaxy->size == 0) {
        error(3);
        return;
    }

	if (index_planet > galaxy->size - 1) {
		error(3);
		return;
	}

	dll_node_t *planet = galaxy->head;

	while (index_planet) {
		planet = planet->next;
		index_planet--;
	}
	add_last(planet, &value);
}
/*
 * Functie care sterge scutul de la index_shield al
 * planetei de la index_planet.
 */
void
rmv_shield(doubly_linked_list_t *galaxy)
{
	unsigned int index_planet, index_shield;

	scanf("%d%d", &index_planet, &index_shield);

	if (!galaxy || !galaxy->head || galaxy->size == 0) {
        error(3);
        return;
    }

	if (index_planet > galaxy->size - 1) {
		error(3);
		return;
	}

	dll_node_t *planet = galaxy->head;

	while (index_planet) {
		planet = planet->next;
		index_planet--;
	}

	if (index_shield > ((planet_t *)(planet->data))->shield_t->size - 1) {
		error(4);
		return;
	}

	if (((planet_t *)(planet->data))->shield_t->size - 1 < 4) {
		printf("A planet cannot have less than 4 shields!\n");
		return;
	}

	dll_node_t *deleted_shield = NULL;
	deleted_shield = dll_remove_nth_node(((planet_t *)(planet->data))->shield_t
		, index_shield);
	free(deleted_shield->data);
	free(deleted_shield);
}
/*
 * Functie care efectueaza coliziunea a doua planete
 * de la indicii index_p1 si index_p2.
 */
void
col(doubly_linked_list_t *galaxy)
{
	unsigned int index_p1, index_p2, index_p1_copy, index_p2_copy;
	unsigned int index_shield_p1, index_shield_p2;

	scanf("%d%d", &index_p1, &index_p2);

	/* Salvez indicii planetelor */
	index_p1_copy = index_p1;
	index_p2_copy = index_p2;

	if (!galaxy || !galaxy->head || galaxy->size == 0) {
        error(3);
        return;
    }

	if (index_p1 > galaxy->size - 1 || index_p2 > galaxy->size - 1) {
		error(3);
		return;
	}

	dll_node_t *planet_1 = galaxy->head;
	dll_node_t *planet_2 = galaxy->head;

	while (index_p1) {
		planet_1 = planet_1->next;
		index_p1--;
	}

	while (index_p2) {
		planet_2 = planet_2->next;
		index_p2--;
	}

	dll_node_t *shield_p1 = ((planet_t *)(planet_1->data))->shield_t->head;
	dll_node_t *shield_p2 = ((planet_t *)(planet_2->data))->shield_t->head;

	/* Gasire scuturi ce vor fi afectate */
	index_shield_p1 = ((planet_t *)(planet_1->data))->shield_t->size / 4;
	index_shield_p2 = ((planet_t *)(planet_2->data))->shield_t->size / 4 * 3;

	while (index_shield_p1) {
		shield_p1 = shield_p1->next;
		index_shield_p1--;
	}

	while (index_shield_p2) {
		shield_p2 = shield_p2->next;
		index_shield_p2--;
	}

	int new_shield_data_p1 = *((int *)(shield_p1->data));
	new_shield_data_p1--;
	memcpy(shield_p1->data, &new_shield_data_p1, sizeof(int));

	int new_shield_data_p2 = *((int *)(shield_p2->data));
	new_shield_data_p2--;
	memcpy(shield_p2->data, &new_shield_data_p2, sizeof(int));

	/* Tratare caz daca ambele planete explodeaza */
	if (new_shield_data_p1 < 0 && new_shield_data_p2 < 0) {
		printf("The planet %s has imploded.\n",
			((planet_t *)(planet_1->data))->name);
		printf("The planet %s has imploded.\n",
			((planet_t *)(planet_2->data))->name);
		blh(galaxy, index_p1_copy, 0);
		index_p2_copy--;
		blh(galaxy, index_p2_copy, 0);
		return;
	}

	/* Tratare caz daca prima planeta explodeaza */
	if (new_shield_data_p1 < 0) {
		printf("The planet %s has imploded.\n",
			((planet_t *)(planet_1->data))->name);
		blh(galaxy, index_p1_copy, 0);
		((planet_t *)(planet_2->data))->kills++;
	}

	/* Tratare caz daca a doua planeta exlpodeaza */
	if (new_shield_data_p2 < 0) {
		printf("The planet %s has imploded.\n",
			((planet_t *)(planet_2->data))->name);
		blh(galaxy, index_p2_copy, 0);
		((planet_t *)(planet_1->data))->kills++;
	}
}
/*
 * Functie care roteste o planeta. Se va modifica doar head-ul listei
 * de scuturi a planetei respective, in functie de sensul in care se
 * roteste planeta.
 */
void
rot(doubly_linked_list_t *galaxy)
{
	unsigned int index_planet, units;
	char direction;
	scanf("%d", &index_planet);
	scanf(" %c", &direction);
	scanf("%d", &units);

	if (index_planet > galaxy->size - 1) {
		error(3);
		return;
	}

	if (direction != 'c' && direction != 't') {
		printf("Not a valid direction!\n");
		return;
	}

	dll_node_t *planet = galaxy->head;

	while (index_planet){
		planet = planet->next;
		index_planet--;
	}

	if (units >= ((planet_t *)(planet->data))->shield_t->size)
		units = units % ((planet_t *)(planet->data))->shield_t->size;

	dll_node_t *shield_head = ((planet_t *)(planet->data))->shield_t->head;

	if (direction == 'c') {
		while (units) {
			shield_head = shield_head->prev;
			((planet_t *)(planet->data))->shield_t->head = shield_head;
			units--;
					}
				} else {
					while (units) {
					shield_head = shield_head->next;
					((planet_t *)(planet->data))->shield_t->head = shield_head;
					units--;
								}
								}
}
/*
 * Functie care afiseaza informatii despre o planeta
 */
void
shw(doubly_linked_list_t *galaxy)
{
	unsigned int index_planet;

	scanf("%d", &index_planet);

	if (!galaxy || !galaxy->head || galaxy->size == 0) {
        error(3);
        return;
    }

	if (index_planet > galaxy->size - 1) {
		error(3);
		return;
								}

	dll_node_t *planet = galaxy->head;

	while (index_planet) {
		planet = planet->next;
		index_planet--;
						}

	/* Tratare caz daca exista o singur planeta */
	if (galaxy->size == 1) {
		printf("NAME: %s\n", ((planet_t *)(planet->data))->name);
		printf("CLOSEST: none\n");
		printf("SHIELDS: ");
		dll_print_int_list(((planet_t *)(planet->data))->shield_t);
		printf("KILLED: %d\n", ((planet_t *)(planet->data))->kills);
		return;
							}

	/* Tratare caz daca exista doar doua planete */
	if (galaxy->size == 2) {
		printf("NAME: %s\n", ((planet_t *)(planet->data))->name);
		printf("CLOSEST: %s\n", ((planet_t *)(planet->prev->data))->name);
		printf("SHIELDS: ");
		dll_print_int_list(((planet_t *)(planet->data))->shield_t);
		printf("KILLED: %d\n", ((planet_t *)(planet->data))->kills);
		return;
	}

	printf("NAME: %s\n", ((planet_t *)(planet->data))->name);
	printf("CLOSEST: %s and %s\n", ((planet_t *)(planet->prev->data))->name,
	 ((planet_t *)(planet->next->data))->name);
	printf("SHIELDS: ");
	dll_print_int_list(((planet_t *)(planet->data))->shield_t);
	printf("KILLED: %d\n", ((planet_t *)(planet->data))->kills);
}
/*
 * Functie ce elibereaza memoria folosita, cu ajutorul functiei
 * blh. Se va sterge mereu elementul de pe pozitia 0 si ok va fi
 * 0 pentru ca sa nu se afiseze erorile corespunzatoare functiei
 * blh.
 */
void
galaxy_free(doubly_linked_list_t **galaxy)
{
	while ((*galaxy)->size) {
		blh((*galaxy), 0, 0);
	}

	free(*galaxy);
}
