#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Structure for stack node
struct StackNode
{
    char data;
    struct StackNode *next;
};

// Functions for stack operations
struct StackNode *createStackNode(char data)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct StackNode **top, char data)
{
    struct StackNode *newNode = createStackNode(data);
    newNode->next = *top;
    *top = newNode;
}

char pop(struct StackNode **top)
{
    if (*top == NULL)
    {
        return '\0'; // Empty stack
    }
    struct StackNode *temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

char peek(struct StackNode *top)
{
    if (top == NULL)
    {
        return '\0'; // Empty stack
    }
    return top->data;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

// Function to check if infix expression is valid
bool isValidInfix(const char *infix)
{
    struct StackNode *stack = NULL;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if (isalpha(ch))
        {
            continue; // Operand, continue to next character
        }
        else if (ch == '(')
        {
            push(&stack, ch);
        }
        else if (ch == ')')
        {
            if (peek(stack) != '(')
            {
                return false; // Unmatched closing parenthesis
            }
            pop(&stack); // Discard the '('
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (peek(stack) != '\0' && precedence(peek(stack)) >= precedence(ch))
            {
                return false; // Operator precedence issue
            }
            push(&stack, ch);
        }
        else
        {
            return false; // Invalid character in expression
        }
    }

    while (stack != NULL)
    {
        if (pop(&stack) == '(')
        {
            return false; // Unmatched opening parenthesis
        }
    }

    return true; // All parentheses matched and operators are valid
}

int main()
{
    const char *infix = "a+b*(c-d)/e";

    if (isValidInfix(infix))
    {
        printf("Infix expression is valid.\n");
    }
    else
    {
        printf("Infix expression is not valid.\n");
    }

    return 0;
}
