//Authors: Anthony Lyster & Kevin Valadez
//Date: 05/07/2024
//Purpose: Final project, group coding assignment

#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

//function prototypes
void displayMenu();
void loadImage(char filename[]);
void displayImage();
void editImage();
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols, int leftCol, int rightCol, int top_row, int bot_row);
void dimImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);
void brightenImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);
void saveImage(char filename[], int numRows, int numCols, int image[MAX_ROWS][MAX_COLS]);

//global vars
int numRows, numCols;
int image[MAX_ROWS][MAX_COLS];

//main function
int main(){
	mainMenu();
	return 0;
}

//function definitions
void mainMenu(){

}
void loadImage(char filename[]){

}
void displayImage(){

}
void editImage(){
	int choice;
	do{
		printf("**EDITING**\n");
		printf("1: Crop image\n");
		printf("2: Dim image\n");
		printf("3: Brighten Image\n");
		printf("0: Return to main menu\n\n");
		printf("Choose from one of the options above: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				cropImage();
				break;
			case 2:
				dimImage();
				break;
			case 3:
				brightenImage();
				break;
			case 0:
				printf("Returning to the main menu!\n");
				break;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}while(choice != 0);
	
}
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols, int leftCol, int rightCol, int top_row, int bot_row){
	int cropped_pic[MAX_ROWS][MAX_COLS];
	int newRows = bot_row - top_row + 1;
	int newCols = rightCol - leftCol + 1;
	
	for(int i = top_row; i <= bot_row; i++){
		for(int j = leftCol; j <= rightCol; j++){
			cropped_pic[i - top_row][j - leftCol] = image[i][j]
		}
	}
}
void dimImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			image[i][j] -= 1;
			if(image[i][j] < 0){
				image[i][j] = 0;
			}
		}
	}
}
void brightenImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			image[i][j] += 1;
			if(image[i][j] > 4){
				image[i][j] = 4;
			}
		}
	}
}
void saveImage(char filename[]){
	char customFile[100];
	printf("Would you like to save the file? (y/n) ");
	char choice;
	scanf(" %c", &choice);
	
	if(choice == 'y' || choice == 'Y'){
		printf("What do you want to name the image file? (include the extension) ");
		scanf("%s", customFile);
		FILE *file = fopen(customFile, "w");
		if(file == NULL){
			printf("Error: Cannot open file for writing.");
			return;
		}
		
		fprintf(file, "%d %d\n", numRows, numCols);
		for(int i = o; i < numRows; i++){
			for(int j = 0; j < numCols; j++){
				fprintf(file, "%d ", image[i][j]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
		printf("Image successfully saved!");
	}
}
