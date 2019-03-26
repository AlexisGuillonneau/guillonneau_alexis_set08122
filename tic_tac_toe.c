#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int boardSize = 3;
char const* const fileName = "data.txt";
bool firstSaving = true;

typedef struct Coord{
	int x;
	int y;
} Coord;

typedef struct Node{
	char data;
	struct Coord* coord;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Player{
	char name[32];
	char sign;

} Player;

typedef struct Game{
	struct Node* board[8];

} Game;


void saveDuringGame(){
	FILE *fptr1, *fptr2; 
    char filename[100], c; 
  	
  	strcpy(filename,"data.txt");
  
    // Open one file for reading 
    fptr1 = fopen(filename, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  	strcpy(filename,"temp.txt");

  
    // Open another file for writing 
    fptr2 = fopen(filename, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  	int line_count = 0;
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    {
    	if(c == '\n'){
    		line_count++;
    	} 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    fclose(fptr1); 
    fclose(fptr2);
    strcpy(filename,"temp.txt");

  
    // Open one file for reading 
    fptr1 = fopen(filename, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  	strcpy(filename,"data.txt");

  
    // Open another file for writing 
    fptr2 = fopen(filename, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  	
  	int n_count = 0;
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    {
    	if(c == '\n'){
    		n_count++;
    	} 
        if(line_count == n_count+1){
        	break;
        } 
        fputc(c, fptr2); 
        c = fgetc(fptr1);
    } 
  
    fclose(fptr1); 
    fclose(fptr2);

}


/* Given a reference (pointer to pointer) to the head of a list  
and an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, struct Coord* coord)  
{  
    struct Node* new_node = malloc(sizeof(struct Node));
    struct Coord* c = malloc(sizeof(struct Coord));  
    c = coord;
  
    new_node->coord = c ;
    new_node->data =' ';  
  
    new_node->next = (*head_ref);  
    new_node->prev = NULL;  
  
    if ((*head_ref) != NULL)  
        (*head_ref)->prev = new_node;  
  
    (*head_ref) = new_node;  
}

struct Node* initialization(){
	struct Node* head = NULL;
    for(int i=0;i<boardSize;i++){
    	for(int j=0;j<boardSize;j++){
    		struct Coord* c = malloc(sizeof(struct Coord));
    		c->x = i;
    		c->y = j;
    		push(&head, c);
    	}
    }
    return head;
}  
  
/* Given a node as next_node, insert a new node before the given node 
void insertBefore(struct Node** head_ref, struct Node* next_node, struct Coord* coord)  
{  
    1. check if the given next_node is NULL 
    if (next_node == NULL) {  
        printf("the given next node cannot be NULL");  
        return;  
    }  
  
     2. allocate new node 
    struct Node* new_node = malloc(sizeof(struct Node));
    struct Coord* c = malloc(sizeof(struct Coord));  
    c = coord;  
  
     3. put in the data 
    new_node->coord = c;  
  
    4. Make prev of new node as prev of next_node 
    new_node->prev = next_node->prev;  
  
    . Make the prev of next_node as new_node 
    next_node->prev = new_node;  
  
     6. Make next_node as next of new_node 
    new_node->next = next_node;  
  
    7. Change next of new_node's previous node 
    if (new_node->prev != NULL)  
        new_node->prev->next = new_node;  
     8. If the prev of new_node is NULL, it will be 
       the new head node 
    else
        (*head_ref) = new_node; 
      
} */ 
  
// This function prints contents of linked list starting from the given node  
void printList(struct Node* node)  
{  
    struct Node* last;  
    printf("\nTraversal in forward direction \n");  
    while (node != NULL) {  
        printf("x= %d ", node->coord->x);
        printf("y= %d\n", node->coord->y);  
        last = node;  
        node = node->next;  
    }   
    while (last != NULL) {  
        /*printf("x= %d ", node->coord->x);
        printf("y= %d\n ", node->coord->y);   */
        last = last->prev;  
    }  
}  

void printBoard(struct Node* node)
{
	struct Node* last;
	char board[boardSize][boardSize];
	
	while(node != NULL){
		board[node->coord->x][node->coord->y] = node->	data;
		last = node;  
        node = node->next;
	}
	printf(" ");
	for(int i=1;i<boardSize+1;i++){
		printf(" %d  ",i);
	}
	printf("\n");
	for(int i=0;i<boardSize;i++){
		printf(" ");
		for(int j=0;j<boardSize;j++){
			printf("----");
		}
		printf("\b \n");
		for(int j=0;j<boardSize;j++){
			printf("| %c ",board[j][i]);
			
		}
		printf("| %d\n",i+1);
	}
	printf(" ");
		for(int j=0;j<boardSize;j++){
			printf("----");
		}
		printf("\b \n");

	

    while (last != NULL) {  
        last = last->prev;  
    } 
}

char checkPart(char boardPart[boardSize]){
	char sign = '\0';
	for(int i=0;i<boardSize;i++){
		if(boardPart[0] == boardPart[i]){
			if(boardPart[0] == 'x'){
				sign = 'x';
			}else if(boardPart[0] == 'o'){
				sign = 'o';
			}
		}else{
			sign = '\0';
			return sign;
		}
	}
	return sign;
}

int checkSign(char sign, struct Player p1){
	if(sign != '\0'){
    	if(sign == p1.sign){
    		return 1;
    	}else{
    		return 2;
    	}
    }else
    return 0; 
}

int checkWin(struct Node* node, struct Player p1){
	struct Node* last;
	char board[boardSize][boardSize];
	char sign = '\0';
	
	while(node != NULL){
		board[node->coord->x][node->coord->y] = node->	data;
		last = node;  
        node = node->next;
	}

	
	//Check horizontal lines
	for(int i=0;i<boardSize;i++){
		char boardPart[boardSize];
		for(int j=0;j<boardSize;j++){
			boardPart[j]=board[j][i];
		}
		sign = checkPart(boardPart);
		if(sign == 'x' || sign == 'o'){
			return checkSign(sign,p1);
		}
	}
	//Check vertical lines
	for(int i=0;i<boardSize;i++){
		char boardPart[boardSize];
		for(int j=0;j<boardSize;j++){
			boardPart[j]=board[i][j];
		}
		sign = checkPart(boardPart);
		if(sign == 'x' || sign == 'o'){
			return checkSign(sign,p1);
		}
	}
	//Check diagonal lines
	
	char boardPart[boardSize];
	for(int j=0;j<boardSize;j++){
		boardPart[j] = board[j][j];
	}
	sign = checkPart(boardPart);
		if(sign == 'x' || sign == 'o'){
			return checkSign(sign,p1);
		}
	int k=0;
	int l=boardSize-1;
	//Check second diagonal
	for(int j=0;j<boardSize;j++){
		boardPart[j] = board[k][l];
		k++;
		l--;
	}
	sign = checkPart(boardPart);
		if(sign == 'x' || sign == 'o'){
			return checkSign(sign,p1);
		}
	


	while (last != NULL) {  
        last = last->prev;  
    }

    return checkSign(sign,p1); 
}

int changeStateNode(struct Node* node, char sign, int x, int y){
	int error = 0;
	struct Node* last;  
    while (node != NULL) {  
    	if(x == node->coord->x && y == node->coord->y){
    		if(node->data == 'x' || node->data == 'o'){
    			error = 1;
    			return error;
    		}
    		node->data = sign;
    	}
        last = node;  
        node = node->next;  
    }   
    while (last != NULL) {  
        last = last->prev;  
    }  
    return error;
}


void cleanStd(){
	fflush(stdout);
	fflush(stdin);
}

void printWinner(char name[50], char sign){
	if(sign == '\0'){
		printf("It is a draw.\n");
	}else{
		printf("%s win !\n",name);
	}
}

int makeMove(struct Node* node, struct Player p){
	int error = 0;
	printf("%s your turn.\nEnter x then y.\n",p.name);
    cleanStd();
    char x;
    char y;
    scanf(" %c",&x); 
    scanf(" %c",&y);
    int nx = x - '0' - 1;
    int ny = y - '0' - 1;
	error = changeStateNode(node,p.sign,nx,ny);

	return error;
}


bool fullBoard(struct Node* node){
	struct Node* last;
    while (node != NULL) {  
    	if(node->data != 'x' || node->data != 'o'){
    		return false;
    	}
        last = node;  
        node = node->next;  
    }   
    while (last != NULL) {  
        last = last->prev;  
    }
    return true;  
}

void changeParam(){
	printf("Size of the board (default: 3):\n");
	char param;
	cleanStd();
	scanf(" %c",&param);
	if(isdigit(param)){
		boardSize = param - '0';
	}else{
		printf("This is not a number, please retry.\n");
		while(true){
			char param;
			cleanStd();
			scanf(" %c",&param);
			if(isdigit(param)){
				boardSize = param - '0';
				break;
			}else{
				printf("This is not a number, please retry.\n");
			}
		}
	}
}

void changeBoardSize(int size){
	boardSize = size;
}

void readData(struct Node* node, struct Player p1, struct Player p2){
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];
    int count = 1;
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
    	line_count++;
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
    	int i = 0;
    	//IMPORTANT check if line[3] == ';' to be sure if it's a new line.
    	
    	while(line[i] != '\n'){
    		i++;

    	}
    	int r = 0;
    	while(line[r] != ' ' ){
    		p1.name[r] = line[r];
    		r++;
    	}
    	int s = 0;
    	r++;
    	while(line[r] != ' '){
    		printf("%d",s);
    		p2.name[s] = line[r];
    		r++;
    		s++;
    	}
    	printf("\n%s _ %s _\n",p1.name,p2.name);
    	changeBoardSize(line[4] - '0');
    	char string[i-2];
    	int k = 0;
    	while(line[k] != '\n'){
    		string[k] = line[k];
    		k++;
    	}
    	char str[i-2];
    	p1.sign = 'x';
    	p2.sign = 'o';
    	strncpy(str, string+6, sizeof(str));	
    	struct Node* head = NULL;
	    for(int i=0;i<boardSize;i++){
	    	for(int j=0;j<boardSize;j++){
	    		struct Coord* c = malloc(sizeof(struct Coord));
	    		c->x = i;
	    		c->y = j;
	    		push(&head, c);
	    	}
	    }
	    for(int k=0;k<boardSize*boardSize;k++){
	    	int x = str[k*6] - '0';
	    	int y = str[k*6+2] - '0';
	    	int error = changeStateNode(head,str[k*6+4],x,y);
	    	if(error == 1){
		    	printf("Error\n");
		    }
	    }
	    printf("Game number %d:\n",count);
	    printBoard(head);
	    count++;
       
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */
    printf("Which game do you want to replay?\n");
    int nb;
    char param;
    cleanStd();
	scanf(" %c",&param);
	if(isdigit(param) && (param-'0')<=line_count){
		nb = param - '0';
	}else{
		while(true){
			printf("Which game do you want to replay?\n");
			cleanStd();
			scanf(" %c",&param);
			if(isdigit(param) && (param-'0')<=line_count){
				nb = param - '0';
				break;
			}
		}
	}
	int cpt = 1;
	fclose(file);

	file = fopen(fileName, "r");
	while(fgets(line, sizeof(line), file)){
		if(cpt == nb){
			int i = 0;
	    	//IMPORTANT check if line[3] == ';' to be sure if it's a new line.

	    	while(line[i] != '\n'){
	    		i++;
	    	}
	    	changeBoardSize(line[4] - '0');
	    	char string[i-2];
	    	int k = 0;
	    	while(line[k] != '\n'){
	    		string[k] = line[k];
	    		k++;
	    	}
	    	char str[i-2];
	    	strncpy(str, string+6, sizeof(str));	
		    for(int k=0;k<boardSize*boardSize;k++){
		    	int x = str[k*6] - '0';
		    	int y = str[k*6+2] - '0';
		    	int error = changeStateNode(node,str[k*6+4],x,y);
		    	if(error == 1){
			    	printf("Error\n");
			    }
		    }
		    break;
		}
		cpt++;
	}
    fclose(file);
}

void saveData(struct Node* node, char name1[50], char name2[50]){
	if(!firstSaving){
		printf("seconde saving");
		saveDuringGame();
		
	}else{
		firstSaving = !firstSaving;
	}
	FILE* file = fopen(fileName, "a+");
	struct Node* last;
	fprintf(file,"%s %s %d;",name1, name2,boardSize);
    while (node != NULL) {  
    	fprintf(file,"%d %d %c;",node->coord->x,node->coord->y,node->data);
    	/*putc((int)node->coord->y,file);
    	putc((int)node->data,file);*/
        last = node;  
        node = node->next;  
    }   
    while (last != NULL) {  
        last = last->prev;  
    }
    fprintf(file,"\n");
	fclose(file);
}

void playMove(struct Node* head, struct Player p1, struct Player p2){
    bool cpt = false; //false for p1, true for p2
    while(true){


    	char answer;
		printf("Do you want to save the current game ? Yes(y) or No(n)");
		cleanStd();
		scanf(" %c",&answer);
		if(answer == 'y' || answer == 'Y'){
			saveData(head,p1.name,p2.name);

		}

    	if(checkWin(head,p1) == 1 || checkWin(head,p1) == 2 || fullBoard(head)){
    		break;
    	}
    	struct Player p;
    	if(!cpt){
    		p = p1;
    	}else{
    		p = p2;
    	}
    	int error = 0;
	    error = makeMove(head,p);
	    if(error ==1){
	    	do{
	    		printf("Move uncorrect, please retry.\n");
	    	error = makeMove(head,p);
	    	}while(error == 1);
	    }
	   
	    printBoard(head);

	  	cpt = !cpt;
    }

    if(checkWin(head,p1) == 1){
    	printWinner(p1.name,p1.sign);
    }else if(checkWin(head,p1) == 2){
    	printWinner(p2.name,p2.sign);
    }else{
    	printWinner('\0','\0');
    }

}

void playGame(struct Node* head, bool b, struct Player p1, struct Player p2){
	if(!b){
		printf("Enter Player 1 name:\n");
		cleanStd();
		scanf(" %s",p1.name);
		
		printf("Play with the cross (1) or the nought (2) ?\n");
		char c;
		cleanStd();
		scanf(" %c",&c);
		if(c == '1'){
			p1.sign='x';
			p2.sign='o';
		}else if(c == '2'){
			p1.sign='o';
			p2.sign='x';
		}else{
			printf("Something went wrong, please retry.\n");
			while(true){
				printf("Play with the cross (1) or the nought (2) ?\n");
				char c;
				cleanStd();
				scanf(" %c",&c);
				if(c == '1'){
					p1.sign='x';
					p2.sign='o';
					break;
				}else if(c == '2'){
					p1.sign='o';
					p2.sign='x';
					break;
				}else{
					printf("Something went wrong, please retry.\n");
				}
			}
		}
		
		
		printf("Enter Player 2 name:\n");
		cleanStd();
		scanf(" %s",p2.name);
	}
	

    printf("%s:%c - %s:%c \n",p1.name,p1.sign,p2.name,p2.sign);

    /*printf(" -----------\n");
    printf("| "RED"x"RESET" | x | x |\n");
    printf(" -----------\n");
    printf("| x | x | x |\n");
    printf(" -----------\n");
    printf("| x | x | x |\n");
    printf(" -----------\n");*/


    /* Initialization */
    printBoard(head);
    playMove(head,p1,p2);
    saveData(head,p1.name,p2.name);
}



int main()
{
	
    /*for(int i=0;i<boardSize;i++){
    	for(int j=0;j<boardSize;j++){
    		struct Coord* c = malloc(sizeof(struct Coord));
    		c->x = i;
    		c->y = j;
    		push(&head, c);
    	}
    }*/
	struct Node* head = initialization();
	Player p1;
	Player p2;
	/*printBoard(head);*/
	while(true){
		printf("Welcome to the Tic Tac Toe Game.\nTo start the game please press (S). To replay a game, please press (R). To change the parameters, please press (P).\n");
		char first;
		cleanStd();
		scanf(" %c",&first);
		if(first == 'P' || first == 'p'){
			changeParam();
		}else if(first == 'S' || first == 's'){
			playGame(head,false,p1,p2);
		}else if(first == 'R' || first == 'r'){
			readData(head,p1,p2);
			playGame(head,true,p1,p2);
		}else{
			printf("Something went wrong, please retry.\n");
		}
	}
    return 0;
}

