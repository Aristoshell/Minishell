/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:15 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:16 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_print_env(t_envlist *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}
