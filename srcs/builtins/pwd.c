
#include "minishell.h"
#include "minishell_louis.h"

int	check_params(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-')
			return (0);
		else if (ft_is_space(str[i]))
			i++;
		else
			return (1);
	}
	return (1);
}

void	print_dashes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < 2)
	{
		ft_dprintf(2, "%c", str[i]);
		i++;
	}
}

int	pwd_no_arg(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		return (ft_putendl_fd(cwd, 1), 0);
	return (1);
}

int	bt_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	t_cmd	*cmd;
	int		i;

	cmd = data->cmd[data->current_cmd];
	if (!cmd->cmd_args[1])
		return (pwd_no_arg(void));
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (check_params(data->cmd[data->current_cmd]->cmd_args[i]) == 0)
		{
			if (getcwd(cwd, PATH_MAX))
			{
				ft_putendl_fd(cwd, 1);
				return (0);
			}
			return (1);
		}
		i++;
	}
	ft_dprintf(2, "pwd: ");
	print_dashes(data->cmd[data->current_cmd]->cmd_args[1]);
	ft_dprintf(2, ": invalid option\n");
	return (2);
}
