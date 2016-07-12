#include <stdlib.h>
#include "Disruptor.h"
#define Max_ailable_Job_index 0
#define success 1
#define failure 0

typedef struct reader_position reader_position;

struct reader_position
{
int reader_index;
}
/*consider cache line padding*/


static Job *Ringbuffer;
/*
	Job list for reader and writer.
*/

static int Ringbuffer_length;
/*
	Job list length.

	It is used to get the ringbuffer real index.
*/

static reader_position *Reader_last_search_list;
/*
	This records all reader last search index by  
get_Max_available_job_index.Reader_last_search_list[0] isn't used.

*/

static int **Reader_dependency_list;
/*
	This records all reader dependency.

	Reader_dependency_list[Max_ailable_Job_index] is for Disruptor. 	

	@simple:
		Assume three readers a,b and c.Reader c should work after a and b.Then,Reader_dependency_list[code of a] and Reader_dependency_list[code of b] are an array:Max_ailable_Job_index,which is one element.Reader_dependency_list[code of c] is an array:index of a,index of b.This has two elements.

*/

static reader_position *Reader_index;
/*
	It records all reader index and Max_ailable_Job_index.

	Reader_index[Max_ailable_Job_index] is writed by commit_job.It is the begin that readers can read for the max search index reader.Other index is writed by get_Max_available_job_index.  

*/

static int Reader_number;
/*
	It records reader number by Create_Job_list.

	Reader_number is used to check the reader_number by Register_Reader.

*/

static int *Dependency_list_number;
/*
*/

int _Create_Job_list_(const int job_list_length,int reader_number)
{
	if((job_list_length <= 0)||(reader_number <= 0))
		{
			return failure;
		}

	reader_number = reader_number + 1;

	Reader_number = reader_number;

	/*reader + 1:that "one" is for Max_ailable_Job_index*/
	
	Ringbuffer_length = job_list_length;

	Ringbuffer = (Job *)malloc(job_list_length * sizeof(Job));

	Reader_last_search_list = (reader_position *)malloc(reader_number * sizeof(reader_position));

	Reader_index = (reader_position *)malloc(reader_number * sizeof(reader_position));

	Reader_dependency_list = (int **)malloc(reader_number * sizeof(int *));

	Dependency_list_number = (int *)malloc(reader_number * sizeof(int));

	if((Ringbuffer == NULL)||(Reader_index == NULL)||(Reader_dependency_list == NULL)||(Reader_dependency_list == NULL)||(Dependency_list_number == NULL))
		{
			if(Ringbuffer != NULL)
				{
					free(Ringbuffer);
				}

			if(Reader_index != NULL)
				{
					free(Reader_index;
				}

			if(Reader_dependency_list != NULL)
				{
					free(Reader_dependency_list);
				}

			if(Reader_last_search_list != NULL)
				{
					free(Reader_last_search_list);
				}

			if(Dependency_list_number != NULL)
				{
					free(Dependency_list_number);
				}			

			return failure;
		}	

	int i = 0;

	for(; i < reader_number ; i++)
		{
			Reader_index[i]			= 0;
			Reader_dependency_list[i]	= (int *)NULL;
			Reader_last_search_list[i]	= 0;
		}

	return success;
}

int _Register_Reader_(const int reader_index,const int *reader_dependency_list,const int list_length)
{
	if((reader_index <= 0)||(reader_index >= Reader_number))
		{
			return failure;
		}
	
	if(Reader_dependency_list[reader_index] != (int *)NULL)
		{
			return failure;
		}	

	/*Reader_dependency_list[reader_index] isn't registered.*/

	if(reader_dependency_list == (int *)NULL)
		{
			Reader_dependency_list[reader_index] = (int *)malloc(sizeof(int));

			if(Reader_dependency_list[reader_index] == NULL)
				{
					return failure;
				}

			(*(Reader_dependency_list[reader_index])) = Max_ailable_Job_index;

			Dependency_list_number[reader_index] = 1;

			return success;
		}

	/*reader_dependency_list isn't NULL*/

	Reader_dependency_list[reader_index] = (int *)malloc(list_length * sizeof(int));

	if(Reader_dependency_list[reader_index] == (int *)NULL)
		{
			return failure;
		}		

	int i = 0;

	for(; i < list_length ; i++)
		{
			Reader_dependency_list[reader_index][i] = reader_dependency_list[i];
		}

	Dependency_list_number[reader_index] = list_length;

	return success;	
}

int _get_empty_job_()
{
}

void _commit_job_()
{
}

int _get_Max_available_job_index_()
{
}

Job _get_next_job_()
{
}

struct Disruptor
{
.Create_Job_list = _Create_Job_list_,
.Register_Reader = _Register_Reader_,
.get_empty_job = _get_empty_job_,
.commit_job = _commit_job_,
.get_Max_available_job_index = _get_Max_available_job_index_,
.get_next_job = _get_next_job_,
};
