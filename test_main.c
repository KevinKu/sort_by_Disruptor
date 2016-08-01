/*
*Test define use:
*
*	TEST_THREAD_COMMIT_JOB:
*
*		test Job_Disruptor.commit_job
*
*
*	
*
*
*
*
*/


#define TEST_THREAD_COMMIT_JOB


#include "Disruptor.h"
#include <pthread.h>
#define waiting 0
#define non_waiting 1
#define job_number 5

int test_max_num;

int start = 1;

int test_thread_num;

pthread_t test_thread_a,test_thread_b;


Job test_job_list_a[job_number];

Job test_job_list_b[job_number];


void *test_multi_thread_commit_job(void *arg)
{


while(start == 1){__sync_synchronize();}


Job *job_array = (Job *)arg;

int current_index;

int i = 0;
	for(;i < test_max_num;i++)
	{

	current_index = Job_Disruptor.get_empty_job();

	Job_Disruptor.commit_job(current_index,job_array[i]);			
	}

return (void*)NULL ;
}


void *test_get_empty_job(void* arg)
{
while(start == 1){__sync_synchronize();}

Job_Disruptor.get_empty_job();

return (void*)NULL;

}


void test_create_multi_thread(void *(*test_function)(void *),void *arg,const int thread_num)
{
int i = 0;
pthread_t thread_id;

	for(;i < thread_num;i++)
	{
	
	pthread_create(&thread_id,0,test_function,arg);

	}

return;

}


int main(int argc,char *argv[])
{

#ifdef TEST_THREAD_COMMIT_JOB

pthread_create(&test_thread_a,0,test_multi_thread_commit_job,&test_job_list_a);

pthread_create(&test_thread_b,0,test_multi_thread_commit_job,&test_job_list_b);

#endif

#ifdef TEST_THREAD_GET_EMPTY_JOB

test_create_multi_thread(test_get_empty_job,0,test_thread_num);


#endif


#ifdef


return 0;
}
