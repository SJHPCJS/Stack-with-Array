#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
This project is a stack implementation.
The stack is based on dynamic array.
User can use it with a menu.
*/
#define Max 100
typedef int Element;

/*
The struct represents the Stack.
*/
typedef struct stack {
    Element *data;
    int top;
    int capacity;
} Stack;

/*
A method to initialize a stack.
Input: the pointer to the stack and the capacity of the stack.
*/
void InitStack(Stack *S, int capacity) {
    S->data = (Element *)malloc(sizeof(Element) * capacity);
    S->top = -1;
    S->capacity = capacity;
}

/*
A method to check if the stack is full.
Input: the pointer to the stack.
*/
bool IsFull(Stack *S) {
    return S->top == S->capacity - 1;
}

/*
A method to check if the stack is empty.
Input: the pointer to the stack.
*/
bool IsEmpty(Stack *S) {
    return S->top == -1;
}

/*
A method to push a element to the stack.
Input: the pointer to the stack and the element to push.
Return: whether the operation is successful or not.
*/
bool Push(Stack *S, Element toPush) {
    if (IsFull(S)) {
        int new_capacity = S->capacity * 2;
        Element *new_data = (Element *)realloc(S->data, sizeof(Element) * new_capacity);
        if (new_data == NULL) {
            return false;
        }
        S->data = new_data;
        S->capacity = new_capacity;
    }
    S->data[++S->top] = toPush;
    return true;
}

/*
A method to pop a element from the stack.
Input: the pointer to the stack and the pointer to the element popped.
Return: whether the operation is successful or not
*/
bool Pop(Stack *S, Element *toPop) {
    if (IsEmpty(S)) {
        return false;
    }
    *toPop = S->data[S->top--];
    return true;
}

/*
A method to get the top element.
Input: the pointer to the stack.
Return: the top element.
*/
Element GetTop(Stack *S) {
    if (IsEmpty(S)) {
        return -1;
    }
    return S->data[S->top];
}

/*
A method to print all element in the stack.
Input: the pointer to the stack.
*/
void PrintStack(Stack *S) {
    int i = S->top;
    if (IsEmpty(S)) {
        printf("Stack is empty.\n");
    } else {
        while (i >= 0) {
            printf("%d ", S->data[i--]);
        }
        printf("\n");
    }
}

/*
A method to free the memory of a stack.
Input: the pointer to the stack.
*/
void DestroyStack(Stack *S) {
    free(S->data);
    S->top = -1;
    S->capacity = 0;
}

/*
Main method:
A menu of using the stack.
*/
int main() {
    Stack S;
    int capacity;
    Element e;
    int choice;
    int length;

    printf("Welcome to the Stack.\n");

    while (true) {
        printf("Please enter a number to choose the operation.\n");
        printf("1. Create a new stack.\n");
        printf("2. Push a number.\n");
        printf("3. Pop a number.\n");
        printf("4. Print the top element.\n");
        printf("5. Print the stack.\n");
        printf("0. Exit.\n");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice < 0 || choice > 5) {
            printf("Invalid choice. Please enter a number between 0 and 5.\n");
            continue;
        }

        if (choice == 0) {
            DestroyStack(&S);
            break;
        }

        switch (choice) {
            case 1:
                if (S.top != -1) {
                    DestroyStack(&S);
                }
                printf("Please enter the initial capacity of the stack: ");
                if (scanf("%d", &capacity) != 1 || capacity <= 0) {
                    printf("Invalid capacity. Please enter a positive integer.\n");
                    continue;
                }
                InitStack(&S, capacity);
                printf("Please enter the length of elements you want to insert: ");
                if (scanf("%d", &length) != 1 || length <= 0) {
                    printf("Invalid length. Please enter a positive integer.\n");
                    continue;
                }
                printf("Please enter all %d elements one by one in order.\n", length);
                while (length--) {
                    if (scanf("%d", &e) != 1) {
                        printf("Invalid element. Please enter a valid integer.\n");
                        continue;
                    }
                    Push(&S, e);
                }
                PrintStack(&S);
                break;

            case 2:
                printf("Please enter an element you want to push: ");
                if (scanf("%d", &e) != 1) {
                    printf("Invalid element. Please enter a valid integer.\n");
                    continue;
                }
                if (Push(&S, e)) {
                    printf("Push successfully!\n");
                } else {
                    printf("Push failed!\n");
                }
                PrintStack(&S);
                break;

            case 3:
                if (Pop(&S, &e)) {
                    printf("Element %d popped successfully!\n", e);
                } else {
                    printf("Pop failed.\n");
                }
                PrintStack(&S);
                break;

            case 4:
                if (!IsEmpty(&S)) {
                    printf("The top element is %d.\n", GetTop(&S));
                } else {
                    printf("Stack is empty.\n");
                }
                break;

            case 5:
                PrintStack(&S);
                break;
        }
    }

    return 0;
}


