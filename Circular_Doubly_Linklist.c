#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the circular doubly linked list
struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
    }
    else
    {
        struct Node *last = (*head)->prev;
        newNode->next = *head;
        newNode->prev = last;
        (*head)->prev = newNode;
        last->next = newNode;
        *head = newNode;
    }
}

// Function to insert a new node at the end of the list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
    }
    else
    {
        struct Node *last = (*head)->prev;
        newNode->next = *head;
        newNode->prev = last;
        (*head)->prev = newNode;
        last->next = newNode;
    }
}

// Function to delete a node by value
void deleteNode(struct Node **head, int key)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *current = *head;
    do
    {
        if (current->data == key)
        {
            if (current == *head && current->next == *head)
            {
                *head = NULL;
            }
            else if (current == *head)
            {
                struct Node *last = current->prev;
                *head = (*head)->next;
                last->next = *head;
                (*head)->prev = last;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Node with value %d deleted successfully.\n", key);
            return;
        }
        current = current->next;
    } while (current != *head);
    printf("Node with value %d not found in the list.\n", key);
}

// Function to print the circular doubly linked list
void printList(struct Node *head)
{
    struct Node *current = head;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    do
    {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

int main()
{
    struct Node *head = NULL;
    int choice, data;

    do
    {
        printf("\n\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete a node\n");
        printf("4. Print the list\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at the beginning: ");
            scanf("%d", &data);
            insertAtBeginning(&head, data);
            break;
        case 2:
            printf("Enter data to insert at the end: ");
            scanf("%d", &data);
            insertAtEnd(&head, data);
            break;
        case 3:
            printf("Enter data to delete: ");
            scanf("%d", &data);
            deleteNode(&head, data);
            break;
        case 4:
            printf("Circular doubly linked list: ");
            printList(head);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
