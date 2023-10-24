
#include "minishell.h"
#include "minishell_louis.h"

int check_n(char *arg)
{
	int j;

	if (arg[0] != '-')
		return (0);
	j = 1;
	while (arg[j])
	{
		if (arg[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}

int	bt_echo(t_data *data, int to_do)
{
	int	i;
	int n_option;

	t_cmd	*cmd;
	cmd = data->cmd[to_do];
	n_option = 0;
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (check_n(cmd->cmd_args[i]) == 0)
			ft_putstr_fd(cmd->cmd_args[i], cmd->fd_out);
		else
			n_option = 1;
		i++;
	}
	if (n_option == 0)
		write(cmd->fd_out, "\n", 1);
	return (0);
}