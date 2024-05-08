//Authors: Anthony Lyster & Kevin Valadez
//Date: 05/07/2024
//Purpose: Final project, group coding assignment

#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void mainMenu();
void loadImage();
void displayImage();
void editImage();
void saveImage();
void markedImage();
void rotate90();
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols);
void dimImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);
void brightenImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);

int numRows, numCols;
int image[MAX_ROWS][MAX_COLS];
char displayChar;
bool imageLoaded = false;

int main(){
	mainMenu();
	return 0;
}

void mainMenu(){
	int choice;
	do{
		printf("**ERINSTAGRAM**\n");
		printf("1: Load image\n");
		printf("2: Display image\n");
		printf("3: Edit image\n");
		printf("0: Exit\n\n");
		printf("Choose from one of the options above: ");
		scanf("%d", &choice);

	switch(choice){
		case 1:
			loadImage();
			break;
		case 2:
			printf("\n");
			displayImage();
			printf("\n");
			break;
		case 3:
			printf("\n\n");
			editImage();
			break;
		case 0:
			printf("Goodbye!\n\n");
			break;
		default:
			printf("Invalid option, please try again.\n\n");
		}
	}while(choice != 0);
	printf("\n");
}
void loadImage(){
	char filename[100];
	printf("What is the name of the file? ");
	scanf("%s", filename);
	printf("\n");
	FILE *file = fopen(filename, "r");
	if(file == NULL){
		printf("Could not find an image with that file name.\n");
		return;
	}
	numRows = 0;
	char line[100];
	while(fgets(line, 100, file) && numRows < MAX_ROWS){
		numCols = 0;
		for(int i = 0; line[i] != '\0' && numCols < MAX_COLS; i++){
			if(line[i] >= '0' && line[i] <= '9') {
				image[numRows][numCols++] = line[i] - '0';
			}
		}
		numRows++;
	}
	fclose(file);
	imageLoaded = true;
	printf("Image successfully loaded!\n\n");
}	
void displayImage(){
	if (!imageLoaded) {
		printf("Sorry, no image to display\n");
	return;
	}
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			char displayChar = ' ';
			switch (image[i][j]) {
				case 0: 
					displayChar = ' '; 
					break;
				case 1: 
					displayChar = '.';
					break;
				case 2:
					displayChar = 'o';
					break;
				case 3:
					displayChar = 'O';
					break;
				case 4:
					displayChar = '0';
					break;
				default:
					displayChar = '?';
					break;
				}
			printf("%c", displayChar);
		}
	printf("\n");
	}
}
void editImage(){
	int choice;
	if(!imageLoaded){
		printf("Sorry, no image to edit!\n\n");
	}else{
		do{
			printf("**EDITING**\n");
			printf("1: Crop image\n");
			printf("2: Dim image\n");
			printf("3: Brighten Image\n");
			printf("4: Rotate 90\n");
			printf("0: Return to main menu\n\n");
			printf("Choose from one of the options above: ");
			scanf("%d", &choice);
		
			switch(choice){
				case 1:
					cropImage(image, &numRows, &numCols);
					break;
				case 2:
					dimImage(numRows, numCols, image);
					break;
				case 3:
					brightenImage(numRows, numCols, image);
					break;
				case 4:
					rotate90();
					break;
				case 0:
					printf("Returning to the main menu!\n\n");
					break;
				default:
					printf("Invalid choice! Please try again.\n");
			}
		}while(choice != 0);
	}
}
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols){
	int leftCol, rightCol, top_row, bot_row;
    int cropped_pic[MAX_ROWS][MAX_COLS];

	markedImage();
	
    printf("Which column do you want to be the new left side? ");
    scanf("%d", &leftCol);
    printf("Which column do you want to be the new right side? ");
    scanf("%d", &rightCol);

    printf("Which row do you want to be the new top? ");
    scanf("%d", &top_row);
    printf("Which row do you want to be the new bottom? ");
    scanf("%d", &bot_row);

    int newRows = bot_row - top_row + 1;
	int newCols = rightCol - leftCol + 1;
	
	for(int i = top_row; i <= bot_row; i++){
		for(int j = leftCol; j <= rightCol; j++){
			cropped_pic[i - top_row][j - leftCol] = image[i][j];
		}
	}

	*rows = newRows;
	*cols = newCols;

	displayImage(cropped_pic, newRows, newCols);
	saveImage();
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
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			char displayChar = ' ';
			switch(image[i][j]){
				case 0: 
					displayChar = ' '; 
					break;
				case 1: 
					displayChar = '.';
					break;
				case 2:
					displayChar = 'o';
					break;
				case 3:
					displayChar = 'O';
					break;
				case 4:
					displayChar = '0';
					break;
				default:
					displayChar = '?';
					break;
				}
			printf("%c", displayChar);
		}
		printf("\n");
	}
	saveImage();
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
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			char displayChar = ' ';
			switch(image[i][j]){
				case 0: 
					displayChar = ' '; 
					break;
				case 1: 
					displayChar = '.';
					break;
				case 2:
					displayChar = 'o';
					break;
				case 3:
					displayChar = 'O';
					break;
				case 4:
					displayChar = '0';
					break;
				default:
					displayChar = '?';
					break;
				}
			printf("%c", displayChar);
		}
		printf("\n");
	}
	saveImage();
}
void saveImage(){
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
		for(int i = 0; i < numRows; i++){
			for(int j = 0; j < numCols; j++){
				fprintf(file, "%d ", image[i][j]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
		printf("Image successfully saved!");
	}
}
void markedImage(){
	int totalRows = 1;
	int totalCols = 1;
	int tempRows = numRows;
	int tempCols = numCols;
	while(tempRows /= 10) totalRows++;
	while(tempCols /= 10) totalCols++;

	printf(" ");
	printf("%d", 0);
    for(int j = 1; j < numCols - 1; j++){
        printf(" ");
    }
    printf("%d\n", numCols - 1);

    for(int i = 0; i < numRows; i++){
    	printf("%*d", totalRows, i);
    	for (int j = 0; j < numCols; j++){
			char displayChar = ' ';
        	switch(image[i][j]){
				case 0: 
					displayChar = ' '; 
					break;
				case 1: 
					displayChar = '.';
					break;
				case 2:
					displayChar = 'o';
					break;
				case 3:
					displayChar = 'O';
					break;
				case 4:
					displayChar = '0';
					break;
				default:
					displayChar = '?';
					break;
			}
			printf("%c", displayChar);
        }
		printf("\n");
    }
	printf("The image you want to crop is %d x %d.\n", numRows, numCols);
	printf("The row and column values start in the upper lefthand corner.\n\n");
}
void rotate90() {
	if(!imageLoaded){
		printf("No image loaded to rotate!\n");
		return;
	}

	int rotatedImage[MAX_COLS][MAX_ROWS];
	int originalNumRows = numRows;
	int originalNumCols = numCols;

	for(int i = 0; i < originalNumRows; i++){
		for(int j = 0; j < originalNumCols; j++){
	rotatedImage[j][originalNumRows - 1 - i] = image[i][j];
		}
	}

	for(int i = 0; i < originalNumCols; i++){
		for(int j = 0; j < originalNumRows; j++){
		image[i][j] = rotatedImage[i][j];
		}
	}

	numRows = originalNumCols;
	numCols = originalNumRows;

	displayImage();
	saveImage();
}
