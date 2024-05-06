//Authors: Anthony Lyster & Kevin Valadez
//Date: 05/07/2024
//Purpose: Final project, group coding assignment

#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

//function prototypes
void mainMenu();
void loadImage();
void displayImage();
void editImage();
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols);
void dimImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);
void brightenImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);
void saveImage(char filename[]);
void markedImage(int image[MAX_ROWS][MAX_COLS], int rows, int cols, int top_row, int bot_row, int leftCol, int rightCol);
void croppedImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]);

//global vars
int numRows, numCols;
int image[MAX_ROWS][MAX_COLS];
bool imageLoaded = false;

//main function
int main(){
	mainMenu();
	return 0;
}

//function definitions
void mainMenu(){
	for 

}
void loadImage(){
	char filename[100];
	printf("what is the name of the file? ");
	scanf("%s", filename);
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Coudl not find an image with that file name.\n");
		return;
	}

	fscanf(file, "%d %d", &numRows, &numCols);
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			fscanf(file, "%d", &image[i][j]);
		}
	}

	fclose(file);
	imageLoaded = true;
	printf("Image successfully loaded!\n");
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
					break; // In case of unexpected values or errors with images, good reference 
				}
			printf("%c", displayChar);
		}
	printf("\n");
	}
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
				cropImage(image, &numRows, &numCols);
				break;
			case 2:
				dimImage(numRows, numCols, image);
				break;
			case 3:
				brightenImage(numRows, numCols, image);
				break;
			case 0:
				printf("Returning to the main menu!\n");
				break;
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}while(choice != 0);
	
}
//the cropping works and will do the job, but its not displaying properly right now, not 100% sure what's going on with it
void cropImage(int image[MAX_ROWS][MAX_COLS], int* rows, int* cols){
	int leftCol, rightCol, top_row, bot_row;
    int cropped_pic[MAX_ROWS][MAX_COLS];
	
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
	for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%3d", image[i][j]);
        }
        printf("\n");
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
	for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%3d", image[i][j]);
        }
        printf("\n");
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
//function to display the test image with the corner markings for rows/columns
void markedImage(int image[MAX_ROWS][MAX_COLS], int rows, int cols, int top_row, int bot_row, int leftCol, int rightCol){
    //top left and right markers
    printf("    ");
    for(int j = 0; j < cols; j++){
        printf("%3d", j);
    }
    printf("\n");
    //first and last column markers
    for(int i = 0; i < rows; i++){
        printf("%3d", i);
        for(int j = 0; j < cols; j++){
            if(j == leftCol || j == rightCol){
                printf("%3d", j);
            } else {
               printf("%3d", image[i][j]); 
            }
        }
        printf("\n");
    }

    //bottom left marker? (needs work, will print beneath bottom left as written)
    printf("    ");
    for(int j = 0; j < cols; j++){
        printf("%3d", j);
    }
    printf("\n");
}
//this is kind of useless right now, but can be used if we need to explicitly call the cropped image anywhere
void croppedImage(int rows, int cols, int image[MAX_ROWS][MAX_COLS]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%3d", image[i][j]);
        }
        printf("\n");
    }
}