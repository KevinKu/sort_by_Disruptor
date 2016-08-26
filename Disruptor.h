#ifndef _DISRUPTOR_H_
#define _DISRUPTOR_H_
#define sort b
#define separate a

typedef struct Job Job;

typedef struct Disruptor Disruptor;

struct Job
{
char job;
int *array_head;
int array_length;
char worker;
};

/*
job		:sort or separate
array_head	:sorted list
array_length	:the list length
worker		:which thread do this job
*/

extern struct Disruptor
{

int (*Create_Job_list)(const int,const int);
/*
	Create job list for writer and reader.

	@parameter:
		   const int : job list length
		   int : reader number
	@return:
		1 : success
		0 : failure
	@code:
		int info_init = Job_Disruptor.Create_Job_list(10,5);

		|This means that has a list of ten jobs and five readers.The code of readers are 1,2,3,4 and 5.

*/

int (*get_empty_job)(void);
/*
	Notice:This function should be used after all reader register.

	This is used for writer.Before producer writes a job to Disruptor,producer should call get_empty_job for getting an empty job index. 
	
	@return :  
		job index  : This index is used by commit_job.
*/
void (*commit_job)(int,Job);
/*
	Notice: This function only be used after get_empty_job.

	This function is used to write a job in job list.
	
	@parameter:
		   int:the index of get_empty_job's return.
		   Job:job which be written in job list

*/


/*
	Simple code for get_empty_job and commit_job.	

	@code :
	       current_index = Job_Disruptor.get_empty_job();

	       Job_Disruptor.commit_job(current_index,job_array[i]);	
*/

int (*Register_Reader)(const int,const int *,const int);
/*
	This function is used to register reader and build dependency with other readers.

	Notice:
	       This function should be called after Create_Job_list return success.

	@parameter:
		   const int : the index of reader.It should be bigger than zero.And,it should be smaller than reader number or equal to.
		   const int * : the dependency list of the reader with first int.If it is NULL,the register reader work after Max_ailable_Job_index(see ./Disruptor.c).
		   const int : the dependency list length
		   Notice: 
			  Dependency list should not have the first int.
			  The function don't check whether third parameter is equal to the length of dependency list.
	@return:
		1 : success
		0 : failure
	@code:
	      int dependency_list[2];
	      dependency_list[0]=1;
	      dependency_list[1]=2;
	      //work after reader 1 and reader 2.
	      int info_reader = Job_Disruptor.Register_Reader(3,dependency_list,2);
	      |Then,reader 3 will work after reader 1 and reader 2.

*/


int (*get_Max_available_job_index)(int);
/*
	This function is used to get max read job list index.	

	Notice:
		The return value isn't used by get_next_job.

	@parameter:
		   int : reader code
	@return:
		the min dependency reader index
	@code:

*/
Job (*get_next_job)(int);
/*

	This function is used to get job data.

	@parameter:
		   int : ringbuffer position.It should be smaller than get_Max_available_job_index return value.

	@return:
		Job : work job.	

	@code:

*/


}Job_Disruptor;




#endif
