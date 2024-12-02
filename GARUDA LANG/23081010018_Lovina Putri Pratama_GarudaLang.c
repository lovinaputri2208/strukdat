#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 1000

typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, char item) {
    stack->items[++stack->top] = item;
}

char pop(Stack *stack) {
    return stack->items[stack->top--];
}

bool isValidBrackets(const char *code) {
    Stack stack;
    initStack(&stack);
    const char *opening = "({[<";
    const char *closing = ")}]>";

    for (int i = 0; code[i] != '\0'; i++) {
        if (strchr(opening, code[i])) {
            push(&stack, code[i]);
        } else if (strchr(closing, code[i])) {
            const char *found = strchr(closing, code[i]);
            if (found) {
                char expected = opening[found - closing];
                if (isEmpty(&stack) || pop(&stack) != expected) {
                    return false;
                }
            }
        }
    }
    return isEmpty(&stack);
}

void clearScreen() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

int main() {
    char userInput[1000];
    char option;

    do {
        printf("Input kode: ");
        scanf(" %[^\n]", userInput);

        if (isValidBrackets(userInput)) {
            printf("Hasil: Kode valid!\n");
        } else {
            printf("Hasil: Kode tidak valid!\n");
        }

        printf("--------------------------------\n");
        printf("Lanjutkan memeriksa kode lain? (Y/T): ");
        scanf(" %c", &option);

        if (option == 'Y' || option == 'y') {
            printf("\n--------------------------------\n");
            printf("Melanjutkan ke inputan berikutnya\n\n");
        }

    } while (option == 'Y' || option == 'y');

    printf("Terima kasih telah menggunakan program ini!\n");
    return 0;
}


// Language:C 
// ProjectType:0 
// Salin kode lengkap dan buka APLIKASI CCoder untuk menjalankannya. 
// CCoder APP download link：https://play.google.com/store/apps/details?id=com.ikou.ccoding 