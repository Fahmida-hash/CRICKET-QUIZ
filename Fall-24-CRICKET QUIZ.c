#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
typedef struct Question {
    char question[256];
    char options[3][100];
    char correctOption;
} Question;

typedef struct Player {
    char name[30];
    int score;
} Player;
void addQuestion(Question questions[], int index);
void updateQuestion(Question questions[], int index);
void deleteQuestion(Question questions[], int index);
int askQuestion(Question q, int difficulty);
void displayWelcomeScreen();
void shuffleQuestions(Question questions[], int size);
void showProgressBar(int currentQuestion, int totalQuestions);
void levelUp(int correctAnswers);
void displayLeaderboard(Player players[], int size);
void playGame(Player *player, Question questions[], int totalQuestions);
int main() {
    uint8_t point = 0;
    char name[30];
    int choice;
    int questionIndex;
    int difficulty = 1; 
    Player players[10];
    int playerCount = 0;
    displayWelcomeScreen();
    printf("\nEnter your name: ");
    scanf("%29s", name); 
    
    Player player;
    strcpy(player.name, name);
    player.score = 0;

    Question questions[20] = {
        {"Q1. Where was the ICC Cricket World Cup held in 2023?", {"India", "Australia", "England"}, '1'},
        {"Q2. Who scored the most runs in the ICC Cricket World Cup 2023?", {"Virat Kohli", "Rohit Sharma", "Quinton de Kock"}, '3'},
        {"Q3. Who took the most wickets in the ICC Cricket World Cup 2023?", {"Mitchell Starc", "Shaheen Afridi", "Adam Zampa"}, '3'},
        {"Q4. Who hit the most sixes in the ICC Cricket World Cup 2023?", {"Glenn Maxwell", "Rohit Sharma", "David Warner"}, '1'},
        {"Q5. Which team won the ICC Cricket World Cup 2023?", {"India", "Australia", "New Zealand"}, '1'},
        {"Q6. How many teams participated in the ICC Cricket World Cup 2023?", {"10", "12", "14"}, '1'},
        {"Q7. Who was the Player of the Tournament in the ICC Cricket World Cup 2023?", {"Virat Kohli", "Rohit Sharma", "Quinton de Kock"}, '1'},
        {"Q8. Which team scored the highest total in the ICC Cricket World Cup 2023?", {"India", "South Africa", "England"}, '2'},
        {"Q9. How many centuries were scored in the ICC Cricket World Cup 2023?", {"41", "36", "29"}, '2'},
        {"Q10. Where was the final match of the ICC Cricket World Cup 2023 held?", {"Ahmedabad", "Mumbai", "Delhi"}, '1'}
    };

    while (1) {
        printf("\nOptions:\n");
        printf("1. Add a new question\n");
        printf("2. Update an existing question\n");
        printf("3. Delete a question\n");
        printf("4. Start the quiz\n");
        printf("5. View leaderboard\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the index where you want to add the new question (0-19): ");
                scanf("%d", &questionIndex);
                if (questionIndex >= 0 && questionIndex < 20) {
                    addQuestion(questions, questionIndex);
                } else {
                    printf("Invalid index. Please enter an index between 0 and 19.\n");
                }
                break;

            case 2:
                printf("Enter the index of the question you want to update (0-19): ");
                scanf("%d", &questionIndex);
                if (questionIndex >= 0 && questionIndex < 20) {
                    updateQuestion(questions, questionIndex);
                } else {
                    printf("Invalid index. Please enter an index between 0 and 19.\n");
                }
                break;

            case 3:
                printf("Enter the index of the question you want to delete (0-19): ");
                scanf("%d", &questionIndex);
                if (questionIndex >= 0 && questionIndex < 20) {
                    deleteQuestion(questions, questionIndex);
                } else {
                    printf("Invalid index. Please enter an index between 0 and 19.\n");
                }
                break;

            case 4:
                printf("Select difficulty level:\n1. Easy\n2. Medium\n3. Hard\nEnter choice: ");
                scanf("%d", &difficulty);
                shuffleQuestions(questions, 10);  // Shuffle the questions before starting the quiz
                playGame(&player, questions, 10);
                printf("Well done %s! Your total points: %d\n", player.name, player.score);
                levelUp(player.score);
                players[playerCount] = player;
                playerCount++;
                break;

            case 5:
                displayLeaderboard(players, playerCount);
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }

    return 0;
}

void displayWelcomeScreen() {
    printf("\n\t#############################################\n");
    printf("\t#                                           #\n");
    printf("\t#          WELCOME TO THE QUIZ GAME         #\n");
    printf("\t#                                           #\n");
    printf("\t#            ICC CRICKET WORLD CUP          #\n");
    printf("\t#                2023 EDITION               #\n");
    printf("\t#############################################\n");
    printf("\n\tGet ready to test your knowledge about the ICC Cricket World Cup 2023!\n\n");
}

void addQuestion(Question questions[], int index) {
    Question newQuestion;

    printf("Enter the new question: ");
    getchar(); // Clear input buffer
    fgets(newQuestion.question, 256, stdin);
    newQuestion.question[strcspn(newQuestion.question, "\n")] = '\0'; // Remove trailing newline

    for (int i = 0; i < 3; i++) {
        printf("Enter option %d: ", i + 1);
        fgets(newQuestion.options[i], 100, stdin);
        newQuestion.options[i][strcspn(newQuestion.options[i], "\n")] = '\0'; // Remove trailing newline
    }

    printf("Enter the correct option (1/2/3): ");
    scanf(" %c", &newQuestion.correctOption);

    questions[index] = newQuestion;
    printf("Question added successfully!\n");
}

void updateQuestion(Question questions[], int index) {
    printf("Enter the updated question: ");
    getchar(); // Clear input buffer
    fgets(questions[index].question, 256, stdin);
    questions[index].question[strcspn(questions[index].question, "\n")] = '\0'; // Remove trailing newline

    for (int i = 0; i < 3; i++) {
        printf("Enter updated option %d: ", i + 1);
        fgets(questions[index].options[i], 100, stdin);
        questions[index].options[i][strcspn(questions[index].options[i], "\n")] = '\0'; // Remove trailing newline
    }

    printf("Enter the correct option (1/2/3): ");
    scanf(" %c", &questions[index].correctOption);

    printf("Question updated successfully!\n");
}

void deleteQuestion(Question questions[], int index) {
    memset(&questions[index], 0, sizeof(Question));
    printf("Question deleted successfully!\n");
}

int askQuestion(Question q, int difficulty) {
    char answer;
    printf("%s\n", q.question);
    for (int i = 0; i < 3; i++) {
        printf("%d) %s\n", i + 1, q.options[i]);
    }
    printf("Choose your answer: ");
    scanf(" %c", &answer);  // Fixed input issue

    if (answer == q.correctOption) {
        printf("Correct!\n");
        return difficulty == 3 ? 3 : difficulty == 2 ? 2 : 1;
    } else {
        printf("Wrong answer\n");
        return 0;
    }
}

void showProgressBar(int currentQuestion, int totalQuestions) {
    int progress = (currentQuestion * 100) / totalQuestions;
    printf("Progress: [");
    for (int i = 0; i < 50; i++) {
        if (i < progress / 2) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", progress);
}

void levelUp(int correctAnswers) {
    if (correctAnswers == 10) {
        printf("Congratulations! You've leveled up!\n");
    }
}

void displayLeaderboard(Player players[], int size) {
    printf("\nLeaderboard:\n");
    for (int i = 0; i < size; i++) {
        if (players[i].score > 0) {
            printf("%d. %s - %d points\n", i + 1, players[i].name, players[i].score);
        }
    }
}

void shuffleQuestions(Question questions[], int size) {
    srand(time(NULL));  // Seed the random number generator
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Generate a random index
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void playGame(Player *player, Question questions[], int totalQuestions) {
    int correctAnswers = 0;
    for (int i = 0; i < totalQuestions; i++) {
        showProgressBar(i + 1, totalQuestions);
        correctAnswers += askQuestion(questions[i], 1);  // Difficulty is passed here
        player->score = correctAnswers;
    }
}