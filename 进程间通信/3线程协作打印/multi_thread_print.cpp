#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond1,cond2,cond3; //类似一个 全局 的votatile flag
pthread_mutex_t the_mutex;

volatile unsigned int buffer = 0;
const int MAX = 100;

void *printer1(void *ptr){
    for(int i = 1; i < MAX; i++){
         
        pthread_mutex_lock(&the_mutex);
        printf("printer1 thread  start wait ...\n");
        while(buffer%3!=0) pthread_cond_wait(&cond1, &the_mutex);
        printf("printer1 thread  解除 wait ...\n");
    buffer++;
        sleep(1);
        printf("printer1 pthread  print %d.\n", 1);
        pthread_cond_signal(&cond2);//唤醒下一个线程 [线程2]
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *printer2(void *ptr){
     
    for(int i = 1; i < MAX; i++){
        pthread_mutex_lock(&the_mutex);
        printf("printer2 thread  start wait ...\n");
        while(buffer%3!=1) pthread_cond_wait(&cond2, &the_mutex);
        printf("printer2 thread  解除 wait ...\n");
        printf("printer2 pthread  print %d.\n", 2);
   buffer++;
        pthread_cond_signal(&cond3); //唤醒下一个线程 [线程3]
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}
void *printer3(void *ptr){
     
    for(int i = 1; i < MAX; i++){
        pthread_mutex_lock(&the_mutex);
        printf("printer3 thread  start wait ...\n");
        while(buffer%3!=2) pthread_cond_wait(&cond3, &the_mutex);
        printf("printe3 thread  解除 wait ...\n");
        printf("printer3 pthread  print %d.\n", 3);
        buffer++;
 
        pthread_cond_signal(&cond1); //唤醒下一个线程 [线程1]
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

int main(void){
    pthread_t th1, th2, th3;
    printf("3 thread  created ...\n");
    pthread_mutex_init(&the_mutex,0);
    pthread_cond_init(&cond1,0);
    pthread_cond_init(&cond2,0);
    pthread_cond_init(&cond3,0);
    pthread_create(&th1, 0, printer1, 0);
    pthread_create(&th2, 0, printer2, 0);
    pthread_create(&th3, 0, printer3, 0);
    pthread_join(th1, 0);
    pthread_join(th2, 0);
    pthread_join(th3, 0);
    // pthread_cond_signal(&cond1);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    pthread_cond_destroy(&cond3);
    pthread_mutex_destroy(&the_mutex);
    return 0;
}