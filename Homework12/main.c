#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Video link: https://youtu.be/lW-yIlWkaKc

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct Asset1 {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct Asset2 {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct Asset3 {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct Asset4 {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;


void fillLinkedList(struct Node** head)
{
    srand(time(NULL));
    int numAssets = rand() % 11 + 10;  // Generate a random number of assets between 10 and 20
    int i;

    for (i = 0; i < numAssets; ++i)
    {
        
        int assetType = rand() % 4;

        
        void* asset = NULL;

        switch (assetType)
        {
            case 0:
            {
                Asset1* asset1 = malloc(sizeof(Asset1));
                strcpy(asset1->type, "Asset1");
                asset1->ivals[0] = rand() % 100;
                asset1->svals[0] = (double)rand() / RAND_MAX;
                asset = asset1;
                break;
            }
            case 1:
            {
                Asset2* asset2 = malloc(sizeof(Asset2));
                strcpy(asset2->type, "Asset2");
                asset2->svals[0] = (double)rand() / RAND_MAX;
                asset2->svals[1] = (double)rand() / RAND_MAX;
                asset2->ivals[0] = rand() % 100;
                asset2->ivals[1] = rand() % 100;
                asset = asset2;
                break;
            }
            case 2:
            {
                Asset3* asset3 = malloc(sizeof(Asset3));
                strcpy(asset3->type, "Asset3");
                strcpy(asset3->string1, "String1");
                strcpy(asset3->string2, "String2");
                asset = asset3;
                break;
            }
            case 3:
            {
                Asset4* asset4 = malloc(sizeof(Asset4));
                strcpy(asset4->type, "Asset4");
                asset4->value1 = (double)rand() / RAND_MAX;
                asset4->value2 = (float)rand() / RAND_MAX;
                asset4->value3 = (double)rand() / RAND_MAX;
                asset = asset4;
                break;
            }
        }

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = asset;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            struct Node* current = *head;

            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = newNode;
        }
    }

    
    printf("Linked List Contents:\n");
    struct Node* current = *head;
    while (current != NULL)
    {
        char* type = ((Asset1*)current->data)->type;
        printf("Type: %s\n", type);

        if (strcmp(type, "Asset1") == 0)
        {
            Asset1* asset = (Asset1*)current->data;
            printf("  ivals[0]: %d ", asset->ivals[0]);
            printf("  svals[0]: %lf\n", asset->svals[0]);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            Asset2* asset = (Asset2*)current->data;
            printf("  svals[0]: %lf ", asset->svals[0]);
            printf("  svals[1]: %lf ", asset->svals[1]);
            printf("  ivals[0]: %d ", asset->ivals[0]);
            printf("  ivals[1]: %d\n", asset->ivals[1]);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            Asset3* asset = (Asset3*)current->data;
            printf("  string1: %s ", asset->string1);
            printf("  string2: %s\n", asset->string2);
        }
        else if (strcmp(type, "Asset4") == 0)
        {
            Asset4* asset = (Asset4*)current->data;
            printf("  value1: %lf", asset->value1);
            printf("  value2: %f ", asset->value2);
            printf("  value3: %lf\n", asset->value3);
        }

        current = current->next;
    }
}
// Function to serialize the linked list
void serializeLinkedList(struct Node* head)
{
    FILE* file = fopen("linkedlist.bin", "wb");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return;
    }

    struct Node* current = head;

    while (current != NULL)
    {
        char* type = ((Asset1*)current->data)->type;

        fwrite(type, sizeof(char), 20, file);

        if (strcmp(type, "Asset1") == 0)
        {
            Asset1* asset = (Asset1*)current->data;
            fwrite(asset, sizeof(Asset1), 1, file);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            Asset2* asset = (Asset2*)current->data;
            fwrite(asset, sizeof(Asset2), 1, file);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            Asset3* asset = (Asset3*)current->data;
            fwrite(asset, sizeof(Asset3), 1, file);
        }
        else if (strcmp(type, "Asset4") == 0)
        {
            Asset4* asset = (Asset4*)current->data;
            fwrite(asset, sizeof(Asset4), 1, file);
        }

        current = current->next;
    }

    fclose(file);
}


void deserializeLinkedList(struct Node** head)
{
    FILE* file = fopen("linkedlist.bin", "rb");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return;
    }

    while (1)
    {
        char type[20];
        size_t bytesRead = fread(type, sizeof(char), 20, file);
        if (bytesRead != 20)
        {
            break;
        }

        void* asset = NULL;
        if (strcmp(type, "Asset1") == 0)
        {
            asset = malloc(sizeof(Asset1));
            fread(asset, sizeof(Asset1), 1, file);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            asset = malloc(sizeof(Asset2));
            fread(asset, sizeof(Asset2), 1, file);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            asset = malloc(sizeof(Asset3));
            fread(asset, sizeof(Asset3), 1, file);
        }
        else if (strcmp(type, "Asset4") == 0)
        {
            asset = malloc(sizeof(Asset4));
            fread(asset, sizeof(Asset4), 1, file);
        }

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = asset;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            struct Node* current = *head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    fclose(file);
}


void freeLinkedList(struct Node* head)
{
    struct Node* current = head;
    
    while (current != NULL)
    {
        struct Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main()
{
    struct Node* head = NULL;

    
  fillLinkedList(&head);

    
  serializeLinkedList(head);

    
    struct Node* deserializedList = NULL;
    deserializeLinkedList(&deserializedList);

   
    printf("\n----------------------------\n");
    printf("Deserialized Linked List:\n");
    
    struct Node* current = deserializedList;
    
    while (current != NULL)
    {
        char* type = ((Asset1*)current->data)->type;
        printf("Type: %s\n", type);

        if (strcmp(type, "Asset1") == 0)
        {
            Asset1* asset = (Asset1*)current->data;
            printf("  ivals[0]: %d ", asset->ivals[0]);
            printf("  svals[0]: %lf\n", asset->svals[0]);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            Asset2* asset = (Asset2*)current->data;
            printf("  svals[0]: %lf ", asset->svals[0]);
            printf("  svals[1]: %lf ", asset->svals[1]);
            printf("  ivals[0]: %d ", asset->ivals[0]);
            printf("  ivals[1]: %d\n", asset->ivals[1]);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            Asset3* asset = (Asset3*)current->data;
            printf("  string1: %s ", asset->string1);
            printf("  string2: %s\n", asset->string2);
        }
        else if (strcmp(type, "Asset4") == 0)
        {
            Asset4* asset = (Asset4*)current->data;
            printf("  value1: %lf ", asset->value1);
            printf("  value2: %f ", asset->value2);
            printf("  value3: %lf\n", asset->value3);
        }

        current = current->next;
    }

    
    freeLinkedList(head);
    freeLinkedList(deserializedList);

    return 0;
}
