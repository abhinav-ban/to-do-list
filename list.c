#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 100
#define FILENAME "todolist.txt"

void addTask(char tasks[MAX_TASKS][TASK_LENGTH], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }
    printf("Enter the task: ");
    getchar(); // To consume the newline character left by previous input
    fgets(tasks[*taskCount], TASK_LENGTH, stdin);
    tasks[*taskCount][strcspn(tasks[*taskCount], "\n")] = '\0'; // Remove newline
    (*taskCount)++;
    printf("Thanks for adding your task\n");
}

void removeTask(char tasks[MAX_TASKS][TASK_LENGTH], int *taskCount) {
    if (*taskCount == 0) {
        printf("oops! you have non tsks to remove.\n");
        return;
    }
    printf("Enter Task No. to remove (1 to %d): ", *taskCount);
    int taskNum;
    scanf("%d", &taskNum);
    if (taskNum < 1 || taskNum > *taskCount) {
        printf("Your task no. is invalid\n");
        return;
    }
    for (int i = taskNum - 1; i < *taskCount - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }
    (*taskCount)--;
    printf("Task removed!\n");
}

void viewTasks(char tasks[MAX_TASKS][TASK_LENGTH], int taskCount) {
    if (taskCount == 0) {
        printf("Sorry no tasks are avaialable\n");
        return;
    }
    printf("To-Do List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d: %s\n", i + 1, tasks[i]);
    }
}

void saveTasks(char tasks[MAX_TASKS][TASK_LENGTH], int taskCount) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving tasks!\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i]);
    }
    fclose(file);
    printf("Tasks saved!\n");
}

void loadTasks(char tasks[MAX_TASKS][TASK_LENGTH], int *taskCount) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No saved tasks found!\n");
        return;
    }
    while (fgets(tasks[*taskCount], TASK_LENGTH, file) != NULL && *taskCount < MAX_TASKS) {
        tasks[*taskCount][strcspn(tasks[*taskCount], "\n")] = '\0'; // Remove newline
        (*taskCount)++;
    }
    fclose(file);
    printf("Tasks loaded!\n");
}

int main() {
    char tasks[MAX_TASKS][TASK_LENGTH];
    int taskCount = 0;
    int choice;

    loadTasks(tasks, &taskCount);

    while (1) {
        printf("\n1. Adding Tasks\n2. Removing Tasks\n3. Viewing Tasks\n4. To Save Tasks\n5. Exit\n");
        printf("Enter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                removeTask(tasks, &taskCount);
                break;
            case 3:
                viewTasks(tasks, taskCount);
                break;
            case 4:
                saveTasks(tasks, taskCount);
                break;
            case 5:
                saveTasks(tasks, taskCount); // Save before exit
                printf("Exiting....\n");
                return 0;
            default:
                printf("Invalid choice! try again later\n");
        }
    }

    return 0;
}
