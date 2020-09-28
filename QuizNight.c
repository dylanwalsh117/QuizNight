#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char *question;
	char *answer;
	char *status;
};

// get shuffled indexes
int getIndex(int * indexes, int size,int length) {
	int index = 0;
	int isMatched = 0;
	do {
		index = (rand() % length);
		for (int i = 0; i < size; i++) {
			if (indexes[i] == index) {
				isMatched = 1;
				break;
			}
		}
		if (isMatched == 0) {
			break;
		}
		else {
			isMatched = 0;
		}
	} while (1);
	indexes[size] = index;
	return index;
}

//

char* getInput() {
	char answer[100];
	do {
		fgets(answer, sizeof(answer), stdin);
		if (answer != "\n") {
			break;
		}
	} while (1);
	return answer;
}

// asks quiz questions
int askQuestion(int difficulty, struct Node quiz[],int totalQuestions) {
	int correct = 0;
	int* quizIndexes = malloc(sizeof(int) * totalQuestions);
	for (int i = 0; i < totalQuestions; i++) {
		int quizIndex = getIndex(quizIndexes,i,totalQuestions);
		char* currAnswer;
		if (difficulty == 1) {
			printf("%s?\n", quiz[quizIndex].question);
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer,_strlwr(strtok(currAnswer,"\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct+1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		else if (difficulty == 2) {
			printf("%s?\n", quiz[quizIndex].question);
			for (int j = 0; j < strlen(quiz[quizIndex].answer);j++) {
					printf("_ ");
				
			}
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct+1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		else if (difficulty == 3) {
			printf("%s?\n", quiz[quizIndex].question);
			for (int j = 0; j < strlen(quiz[quizIndex].answer); j++) {
				if (j == 0 || j == strlen(quiz[quizIndex].answer) - 1) {
					printf("%c ", quiz[quizIndex].answer[j]);
				}
				else {
					printf("_ ");
				}
			}
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct+1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		else if (difficulty == 4) {
			printf("%s?\n", quiz[quizIndex].question);
			int firstLetter = rand() % strlen(quiz[quizIndex].answer);
			int secondLetter = 0;
			do {
				secondLetter = rand() % strlen(quiz[quizIndex].answer);
			} while (secondLetter == firstLetter);
			for (int j = 0; j < strlen(quiz[quizIndex].answer); j++) {
				if (j == firstLetter || j == secondLetter) {
					printf("%c ", quiz[quizIndex].answer[j]);
				}
				else {
					printf("_ ");
				}
			}
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct+1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		else if (difficulty == 5) {
			printf("%s?\n", quiz[quizIndex].question);
			int* usedIndexes = malloc(sizeof(int) * strlen(quiz[quizIndex].answer));
			for (int j = 0; j < strlen(quiz[quizIndex].answer); j++) {
				int index = getIndex(usedIndexes, j,strlen(quiz[quizIndex].answer));
				printf("%c ", quiz[quizIndex].answer[index]);
			}
			free(usedIndexes);
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct + 1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		printf("Current Score IS: %d/%d\n", correct, totalQuestions);
	}
	free(quizIndexes);
	return correct;
}

// gets total number of questions
int getCount(char* fileName) {
	FILE* in_file;
	fopen_s(&in_file,fileName, "r");
	int count = 0;
	if (in_file == NULL) 
		return  -1;
	

	while (1)
	{
		char currQuestion[100];
		if (fscanf(in_file, "%[^\?]", currQuestion) != -1) {
			if (fscanf(in_file, "%[^\n]", currQuestion) != -1) {
				count++;
			}
		}
		else {
			break;
		}
		
	}
	return count;
}

// add questions to quiz array
void addQuestion(char* fileName, struct Node* quiz) {
	FILE* in_file;
	fopen_s(&in_file, fileName, "r");
	if (in_file == NULL)
		return  -1;

	int i = 0;
	while (1)
	{
		char* currQuestion = malloc(sizeof(char)*100);
		char* currAnswer = malloc(sizeof(char)*100);
		if (fscanf(in_file, "%[^\?]", currQuestion) != -1) {
			if (fscanf(in_file, "%[^\n]", currAnswer) != -1) {
				quiz[i].question = currQuestion;
				quiz[i].answer = strtok(currAnswer, "?");
				quiz[i].answer = _strlwr(strtok(quiz[i].answer, " "));
				quiz[i].status = "";
				i++;
			}
		}
		else {
			free(currQuestion);
			free(currAnswer);
			break;
		}

	}
}

// print incorrect answer
void print(struct Node* quiz,int totalQuestions) {
	printf("Here are correct answers to your wrong questions.\n");
	for (int i = 0; i < totalQuestions; i++) {
		if (strcmp(quiz[i].status,"incorrect") == 0) {
			printf("%s?\n", quiz[i].question);
			printf("%s\n", quiz[i].answer);
		}
	}
}

char getChoice() {
	char choice = ' ';
	do {
		printf("do you wnat to see correct answers of your wrong answers?\n");
		int val = scanf("%c", &choice);
		if (choice == 'y' || choice == 'Y' || choice == 'N' || choice == 'n') {
			break;
		}
		else {
			printf("invalid choice valid choices are['y' or 'n']\n");
		}
		while (getchar() != '\n');
	} while (1);
	return choice;
}

int main(int argc, char*argv[]) {
	
	srand(time(NULL));
	if (argc != 3) {
		printf("Please provide all parameters. FILE NAME DIFFICULTY LEVEL");
		return 0;
	}
	else {
		struct Node* quiz;
		int totalQuestions = 0;
		int difficulty = atoi(argv[2]);
		if (difficulty < 0 || difficulty > 6) {
			printf("Invalid difficulty level must be >= 1 and  <=6 ");
			return;
		}
		totalQuestions = getCount(argv[1]);
		if (totalQuestions == -1) {
			printf("file can't be read,check file name again.\n");
			return;
		}
		else if (totalQuestions == 0) {
			printf("file has no data.\n");
			return;
		}
		else if(totalQuestions >=1){
			quiz = malloc(sizeof(struct Node) * totalQuestions);
			addQuestion(argv[1], quiz);
			if (difficulty == 6) {
				difficulty = (rand() % 5) + 1;
			}
			int correct = askQuestion(difficulty,quiz,totalQuestions);
			if (correct != totalQuestions) {
				char choice = getChoice();
				if(choice == 'y' || choice == 'Y')
					print(quiz,totalQuestions);
			}
			free(quiz);
		}
		
	}
	return 0;
}c ", quiz[quizIndex].answer[j]);
				}
				else {
					printf("_ ");
				}
			}
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct+1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		else if (difficulty == 5) {
			printf("%s?\n", quiz[quizIndex].question);
			int* usedIndexes = malloc(sizeof(int) * strlen(quiz[quizIndex].answer));
			for (int j = 0; j < strlen(quiz[quizIndex].answer); j++) {
				int index = getIndex(usedIndexes, j,strlen(quiz[quizIndex].answer));
				printf("%c ", quiz[quizIndex].answer[index]);
			}
			free(usedIndexes);
			printf("\n");
			currAnswer = getInput();
			if (strcmp(quiz[quizIndex].answer, _strlwr(strtok(currAnswer, "\n"))) == 0) {
				printf("Correct Answer.\n");
				quiz[i].status = "correct";
				correct = correct + 1;
			}
			else {
				printf("Wrong Answer.\n");
				quiz[i].status = "incorrect";
			}
		}
		printf("Current Score IS: %d/%d\n", correct, totalQuestions);
	}
