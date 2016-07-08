#include <stdlib.h>
#include "Disruptor.h"
#define Max_ailable_Job_index 0
#define sucess 1
#define failure 0

typedef struct reader reader;

struct reader
{
int reader_index;
}


static Job *Ringbuffer;
/*
	Job list for reader and writer.
*/

static int *Reader_last_search_list;
/*
	This records all reader last search index by  
get_Max_available_job_index.

	Reader_last_search_list[Max_ailable_Job_index] is writed by commit_job.It is the begin that readers can read for the max search index reader.  

*/

static int **Reader_dependency_list;
/*
	This records all reader dependency.

	Reader_dependency_list[Max_ailable_Job_index] is for Disruptor. 	

	@simple:
		Assume three readers a,b and c.Reader c should work after a and b.Then,Reader_dependency_list[index of a] and Reader_dependency_list[index of b] are an array:Max_ailable_Job_index,which is one element.Reader_dependency_list[index of c] is an array:index of a,index of b.Thishas two elements.

*/

int _Create_Job_list_(int job_list_length,int reader_number)
{
	Ringbuffer = (Job *)malloc(job_list_length * sizeof(Job));

	if(Ringbuffer == NULL)
		{
			return failure;
		}

	Reader_last_search_list = (int *)malloc((reader_number + 1) * sizeof(reader));
	/*reader + 1:that "one" is for Max_ailable_Job_index*/	

	if(Reader_last_search_list == NULL)
		{
			return failure;
		}

	Reader_dependency_list = (int **)malloc((reader_number + 1) * sizeof(int *));
	/*reader + 1:that "one" is for Max_ailable_Job_index*/	


	if(Reader_dependency_list == NULL)
		{
			return failure;
		}

	return sucess;
}

int _Register_Reader_(int reader_index,int *reader_dependency_list,int list_length)
{
	
}


