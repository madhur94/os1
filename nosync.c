#include <pthread.h>
#include <stdio.h>

int totalBooks = 100;
int numreader = 0;

void *add_books(void *wno) {
    int booksAdd = 20;
    totalBooks += booksAdd;
    printf("Librarian %d added %d books. Current books available: %d\n", *((int *)wno), booksAdd, totalBooks);
}

void *remove_books(void *wno) {
    int booksRemove = 10;
    totalBooks -= booksRemove;
    printf("Librarian %d removed %d books. Current books available: %d\n", *((int *)wno), booksRemove, totalBooks);
}

void *reader(void *rno) {
    printf("Reader %d checked out books. Books available: %d\n", *((int *)rno), totalBooks);
}

int main() {
    pthread_t reader_threads[10], librarian_threads[5];
    char actions[] = {'R', 'A', 'A', 'R', 'A'};
    int ids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 5; i++) {
        pthread_create(&reader_threads[i], NULL, reader, (void *)&ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        if (actions[i] == 'A') {
            pthread_create(&librarian_threads[i], NULL, add_books, (void *)&ids[i]);
        } else {
            pthread_create(&librarian_threads[i], NULL, remove_books, (void *)&ids[i]);
        }
    }

    for (int i = 5; i < 10; i++) {
        pthread_create(&reader_threads[i], NULL, reader, (void *)&ids[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(librarian_threads[i], NULL);
    }

    return 0;
}
