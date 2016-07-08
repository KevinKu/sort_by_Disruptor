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
int number;
char worker;
};


extern struct Disruptor
{

int (*Create_Job_list)(int,int);
/*
	Create job list for writer and reader.

	@parameter:
		   int : job list length
		   int : reader number
	@return:
		1 : sucess
		0 : failure
	@code:
		int info_init = Job_Disruptor.Create_Job_list(10,5);

		|This means that has a list of ten jobs and five readers.

*/

int (*get_empty_job)(void);
/*
	This is used for producer.Before producer writes a job to Disruptor,producer should call get_empty_job for getting an empty job index. 
	@return :  
		job index  : This index is used by commit_job.
*/
void (*commit_job)(int,Job);
/*
	Notice: This function only be used after get_empty_job.

*/


/*
	Simple code for get_empty_job and commit_job.	

	@code :

*/

int (*Register_Reader)(int,int *,int);
/*
	This function is used to register reader and build dependency with other readers.

	Notice:
	       This function should be called after Create_Job_list.

	@parameter:
		   int : the index of reader.It should be bigger than zero.And,it should be smaller than reader number or equal to.
		   int * : the dependency list of the reader with first int.If it is NULL,the register reader work after Max_ailable_Job_index(see ./Disruptor.c).
		   int : the dependency list length
		   Notice: 
			  Dependency list should not have the first int.
			  The function don't check whether third parameter is equal to the length of dependency list.
	@return:
		1 : sucess
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
Job (*get_next_job)(int);



}Job_Disruptor;




#endif
