/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:27 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/12 14:29:19 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	heredoc2(const char *limiter, int fd)
{
	const char	*input;

	while (1)
	{
		input = readline(">");
		if (g_glb == 130)
			return (-1);
		if (input && input[0] != 0)
		{
			if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0 && \
			(input[ft_strlen(limiter)] == 0 \
				|| input[ft_strlen(limiter)] == '\n'))
				return (0);
			ft_putstr_fd((char *)input, fd);
			write(fd, "\n", 1);
		}
		if (!input)
			return (printf("aristoshell: warning: here-document at line 1 \
				delimited by end-of-file (wanted `%s')\n", limiter), 0);
		input = NULL;
	}
	return (0);
}

int	heredoc(char *filename, char *limiter)
{
	int	fd;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd != -1)
	{
		if (heredoc2(limiter, fd) == -1)
			return (close(fd), -2);
		close(fd);
	}
	return (fd);
}

void	get_name(t_files *f, t_data *data, t_cmd *cmd, t_pipe *pipes)
{
	char	*limiter;

	limiter = f->filename;
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
	if (!f->filename)
		clean_heredoc(data, pipes, limiter);
	handle_signals_heredoc(data);
	cmd->fd_in = heredoc(f->filename, limiter);
	free(limiter);
}

int	handle_heredoc(t_data *data, t_pipe *pipes)
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
			get_name(f, data, cmd, pipes);
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
	return (cmd->fd_in);
}
