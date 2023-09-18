/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:25 by madavid           #+#    #+#             */
/*   Updated: 2023/09/18 20:19:09 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_envlist *env)
{
	while (env)
	{
		if (MASK_EXPORT & env->flag && MASK_SET & env->flag)
			ft_dprintf(STDOUT_FILENO, GREEN"%s=%s\n"NC, env->key, env->val);
		env = env->next;
	}
}
