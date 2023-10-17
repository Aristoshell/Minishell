#include "minishell.h"
#include "minishell_louis.h"

void	ft_print_redir_files(t_list *list_files)
{
	t_files	*curr_file;
	int		m;

	curr_file = (t_files *)list_files->content;
	m = 0;
	while (curr_file)
	{
		printf("\tfile [%d], %s (%d)\n", m, curr_file->filename, curr_file->filetype);
		m++;
		list_files = list_files->next;
		if (!list_files)
			return ;
		curr_file = (t_files *)list_files->content;
	}
}

void	ft_display_tab_cmd(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	printf("rentre\n");
	while (i < data->nb_command)
	{
		printf(GREEN"cmd %d\n"NC, i);
		j = 0;
		while (data->cmd[i] && data->cmd[i]->cmd_args[j])
		{
			if (data->cmd[i]->cmd_args[j][0])
				printf("arg[%d], %s\n", j, data->cmd[i]->cmd_args[j]);
			j++;
		}
		printf("arg[%d], %s\n", j, data->cmd[i]->cmd_args[j]);
		printf("in : %d, out : %d, more redir ? : %p\n", data->cmd[i]->fd_in, data->cmd[i]->fd_out, data->cmd[i]->list_files);
		if (data->cmd[i]->list_files)
			ft_print_redir_files(data->cmd[i]->list_files);
		printf("\n");
		i++;
	}
}
