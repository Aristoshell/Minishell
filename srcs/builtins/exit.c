
#include "minishell.h"
#include "minishell_louis.h"

void	error_exit(t_cmd *cmd, int exit_val)
{
	if (!cmd)
		return ;
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
		cmd->cmd_args[1]);
	exit(exit_val);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_no_code(t_data *data, t_pipe *pipes)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (data->nb_command > 1)
		close_pipes(data, pipes);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	ft_clean_t_data(data);
	exit(0);
}

int	exit_with_code(t_cmd *built_cmd, int *exit_val)
{
	if (built_cmd->cmd_args[2] != NULL)
	{
		*exit_val = 1;
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (1);
	}
	*exit_val = ft_atoi(built_cmd->cmd_args[1]) % 256;
	return (0);
}

int	bt_exit(t_data *data, int i, t_pipe *pipes)
{
	int		exit_val;
	t_cmd	*built_cmd;

	built_cmd = data->cmd[i];
	exit_val = 0;
	if (!built_cmd->cmd_args[1])
		exit_no_code();
	if (ft_isnumber((built_cmd->cmd_args[1])))
	{
		if (exit_with_code(built_cmd, &exit_val) == 1)
			return (1);
	}
	else
		error_exit(built_cmd, 2);
	if (data->nb_command > 1)
		close_pipes(data, pipes);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	ft_clean_t_data(data);
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit(exit_val);
	return (0);
}
