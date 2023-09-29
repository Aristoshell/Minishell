/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:11:46 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 12:11:11 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define HEXA_VAL "0123456789ABCDEF"
# define HEXA_VAL_MIN "0123456789abcdef"

char	*fill_str_with_param(char *new, va_list args, char c, int *size);
char	*fill_str_with_buff(char *new, char *buff, int *size);
char	*arg_to_content(char c, va_list args, int *size);
char	*fill_new(char	*str, va_list args, int *size);

char	*ft_intohex(char *str, unsigned long nbr, char *base_to);
char	*str_reverse(char *str);
char	*ft_itoa_hex(unsigned long nbr, char *base_to);

int		calc_char(unsigned int n);
char	*ft_itoa_u(unsigned int n);

char	*get_char(int c, int *size);
char	*get_string(char *str, int *size);
char	*get_pointer(unsigned long pntr, int *size);
char	*get_int(int nbr, int *size);
char	*get_unsigned_int(unsigned int nbr, int *size);
char	*get_hex_value_min(unsigned long nbr, int *size);
char	*get_hex_value(unsigned long nbr, int *size);

int		ft_dprintf(int i, char	*str, ...);
int		is_convert(char c);

#endif