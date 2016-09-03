import gdb
import string

class init_test_job_list_and_reader_dependency(gdb.Command):

	def __init__(self):
		super(init_test_job_list_and_reader_dependency,self).__init__("init_test_job_list_and_reader_dependency",gdb.COMMAND_USER)

	def invoke(self,file_name,from_tty):


		(job_list_file,reader_dependency_file) = file_name.split(" ")

		job_list_info = open(job_list_file)

		tmp = job_list_info.readline()

		_tmp = tmp.split(" ")

		job_list_length = _tmp[0]

		reader_num = _tmp[1]

		c = "init_job_list "+job_list_length+" "+reader_num

		gdb.execute(c,True,True)

		c = "init_reader_dependency "+reader_dependency_file

		gdb.execute(c,True,True)

		print("success")


		
	

class init_job_list(gdb.Command):

	def __init__(self):
		super(init_job_list,self).__init__("init_job_list",gdb.COMMAND_USER)

	def invoke(self,arg,from_tty):

		(job_list_length,reader_num)=arg.split(" ")

		c = "p Job_Disruptor.Create_Job_list("+ job_list_length +","+ reader_num +")"

		gdb.execute(c,True,True)

		print("success")


class init_writer_test_job_data_from_file(gdb.Command):

	def __init__(self):
		super(init_writer_test_job_data_from_file,self).__init__("init_writer_test_job_data_from_file",gdb.COMMAND_USER)

	def invoke(self,file_name,from_tty): 

		writer_info = open(file_name)

		writer_num = writer_info.readline()

		writer_num = writer_num.split(" ")

		writer_num = writer_num[0]

		i = 0

		c = "p test_writer_num="+writer_num

		gdb.execute(c,True,True)

		c = "p test_job_length=(int *)malloc(sizeof(int)*"+writer_num+")"

		gdb.execute(c,True,True)

		c = "p test_job_list=(Job **)malloc(sizeof(Job*)*"+writer_num+")"

		gdb.execute(c,True,True)

		writer_info.readline()

		while(i < int(str(writer_num))):

			writer_job_list_info = writer_info.readline()


			tmp = writer_job_list_info.split(" ")

			tmp_data = writer_job_list_info.split(" ")

			list_length = tmp_data[0]

			job_list_file_name = tmp_data[1]


			c = "p test_job_list["+str(i)+"]=(Job *)malloc(sizeof(Job)*"+list_length+")"

			gdb.execute(c,True,True)

			c = "p test_job_length["+str(i)+"]= "+list_length

			gdb.execute(c,True,True)

			c = "insert_job_list_from_file test_job_list["+str(i)+"] "+list_length +" "+job_list_file_name

			gdb.execute(c,True,True)

			i = i + 1

		print("init success")

class init_reader_dependency(gdb.Command):

	def __init__(self):
		super(init_reader_dependency,self).__init__("init_reader_dependency",gdb.COMMAND_USER)

	def invoke(self,file_name,from_tty):

		reader_data=open(file_name)

		test_data=reader_data.readline()

		num=test_data.split(" ")

		reader_num = num[0]

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

		print("init success")

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
				gdb.execute(c,True,True)
				c="p "+job_list_head+"["+str(i)+"]"+".array_head="+data[1]
				gdb.execute(c,True,True)
				c="p "+job_list_head+"["+str(i)+"]"+".array_length="+data[2]
				gdb.execute(c,True,True)
				c="p "+job_list_head+"["+str(i)+"]"+".worker="+"'"+data[3]+"'"
				gdb.execute(c,True,True)
				i = i + 1

		print("insert success")


insert_job_list_from_file()

"""
insert_job_list_from_file 

Use : 

insert_job_list_from_file job_list_name job_list_length file_name


"""


test_get_empty_job_env_init()

"""

test_get_empty_job_env_init

Use : 

test_get_empty_job_env_init job_list_length

"""


init_reader_dependency()

"""
init_env_and_build_reader_dependency

Use : 

init_env_and_build_reader_dependency file_name

Test_main.c parameter : 

"""

init_writer_test_job_data_from_file()

"""
init_writer_test_job_data_from_file

Use :

init_writer_test_job_data_from_file file_name

Test_main.c parameter : 

test_writer_num , test_job_length , test_job_list 

"""

init_job_list()

"""
init_job_list

Use : 

init_job_list job_list_length reader_number

Test_main.c parameter :

none

"""

init_test_job_list_and_reader_dependency()


"""
init_test_job_list_and_reader_dependency

Use :

init_test_job_list_and_reader_dependency job_list_info_file_name

 reader_dependency_info_file_name

Test_main.c parameter :

test_reader_num

"""


