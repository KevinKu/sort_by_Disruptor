#ifndef _DISRUPTOR_H_
#define _DISRUPTOR_H_


typedef struct Job Job;

typedef struct Disruptor Disruptor;

extern struct Job{
int *array_head;
int number;
char worker;
};


extern struct Disruptor{


int *Reader_last_search_list;
/*
	This records all reader last search index by  
get_Max_available_job_index.  

*/
int **Reader_dependency_list;
/*
	This records all reader dependency.

*/
Job *ringbuffer;
/*
*/

void (*Create_ring_buffer)();
/*
*/

int (*get_empty_job)(void);
/*
	This is used for producer.Before producer writes a job to Disruptor,producer should call get_empty_job for getting an empty job index. 
	return :  job index 
		This index is used by commit_job.
*/
void (*commit_job)(int,Job);
/*
	Notice: This function only be used after get_empty_job.

	p
*/

int (*register_reader)(int);
int (*get_Max_available_job_index)(int);
Job (*get_next_job)(int);



}Disruptor;




#endif
