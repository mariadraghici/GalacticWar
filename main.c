/*Copyright [2021] <Maria Draghici>*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"

#define MAX_COMMAND_SIZE 200
#define MAX_WORDS 5

int
main()
{
    doubly_linked_list_t *galaxy = NULL;
    galaxy = dll_create(sizeof(planet_t));
    int number_commands = 0, j = 0;
    char command[MAX_COMMAND_SIZE];
    scanf("%d", &number_commands);
    for (j = 0; j < number_commands; ++j) {
        scanf("%s", command);
        if (strcmp(command, "ADD") == 0) {
            add_planet(galaxy);
                            }
        if (strcmp(command, "BLH") == 0) {
            unsigned int index_planet;
            scanf("%d", &index_planet);
            blh(galaxy, index_planet, 1);
                            }
        if (strcmp(command, "UPG") == 0) {
            upgrade_shield(galaxy);
                            }
        if (strcmp(command, "EXP") == 0) {
            exp_shield(galaxy);
                            }
        if (strcmp(command, "RMV") == 0) {
            rmv_shield(galaxy);
                            }
        if (strcmp(command, "COL") == 0) {
            col(galaxy);
                            }
        if (strcmp(command, "ROT") == 0) {
            rot(galaxy);
                            }
        if (strcmp(command, "SHW") == 0) {
            shw(galaxy);
                            }
    }
    galaxy_free(&galaxy);
    return 0;
}
