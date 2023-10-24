/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/23 12:58:44 by lmarchai         ###   ########.fr       */
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

char	*add_char(char *s, char c)
{
	int				len_tot;
	unsigned int	i;
	char			*res;

	if (s[0] == '\0')
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		return (res[0] = c, res[1] = 0, res);
	}
	len_tot = ft_strlen(s);
	res = malloc(sizeof(char) * len_tot + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return (free(s), res);
}

int	heredoc2(const char *limiter, int fd)
{
	char	input;

	handle_signals_heredoc();
	while (1)
	{
		if (read(0, &input, 1) == -1)
		{
			perror("read");
			break ;
		}
		if (input == '\n')
			break ;
		if (input == 0)
		{
			printf("\n");
			printf("warning: here-document at line 1 delimited\
				 by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (g_glb == 130)
		{
			printf("hello\n");
			break ;
		}
		write(fd, &input, 1);
	}
	return (fd);
}

int heredoc(char *limiter, t_data *data)
{
	int result;
	int fd;

	fd = data->cmd[data->current_cmd]->fd_in;
	if (fd == -1)
		return (-1);
	result = heredoc2(limiter, fd);
	return (result);
}

int	handle_heredoc(t_data *data)
{
	t_files	*f;
	t_list	*l;
	t_cmd	*cmd;

	cmd = data->cmd[data->current_cmd];
	l = cmd->list_files;
	if (!l)
		return (0);
	f = (t_files *)l->content;
	while (l)
	{
		if (f->filetype == heredoc_)
		{
			cmd->fd_in = heredoc(f->filename, data);
			handle_signals_prompt();
			if (!data->cmd[data->current_cmd]->cmd_args)
			{
				f->filename = seeded_word(785 * (data->nb_command + 1), \
				"abcdefghijklmnopqrstuvwxyz0123456789");
			}
			else
			{
				f->filename = seeded_word(total_ascii \
					(data->cmd[data->current_cmd]->cmd_args, \
					data->current_cmd), \
					"abcdefghijklmnopqrstuvwxyz0123456789");
			}
			cmd->input = file_from;
		}
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
	return (cmd->fd_in);
}
