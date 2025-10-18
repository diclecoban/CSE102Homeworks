#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 200

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Node* mother;
    struct Node* father;
} Node;

void menu();
void addNode(Node** root);
void removeNode(Node** root);
void saveFamilyTree(Node* root, int treeId);
Node* loadFamilyTree(int treeId);
void printFamilyTreeHelper(Node* node, FILE* file);
void printFamilyTree(Node* root, FILE* file);
void freeFamilyTree(Node** root);

int main()
{
    menu();
    return 0;
}

void menu()
{
    Node* familyTree = NULL;
    int choice, treeId;
    FILE* file;

    while (1)
    {
        printf("1. Add a family tree\n");
        printf("2. Load a family tree\n");
        printf("3. Print a family tree\n");
        printf("4. Remove a family tree\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addNode(&familyTree);
                break;

            case 2:
                printf("Enter the tree ID to load: ");
                scanf("%d", &treeId);

                familyTree = loadFamilyTree(treeId);

                if (familyTree == NULL)
                {
                    printf("Failed to load the family tree.\n");
                }
                else
                {
                    printf("Family tree loaded successfully.\n");
                }
                break;

            case 3:
                printf("Please enter the file name to print the family tree: ");
                
                char filename[MAX_NAME_LENGTH];
                scanf("%s", filename);
                file = fopen(filename, "w");
                
                if (file == NULL)
                {
                    printf("Warning! Failed to open the file for printing the family tree.\n");
                }
                else
                {
                    printFamilyTree(familyTree, file);
                    fclose(file);
                }
                break;

            case 4:
                removeNode(&familyTree);
                break;

            case 5:
                printf("Enter the tree ID to save: ");
                scanf("%d", &treeId);
                saveFamilyTree(familyTree, treeId);
                freeFamilyTree(&familyTree);
                return;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addNode(Node** root)
{
    if (*root == NULL)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));

        printf("Enter the name of the person: ");
        scanf("%s", newNode->name);

        printf("Enter the age of %s: ", newNode->name);
        scanf("%d", &(newNode->age));

        newNode->mother = NULL;
        newNode->father = NULL;

        *root = newNode;
        printf("New person added to the family tree.\n");
    }
    else
    {
        
        char name[MAX_NAME_LENGTH];
        printf("Enter the name of the person to add: ");
        scanf("%s", name);

        Node* current = *root;

        while (1)
        {
            int choice;
            printf("Add %s as (1) mother or (2) father? Enter your choice: ", name);
            scanf("%d", &choice);

            if (choice == 1)
            {
                if (current->mother == NULL)
                {
                    Node* newNode = (Node*)malloc(sizeof(Node));

                    strcpy(newNode->name, name);
                    printf("Enter the age of %s: ", newNode->name);
                    scanf("%d", &(newNode->age));

                    newNode->mother = NULL;
                    newNode->father = NULL;

                    current->mother = newNode;
                    printf("%s added as the mother.\n", name);
                    break;
                }
                else
                {
                    current = current->mother;
                }
            }
            else if (choice == 2)
            {
                if (current->father == NULL)
                {
                    Node* newNode = (Node*)malloc(sizeof(Node));

                    strcpy(newNode->name, name);
                    printf("Enter the age of %s: ", newNode->name);
                    scanf("%d", &(newNode->age));

                    newNode->mother = NULL;
                    newNode->father = NULL;

                    current->father = newNode;
                    printf("%s added as the father.\n", name);
                    break;
                }
                else
                {
                    current = current->father;
                }
            }
            else
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
}

void removeNode(Node** root)
{

    if (*root == NULL)
    {
        printf("The family tree is empty.\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    printf("Enter the name of the person to remove: ");
    scanf("%s", name);

    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (parent == NULL)
            {
                // The node to remove is the root node
                freeFamilyTree(root);
                *root = NULL;
                printf("The family tree has been removed.\n");
            }
            else
            {
                // Remove the current node from the family tree
                if (parent->mother == current)
                {
                    parent->mother = NULL;
                }
                else
                {
                    parent->father = NULL;
                }

                freeFamilyTree(&current);
                printf("The person has been removed from the family tree.\n");
            }

            return;
        }

        parent = current;
        current = current->mother;

        if (current == NULL)
        {
            current = parent->father;
        }
    }

    printf("The person was not found in the family tree.\n");
}

void saveFamilyTree(Node* root, int treeId)
{
    char filename[20];
    sprintf(filename, "family%d.txt", treeId);

    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Failed to open the file for saving the family tree.\n");
        return;
    }

    if (root == NULL)
    {
        fprintf(file, "Empty family tree.\n");
    }
    else
    {
        fprintf(file, "Family tree:\n");
        fprintf(file, "------------\n");
        fprintf(file, "Name\tAge\tMother\tFather\n");
        fprintf(file, "----\t---\t------\t------\n");

        printFamilyTreeHelper(root, file);
    }

    fclose(file);
    printf("Family tree saved to %s\n", filename);
}


Node* loadFamilyTree(int treeId)
{
    char filename[20];
    sprintf(filename, "family%d.txt", treeId);

    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Failed to open the file for loading the family tree.\n");
        return NULL;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    
    if (strcmp(buffer, "Empty family tree.\n") == 0)
    {
        fclose(file);
        return NULL;
    }

    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);

    Node* root = NULL;
    Node* current = NULL;
    Node* parent = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (buffer[0] == '\n')
        {
            break;
        }

        char name[MAX_NAME_LENGTH];
        int age;
        char mother[MAX_NAME_LENGTH];
        char father[MAX_NAME_LENGTH];

        sscanf(buffer, "%s\t%d\t%s\t%s\n", name, &age, mother, father);

        Node* newNode = (Node*)malloc(sizeof(Node));
        strcpy(newNode->name, name);
        newNode->age = age;

        newNode->mother = NULL;
        newNode->father = NULL;

        if (root == NULL)
        {
            root = newNode;
            current = newNode;
        }
        else if (strcmp(mother, "-") == 0 && strcmp(father, "-") == 0)
        {
            current->mother = newNode;
            current->father = newNode;
            current = newNode;
        }
        else if (strcmp(mother, "-") != 0 && strcmp(father, "-") == 0)
        {
            Node* motherNode = (Node*)malloc(sizeof(Node));
            strcpy(motherNode->name, mother);
            motherNode->age = 0;
            motherNode->mother = NULL;
            motherNode->father = NULL;

            current->mother = motherNode;
            current->father = newNode;
            current = newNode;
        }
        else if (strcmp(mother, "-") == 0 && strcmp(father, "-") != 0)
        {
            Node* fatherNode = (Node*)malloc(sizeof(Node));
            strcpy(fatherNode->name, father);
            fatherNode->age = 0;
            fatherNode->mother = NULL;
            fatherNode->father = NULL;

            current->mother = newNode;
            current->father = fatherNode;
            current = newNode;
        }
        else
        {
            Node* motherNode = (Node*)malloc(sizeof(Node));
            strcpy(motherNode->name, mother);
            motherNode->age = 0;
            motherNode->mother = NULL;
            motherNode->father = NULL;

            Node* fatherNode = (Node*)malloc(sizeof(Node));
            strcpy(fatherNode->name, father);
            fatherNode->age = 0;
            fatherNode->mother = NULL;
            fatherNode->father = NULL;

            current->mother = motherNode;
            current->father = fatherNode;
            current = newNode;
        }
    }

    fclose(file);
    return root;
}

void printFamilyTreeHelper(Node* node, FILE* file)
{
    if (node != NULL)
    {
        fprintf(file, "%s\t%d\t", node->name, node->age);

        if (node->mother != NULL)
        {
            fprintf(file, "%s\t", node->mother->name);
        }
        else
        {
            fprintf(file, "-\t");
        }

        if (node->father != NULL)
        {
            fprintf(file, "%s\n", node->father->name);
        }
        else
        {
            fprintf(file, "-\n");
        }

        
        printFamilyTreeHelper(node->mother, file);
        printFamilyTreeHelper(node->father, file);
    }
}

void printFamilyTree(Node* root, FILE* file)
{
    if (root == NULL)
    {
        fprintf(file, "Empty family tree.\n");
    }
    else
    {
        fprintf(file, "Family tree:\n");
        fprintf(file, "------------\n");
        fprintf(file, "Name\tAge\tMother\tFather\n");
        fprintf(file, "----\t---\t------\t------\n");

        printFamilyTreeHelper(root, file);
    }
}

void freeFamilyTree(Node** root)
{
    if (*root != NULL)
    {
        freeFamilyTree(&(*root)->mother);
        freeFamilyTree(&(*root)->father);
        free(*root);
        *root = NULL;
    }
}
