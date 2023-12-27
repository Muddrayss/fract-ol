/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:57:25 by egualand          #+#    #+#             */
/*   Updated: 2023/12/27 14:04:36 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_data(t_gdata *data);
static void	init_window(t_wdata *win_data, t_gdata *data);
static void	set_julia_c(t_gdata *data, char **argv);

int	main(int argc, char **argv)
{
	t_wdata	win_data;
	t_gdata	data;

	if (argc < 2 || argc > 4)
		(void)(write(2, "Error: wrong n. of arguments\n", 25) + quit(1, NULL));
	init_data(&data);
	if (0 == ft_strcmp(argv[1], "mandelbrot"))
		data.f = &apply_mandelbrot;
	else if (0 == ft_strcmp(argv[1], "julia") && check_julia_args(argc, argv))
	{
		data.f = &apply_julia;
		set_julia_c(&data, argv);
	}
	else if (0 == ft_strcmp(argv[1], "burning_ship"))
		data.f = &apply_burning_ship;
	else
		(void)(write(2, "Error: unknown fractal\n", 23) + write(1,
				"Arguments: mandelbrot, julia c.x c.y, burning_ship\n", 52)
			+ quit(3, &data));
	init_window(&win_data, &data);
	mlx_mouse_hook(win_data.win, &mouse_hook, &data);
	mlx_hook(win_data.win, 2, 1, &key_hook, &data);
	mlx_hook(win_data.win, 17, 1L << 17, &press_x, &data);
	mlx_loop(win_data.mlx);
}

static void	init_data(t_gdata *data)
{
	if (data->f == &apply_mandelbrot || data->f == &apply_julia)
	{
		data->center.x = 0;
		data->center.y = 0;
	}
	else
	{
		data->center.x = -0.5;
		data->center.y = -0.5;
	}
	data->previous_center.x = -0.75;
	data->previous_center.y = 0;
	data->previous_range = STARTING_ROI_MAND;
	data->previous_max_iter = STARTING_MAX_ITER;
	data->julia_c.x = STARTING_JULIA_C_X;
	data->julia_c.y = STARTING_JULIA_C_Y;
	data->max_iter = STARTING_MAX_ITER;
	data->win_data = NULL;
	data->frequency = 0.1;
	data->biggest = (WIDTH > HEIGHT) * WIDTH + (WIDTH <= HEIGHT) * HEIGHT;
}

static void	init_window(t_wdata *win_data, t_gdata *data)
{
	data->win_data = win_data;
	set_roi_range(data);
	win_data->mlx = mlx_init();
	win_data->win = mlx_new_window(win_data->mlx, WIDTH, HEIGHT,
			"Fractal_visualizer");
	win_data->img = mlx_new_image(win_data->mlx, WIDTH, HEIGHT);
	win_data->addr = mlx_get_data_addr(win_data->img, &win_data->bits_per_pixel,
			&win_data->line_length, &win_data->endian);
	if (!win_data->win)
		(void)(write(2, "Error: window initialization failed\n", 36) + quit(2,
				data));
	call_threads(data);
}

static void	set_julia_c(t_gdata *data, char **argv)
{
	data->julia_c.x = ft_atod(argv[2]);
	data->julia_c.y = ft_atod(argv[3]);
	printf("julia_c: %f %f\n", data->julia_c.x, data->julia_c.y);
}

void	set_roi_range(t_gdata *data)
{
	if (data->f == NULL)
		data->roi_range = 1;
	if (data != NULL && WIDTH > HEIGHT)
	{
		if (data->f == &apply_mandelbrot || data->f == NULL)
			data->roi_range = STARTING_ROI_MAND * WIDTH / HEIGHT;
		else if (data->f == &apply_julia)
			data->roi_range = STARTING_ROI_JULIA * WIDTH / HEIGHT;
		else if (data->f == &apply_burning_ship)
			data->roi_range = STARTING_ROI_BURNING_SHIP * WIDTH / HEIGHT;
	}
	else if (data != NULL && WIDTH <= HEIGHT)
	{
		if (data->f == &apply_mandelbrot || data->f == NULL)
			data->roi_range = STARTING_ROI_MAND * HEIGHT / WIDTH;
		else if (data->f == &apply_julia)
			data->roi_range = STARTING_ROI_JULIA * HEIGHT / WIDTH;
		else if (data->f == &apply_burning_ship)
			data->roi_range = STARTING_ROI_BURNING_SHIP * HEIGHT / WIDTH;
	}
	if (data->f == &apply_mandelbrot)
		data->center.x = -0.75;
	data->previous_range = data->roi_range;
}
