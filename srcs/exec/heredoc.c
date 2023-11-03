/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/03 12:02:18 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int				len_tot;
	unsigned int	i;
	char			*res;

	len_tot = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof (char) * len_tot + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	res[len_tot] = '\0';
	return (free(s1), res);
}

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

int	heredoc2(const char *limiter, int fd)
{
	const char	*input;

	while(1)
	{
		input = readline(">");
		if (g_glb == 130)
			return (-1);
		if (!input || input[0] == 0)
			return (printf("aristoshell: warning: here-document at line 1 delimited by end-of-file (wanted `stop')\n"), 0);
		if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0 && \
			(input[ft_strlen(limiter)] == 0 || input[ft_strlen(limiter)] == '\n'))
			return (0);
		else
		{
			ft_putstr_fd((char *)input, fd);
			write(fd, "\n", 1);
		}
		input = NULL;
	}
	return (0);
}

int heredoc(char *filename, char *limiter)
{
	int fd;
	
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd != -1)
	{
		if (heredoc2(limiter, fd) == -1)
			return (close(fd),-2);
		close(fd);
	}
	return (fd);
}

int	handle_heredoc(t_data *data)
{
	t_files	*f;
	t_list	*l;
	t_cmd	*cmd;
	char 	*limiter;

	cmd = data->cmd[data->current_cmd];
	l = cmd->list_files;
	if (!l)
		return (0);
	f = (t_files *)l->content;
	while (l)
	{
		if (f->filetype == heredoc_)
		{
			limiter = f->filename;
			if (!data->cmd[data->current_cmd]->cmd_args)
			{
				f->filename = seeded_word(785 * (data->nb_command + 1), \
				"abcdefghijklmnopqrstuvwxyz0123456789");
				if (!f->filename)
				{
					//error 1
					return (-1);
				}
			}
			else
			{
				f->filename = seeded_word(total_ascii \
					(data->cmd[data->current_cmd]->cmd_args, \
					data->current_cmd), \
					"abcdefghijklmnopqrstuvwxyz0123456789");
				if (!f->filename)
				{
					//error 1
					return (-1);
				}
			}
			handle_signals_heredoc(data);
			cmd->fd_in = heredoc(f->filename, limiter);
			free(limiter);
			handle_signals_prompt(data);
		}
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
	return (cmd->fd_in);
}
