#define TEST_MULTI_THREAD_WRITER_AND_READER 
/*
*Test define use:
*
*	TEST_THREAD_COMMIT_JOB:
*
*		test Job_Disruptor.commit_job
*
*	TEST_THREAD_GET_EMPTY_JOB:
*	
*		test Job_Disruptor.get_empty_job
*
*	TEST_THREAD_GET_MAX_AVAILABLE_JOB_INDEX:
*
*		test get_Max_available_job_index
*
*	TEST_MULTI_THREAD_WRITER_AND_READER :
*
*		test writers and readers
*
*
*
*/


#include "Disruptor.h"
#include <pthread.h>
#include <stdlib.h>
#define waiting 0
#define non_waiting 1
#define job_number 5

void *test_reader(void*);

void *test_writer(void*);


static int test_max_num;

static int start = 1;

/*

every test thread will be blocked by start.

If want to go next step,change this value.

*/

static int test_thread_num;

/*

test_thread_num is thread number in test.

Use : TEST_THREAD_GET_EMPTY_JOB


*/

static int test_reader_num;

/*

test_reader_num determines reader code number.One thread has only one reader code. 

Use : test_multi_thread_get_Max_available_job_index

      test_multi_thread_writer_and_reader


Gdb test command : init_env_and_build_reader_dependency


*/

static int test_writer_num;

/*

test_writer_num determines writer number.One thread has only one writer.

Use : test_multi_thread_writer_and_reader

Gdb test command : init_writer_test_job_data_from_file

*/


static int *test_job_length;

/*

test_job_length is the test job data number list.

Use : test_multi_thread_writer_and_reader

Gdb test command : init_writer_test_job_data_from_file


*/

static Job **test_job_list;

/*

test_job_list is the job list for every writer.

Use : test_multi_thread_writer_and_reader

Gdb test command : init_writer_test_job_data_from_file

*/

void test_multi_thread_writer_and_reader(void)
{

pthread_t thread_id;

int *reader_code = (int *)malloc(sizeof(int) * test_reader_num);

int *writer_code = (int *)malloc(sizeof(int) * test_writer_num);

int i = 0;

	for(;i < test_writer_num;i++)
	{

		writer_code[i] = i;

		pthread_create(&thread_id,0,test_writer,&(writer_code[i]));
	}


/*create  writer .  One thread has only one writer.*/


i = 0;


	for(;i < test_reader_num;i++)
	{

		reader_code[i] = i + 1;

		pthread_create(&thread_id,0,test_reader,&(reader_code[i]));

	}


/*create reader thread. One thread has only one reader.*/


return;


}


void *test_writer(void *arg)
{

while(start == 1){__sync_synchronize();}

int writer_code = (*((int *)arg));

int current_index;

int i = 0;

	for(;i < test_job_length[writer_code];i++)
	{

		current_index = Job_Disruptor.get_empty_job();

		Job_Disruptor.commit_job(current_index,test_job_list[writer_code][i]);

	}


return (void *)NULL;

}


void *test_reader(void *arg)
{

while(start == 1){__sync_synchronize();}

int reader_code = (*((int *)arg));

Job now_work;

int work_index = 0 ;
int Max_job_index;

	for(;;)
	{

	Max_job_index = Job_Disruptor.get_Max_available_job_index(reader_code);

		for(;work_index < Max_job_index;work_index++)
		{

		now_work = Job_Disruptor.get_next_job(work_index);		

		}

	}

return (void *)NULL;
}

pthread_t test_thread_a,test_thread_b;


Job test_job_list_a[job_number];

Job test_job_list_b[job_number];

void *test_get_Max_available_job_index(void *arg)
{

const int reader = (*(int*)arg);

while(start == 1){__sync_synchronize();}

int Max_job_index = 0;

	for(;;)
	{

	Max_job_index = Job_Disruptor.get_Max_available_job_index(reader);

	}


return (void*)NULL;

}


void test_multi_thread_get_Max_available_job_index(void)
{

int *reader_code = (int *)malloc(test_reader_num * sizeof(int));

pthread_t thread_id;

int i = 0;

	for(;i  < test_reader_num;i++)
	{

		reader_code[i] = i + 1;		


		pthread_create(&thread_id,0,test_get_Max_available_job_index,&(reader_code[i]));

	}

return;

}



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

#ifdef TEST_THREAD_GET_MAX_AVAILABLE_JOB_INDEX

test_multi_thread_get_Max_available_job_index();

#endif

#ifdef TEST_MULTI_THREAD_WRITER_AND_READER

test_multi_thread_writer_and_reader();

#endif

return 0;
}
