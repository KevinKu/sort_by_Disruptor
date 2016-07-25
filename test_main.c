#include "Disruptor.h"
#include <pthread.h>
#define waiting 0
#define non_waiting 1
#define job_number 5


Job test_job_list_a[job_number];

Job test_job_list_b[job_number];


void test_multi_thread_commit_job(void *arg)
{

Job *job_array = (Job *)arg;

int current_index;

int i = 0;
	for(;i < job_number;i++)
	{

	current_index = Job_Disruptor.get_empty_job();

	Job_Disruptor.commit_job(current_index,job_array[i]);			
	}

return;
}


int main(int argc,char *argv[])
{



return 0;
}
