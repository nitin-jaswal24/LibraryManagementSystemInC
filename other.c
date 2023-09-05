
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct library{ 
    int book_id;
    char book_name[20];
    char author_name[20];
} book;



// code for addition of the book in the library

int addition(int id, char name[], char author[])
{
    FILE *fp = NULL;
    fp = fopen("bookLibrary.dat", "ab+"); // this means in append binary and read and write mode

    if (fp == NULL)
    {
        printf("\n Error: could not open the file");
    }
    else
    {
        book *newBook = NULL;
        newBook = malloc(sizeof(book));
	newBook->book_id = id;

        strcpy(newBook->book_name, name);

        strcpy(newBook->author_name, author);

        fwrite(newBook, sizeof(book), 1, fp);
        fclose(fp);

        free(newBook);

        return 1;
    }
}

// now lets write for deleting the book
int deleteBook(int id)
{
    FILE *fp = NULL;
    FILE *ft = NULL;

    fp = fopen("bookLibrary.dat", "rb"); // this rb means reading and binary
    ft = fopen("temp.dat", "wb");

    if (fp == NULL || ft == NULL)
    {
        printf("\n Error: could not open the file");
        return 0;
    }
    else
    {
        rewind(fp);

        book *discardedBook = (book *)malloc(sizeof(book));
while (fread(discardedBook, sizeof(book), 1, fp) == 1)
        {
            if (id != discardedBook->book_id)
            {
                fwrite(discardedBook, sizeof(book), 1, ft);
            }
        }
        fclose(fp);
        fclose(ft);
        free(discardedBook);

        remove("bookLibrary.dat");
        rename("temp.dat", "bookLibrary.dat");
        return 1;
    }
}

// code to search the books in the library
int searchBook(int id)
{
    FILE *fp = NULL;
    fp = fopen("bookLibrary.dat", "rb"); // read and binary file

    if (fp == NULL)
    {
        printf("\n Error : could  not open the file");
        return 0;
    }
    else
    {
        book *book_to_find = (book *)malloc(sizeof(book));
        while (fread(book_to_find, sizeof(book), 1, fp))
        {
            if (book_to_find->book_id == id)
            {
                printf("\n Book_Id: %d\t\tBook_Name: %s\t\tBook_Author: %s", book_to_find->book_id, book_to_find->book_name, book_to_find->author_name);
                fclose(fp);
                free(book_to_find);
		 return 1;
            }
        }
        fclose(fp);
        free(book_to_find);
        printf("\n specified book is not present\n");
        return 0;
    }
}

// code to issue the book
int issueBook(int id)
{
    char name1[20];
    FILE *fp = NULL;
    fp = fopen("bookLibrary.dat", "rb");
    if (fp == NULL)
    {
        printf("\n Error : could not open the file");
        return 0;
    }
    else
    {
        scanf("%19s student_name", name1);
        book *book_to_find = (book *)malloc(sizeof(book));

        while (fread(book_to_find,sizeof(book),1,fp))
        {
            if (book_to_find->book_id == id)
            {
                printf("\nBook_Id: %d\t\tBook_name: %s\t\tBook_Author: %s", book_to_find->book_id, book_to_find->book_name, book_to_find->author_name);
                printf("\n Book is issued to %s",name1);
                fclose(fp);
                free(book_to_find);
                return 1;
		  }
        }
        fclose(fp);
        free(book_to_find);
        printf("\n book specified is not present");
        return 0;

    }
}

//code to view the book
int viewBook(){
    FILE *fp=NULL;

    fp=fopen("bookLibrary.dat","rb");

    if(fp==NULL){
        printf("\n Error: could not open the file");
        return 0;
    }
    else{
        book *book_to_find=(book*)malloc(sizeof(book));
        while(fread(book_to_find,sizeof(book),1,fp)){
    printf("\n%d\t\t\t%s\t\t\t%s", book_to_find->book_id, book_to_find->book_name, book_to_find->author_name);

        }
        fclose(fp);
        free(book_to_find);
        return 1;
    }
}
