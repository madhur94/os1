#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int totalBooks = 100;
int numreader = 0;

void *add_books(void *wno) {
    int booksAdd = 20;
    sem_wait(&wrt);
    totalBooks += booksAdd;
    printf("Librarian %d added %d books. Current books available: %d\n", *((int *)wno), booksAdd, totalBooks);
    sem_post(&wrt);
}

void *remove_books(void *wno) {
    int booksRemove = 10;
    sem_wait(&wrt);
    totalBooks -= booksRemove;
    printf("Librarian %d removed %d books. Current books available: %d\n", *((int *)wno), booksRemove, totalBooks);
    sem_post(&wrt);
}

void *reader(void *rno) {
    pthread_mutex_lock(&mutex);
    numreader++;

    if (numreader == 1) {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d checked out books. Books available: %d\n", *((int *)rno), totalBooks);

    pthread_mutex_lock(&mutex);
    numreader--;

    if (numreader == 0) {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t reader_threads[10], librarian_threads[5];
    char actions[] = {'R', 'A', 'A', 'R', 'A'};
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

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

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
