/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:03:25 by madavid           #+#    #+#             */
/*   Updated: 2023/09/15 20:24:16 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_envlist *env, )
{
	
}

// export tout court va afficher la liste dans l'ordre alphabetique, du coup des que je fais export dune valeur je vais rajouter le node directement au bon endroit
void	display_export(t_envlist *env)
{
	while (env)
	{
		if (MASK_EXPORT & env->flag) // si different de 0
			printf("export %s\"=%s\"\n", env->key, env->val);
		env = env->next;
	}
}

// export qq chose
// avec val ou pas
