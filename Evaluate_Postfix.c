#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure for stack node
struct StackNode
{
    int data;
    struct StackNode *next;
};

// Functions for stack operations
struct StackNode *createStackNode(int data)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct StackNode **top, int data)
{
    struct StackNode *newNode = createStackNode(data);
    newNode->next = *top;
    *top = newNode;
}

int pop(struct StackNode **top)
{
    if (*top == NULL)
    {
        return -1; // Empty stack
    }
    struct StackNode *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

// Function to evaluate postfix expression
int evaluatePostfix(const char *postfix)
{
    struct StackNode *stack = NULL;
    int operand1, operand2;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if (ch >= '0' && ch <= '9')
        {
            push(&stack, ch - '0'); // Convert character to integer
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch (ch)
            {
            case '+':
                push(&stack, operand1 + operand2);
                break;
            case '-':
                push(&stack, operand1 - operand2);
                break;
            case '*':
                push(&stack, operand1 * operand2);
                break;
            case '/':
                push(&stack, operand1 / operand2);
                break;
            }
        }
    }

    return pop(&stack);
}

int main()
{
    const char *postfix = "235*+";
    int result = evaluatePostfix(postfix);
    printf("Postfix expression: %s\n", postfix);
    printf("Result of evaluation: %d\n", result);

    return 0;
}
