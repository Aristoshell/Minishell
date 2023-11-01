
#include "minishell.h"
#include "minishell_louis.h"

int ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void bt_exit(t_data *data, int i, t_pipe *pipes)
{
	int exit_val;
	t_cmd *built_cmd;

	built_cmd = data->cmd[i];
	exit_val = 0;
	if (!built_cmd->cmd_args[1])
	{
		printf("exit\n");
		if (data->nb_command > 1)
			close_pipes(data, pipes);
		close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
		close_files(data);
		ft_clean_t_data(data);
		exit(0);
	}
	if (ft_isnumber((built_cmd->cmd_args[1])))
	{
		if (built_cmd->cmd_args[2] != NULL)
		{
			exit_val = 1;
			printf("exit: too many arguments\n");
			return;
		}
		exit_val = ft_atoi(built_cmd->cmd_args[1]) % 256;
	}
	else
		error_management(built_cmd, "exit: numeric argument required", 2);
	if (data->nb_command > 1)
		close_pipes(data, pipes);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	ft_clean_t_data(data);
	printf("exit\n");
	exit(exit_val);
}
