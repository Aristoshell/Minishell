/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 20:19:18 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_envlist *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}
