#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAXSIZE 10
#define NUMLINES 11

int main() {
    //Creates reference to wordbank.txt file
    static const char *pathname = "/Users/holdencasey/Documents/Coding Practice/Hangman/wordbank.txt";
    FILE *fp = fopen(pathname, "r");
    if (fp == NULL) {
        perror("Could not open wordbank file");
        exit(1);
    }

    //Creates string for current word
    char *word;
    word = malloc(sizeof(char) * MAXSIZE);
    if (word == NULL) {
        perror("Memory error");
        exit(1);
    }

    //Choose random line
    srand((unsigned)time(NULL));
    int linenum = rand() % NUMLINES;

    //Get word at line
    int linecount = 0;
    while (fgets(word, MAXSIZE, fp) != NULL) {
        if (linecount == linenum) {
            break;
        }
        linecount++;
    }
    strtok(word, "\n");
    int wordlength = strlen(word);

    //Put spaces for letters
    char *answer;
    answer = malloc(sizeof(char) * MAXSIZE);
    for (int i = 0; i < wordlength; i++) {
        strcat(answer, "_");
    }
    printf("%s (%d letters)\n", answer, wordlength);

    //Guessing logic
    char guess;
    int correct = 0;
    int guesscount = 0;
    while (correct != wordlength) {
        //Take in guess
        printf("Enter a character to guess: ");
        guess = getchar();
        fflush(stdin);
        guess = toupper(guess);
        for (int i = 0; i < wordlength; i++) {
            if (word[i] == guess) {
                answer[i] = guess;
                correct++;
            }
        }
        guesscount++;
        printf("%s\n", answer);
    }

    //End of game
    printf("Congratulations! You guessed %s in %d guesses!\n", word, guesscount);
    fclose(fp);
    return 0;
}