#include <stdio.h>
#include <string.h>

void addBook();
void deleteBook();
void searchBook();
void issueBook();
void returnBook();
void displayBook();
void feedback();
void login();

struct Book {
    char title[60];
    char author[60];
    int publishYear; 
};

void login() {
    char name[40], department[40], email[40]; 
    printf("Enter Your Name: ");
    scanf("%s", name);
    printf("Enter Department/Class: ");
    scanf("%s", department);
    printf("Enter Email: ");
    scanf("%s", email);

    FILE *fp = fopen("students.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s %s %s\n", name, department, email);
    fclose(fp);
}

void addBook() {
    struct Book book;
    printf("Enter Title of Book: ");
    scanf(" %s", book.title);
    printf("Enter Author of Book: ");
    scanf(" %s", book.author);
    printf("Enter Publish Year of Book: ");
    scanf("%d", &book.publishYear);

    FILE *fp = fopen("library.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s %s %d\n", book.title, book.author, book.publishYear);
    fclose(fp);
    printf("The book was added successfully.\n");
    
    feedback();
}

void deleteBook() { 
    char title[60];
    struct Book book;
    printf("Enter Title of Book to Delete: ");
    scanf(" %s", title);

    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %s %d", book.title, book.author, &book.publishYear) != EOF) { 
        if (strcmp(book.title, title) == 0) { 
            found = 1;
            printf("The book was deleted successfully.\n");
        } else {
            fprintf(temp, "%s %s %d\n", book.title, book.author, book.publishYear);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        printf("Book not found.\n");
    }
    feedback();
}

void searchBook() {
    char title[60];
    struct Book book;
    printf("Enter Title of Book to Search: ");
    scanf(" %s", title);

    FILE *fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %s %d", book.title, book.author, &book.publishYear) != EOF) {
        if (strcmp(book.title, title) == 0) {
            printf("Book Found:\nTitle: %s\nAuthor: %s\nYear: %d\n", book.title, book.author, book.publishYear);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("Book not found.\n");
    }
    feedback();
}

void issueBook() {
	struct Book book;
    char title[60];
    int issueDate;
    printf("Enter Title of Book: ");
    scanf(" %s", title);
    
    FILE *fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %s %d", book.title, book.author, &book.publishYear) != EOF) {
        if (strcmp(book.title, title) == 0) {
            printf("Book Found:\nTitle: %s\nAuthor: %s\nYear: %d\n", book.title, book.author, book.publishYear);
            found = 1;
                printf("Enter Date of Issue: ");
   				scanf("%d", &issueDate);
   				printf("Return Date: %d\n", issueDate + 4);
    			printf("Late return penalty: Rs 50 per day.\n");
    			
    		FILE *issueFile = fopen("issued_books.txt", "a");
            if (issueFile != NULL) {
                fprintf(issueFile, "%s %d\n", book.title, issueDate);
                fclose(issueFile);
            } else {
                printf("Error opening issued books file!\n");
            }
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("Book not found.\n");
    }
    feedback();
}

void returnBook() {
    char title[60];
    int issueDate, returnDate, found = 0, penalty = 50;

    printf("Enter Title of Book: ");
    scanf(" %s", title);

    FILE *issueFile = fopen("issued_books.txt", "r");
    if (issueFile == NULL) {
        printf("Error opening issued books file!\n");
        return;
    }

    char issuedTitle[60];
    while (fscanf(issueFile, "%s %d", issuedTitle, &issueDate) != EOF) {
        if (strcmp(issuedTitle, title) == 0) {
            found = 1;
            printf("Enter Return Date: ");
            scanf("%d", &returnDate);
            if (returnDate > issueDate + 4) {
                int extraDays = returnDate - (issueDate + 4);
                printf("Pay penalty of Rs %d for %d extra days.\n", penalty * extraDays, extraDays);
            } else {
                printf("Thank you for returning the book on time.\n");
            }
        } 
    }

    fclose(issueFile);

    remove("issued_books.txt");
    rename("temp.txt", "issued_books.txt");

    if (!found) {
        printf("This book was not issued by us.\n");
    }
    feedback();
}

void displayBook()
{
    FILE *fp;
    fp = fopen("library.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);  
}

void feedback() {
    char fb[500];
    printf("Give us feedback about our library: ");
    scanf(" %s", fb);
    FILE *fp = fopen("feedback.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s\n", fb);
    fclose(fp);
    printf("Thank you for your feedback!\n");
}

int main() {
	
	int select;
	do
	{
	printf("Welcome to DSU Library!\n");
	printf("1. login.\n");
	printf("2. exit.\n");
    printf("Select from above: ");
    scanf("%d", &select);	

	switch(select)
	{
		case 1:
			login();
			break;	
		case 2:
            printf("Exiting...\n");
            return 0;
		default:
		 	printf("Invalid choice. Please try again.\n");  
		 	break;
	}
	}while(select > 2);
	
    int choice;
    
    while (1) {
    	printf("\nOur Library Menu");
        printf("\n1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book by Title\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Display Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
               	searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
              	displayBook();
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");   
        }    
	}
 return 0;
}
