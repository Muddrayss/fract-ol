/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_julia_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:03:01 by egualand          #+#    #+#             */
/*   Updated: 2023/12/21 16:22:47 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_isdigit_or_minus(char c)
{
	if (c == '-' || c == '.' || (c > '0' && c < '9'))
		return (1);
	return (0);
}

static int	check_minus(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '-')
	{
		i++;
		count++;
	}
	while (str[i])
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

static int	check_dots(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '.')
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int	check_julia_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 2;
	if (argc == 4)
	{
		while (i < argc)
		{
			if (!check_minus(argv[i]) || !check_dots(argv[i]))
				return (0);
			j = 0;
			while (argv[i][j])
			{
				if (!ft_isdigit_or_minus(argv[i][j]))
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}
