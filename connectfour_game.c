#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printgrid(char **grid, int rc);
int wincheck(char shape, char **grid, int rc);
char turncheck( char **grid, int win, int rc);
void printScore();
void updateScore(const char *winner);
void gridoptions();

int main(){	
	int rc;	
	
	char shape = '\0';
	char playerX[50], playerO[50];
	
	printf("\n******************************\n");
	printf("     Welcome to Connect 4!    \n");
	printf("******************************\n\n");
	
	printf("Rules of the game:\n");
	printf("--------------------\n");
	printf("1. Players take turns to drop a disc into one of the columns.\n");
	printf("2. The disc will fall to the lowest available space in the chosen column.\n");
	printf("3. The first player to connect 4 discs in a row, column, or diagonal wins!\n");
	printf("4. The game ends in a draw if all spaces are filled without a winner.\n\n");
	
	printf("Good luck and let's play!\n");
	printf("\n******************************\n");
	
	printf("Player 1 is X, Player 2 is O.\n");

	// Get player names
    printf("Enter Player X's name: ");
    scanf("%s", playerX);
    printf("Enter Player O's name: ");
    scanf("%s", playerO);
    
    //Asking for grid size from 4x4,5x5,6x6 until valid input
	printf("Enter the type of grid you'd like to play on\n'");
	gridoptions();
	
	do {
	    printf("Enter number between 4-6: ");
	    scanf("%d", &rc);
	} while (rc < 4 || rc > 6);
	
	
	//Dynamically allocating memory based on chosen grid
	char **grid = (char **)malloc(rc * sizeof(char *));
	if (grid == NULL) {
        printf("Memory allocation failed for rows.\n");
        return 1;  // Exit the program if memory allocation fails
    }

	int win = 0;
	for(int i = 0; i <rc ; i++){
		grid[i] = (char *)malloc(rc * sizeof(char));
		
		if (grid[i] == NULL) { 
			printf("Memory allocation failed for column %d.\n", i); 
			// Free the allocated memory to prevent memory leak 
			for (int j = 0; j < rc; j++) { 
				free(grid[j]); 
			} 
			free(grid); // Free grid pointer 
			return 1; // Exit the program if memory allocation fails 
		}

		
		for(int j = 0; j <rc ; j++){
			grid[i][j] = ' ';
		}
		
	}
	while(shape =='\0'){
		printgrid(grid,rc);
		shape = turncheck(grid, win,rc);
	}
	if(shape == 'D'){
		printf("There has been a draw. No one gets a point\n", playerX);
	}	
	if(shape == 'X'){
		updateScore(playerX);
		printf("Player %s is the winner! Congratulations!\n", playerX);
	}
	else if(shape == 'O'){
		updateScore(playerO);
		printf("Player %s is the winner! Congratulations!\n", playerO);
	}
	
	printScore();
	
	//free grid once done
	for (int j = 0; j < rc; j++) { 
		free(grid[j]); 
	} 
	free(grid); // Free the original grid pointer 
	
	return 0;
}

//Function to print the different grids users can choose from
void gridoptions(){
		printf("4x4\n");
	
	//printing 4x4 grid
	for(int i = 0; i <4 ; i++){
		for(int j = 0; j <4 ; j++){
			printf("   |   ");
		}
		printf("\n");
		printf("--------------------------------"); 
		printf("\n"); 
	}
	printf("\n");

	//printing 5x5 grid
	printf("5x5\n");
	for(int i = 0; i <5 ; i++){
		for(int j = 0; j <5 ; j++){
			printf("   |   ");
		}
		printf("\n");
		printf("--------------------------------"); 
		printf("\n"); 
	}
	printf("\n");
	
	//printing 6x6 grid
	printf("6x6\n");
	for(int i = 0; i <6 ; i++){
		for(int j = 0; j <6 ; j++){
			printf("   |  ");
		}
		printf("\n");
		printf("--------------------------------"); 
		printf("\n"); 
	}
	printf("\n");
}


//Function to display the current state of the grid
void printgrid(char **grid,int rc){
	for(int i = 0; i <rc ; i++){
		for(int j = 0; j <rc ; j++){
			printf("   %c 	|", grid[i][j]);
		}
		printf("\n");
//		
//		printf("-------------------------------------------------");
		for(int k = 0; k <(rc * 7 + rc); k++){
			printf("-");
		} 
		printf("\n"); 
	}
	printf("\n");
}


//Function for user to take turn and toggle turns
char turncheck(char **grid, int win,int rc) {
    int col = 0;
    int turn = 0;
    int filledspaces =0;
    int draw=0;

    while (win != 1 && draw!=1) { // Turn-based loop
        char shape;
        int placed = 0;
        int changeColumn = 0;


        while (!placed) { // Loop until a valid column is selected
            if (changeColumn == 0) {
                printf("Input column number: \n");
            } else {
                printf("Column full. Input a different column number: \n");
            }
            scanf("%u", &col);

            // Ensure column is valid
            if (col < 1 || col > rc) {
                printf("Invalid column. Try again.\n");
                continue;
            }
		if(turn == 0){
			shape = 'X';
		}
		else{
			shape = 'O';
		}
		for( int i = rc-1; i >= 0; i --){
			if(grid[i][col - 1] == ' '){
				grid[i][col - 1] = shape;
				placed = 1;   //confirms that shape has been placed 
				break;          
			}
		}
		if (!placed) {
                changeColumn++; // Indicate the column was full
            }
        }
        
        printgrid(grid,rc);
        
    	//check for draw
    	filledspaces =0;
        for (int i = 0; i < rc; i++) {
            for (int j = 0; j < rc; j++) {
                if (grid[i][j] != ' ') {
                    filledspaces++;
                }
            }
        }
        
        if (filledspaces == rc * rc && win!= 1) { // Grid is full, no winner
			draw=1;
        }
        
        
        // Check win, return respective shape if so
        win = wincheck(shape, grid,rc);
        if(win == 1){
			return shape;
		}else if(win!=1 && draw==1){
			return 'D';
		}
		else{		
			// toggle turn to other player
  			if(turn == 1){
				turn = 0;
			}
			else{
				turn = 1;
			}
		}
	} 
	
}

// checking if there is a win state i grid; whether horizontal, vertical or diagonal
int wincheck(char shape, char **grid,int rc){
	//search in grid
		//setting cmpstr to the string that needs to be found for winning
		char cmpstr[100];
		char search[100] = "";
		int found = 0;
		if(shape == 'X'){
			strcpy(cmpstr, "XXXX");			
		}
		else if(shape=='O'){
			strcpy(cmpstr, "OOOO");
		}
		
		//horizontal search: checks 4 consecutive O's or X's in the form "XXXX" or "OOOO" in a row
		for(int i=0; i < rc; i++){
			for(int k=0;k<rc-3;k++){
				strcpy(search,"");
				for(int j = k; j< k+4; j++){
					char letter[2] ={grid[i][j],'\0'};
					strcat(search, letter);
				}
				if(strcmp(search, cmpstr) == 0){
					printf("Found \n");
					found = 1;
					break;
				}
			}
			printf("\n");
		}

		//vertical search
		//checks if there is a column with the form "OOOO" OR"XXXX"
		if(found != 1){
			for(int j=0;j<rc;j++){
				for(int k=0;k<rc-3;k++){
					strcpy(search,"");
					for(int i=k;i<k+4;i++){
						char letter[2] ={grid[i][j],'\0'};
						strcat(search, letter);
			    	}
					if(strcmp(search, cmpstr) == 0){
						printf("Found \n");
						found=1;
						break;
					}
				}
			}
		}
		//LEFT diagonal: checks if there is a diagonal with the form 
		//"OOOO" OR"XXXX" running from top left to bottom right
		
		if(found != 1){
			for(int i=0;i<rc-3;i++){
				for(int k =0;k<rc-3;k++){
					strcpy(search,"");
					for(int j=0;j<4;j++){
							char letter[2] ={grid[i+j][k+j],'\0'};
							strcat(search, letter);
					}
					if(strcmp(search, cmpstr) == 0){
						printf("Found \n");
						found=1;
					}
				}	
			}
		}
		
		//Right diagonal: checks if there is a diagonal with the form 
		//"OOOO" OR"XXXX" running from top right to bottom left

		if(found != 1){
			for(int i=0;i<=rc-4;i++){
				for(int j =rc-1;j>=3;j--){
					strcpy(search,"");
					for(int k=0;k<4;k++){
						if((i + k < rc) && (j - k >= 0)){
							char letter[2] ={grid[i+k][j-k],'\0'};
							strcat(search, letter);	
						}

					}	
					if(strcmp(search, cmpstr) == 0){
						printf("Found \n");
						found=1;
						break;
					}
				}		

			}
		}
		
		
		if(found == 1){
			return 1;//if win
		}

		return 0; //no win
}

	
// function to read and print scores from the file
void printScore() {
    FILE *winsFile = fopen("wins.txt", "r");
    if (winsFile == NULL) {
        printf("Error: No wins available.\n");
        return;
    }

    char name[50];
    int wins;

    // Show the wins
    printf("\nCurrent Wins:\n");
    printf("----------------------\n");
    while (fscanf(winsFile, "%s %d", name, &wins) == 2) {
        printf("%s ---- %d\n", name, wins);
    }
    printf("----------------------\n");

    fclose(winsFile);
}

//function to update scores in files as each player wins
void updateScore(const char *winner) {
    FILE *winsFile = fopen("wins.txt", "r");
    FILE *tempwins = fopen("tempwins.txt", "w");

    if (tempwins == NULL) {
        printf("Unable to create file.\n");
        return;
    }

    int updated = 0;
    int wins;
    char name[50];

    // If no scores file exists, write the winner directly
    if (winsFile == NULL) {
        fprintf(tempwins, "%s %d\n", winner, 1);
    } else {
        // Copy data to a temporary file, updating the winner's score
        while (fscanf(winsFile, "%s %d", name, &wins) == 2) {
            if (strcmp(name, winner) == 0) {
                fprintf(tempwins, "%s %d\n", name, wins + 1);
                updated = 1;
            } else {
                fprintf(tempwins, "%s %d\n", name, wins);
            }
        }
        fclose(winsFile);

        // If new player, add them
        if (!updated) {
            fprintf(tempwins, "%s %d\n", winner, 1);
        }
    }

    fclose(tempwins);

    // Replace old wins file with updated file
    remove("wins.txt");
    rename("tempwins.txt", "wins.txt");
}
