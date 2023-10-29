1 - dup stdin/stdout
2 - pipe
1er fail = cross_array (pipe) done
	3 - filename heredoc
	4 - open heredoc fd
		2eme fail = gen_child - handle_heredoc - seeded_word
		3eme fail = gen_child - handle_heredoc - heredoc - open fd heredoc
		4eme fail = gen_child - fork
	child case
		5 - envp = list_to_array envp
		6 - potentiel fd open
		5eme fail = child_process - ft_split
		7 - path_cmd = cmd->path_cmd
			6eme fail = tmp (get_cmd)
			8 - tmp
			7eme fail = to_try(get_cmd)
			9 - to try
	no child case
		5 - potentiel fd open
		

	