#include "Disruptor.h"
#include <pthread.h>
#define waiting 0
#define non_waiting 1
#define job_number 5

int test_max_num;

int start = 1;

pthread_t test_thread_a,test_thread_b;


Job test_job_list_a[job_number];

Job test_job_list_b[job_number];


void *test_multi_thread_commit_job(void *arg)
{


//while(start == 1){__sync_synchronize();}


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


int main(int argc,char *argv[])
{

pthread_create(&test_thread_a,0,test_multi_thread_commit_job,&test_job_list_a);

pthread_create(&test_thread_b,0,test_multi_thread_commit_job,&test_job_list_b);

return 0;
}
