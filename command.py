import gdb
import string

class test_gdb_python_command(gdb.Command):

	"""test help"""

	def __init__(self):

		super(test_gdb_python_command,self).__init__("test_gdb_python_command",gdb.COMMAND_USER)

	def invoke(self,arg,from_tty):

		print("gdb test")

test_gdb_python_command()
