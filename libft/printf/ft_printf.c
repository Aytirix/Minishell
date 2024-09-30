/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:27:56 by dbislimi          #+#    #+#             */
/*   Updated: 2024/05/07 14:22:39 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	manage_format(char c, va_list arg, unsigned int *pc)
{
	if (c == 'c')
		*pc += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		*pc += ft_putstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		*pc += ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		*pc += ft_putuinbr(va_arg(arg, unsigned int));
	else if (c == 'p')
		*pc += ft_handle_adress(va_arg(arg, unsigned long long));
	else if (c == 'x')
		*pc += ft_putnbrbase(va_arg(arg, unsigned int), "0123456789abcdef", 16);
	else if (c == 'X')
		*pc += ft_putnbrbase(va_arg(arg, unsigned int), "0123456789ABCDEF", 16);
	else if (c == '%')
		*pc += ft_putchar('%');
}

static int	analyse_the_string(const char *s, va_list arg)
{
	unsigned int	printed_char;
	int				i;

	i = 0;
	printed_char = 0;
	while (s[i])
	{
		while (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]) != NULL)
		{
			manage_format(s[++i], arg, &printed_char);
			i++;
		}
		if (s[i])
		{
			write(1, &s[i++], 1);
			printed_char++;
		}
	}
	return (printed_char);
}

int	ft_printf(const char *s, ...)
{
	int		printed_char;
	va_list	ap;

	va_start(ap, s);
	printed_char = analyse_the_string(s, ap);
	va_end(ap);
	return (printed_char);
}
