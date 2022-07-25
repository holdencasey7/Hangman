/* To-do list
 * TODO: cap incorrect guesses
 * TODO: differentiate incorrect letters when showing guessed letters
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAXWORDSIZE 10
#define NUMWORDS 43

int main() {
    //Wordbank array
    char wordbank[NUMWORDS][MAXWORDSIZE] = {
            "APPLE",
            "APE",
            "ALE",
            "AIRPORT",
            "AWESOME",
            "ANTE",
            "ANT",
            "BALL",
            "BOWL",
            "BLOW",
            "BEACH",
            "BEND",
            "CARROT",
            "CATCH",
            "CITY",
            "COOLER",
            "DIRTY",
            "DIMENSION",
            "DOUBLE",
            "DITCH",
            "EGGPLANT",
            "EAGLE",
            "EGG",
            "FORT",
            "FAST",
            "FAIR",
            "FETCH",
            "FIGHTER",
            "FOLLOW",
            "GOOD",
            "GUARDIAN",
            "GUESS",
            "ZEBRA",
            "ZOO",
            "YELLOW",
            "YES",
            "WELL",
            "WILT",
            "QUANTITY",
            "QUILT",
            "CAKE",
            "POOL",
            "LOOP"
    };

    //Creates string for current word
    char *word;
    word = malloc(sizeof(char) * MAXWORDSIZE);
    if (word == NULL) {
        perror("Memory error");
        exit(1);
    }

    //Choose random word
    srand((unsigned)time(NULL));
    int wordnum = rand() % NUMWORDS;
    strcpy(word, wordbank[wordnum]);
    int wordlength = strlen(word);

    //Put spaces for letters
    char *answer;
    answer = malloc(sizeof(char) * MAXWORDSIZE);
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
    int correctguesses = 0;
    int correctletters = 0;
    int correct = 0;
    int guesscount = 0;
    while (correctletters != wordlength) {
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
                    correct = 1;
                    correctletters++;
                }
            }
            if (correct == 1) {
                correct = 0;
                correctguesses++;
            }
            guesscount++;
            printf("%s\n", answer);
        }
        //Display guessed letters
        printf("Guessed letters: %s\n", guesses);
    }

    //End of game
    printf("Congratulations! You guessed %s with %d incorrect guess%s!\n",
           word, guesscount - correctguesses, guesscount - correctguesses == 1 ? "" : "es");
    return 0;
}
