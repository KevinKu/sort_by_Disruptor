def  print_job_list

	set $_head = $arg0

	set $_i = 0

		while($_i < $arg1)

		p ($_head)[$_i].job

		p ($_head)[$_i].array_head

		p ($_head)[$_i].array_length

		p ($_head)[$_i].worker

		p $_i = $_i + 1
		
		end

end
