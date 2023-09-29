
#include "minishell.h"
#include "minishell_louis.h"

int	bt_echo(t_cmd **cmd_tab, int to_do)
{
	int	i;
	int	n_option;
	t_cmd	*cmd;
	
	cmd = cmd_tab[to_do];
	i = 1;
	n_option = 0;
	
	if (cmd->cmd_args[1] != NULL)
	{
		if (ft_strncmp(cmd->cmd_args[1], "-n", ft_strlen(cmd->cmd_args[1])) == 0)
		{
			n_option = 1;
			i++;
		}
	}
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		if (cmd->cmd_args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}