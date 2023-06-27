/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:43:35 by madavid           #+#    #+#             */
/*   Updated: 2023/02/08 17:43:40 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*s_new;

	i = 0;
	j = 0;
	if (!s1 || ! s2)
		return (NULL);
	s_new = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (s_new == NULL)
		return (NULL);
	while (i < ft_strlen_gnl(s1))
	{
		s_new[i] = s1[i];
		i++;
	}
	while (j < ft_strlen_gnl(s2))
		s_new[i++] = s2[j++];
	if (ft_strlen_gnl(s1) != 0)
		free(s1);
	return (s_new[i] = 0, s_new);
}

int	find_new_line(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' && (i != ft_strlen_gnl(buffer)))
		return (i + 1);
	else
		return (0);
}

void	cut_and_save(char **to_truncate, char *to_save, int buffer_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void) buffer_size;
	while ((*to_truncate)[i] != '\n' && (*to_truncate)[i] != '\0')
		i++;
	i++;
	while (j < buffer_size)
	{
		(to_save)[j] = 0;
		j++;
	}
	j = 0;
	while ((*to_truncate)[i] != '\0')
	{
		(to_save)[j] = (*to_truncate)[i];
		(*to_truncate)[i] = 0;
		i++;
		j++;
	}
}

char	*ft_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*stash;
	int			readc;

	stash = "";
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (buffer[0] == '\0')
		readc = read(fd, buffer, BUFFER_SIZE);
	while (find_new_line(buffer) == 0)
	{
		stash = ft_strjoin_gnl(stash, buffer);
		readc = read(fd, buffer, BUFFER_SIZE);
		buffer[readc] = 0;
		if (readc <= 0)
		{
			if (*stash)
				return (stash);
			else
				return (free(stash), NULL);
		}
	}
	stash = ft_strjoin_gnl(stash, buffer);
	return (cut_and_save(&stash, buffer, BUFFER_SIZE), stash);
}
