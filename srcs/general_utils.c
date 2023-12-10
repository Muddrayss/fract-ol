/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:37:07 by craimond          #+#    #+#             */
/*   Updated: 2023/12/10 01:28:46 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
int	quit(char id, t_gdata *data)
{
	t_wdata *win_data;

	if (data)
	{
		win_data = data->win_data;
		mlx_destroy_window(win_data->mlx, win_data->win);
		mlx_destroy_image(win_data->mlx, win_data->img);
		mlx_destroy_display(win_data->mlx);
		free(win_data->mlx);
	}
	exit(id);
}

int	press_x(t_gdata *data)
{
	quit(0, data);
	return (0);
}

