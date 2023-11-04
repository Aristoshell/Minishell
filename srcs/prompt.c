
#include "minishell.h"
#include "minishell_louis.h"

int	prompt(t_data *data)
{
	const char	*input;
	int			check_error;
	int			exec_val;

	while (1)
	{
		handle_signals_prompt(data);
		input = readline("minishell$ ");
		if (g_glb == 130)
		{
			data->exec_val = 130;
			g_glb = 0;
		}
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
		{
			exec_val = data->exec_val;
			printf("exit\n");
			ft_clean_t_data(data);
			clear_history();
			exit(exec_val);
		}
	}
	return (clear_history(), FUNCTION_SUCCESS);
}
