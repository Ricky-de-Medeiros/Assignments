#include <stdio.h>
#include <stdlib.h>
#include "assign4.h"

static int sectors[32];

void read_fat(void) {
	int i;
	FILE *fatdat;
	fatdat = fopen("fat.dat", "r");
	if (fatdat != NULL) {
		for (i = 0; i < 32; i++) {
			fscanf(fatdat, "%d", &fat[i]);
		}
	}
}

void save_fat(void) {
	int i;
	FILE *fatdat;
	fatdat = fopen("fat.dat", "w");
	for (i = 0; i < 32; i++) {
		fprintf(fatdat, "%d\n", fat[i]);
	}
	fclose(fatdat);
}

int free_sectors(void) {
	int i;
	int free_count = 0;
	for (i = 0; i < 32; i++) {
		if (fat[i] == 1) {
			free_count++;
		}
	}
return free_count;
}

int first_free_sector(void) { //no parameters, returns a count of 1s in fat
	int i;
	for (i = 0; i < 32; i++) {
		if (fat[i] == 1) {
			break;
		}
	}
	return i;
}


void allocate_sectors(int start_sector, int n) { //sent first sector and number of sectors in the chain
	int i, j;
	for (j = 0; j < n-1; j++) {
		i = start_sector +1;
		while (fat[i] != 1) {
			i++;
		}
		fat[start_sector] = i;
		start_sector = i;
		}
		fat[i] = 0;
	}

void deallocate_sectors(int start_sector) { //sent file's first sector , no return
	int i = start_sector;
	int next;
	while (fat[i] != 0) {
//record next variable before overwriting
		next = fat[i];
//overwrite fat entry
		fat[i] = 1;
		i = next;
	}
//overwrite the 0 at the end of chain with a 1;
	fat[i] = 1;
}

void print_sector_chain(int start_sector) { //sent the first sector, no return
	printf("%d ", start_sector);
	while (fat[start_sector] != 0) {
		printf("%d ", fat[start_sector]);
		start_sector = fat[start_sector];
	}
	printf("\n");
}
