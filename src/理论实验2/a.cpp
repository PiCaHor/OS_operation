#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define TOTAL_NUM 10000000                          
#define THREAD_NUM 2                                

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;   
int circle_num = 0;                                 
int num = 0;								
void* monte_carlo(void* tid)                     
{
    srand((unsigned)time(NULL));
    int i = 0;
    while(i<TOTAL_NUM/THREAD_NUM)
    {
        pthread_mutex_lock(&lock);                  
        
        double pointX = (double)rand()/(double)RAND_MAX;
        double pointY = (double)rand()/(double)RAND_MAX;
        double l = pointX*pointX+pointY*pointY;

        if(l<=1.0)
            ++circle_num;
        ++num;
        ++i;
        
        pthread_mutex_unlock(&lock);               
        
    }
}

int main()
{
    pthread_t thread[THREAD_NUM];                   
    int i, state;

    for(i = 0;i<THREAD_NUM;i++)                     
    {
        printf("create thread%d\n", i);
        state = pthread_create(&thread[i], NULL, monte_carlo, NULL);
        if(state)
        {
            printf("error!\n");
            exit(-1);
        }
    }

    for(i = 0;i<THREAD_NUM;i++)                    
    {
        pthread_join(thread[i],NULL);
    }

    pthread_mutex_destroy(&lock);                 

 
    printf("num = %d, circle_num = %d, pi = %.5lf\n", num, circle_num, 4.0*circle_num/TOTAL_NUM);

    return 0;
}

