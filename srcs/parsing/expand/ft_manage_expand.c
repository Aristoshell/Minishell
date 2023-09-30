
#include <minishell.h>

// single quote, pas d'expand
// double quote, expand

void	ft_pass_simple_quote(const char *input, int *count, int *i)
{
	*i += 1;
	*count += 1;
	while (input[*i] && input[*i] != '\'')
	{
		*i += 1;
		*count += 1;
	}
}


void	ft_pass_normal_text(int *count, int *i)
{
	*i += 1;
	*count += 1;
}

int	ft_get_expand_key(const char *input, int *i, char	*var_name)
{
	int		tmp_start;
	int		len_key;

	len_key = 0;
	*i += 1;
	tmp_start = *i;
	while (input[*i] && !ft_is_dollar(input[*i]) && !ft_is_operator(input[*i]))
	{
		len_key++;
		*i +=1 ;
	}
	var_name = ft_substr(input, (unsigned int)tmp_start, (size_t)len_key);
	if (!var_name)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}

void	ft_add_len_env_var(char *var_name, t_envlist *env, int *count)
{
	t_envlist	*tmp_start_env = env;

	while (env && ft_strncmp((const char*)var_name, (const char*)env->key, ft_strlen(env->key)))
		env = env->next;
	if (!env)
		return ;
	*count += ft_strlen(env->val);
	env = tmp_start_env;
}

int	ft_pass_dollar(const char *input, int *count, int *i, t_envlist *env)
{
	char		*var_name;
	
	var_name = NULL;
	if (!env)
		return (FUNCTION_SUCCESS);//penser a free varname
	if (ft_get_expand_key(input, i, var_name) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	ft_add_len_env_var(var_name, env, count);
	free(var_name);
	return (FUNCTION_SUCCESS);
}

int	ft_count_exp_input_size(const char *input, t_envlist *env)
{
	int		i;
	int		count;
	
	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_is_simple_quote(input[i]))
			ft_pass_simple_quote(input, &count, &i);
		else
		{
			if (ft_is_dollar(input[i]) && !ft_is_space(input[i + 1]))
			{
				if (ft_pass_dollar(input, &count, &i, env) != FUNCTION_SUCCESS) // attention ici il faudra mettre data env a la place de NULL
					return (MEMORY_ERROR_NB);
			}
			else
				ft_pass_normal_text(&count, &i);
		}
	}
	return (count);
}

char	*ft_manage_expand(const char *input, t_envlist *env) // a changer dans le .h
{
	int	input_size;
	int	expanded_input_size;
	char	*expanded; // a malloc

	expanded = NULL;
	input_size = ft_strlen(input);
	expanded_input_size = ft_count_exp_input_size(input, env);
	printf("Taille normal : %d |%s|\n", input_size, input);
	printf("Taille expanded : %d\n", expanded_input_size);
	return (expanded);
}
