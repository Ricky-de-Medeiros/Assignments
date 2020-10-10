#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assign4.h"

//global variable definitions
int fat[32];
char dir[30][80];
int sect1[30];
int dircount;

int main(){
//Call functions and sort out error messages
	char filename[25];
	char temp[100];
	char command[50];
	int num_sectors;
	int indx;
	int firstF;


	read_dir();
	read_fat();


	printf(":");
	gets(temp);
	sscanf(temp, "%s %s %d", command, filename, &num_sectors);

//read user input until quit
	while(1) {
		indx = does_file_exist_in_dir(filename);
		if (strcmp(command, "sectors") == 0) {

			if (indx == -1) {
				printf("File does not exist\n");
				}
			else {
				print_sector_chain(sect1[indx]);
				}
			}

		else if (strcmp(command, "delete") == 0) {
			if (indx == -1) {
				printf("File does not exist\n");
				}
			else {
				deallocate_sectors(sect1[indx]);
				delete_file_from_dir(indx);

				save_dir();
				save_fat();
				}
			}

		else if (strcmp(command, "add") == 0) {
			int numfree = free_sectors();
			if (indx != -1) {
				printf("File already exists\n");
			}
			else if (numfree == 0) {
				printf("Directory is full\n");
			}
			else if (num_sectors > numfree) {
				printf("Not enough free spaces\n");
			}
			else {
				firstF = first_free_sector();
				add_file_to_dir(filename, firstF);
 				allocate_sectors(firstF, num_sectors);

				save_dir();
				save_fat();
				}
			}

		else if (strcmp(command, "dir") == 0) {
			print_dir();
		}

		else if (strcmp(command, "quit") == 0) {
			exit(1);
		}
		printf(":");
		gets(temp);
		sscanf(temp, "%s %s %d", command, filename, &num_sectors);
	}
}
