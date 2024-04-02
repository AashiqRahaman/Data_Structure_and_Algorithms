#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Function to convert infix to postfix
void infixToPostfix(const char *infix, char *postfix)
{
    struct StackNode *stack = NULL;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            postfix[j++] = ch;
        }
        else if (ch == '(')
        {
            push(&stack, ch);
        }
        else if (ch == ')')
        {
            while (peek(stack) != '\0' && peek(stack) != '(')
            {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Discard the '('
        }
        else
        { // Operator
            while (peek(stack) != '\0' && precedence(peek(stack)) >= precedence(ch))
            {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    // Pop remaining operators from stack to output
    while (peek(stack) != '\0')
    {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0'; // Null terminate the postfix expression
}

int main()
{
    const char *infix = "a+b*(c-d)/e";
    char postfix[100];

    infixToPostfix(infix, postfix);
    printf("Infix expression: %s\n", infix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
