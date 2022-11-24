#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int count = 0;
sem_t sem;
clock_t start1, end1, start2, end2, s, e, s1, e1, s2, e2;
double time_use1, time_use2;

void *thread_1(void *arg) {
    sem_wait(&sem);
    s = clock();
    printf("\nThời gian 1 : %lf\n", (double)s/CLOCKS_PER_SEC);
    printf("Enter Critical Section 1...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 1...\n");
    e = clock();
    printf("Thời gian 1 : %lf\n", (double)e/CLOCKS_PER_SEC);


    sem_post(&sem);
    
}

void *thread_2(void *arg) {
    sem_wait(&sem);
    s1 = clock();
    printf("\nThời gian 2 : %lf\n", (double)s1/CLOCKS_PER_SEC);
    printf("Enter Critical Section 2...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 2...\n");
    e1 = clock();
    printf("Thời gian 2 : %lf\n", (double)e1/CLOCKS_PER_SEC);
    sem_post(&sem);
   
}

void *thread_3(void *arg) {
    sem_wait(&sem);
    s2 = clock();
    printf("\nThời gian 3 : %lf\n", (double)s2/CLOCKS_PER_SEC);
    printf("Enter Critical Section 3...\n");
    for (int i = 0; i < 100000000; i++) {
        count ++;
    }
    
    printf("Exit Critical Section 3...\n");
    e2 = clock();
    printf("Thời gian 3 : %lf\n", (double)e2/CLOCKS_PER_SEC);


    sem_post(&sem);
   
}
int main() {
    sem_init(&sem, 0, 1); //1 là giá trị của semaphore

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;


    pthread_create(&thread1, NULL, thread_1, NULL);
    pthread_create(&thread2, NULL, thread_2, NULL);
    pthread_create(&thread3, NULL, thread_3, NULL);


    
    pthread_join(thread1, NULL);
    
    pthread_join(thread2, NULL);
        
    pthread_join(thread3, NULL);   

    sem_destroy(&sem);

    printf("count = %d\n", count);
    


    return 0;
}