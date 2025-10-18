#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define ISBN_LENGTH 13
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100

struct Book {
    char isbn[ISBN_LENGTH];
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int publication_year;
    int reserved_status;
};


void displayBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Failed to open books.txt file.\n");
        return;
    }

    printf("Book List:\n");
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char isbn[ISBN_LENGTH];
        char title[TITLE_LENGTH];
        char author[AUTHOR_LENGTH];
        int publication_year;
        int reserved_status;

        sscanf(line, "%[^,],%[^,],%[^,],%d,%d", isbn, title, author, &publication_year, &reserved_status);

        printf("ISBN: %s\n", isbn);
        printf("Title: %s\n", title);
        printf("Author: %s\n", author);
        printf("Publication Year: %d\n", publication_year);
        printf("Reserved Status: %d\n", reserved_status);
        printf("--------------------\n");
    }

    fclose(file);
}



int main() {
    struct Book books[MAX_BOOKS];
    int numBooks = 0;
    
    
    FILE *file = fopen("books.txt", "r");

    if (file != NULL)
        
    {
        while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", books[numBooks].isbn, books[numBooks].title, books[numBooks].author, &books[numBooks].publication_year, &books[numBooks].reserved_status) == 5) {
            numBooks++;
            if (numBooks == MAX_BOOKS) {
                printf("Maximum number of books reached.\n");
                break;
            }
        }
        fclose(file);
    }

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Display Book List\n");
        printf("2. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks(books, numBooks);
                break;
            case 2:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
