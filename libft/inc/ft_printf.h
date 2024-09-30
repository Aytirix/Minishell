/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:30:05 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/30 16:12:21 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);
int		ft_putnbrbase(unsigned long long n, char *base, unsigned int lenbase);
int		ft_putuinbr(unsigned int n);
int		ft_nbrlen(int nb);
int		ft_handle_adress(unsigned long long p);

#endif