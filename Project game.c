#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

char map[20][40];
char player = '^';
char tail = '*';
char food = 'x';
int x = 5, y = 5;
int panjang = 40, lebar = 20;
int xTail[100];
int yTail[100];
int totalTail = 2;
int maxTail = 100;
int xFood, yFood;
int score = 0;

void createMap(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 40; j++){
			if(i == 0 || i == 19){
				map[i][j] = '-';
			}
			else if(j == 0 || j == 39){
				map[i][j] = '|';
			}
			else{
				map[i][j] = ' ';
			}
		}
	}
	map[y][x] = player;
	map[yFood][xFood] = food;
	for(int i = 0; i <= totalTail; i++){
		map[yTail[i]][xTail[i]] = tail;
	}
}

void displayMap(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 40; j++){
		printf("%c", map[i][j]);
		}
		printf("\n");
	}
	printf("Score : %d\n", score);
}

int checkCrash(int newY, int newX){
    if(map[newY][newX] == '-' || map[newY][newX] == '|'){
        return 1;
    }
    else{	
	return 0;
	}
}

void moveUp(){
	if(y-1 > 0 && !checkCrash(y-1, x)){
		yTail[0] = y;
		xTail[0] = x;
		y--;
	}
	else{
		printf("Game Over!\n");
		printf("Snake crashed into the wall!\n");
		// save player data ke file
        FILE *file = fopen("winner.data", "a"); //append mode
        char playerName[50];
        printf("Enter your name: ");
        scanf("%[^\n]", playerName);
        fprintf(file, "Player: %s, Score: %d\n", playerName, score);
        fclose(file);
        exit(0);
	}
}

void moveDown(){
	if(y+1 < lebar-1 && !checkCrash(y+1, x)){
		yTail[0] = y;
		xTail[0] = x;		
		y++;
	}
	else{
		printf("Game Over!\n");
		printf("Snake crashed into the wall!\n");
		// save player data ke file
        FILE *file = fopen("winner.data", "a"); //append mode
        char playerName[50];
        printf("Enter your name: ");
        scanf("%[^\n]", playerName);
        fprintf(file, "Player: %s, Score: %d\n", playerName, score);
        fclose(file);
        exit(0);
	}
}

void moveLeft(){
	if(x-1 > 0 && !checkCrash(y, x-1)){
		yTail[0] = y;
		xTail[0] = x;		
		x--;
	}
	else{
		printf("Game Over!\n");
		printf("Snake crashed into the wall!\n");
		// save player data ke file
        FILE *file = fopen("winner.data", "a"); //append mode
        char playerName[50];
        printf("Enter your name: ");
        scanf("%[^\n]", playerName);
        fprintf(file, "Player: %s, Score: %d\n", playerName, score);
        fclose(file);
        exit(0);
	}
}

void moveRight(){
	if(x+1 < panjang-1 && !checkCrash(y, x+1)){
		yTail[0] = y;
		xTail[0] = x;		
		x++;
	}
	else{
		printf("Game Over!\n");
		printf("Snake crashed into the wall!\n");
		// save player data ke file
        FILE *file = fopen("winner.data", "a"); //append mode
        char playerName[50];
        printf("Enter your name: ");
        scanf("%[^\n]", playerName);
        fprintf(file, "Player: %s, Score: %d\n", playerName, score);
        fclose(file);
        exit(0);
	}
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int scores[], int n){
	for(int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){// -i supaya yang udah ke sort gaakan di cek lagi
			if(scores[j] < scores[j+1]){
				swap(&scores[j], &scores[j+1]);
			}
		}
	}
}

void displayHighScores(int scores[], int n){
	printf("\nHigh Scores:\n");
	for(int i=0; i<n; i++){
		printf("%d. %d", i+1, scores[i]);
	}
}

void readWinnerData(int scores[], int n){
	FILE *file = fopen("winner.data", "r");
	for(int i=0; i<n; i++){
		if(fscanf(file, "Player: %*s, Score: %d\n", &scores[i]) != 1){
			break;
		}
	}
	fclose(file);
}

int main(){
	char move;
	int i, n=5;
	time_t t;
	srand((unsigned) time(&t));
	yFood = rand() % 18 + 1;
	xFood = rand() % 38 + 1;
	xTail[0] = x;
	yTail[0] = y+1;
	xTail[1] = x;
	yTail[1] = y+2;
	int highScores[100];
	
	for(int i=0; i<100; i++){
		highScores[i] = 0;
	}
	
	readWinnerData(highScores, 100);
	bubbleSort(highScores, 100);
	displayHighScores(highScores, 100);
	
	do{
		system("cls");
		createMap();
		displayMap();
		move = getch();
		
		switch(move){
			case 'w' :
				player = '^';
				moveUp();
				break;
					
			case 'a' :
				player = '<';
				moveLeft();
				break;
				
			case 's' :
				player = 'v';
				moveDown();
				break;
				
			case 'd' :
				player = '>';
				moveRight();
				break;
		}
		if(y == yFood && x == xFood){
			map[y][x] = player;
			score++;
			if(totalTail < maxTail){
			totalTail++;				
			}
			yFood = rand() % 18 + 1;
			xFood = rand() % 38 + 1;
			
			highScores[99] = score;
			bubbleSort(highScores, 100);
			displayHighScores(highScores, 100);
			
			
		}
		
		for(int i = totalTail; i > 0; i--){
			yTail[i] = yTail[i - 1];
			xTail[i] = xTail[i-1];
		}
		
		
	}while(score<100);
	printf("CONGRATULATIONS\n");
	printf("You Win With Score : %d\n", score);
	
	// save player data ke file
	FILE *file = fopen("winner.data", "a"); //append mode
	char playerName[50];
	printf("Enter your name: ");
	scanf("%[^\n]", playerName);
	fprintf(file, "Player: %s, Score: %d\n", playerName, score);
	fclose(file);

 
	return 0;
}


