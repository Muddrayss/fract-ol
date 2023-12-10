/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:26:42 by claudio           #+#    #+#             */
/*   Updated: 2023/12/10 18:02:13 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

// static void	set_color(char *addr, unsigned char red, unsigned char green,
// 		unsigned char blue)
// {
// 	addr[0] = blue;
// 	addr[1] = green;
// 	addr[2] = red;
// 	addr[3] = (unsigned char)255;
// }

// void	my_mlx_pixel_put(t_wdata *win_data, int x, int y,
// 		unsigned int intensity, unsigned int max_intensity)
// {
// 	int		index;
// 	float	threshold;
// 	unsigned char red, green, blue;
// 	float intensity_ratio, color_scale;

// 	intensity_ratio = (float)intensity / max_intensity;
// 	threshold = 0.4f;
// 	if (intensity_ratio < threshold)
// 	{
// 		color_scale = intensity_ratio / threshold;
// 		red = (unsigned char)(color_scale * 255);
// 		green = (unsigned char)(color_scale * 255);
// 		blue = (unsigned char)(color_scale * 255);
// 	}
// 	else
// 	{
// 		red = 220;
// 		green = (unsigned char)((1 - (intensity_ratio - threshold) / (1
// 						- threshold)) * 255);
// 		blue = (unsigned char)((1 - (intensity_ratio - threshold) / (1
// 						- threshold)) * 255);
// 	}
// 	index = (y * win_data->line_length + x * (win_data->bits_per_pixel / 8));
// 	set_color(win_data->addr + index, red, green, blue);
// }

void	my_mlx_pixel_put(t_gdata *data, int x, int y, unsigned short intensity)
{
	int			index;
	t_colors	colors;
	double		frequency;

	frequency = 0.2;
	colors.red = sin(frequency * intensity + 0) * 127 + 128;
	colors.blue = sin(frequency * intensity + 2 * PI / 3) * 127 + 128;
	colors.green = sin(frequency * intensity + 4 * PI / 3) * 127 + 128;
	index = y * data->win_data->line_length + x
		* (data->win_data->bits_per_pixel / 8);
	data->win_data->addr[index] = colors.blue / 2;      // blue
	data->win_data->addr[index + 1] = colors.green / 3; // green
	data->win_data->addr[index + 2] = colors.red;       // red
	if (intensity >= (int)data->max_iter)
	{
		data->win_data->addr[index] = 0;
		data->win_data->addr[index + 1] = 0;
		data->win_data->addr[index + 2] = 0;
	}
}
