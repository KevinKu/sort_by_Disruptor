import gdb
import string

class test_get_empty_job_env_init(gdb.Command):

	def __init__(self):
		super(test_get_empty_job_env_init,self).__init__("test_get_empty_job_env_init",gdb.COMMAND_USER)

	def invoke(self,arg,from_tty):		

		c = "p Job_Disruptor.Create_Job_list("+ arg +",1)"
		gdb.execute(c,True,True)

		c = "p Job_Disruptor.Register_Reader(1,0,0)"
		gdb.execute(c,True,True)
	
		print("init success")

class insert_job_list_from_file(gdb.Command):

	def __init__(self):
		super(insert_job_list_from_file,self).__init__("insert_job_list_from_file",gdb.COMMAND_USER)


	def invoke(self,arg,from_tty):
		(job_list_head,list_length,file_name)=arg.split(" ")
		test_data=open(file_name)
		i = 0
		for line in test_data:
			if i < int(list_length):
				data=line.split(" ")
				c="p "+job_list_head+"["+str(i)+"]"+".job="+"'"+data[0]+"'"
				gdb.execute(c,False,False)
				c="p "+job_list_head+"["+str(i)+"]"+".array_head="+data[1]
				gdb.execute(c,False,False)
				c="p "+job_list_head+"["+str(i)+"]"+".array_length="+data[2]
				gdb.execute(c,False,False)
				c="p "+job_list_head+"["+str(i)+"]"+".worker="+"'"+data[3]+"'"
				gdb.execute(c,False,False)
				i = i + 1
	


insert_job_list_from_file()
test_get_empty_job_env_init()
