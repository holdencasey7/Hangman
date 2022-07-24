/* To-do list
 * TODO: cap incorrect guesses
 * TODO: make file an array of words
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define MAXSIZE 10
#define NUMLINES 11

int main() {
    //Creates reference to wordbank.txt file
    char *pathname;
    pathname = malloc(sizeof(char) * 200);
    if (pathname == NULL) {
        perror("Memory error");
        exit(1);
    }
    getcwd(pathname, 200);
    strcat(pathname, "/wordbank.txt");
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
    if (answer == NULL) {
        perror("Memory error");
        exit(1);
    }
    for (int i = 0; i < wordlength; i++) {
        strcat(answer, "_");
    }
    printf("%s (%d letters)\n", answer, wordlength);

    //Store guesses
    char *guesses;
    guesses = malloc(sizeof(char) * 30);
    if (guesses == NULL) {
        perror("Memory error");
        exit(1);
    }

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
        int guessed = 0;
        //Check if previously guessed
        for(int i = 0; i < guesscount; i++) {
            if (guesses[i] == guess) {
                printf("You already guessed %c.\n", guess);
                guessed = 1;
            }
        }
        //Only count towards a guess if not already guessed
        if (guessed == 0) {
            guesses[guesscount] = guess;
            for (int i = 0; i < wordlength; i++) {
                if (word[i] == guess) {
                    answer[i] = guess;
                    correct++;
                }
            }
            guesscount++;
            printf("%s\n", answer);
        }
        //Display guessed letters
        printf("Guessed letters: %s\n", guesses);
    }

    //End of game
    printf("Congratulations! You guessed %s with %d incorrect guess%s!\n",
           word, guesscount - correct, guesscount - correct == 1 ? "" : "es");
    fclose(fp);
    return 0;
}