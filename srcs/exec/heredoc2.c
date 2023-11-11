/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:31:12 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 21:33:30 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	total_ascii(char **cmd, int multiplier)
{
	long	total;
	int		i;
	int		j;

	total = 1;
	i = 0;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			total += cmd[i][j];
			j++;
		}
		i++;
	}
	multiplier++;
	total *= multiplier;
	return (total);
}

char	*seeded_word(long nbr, char *alnum)
{
	char	*word;
	int		i;

	word = malloc((nbr / 10) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (nbr > 0)
	{
		word[i] = alnum[nbr % 36];
		nbr = nbr / 12;
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	clean_heredoc(t_data *data, t_pipe *pipes, char *limiter)
{
	int	i;

	i = 0;
	g_glb = 990;
	if (data->current_cmd > 1)
		waitpid(-1, NULL, 0);
	free(limiter);
	close(data->stdin_save);
	close(data->stdout_save);
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free(pipes);
	ft_dprintf(STDERR_FILENO, "!!!!ERROR MALLOC!!!!");
	exit(99);
}
