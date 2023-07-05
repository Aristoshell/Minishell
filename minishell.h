/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:47 by lmarchai          #+#    #+#             */
/*   Updated: 2023/07/04 15:54:45 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<readline/readline.h>
# include<readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>

typedef struct s_cmd
{
	pid_t	pid1;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
    int     infile;
    int     outfile;
}t_cmd;

char	**ft_split(char const *s, char c);