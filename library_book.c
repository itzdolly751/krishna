#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100

typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

Book library[MAX_BOOKS];
int book_count = 0;

// Function prototypes
void add_book();
void view_books();
void search_book();
void delete_book();

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Book Management System\n");
        printf("1. Add a Book\n");
        printf("2. View All Books\n");
        printf("3. Search for a Book\n");
        printf("4. Delete a Book\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                view_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                delete_book();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book new_book;

    printf("Enter the book title: ");
    fgets(new_book.title, TITLE_LENGTH, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0; // Remove newline character

    printf("Enter the author's name: ");
    fgets(new_book.author, AUTHOR_LENGTH, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove newline character

    printf("Enter the year of publication: ");
    scanf("%d", &new_book.year);
    getchar(); // Consume the newline character

    library[book_count] = new_book;
    book_count++;

    printf("Book added successfully!\n");
}

void view_books() {
    if (book_count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nList of Books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("%d. Title: %s, Author: %s, Year: %d\n", i + 1, library[i].title, library[i].author, library[i].year);
    }
}

void search_book() {
    char title[TITLE_LENGTH];
    printf("Enter the title of the book to search: ");
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0; // Remove newline character

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("Book found!\n");
            printf("Title: %s, Author: %s, Year: %d\n", library[i].title, library[i].author, library[i].year);
            return;
        }
    }

    printf("Book not found.\n");
}