/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:21:30 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 13:51:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*add_string(char *s1, char *s2, int size_s1, int size_s2)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * size_s1 + size_s2);
	if (!res)
		return (NULL);
	while (i < size_s1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < size_s2)
	{
		res[i + size_s1] = s2[i];
		i++;
	}
	return (res);
}

char	*dup_string(char *src, int size)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}

char	*fill_str_with_param(char *new, va_list args, char c, int *size)
{
	char	*to_add;
	char	*temp;
	int		len_new;

	len_new = *size;
	to_add = arg_to_content(c, args, size);
	if (new == NULL || *size == 0)
	{
		new = dup_string(to_add, *size - len_new);
		return (free(to_add), new);
	}
	temp = dup_string(new, len_new);
	free(new);
	new = add_string(temp, to_add, len_new, *size - len_new);
	free(temp);
	return (free(to_add), new);
}

char	*fill_str_with_buff(char *new, char *buff, int *size)
{
	int		len_new;
	char	*temp;

	if (buff[0] == '\0')
		return (new);
	len_new = *size;
	*size += ft_strlen(buff);
	if (new == NULL || *size == 0)
		new = ft_strdup(buff);
	else
	{
		temp = dup_string(new, len_new);
		free(new);
		new = add_string(temp, buff, len_new, *size - len_new);
		free(temp);
	}
	return (new);
}

char	*fill_new(char	*str, va_list args, int *size)
{
	int		i;
	int		j;
	char	*new;
	char	buff[64];

	i = 0;
	new = NULL;
	while (str[i] != '\0')
	{
		j = 0;
		ft_bzero(buff, 64);
		while (str[i] != '\0' && str[i] != '%' && j < 64)
			buff[++j - 1] = str[++i - 1];
		if (j > 0)
			new = fill_str_with_buff(new, buff, size);
		if (str[i] == '%' && str[i + 1] != '\0' && is_convert(str[i + 1]) == 1)
		{
			new = fill_str_with_param(new, args, str[i + 1], size);
			i += 2;
		}
	}
	return (new);
}
