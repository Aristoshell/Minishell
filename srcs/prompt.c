
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
			if (cross_array_list(data) == EXIT)
				return (clear_history(), ft_clean_t_data(data), EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			exit (0);
	}
	clear_history();
	return (FUNCTION_SUCCESS);
}
