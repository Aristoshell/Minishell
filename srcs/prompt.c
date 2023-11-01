
#include "minishell.h"
#include "minishell_louis.h"

int	prompt(t_data *data)
{
	const char	*input;
	int			check_error;

	while (1)
	{
		handle_signals_prompt();
		input = readline(PROMPT_COLOUR"aristoshell$ "PROMPT_RESET);
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
		}
		else if (!input)
		{
			ft_clean_t_data(data);
			clear_history();
			exit(0);
		}
	}
	return (clear_history(), FUNCTION_SUCCESS);
}
