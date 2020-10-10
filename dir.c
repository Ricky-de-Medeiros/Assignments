#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assign4.h"

int sects[30];
char file[25];
char fname[25];


void read_dir(void) {
	int i = 0;
	//DOChAC = Declare, open, check, Access, Close
  FILE *dirdat;
  dirdat = fopen("dir.dat", "r");
  if (dirdat != NULL) {
    while (fscanf(dirdat, "%s %d", dir[i], &sect1[i]) != EOF) {
      i++;
    }
	 }
	 dircount = i;
	 fclose(dirdat);
	}

void save_dir(void) {
	//DO, no checking, A, C
	int i;
	FILE *dirdat;
	dirdat = fopen("dir.dat", "w");
	for (i = 0; i <= dircount; i++) {
		fprintf(dirdat, "%s %d\n", dir[i], sect1[i]);
		}
	fclose(dirdat);
}

void print_dir(void) {
	int i;
	for (i = 0; i < dircount; i++) {
		printf("%s %d\n", dir[i], sect1[i]);
	}
}

int does_file_exist_in_dir(char *file) { 	//works on main fname. Returns indx or -1 (doesn't exist)
	int i;
	for (i = 0; i < dircount; i++) {
  	if (strcmp(file, dir[i]) == 0) {
    	return i;
    }
  }
  return -1;
}

/* Function not needed
int is_dir_full(){
}
*/

void add_file_to_dir(char *file, int start_sector) { //sent file name an first_sector, no return
	strcpy(dir[dircount], file);
	sect1[dircount] = start_sector;
	dircount++;
}

void delete_file_from_dir(int position) {
	int i;
	for (i = position; i < (dircount-1); i++) {
		//shuffle up data in dir and sct1 arrays
		strcpy(dir[i], dir[i+1]);
		sect1[i] = sect1[i + 1];
	}
	dircount -= 1;
}
