/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:56:17 by egualand          #+#    #+#             */
/*   Updated: 2023/12/27 14:00:57 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_color(t_gdata *data, int x, int y, unsigned short intensity)
{
	t_color			clr;
	unsigned int	clr_hex;

	if (data->frequency > 0.5)
		data->frequency = 0.1;
	if (intensity >= (int)data->max_iter)
		clr_hex = 0x000000;
	else
	{
		clr.red = sin(data->frequency * intensity + 0) * 127 + 128;
		clr.blue = sin(data->frequency * intensity + 2 * PI / 3) * 127 + 128;
		clr.green = sin(data->frequency * intensity + 4 * PI / 3) * 127 + 128;
		clr_hex = ((int)clr.red << 16) | ((int)clr.green << 8) | (int)clr.blue;
	}
	my_mlx_pixel_put(data, x, y, clr_hex);
}

void	my_mlx_pixel_put(t_gdata *data, int x, int y, unsigned int color)
{
	int	index;

	index = y * data->win_data->line_length + x
		* (data->win_data->bits_per_pixel / 8);
	data->win_data->addr[index] = color & 0xFF;
	data->win_data->addr[index + 1] = (color >> 8) & 0xFF;
	data->win_data->addr[index + 2] = (color >> 16) & 0xFF;
}
