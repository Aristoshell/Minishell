/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_marine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:39:26 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/20 18:53:01 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


char *get_args(char **argv)
{
    unsigned int i; 
    char *final;
    char space;

    i = 2;
    space = ' ';
    final = ft_strdup(argv[1]);
    final = strncat(final, &space, 1);
    while (argv[i] != NULL)
    {
        final = ft_strjoin(final, argv[i]);
        final = strncat(final, &space, 1);
        i++;
    }
    return (final);
}

//recuperation des arguments pour decouper comme le parsing le ferais
//a la place d'utiliser je char "|" on utilise "I" car cela creais des soucis


char **gen_first_cmd(char **argv)
{
	int i = 3;
	char *final;
	char **ret;

	final = ft_strdup(argv[2]);
	final = ft_strcat(final, " ");
	while(argv[i] && ft_strncmp(argv[i], "I", ft_strlen(argv[i])))
	{
		final = ft_strcat(final, argv[i]);
		final = ft_strcat(final, " ");
		i++;
	}
	ret = ft_split(final, ' ');
	free(final);
	return (ret);
}

char **gen_sec_cmd(char **argv)
{
	char *final;
	char **ret;
	
	int i = 2;
	
	while(argv[i] && ft_strncmp(argv[i], "I", ft_strlen(argv[i])))
		i++;
	i++;
	final = ft_strdup(argv[i]);
	final = ft_strcat(final, " ");
	i++;
	while(argv[i] && ft_strncmp(argv[i], "I", ft_strlen(argv[i])))
	{
		final = ft_strcat(final, argv[i]);
		final = ft_strcat(final, " ");
		i++;
	}
	ret = ft_split(final, ' ');
	free(final);
	return (ret);
}

char **gen_third_cmd(char **argv, int argc)
{
	char *final;
	char **ret;
	
	int i = 2;
	
	while(argv[i] && ft_strncmp(argv[i], "I", ft_strlen(argv[i])))
		i++;
	i++;
	while(argv[i] && ft_strncmp(argv[i], "I", ft_strlen(argv[i])))
		i++;
	i++;
	final = ft_strdup(argv[i]);
	final = ft_strcat(final, " ");
	i++;
	while(i < argc)
	{
		final = ft_strcat(final, argv[i]);
		final = ft_strcat(final, " ");
		i++;
	}
	ret = ft_split(final, ' ');
	free(final);
	return (ret);
}