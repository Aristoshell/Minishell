/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_marine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:39:26 by lmarchai          #+#    #+#             */
/*   Updated: 2023/07/11 18:35:42 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char* ft_strncat(char* destination, const char* source, size_t num)
{
    char* ptr = destination + ft_strlen(destination);
    while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return (destination);
}

char *get_args(char **argv)
{
    unsigned int i; 
    char *final;
    char space;

    i = 2;
    space = ' ';
    final = ft_strdup(argv[1]);
    final = ft_strncat(final, &space, 1);
    while (argv[i] != NULL)
    {
        final = ft_strjoin(final, argv[i]);
        final = ft_strncat(final, &space, 1);
        i++;
    }
    return (final);
}

char **gen_first_cmd(char **argv)
{
	int i = 2;
	char *final;

	final = ft_strdup(argv[1]);
	final = strcat(final, " ");
	while(argv[i] && ft_strncmp(argv[i], "|", ft_strlen(argv[i])))
	{
		final = strcat(final, argv[i]);
		final = strcat(final, " ");
		i++;
	}
	return (ft_split(final, ' '));
}

char **gen_sec_cmd(char **argv, int argc)
{
	char *final;
	int i = 2;
	
	while(argv[i] && ft_strncmp(argv[i], "|", ft_strlen(argv[i])))
		i++;
	i++;
	final = ft_strdup(argv[i]);
	final = strcat(final, " ");
	i++;
	while(i < argc)
	{
		final = strcat(final, argv[i]);
		final = strcat(final, " ");
		i++;
	}
	return (ft_split(final, ' '));
}