#include <stdio.h>
#include <stdlib.h>

// Structure to represent each line node
struct LineNode {
    char *line;
    struct LineNode *next;
};

// Function to add a line to the end of the linked list
void addLine(struct LineNode **head, char *line) {
    struct LineNode *newNode = (struct LineNode *)malloc(sizeof(struct LineNode));
    newNode->line = line;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct LineNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the last n lines
void printLastNLines(struct LineNode *head, int n) {
    int numLines = 0;
    struct LineNode *current = head;

    // Count the number of lines in the linked list
    while (current != NULL) {
        numLines++;
        current = current->next;
    }

    // If n is greater than the number of lines, set n to the total number of lines
    if (n > numLines) {
        n = numLines;
    }

    // Move the 'current' pointer to the appropriate position to print the last n lines
    current = head;
    for (int i = 0; i < numLines - n; i++) {
        current = current->next;
    }

    // Print the last n lines
    while (current != NULL) {
        printf("%s", current->line);
        current = current->next;
    }
}

// Function to free the memory used by the linked list
void freeLinkedList(struct LineNode *head) {
    struct LineNode *current = head;
    while (current != NULL) {
        struct LineNode *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}

int main() {
    int n;
    printf("Enter the number of lines to display: ");
    scanf("%d", &n);
    
    // Clear the input buffer to avoid any issues with reading lines
    while (getchar() != '\n');

    // Read lines from user input and store them in a linked list
    struct LineNode *head = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Enter the lines (press Enter after each line, enter 'q' to stop):\n");
    while (1) {
        read = getline(&line, &len, stdin);
        if (read == -1 || line[0] == 'q') {
            break; // Stop reading lines if 'q' is entered or EOF is encountered
        }
        addLine(&head, line);
        line = NULL;
    }

    // Print the last n lines
    printf("\nLast %d lines:\n", n);
    printLastNLines(head, n);

    // Free the memory used by the linked list
    freeLinkedList(head);

    return 0;
}
