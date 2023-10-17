
#include "minishell.h"
#include "minishell_louis.h"

void bt_echo2(t_data *data, t_cmd *cmd, int i)
{
	int j;

	while (cmd->cmd_args[i])
	{
		if (i != 1)
			write(1, " ", 1);
		j = 0;
		while (cmd->cmd_args[i][j])
		{
			if (cmd->cmd_args[i][j + 1] && cmd->cmd_args[i][j] == '$' && cmd->cmd_args[i][j + 1] == '?')
			{
				ft_dprintf(1, "%d", data->exec_val);
				j++;
			}
			else
				write(1, &cmd->cmd_args[i][j], 1);
			j++;
		}
		i++;
	}

}

int	bt_echo(t_data *data, int to_do)
{
	int	i;
	int	n_option;
	t_cmd	*cmd;

	cmd = data->cmd[to_do];
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
	bt_echo2(data, cmd, i);
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}