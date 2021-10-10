#include<stdio.h>
#include<string.h>

/******************
* Function Name:changeStr
* Input:char board[],char str[]
* Output:return 0 or 1 (true or false)
* Function Operation:check if a string can be a soduko .
******************/
int changeStr(char board[][SIZE*SIZE],char str[]) {
	int counter = 0;
	int dashCounter = 0;
	char changedStr[(SIZE * SIZE * SIZE * SIZE) + (SIZE * SIZE)];
	//looping through the string and making a new one
	if (SIZE==3){	
		for (int indexCounter = 0; indexCounter < strlen(str); indexCounter++) {
			if (counter >= (SIZE * SIZE * SIZE * SIZE) + (SIZE * SIZE) - 1) {
				return 0;
			}
			//search for next row
			else if (str[indexCounter] == '/') {
				changedStr[counter] = str[indexCounter];
				dashCounter++;
				counter++;
			}
			//if the number is between 1-9
			else if ((str[indexCounter] <= '9') &&
				(str[indexCounter] >= '1')) {
				changedStr[counter] = str[indexCounter];
				counter++;
			}
			//if there is a letter between a-i fill spaces as needed
			else if ((str[indexCounter] <= 'i') &&
				(str[indexCounter] >= 'a')) {
				for (int fillSpeaces = 0; fillSpeaces < (str[indexCounter] + 1 - 'a'); fillSpeaces++) {
					changedStr[counter] = ' ';
					counter++;
				}
			}
			else {
				return 0;
			}
		}
	}
	else if (SIZE == 2) {
		for (int indexCounter = 0; indexCounter < strlen(str); indexCounter++) {
			if (counter >= (SIZE * SIZE * SIZE * SIZE) + (SIZE * SIZE) - 1) {
				return 0;
			}
			//search for next row
			else if (str[indexCounter] == '/') {
				changedStr[counter] = str[indexCounter];
				dashCounter++;
				counter++;
			}
			//if the number is between 1-9
			else if ((str[indexCounter] <= '4') &&
				(str[indexCounter] >= '1')) {
				changedStr[counter] = str[indexCounter];
				counter++;
			}
			//if there is a letter between a-i fill spaces as needed
			else if ((str[indexCounter] <= 'd') &&
				(str[indexCounter] >= 'a')) {
				for (int fillSpeaces = 0; fillSpeaces < (str[indexCounter] + 1 - 'a'); fillSpeaces++) {
					changedStr[counter] = ' ';
					counter++;
				}
			}
			else {
				return 0;
			}
		}
	}
	//if every thing works so far make the board
	if (dashCounter==SIZE*SIZE -1){
		changedStr[counter] = '/';
		int nineCounter = 0;
		counter = 0;
		int col = 0;
		int row = 0;
		//make the board
		while (counter < (SIZE * SIZE * SIZE * SIZE) + (SIZE * SIZE)) {
			if (changedStr[counter] == '/') {
				while (nineCounter < SIZE * SIZE) {
					board[row][col] = ' ';
					col++;
					nineCounter++;
				}
				col = 0;
				nineCounter = 0;
				row++;
			}
			else {
				board[row][col] = changedStr[counter];
				col++;
				nineCounter++;
			}
			counter++;
		}
	}
	else
	{
		return 0;
	}
}
/******************
* Function Name:create board
* Input:char board[],char str[]
* Output:no out pot only print
* Function Operation:make a string soduko if possible.
******************/
void createBoard(char board[][SIZE * SIZE], char str[]) {
	if (SIZE == 1 &&
		strlen(str) <= 1) {
		if (str[0] == ' ' ||
			str[0] == 'a' ||
			str[0] == "") {
			board[0][0] = ' ';
		}
		else if (str[0] == '1') {
			board[0][0] = '1';
		}
		else {
			printf("Error\n");
		}
	}
	else if(changeStr(board,str)==0){
		printf("Error\n");
	}
}
/******************
* Function Name:print board
* Input:char board[]
* Output:no out pot only print
* Function Operation:print board
******************/
void printBoard(char board[][SIZE * SIZE]){
	int col = 0;
	int row = 0;
	while (row < SIZE * SIZE)
	{
		if (col == SIZE * SIZE)	{
			col = 0;
			row++;
			printf("\n");
			if (row % SIZE == 0 &&
				row <= SIZE* SIZE) {
				printf("\n");
			}
		}
		if (col % SIZE == 0 &&
			col > 0) {
			printf(" | ");
		}
		if (col != SIZE * SIZE && row != SIZE * SIZE) {
			printf("%c", board[row][col]);
		}
		col = col++;
	}
}
/******************
* Function Name:betweenOneOrNine
* Input:char board[]
* Output:return 0 or 1 (true or false)
* Function Operation:check if all items on board are numbers
******************/
int betweenOneOrNine(char board[][SIZE * SIZE]) {
	int row = 0;
	int col = 0;
	for (int col = 0; col < SIZE * SIZE; col++) {
		for (int row = 0; row < (SIZE * SIZE); row++) {
			if (SIZE == 1) {
				if (board[row][col] != 1 &&
					board[row][col] != ' ') {
					return 0;
				}
			}
			else if (SIZE == 2) {
				if ((board[row][col] < '1' ||
					board[row][col] > '4') &&
					board[row][col] != ' ') {
					return 0;
				}
			}
			else if (SIZE == 3) {
				if ((board[row][col] < '1' ||
					board[row][col] > '9') &&
					board[row][col] != ' ') {
					return 0;
				}
			}
		}
	}
	return 1;
}
/******************
* Function Name:testCols
* Input:char board[]
* Output::return 0 or 1 (true or false)
* Function Operation:check if cols are in soduko rules.
******************/
int testCols(char board[][SIZE * SIZE]) {
	for (int col = 0; col < SIZE * SIZE; col++) {
		for (int row = 0; row < (SIZE * SIZE) - 1; row++) {
			for (int row2 = row + 1; row2 < SIZE * SIZE; row2++) {
				if (board[row][col] == board[row2][col] &&
					board[row][col] != ' '){
					return 0;
				}
			}
		}
	}
	return 1;
}
/******************
* Function Name:testSquares
* Input:char board[]
* Output::return 0 or 1 (true or false)
* Function Operation:check if squares are in soduko rules.
******************/
int testSquares(char board[][SIZE * SIZE], int startCol, int startRow) {
	int dimantionFix = 0;
	char oneDimantion[SIZE * SIZE];
	for (int col = 0; col < SIZE; col++) {
		for (int row = 0; row < SIZE; row++) {		
			oneDimantion[col + row + dimantionFix] = board[row + startRow][col + startCol];
		}
		dimantionFix = dimantionFix + SIZE-1;
	}
	for (int col = 0; col < (SIZE * SIZE) - 1; col++) {
		for (int col2 = col + 1; col2 < (SIZE * SIZE); col2++) {
			if (oneDimantion[col] == oneDimantion[col2] &&
				oneDimantion[col] != ' ') {
				return 0;
			}
		}
	}
	return 1;
}
/******************
* Function Name:testRows
* Input:char board[]
* Output::return 0 or 1 (true or false)
* Function Operation:check if rows are in soduko rules.
******************/
int testRows(char board[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE * SIZE; row++) {
		for (int col = 0; col < (SIZE * SIZE) - 1; col++) {
			for (int col2 = col + 1; col2 < SIZE * SIZE; col2++) {
				if (board[row][col] == board[row][col2] &&
					board[row][col] != ' ') {
					return 0;
				}
			}
		}
	}
	return 1;
}
/******************
* Function Name:testBoard
* Input:char board[]
* Output::return 0 or 1 (true or false)
* Function Operation:check if board are in soduko rules
******************/
int testBoard(char board[][SIZE * SIZE]) {
	//check rows
	if (testRows(board) == 0){
		return 0;
	}
	//check cols
	if (testCols(board) == 0){
		return 0;
	}
	//check 1-9
	if (betweenOneOrNine(board) == 0) {
		return 0;
	}
	//check squares
	for (int col = 0; col < SIZE * SIZE; col= col + SIZE) {
		for (int row = 0; row < (SIZE * SIZE); row= row + SIZE) {
			if (testSquares(board, col, row) == 0) {
				return 0;
			}
		}
	}
	return 1;
}
/******************
* Function Name:isSameBoard
* Input:char board[]
* Output::return 0 or 1 (true or false)
* Function Operation:check if board 2 boards are the same.
******************/
int isSameBoard(char board[][SIZE * SIZE], char board1[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE*SIZE;row++){
		for (int col = 0; col < SIZE * SIZE; col++) {
			if (board[row][col] != board1[row][col]) {
				printf("Found inequality on row %d col %d.\n", row, col);
				return 0;
			}
		}
	}
	return 1;
}

/******************
* Function Name:checkTwoDigit
* Input:char *token
* Output:return 0 or 1 (true or false)
* Function Operation:return 0-9 if token is between 0-9
******************/
int checkTwoDigit(char* token) {
	token = strtok(NULL, ",");
	if (SIZE==1){
		if (*token=='0'){
			return *token;
		}
		return 0;
	}
	else if (SIZE== 2){
		if (*token >= '0' &&
			*token <= '4') {
			return *token;
		}
		return 0;
	}
	else if (SIZE == 3){
		if (*token >= '0' &&
			*token <= '9') {
			return *token;
		}
		return 0;
	}
}
/******************
* Function Name:replaceAll
* Input:char board[],char *token
* Output:no output only print
* Function Operation:replace all chars with given char
******************/
void replaceAll(char board[][SIZE * SIZE], char* token) {
	int exists = 0;
	token = strtok(NULL, ",");
	if (strcmp(token, " ") != 0 &&
		strcmp(token, "\n") != 0) {
		char searchChar = *token;
		token = strtok(NULL, ",");
		int row = 0;
		int col = 0;
		for (int col = 0; col < SIZE * SIZE; col++) {
			for (int row = 0; row < (SIZE * SIZE); row++) {
				if (board[row][col]==searchChar){
					board[row][col] = *token;
					exists++;
				}
			}
		}	
	}
	if(exists==0){
		return printf("Error\n");
	}
}
/******************
* Function Name:change
* Input:char board[],char *token
* Output:no output only print
* Function Operation:change char in given row,col
******************/
void change(char board[][SIZE * SIZE], char* token) {
	int row = checkTwoDigit(token);
	if (row != 0) {
		int col = checkTwoDigit(token);
		if (col != 0) {
			token = strtok(NULL, ",");
			if (board[row - '0'][col - '0'] == ' ') {
				return printf("Error\n");
			}
			else{
				board[row - '0'][col - '0'] = *token;
			}
		}
	}
}
/******************
* Function Name:add
* Input:char board[],char *token
* Output:no output only print
* Function Operation:add char in given row,col
******************/
void add(char board[][SIZE * SIZE], char* token) {
	int row = checkTwoDigit(token);
	if (row != 0) {
		int col = checkTwoDigit(token);
		if (col != 0) {
			if (board[row - '0'][col - '0'] == ' ') {
				token = strtok(NULL, ",");
				board[row - '0'][col - '0'] = *token;
			}
			else{
				return printf("Error\n");
			}
		}
	}
}
/******************
* Function Name:delete
* Input:char board[],char *token
* Output:no output only print
* Function Operation:delete char in given row,col
******************/
void delete(char board[][SIZE * SIZE],char *token) {
	int row = checkTwoDigit(token);
	if (row != 0) {
		int col = checkTwoDigit(token);
		if (col != 0) {
			if (board[row - '0'][col - '0'] == ' ') {
				return printf("Error\n");
			}
			else {
				token = strtok(NULL, ",");
				board[row - '0'][col - '0'] = ' ';
			}
		}
	}
}
/******************
* Function Name:makeMove
* Input:char board[],char *token
* Output:no output only print
* Function Operation:make one of the 4 move delete,replaceAll,change,add
******************/
void makeMove(char board[][SIZE * SIZE], char move[]) {
	int makeMove = 0;
	int lengthofarray = strlen(move);
	char* token = strtok(move, ",");
	if (strcmp(token, "replaceAll") == 0 &&
		lengthofarray == 14) {
		replaceAll(board, token);
		
	}
	else if (strcmp(token, "change") == 0 &&
		lengthofarray == 12) {
		change(board, token);
	}
	else if (strcmp(token, "add") == 0 &&
		lengthofarray == 9){
		add(board, token);
	}
	else if (strcmp(token,"delete") == 0 &&
	lengthofarray == 10) {
		delete(board, token);
	}
	else{
		printf("Error\n");
	}
}
/******************
* Function Name:completeBoard
* Input:char board[]
* Output:no output only print
* Function Operation:solve the board if it is almost solved.
******************/
void completeBoard(char board[][SIZE * SIZE]) {
	if (SIZE == 1)
	{
		if (board[0][0] == ' ' ) {
			board[0][0] = '1';
		}
		
		else {
			printf("Error\n");
		}
	}
	else if (betweenOneOrNine(board) == 1) {
		int sumRows[SIZE * SIZE];
		int sumCols[SIZE * SIZE];
		int toTest = 0;
		int spaces = 0;
		for (int row = 0; row < SIZE * SIZE; row++) {
			int rowsum = 0;
			int colsum = 0;
			for (int col = 0; col < SIZE * SIZE; col++) {
				if (board[row][col] != ' ') {
					rowsum = rowsum + board[row][col] - '0';
				}
				if (board[col][row] != ' ') {
					colsum = colsum + board[col][row] - '0';
				} 
			}
			if (SIZE == 3) {
				sumRows[row] = 45 - rowsum;
				sumCols[row] = 45 - colsum;
			}
			if (SIZE == 2) {
				sumRows[row] = 10 - rowsum;
				sumCols[row] = 10 - colsum;
			}
		}
		char board1[SIZE * SIZE][SIZE * SIZE];
		for (int row = 0; row < SIZE * SIZE; row++) {
			for (int col = 0; col < SIZE * SIZE; col++) {
				board1[row][col] = board[row][col];
				if (board[row][col] == ' ' &&
					sumCols[col]==sumRows[row]){
					board1[row][col] = sumRows[row] + '0' ;
					toTest++;
				}
				if (board[row][col] == ' '){
					spaces++;
				}
			}
		}
		if (testBoard(board1) == 1 &&
			toTest > 0) {
			for (int row = 0; row < SIZE * SIZE; row++) {
				for (int col = 0; col < SIZE * SIZE; col++) {
					if (board[row][col] == ' ') {
						board[row][col] = sumRows[row] + '0';
					}
				}
			}
		}
		else if (spaces > 0) {
			printf("Error");
		}
	}
	else {
		printf("Error");
	}
}







