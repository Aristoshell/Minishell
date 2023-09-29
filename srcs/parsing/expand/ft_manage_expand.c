/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:36:40 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 17:51:15 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// single quote, pas d'expand
// double quote, expand

bool	word_has_expand(const char *token_val)
{
	int		i;
	int a =0;
	(void)a;
	i = 0;
	while (token_val[i])
	{
		if (ft_is_simple_quote(token_val[i]))
		{
			i++;
			while (token_val[i] && token_val[i] != '\'')
				i++;
		}
		else if (ft_is_double_quote(token_val[i]))
		{
			i++;
			while (token_val[i] && token_val[i] != '"')
			{
				if (ft_is_dollar(token_val[i]))
					return (true);
				i++;
			}
		}
		else if (ft_is_dollar(token_val[i]))
			return (true);
		i++;
	}
	return (false);
}

void	pass_simple_quote(const char *input, int *count, int *i)
{
	*i += 1;
	*count += 1;
	while (input[*i] && input[*i] != '\'')
	{
		*i += 1;
		*count += 1;
	}
}


void	pass_normal_text(int *count, int *i)
{
	*i += 1;
	*count += 1;
}

int	pass_dollar(const char *input, int *count, int *i, t_envlist *env)
{
	char		*var_name;
	int			len_key;
	int			tmp_start;
	t_envlist	*tmp_start_env = env;
	
	if (!env)
		return (FUNCTION_SUCCESS);//penser a free varname
	//identifier le nom de la variable (en gros, tant quon na pas despace ou de $);//pendant ce temps la on i++ mais pas count
	*i += 1;
	tmp_start = *i;
	len_key = 0;
	while (input[*i] && !ft_is_dollar(input[*i]) && !ft_is_operator(input[*i]))
	{
		len_key++;
		*i +=1 ;
	}
	var_name = ft_substr(input, (unsigned int)tmp_start, (size_t)len_key);
	if (!var_name)
		return (MEMORY_ERROR_NB);
	// chercher la correspondance 
	while (env && ft_strncmp((const char*)var_name, (const char*)env->key, ft_strlen(env->key)))
		env = env->next;
	if (!env)
		return(FUNCTION_SUCCESS);//penser a free varname
	*count += ft_strlen(env->val);
	env = tmp_start_env;
	free(var_name);
	return (*count);
}

int	count_exp_input_size(const char *input, t_envlist *env)
{
	int		i;
	int		count;
	
	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_is_simple_quote(input[i]))
			pass_simple_quote(input, &count, &i);
		else
		{
			if (ft_is_dollar(input[i]) && !ft_is_space(input[i + 1]))
				pass_dollar(input, &count, &i, env); // attention ici il faudra mettre data env a la place de NULL
			else
				pass_normal_text(&count, &i);
		}
	}
	return (count);
}

void	ft_manage_expand(const char *input, t_envlist *env)
{
	int	input_size;
	int	expanded_input_size;

	input_size = ft_strlen(input);
	expanded_input_size = count_exp_input_size(input, env);
	printf("Taille normal : %d |%s|\n", input_size, input);
	printf("Taille expanded : %d\n", expanded_input_size);
}
