
#include "minishell.h"
#include "minishell_louis.h"

void	ft_check_signal(t_data *data)
{
	if (g_glb == 130)
	{
		data->exec_val = 130;
		g_glb = 0;
	}
}

void	ft_no_input(t_data *data)
{
	int			exec_val;

	exec_val = data->exec_val;
	printf("exit\n"); // mon ft_printf est pete oups (il attend les args dun d printf)
	ft_clean_t_data(data);
	clear_history();
	exit(exec_val);
}

int	prompt(t_data *data)
{
	const char	*input;
	int			check_error;

	while (1)
	{
		handle_signals_prompt(data);
		input = readline("minishell$ ");
		ft_check_signal(data);
		if (input && input[0] != 0)
		{
			add_history(input);
			check_error = parsing(data, input);
			free((void *)input);
			input = NULL;
			if (check_error)
				return (clear_history(), ft_clean_t_data(data), MEMORY_ERR_NB);
			if (cross_array_list(data))
				return (clear_history(), ft_clean_t_data(data), EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			ft_no_input(data);
	}
	return (clear_history(), FUNCTION_SUCCESS);
}
