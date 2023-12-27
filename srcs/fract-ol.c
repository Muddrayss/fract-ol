/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:21:21 by mdella-r          #+#    #+#             */
/*   Updated: 2023/12/10 01:28:04 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

static void	init_data(t_gdata *data, t_wdata *win_data);
static void	init_window(t_wdata *win_data, t_gdata *data);

int	main(int argc, char **argv)
{
	t_wdata 		win_data;
	t_gdata			data;

	if (argc != 2)
		(void) (write(2, "Error: too few arguments\n", 25) + quit(1, NULL));
	init_data(&data, &win_data);
	init_window(&win_data, &data);
	if (0 == ft_strcmp(argv[1], "mandelbrot"))
		data.f = &apply_mandelbrot;
	else if (0 == ft_strcmp(argv[1], "julia"))
		data.f = &apply_julia;
	else
		(void) (write(2, "Error: unknown fractal\n", 23) + write(1, "Available fractals: mandelbrot, julia\n", 39) + quit(3, &data));
	if (data.f == &apply_mandelbrot)
		data.center.x = -0.75;
	call_threads(&data);
	mlx_mouse_hook(win_data.win, &mouse_hook, &data);
	mlx_hook(win_data.win, 2, 1, &key_hook, &data);
	mlx_hook(win_data.win, 17, 1L << 17, &press_x, &data);
	mlx_loop(win_data.mlx);
}

static void	init_data(t_gdata *data, t_wdata *win_data)
{
	data->center.x = 0;
	data->center.y = 0;
	data->previous_center.x = -0.75;
	data->previous_center.y = 0;
	data->previous_range = STARTING_ROI_MAND;
	data->julia_c.x = 1;
	data->julia_c.y = 1.5;
	data->max_iter = STARTING_MAX_ITER;
	data->win_data = win_data;
	if (WIN_WIDTH > WIN_HEIGHT)
		data->roi_range = STARTING_ROI_MAND * WIN_WIDTH / WIN_HEIGHT;
	else
		data->roi_range = STARTING_ROI_MAND * WIN_HEIGHT / WIN_WIDTH;
}

static void	init_window(t_wdata *win_data, t_gdata *data)
{
	win_data->mlx = mlx_init();
	win_data->win = mlx_new_window(win_data->mlx, WIN_WIDTH, WIN_HEIGHT, "Fractal_visualizer");
	win_data->img = mlx_new_image(win_data->mlx, WIN_WIDTH, WIN_HEIGHT);
	win_data->addr = mlx_get_data_addr(win_data->img, &win_data->bits_per_pixel, &win_data->line_length, &win_data->endian);
	if (!win_data->win)
		(void) (write(2, "Error: window initialization failed\n", 36) + quit(2, data));
}
