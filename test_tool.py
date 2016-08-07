import gdb
import string

class init_env_and_build_reader_dependency(gdb.Command):

	def __init__(self):
		super(init_env_and_build_reader_dependency,self).__init__("init_env_and_build_reader_dependency",gdb.COMMAND_USER)

	def invoke(self,file_name,from_tty):

		reader_data=open(file_name)

		test_data=reader_data.readline()

		num=test_data.split(" ")
		
		job_list_num = num[0]

		reader_num = num[1]

		c = "p Job_Disruptor.Create_Job_list("+job_list_num+","+reader_num+")"
		gdb.execute(c,True,True)

		c = "set $_h=(int*)malloc(sizeof(int)*"+reader_num+")"

		gdb.execute(c,True,True)

		i=1

		while(i <= int(reader_num)):

			reader_data.readline()

			reader_code = reader_data.readline()

			dependency_list_num = reader_data.readline()

			dependency_code = (reader_data.readline()).split(" ")

			_i=0


			while(_i < int(dependency_list_num)):

				c = "p $_h["+str(_i)+"]="+dependency_code[_i]
				gdb.execute(c,True,True)

				_i = _i + 1
			
			c = "p Job_Disruptor.Register_Reader("+reader_code+",$_h,"+dependency_list_num+")"

			gdb.execute(c,True,True)

			i = i + 1

		c = "p free($_h)"

		gdb.execute(c,True,True)

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
init_env_and_build_reader_dependency()

