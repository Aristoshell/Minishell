/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:38:41 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 16:29:04 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("exit\n");
	ft_clean_t_data(data);
	rl_clear_history();
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
				return (rl_clear_history(), \
					ft_clean_t_data(data), MEMORY_ERR_NB);
			if (cross_array_list(data))
				return (rl_clear_history(), ft_clean_t_data(data), EXIT);
			ft_reinit_data(data);
		}
		else if (!input)
			ft_no_input(data);
	}
	return (rl_clear_history(), FUNCTION_SUCCESS);
}
