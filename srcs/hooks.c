/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:58:47 by egualand          #+#    #+#             */
/*   Updated: 2023/12/27 14:01:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	switch_to_mandelbrot(t_gdata *data);
static void	switch_to_julia(t_gdata *data, t_wdata *win_data);
static void	switch_to_burning_ship(t_gdata *data);

int	key_hook(int keycode, t_gdata *data)
{
	if (keycode == ESC_KEY)
		quit(0, data);
	else if (keycode == LEFT_ARR_KEY || keycode == A_KEY)
		data->center.x -= data->roi_range * STEP_SIZE;
	else if (keycode == RIGHT_ARR_KEY || keycode == D_KEY)
		data->center.x += data->roi_range * STEP_SIZE;
	else if (keycode == UP_ARR_KEY || keycode == W_KEY)
		data->center.y -= data->roi_range * STEP_SIZE;
	else if (keycode == DOWN_ARR_KEY || keycode == S_KEY)
		data->center.y += data->roi_range * STEP_SIZE;
	else if (keycode == R_KEY)
		reset_to_default(data);
	else if (keycode == M_KEY && data->f != &apply_mandelbrot)
		switch_to_mandelbrot(data);
	else if (keycode == J_KEY && data->f != &apply_julia)
		switch_to_julia(data, data->win_data);
	else if (keycode == B_KEY)
		switch_to_burning_ship(data);
	else if (keycode == SPACE_KEY)
		data->frequency += 0.01;
	else
		return (0);
	call_threads(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_gdata *data)
{
	double	tmp;

	tmp = data->roi_range;
	if (button == 4)
	{
		data->center.x -= (x - WIDTH / 2) * (1 - ZOOM) * tmp / WIDTH;
		data->center.y -= (y - HEIGHT / 2) * (1 - ZOOM) * tmp / HEIGHT;
		data->roi_range /= ZOOM;
		if (data->max_iter < MAX_ITER_MAX)
			data->max_iter *= MAX_ITER_CHANGE_FACTOR;
		else
			data->max_iter = MAX_ITER_MAX;
	}
	else if (button == 5)
	{
		data->center.x -= (x - WIDTH / 2) * (1 - 1 / ZOOM) * tmp / WIDTH;
		data->center.y -= (y - HEIGHT / 2) * (1 - 1 / ZOOM) * tmp / HEIGHT;
		data->roi_range *= ZOOM;
		data->max_iter /= MAX_ITER_CHANGE_FACTOR;
	}
	if (button == 5 || button == 4)
		call_threads(data);
	return (0);
}

static void	switch_to_mandelbrot(t_gdata *data)
{
	if (data->f == NULL)
		data->previous_range = 0;
	data->f = &apply_mandelbrot;
	data->center.x = data->previous_center.x;
	data->center.y = data->previous_center.y;
	if (data->previous_range == 0)
		set_roi_range(data);
	else
		data->roi_range = data->previous_range;
	data->max_iter = data->previous_max_iter;
}

static void	switch_to_julia(t_gdata *data, t_wdata *win_data)
{
	t_dcoord	mouse_complex;
	int			mouse_pos_x;
	int			mouse_pos_y;

	mlx_mouse_get_pos(win_data->mlx, win_data->win, &mouse_pos_x, &mouse_pos_y);
	data->julia_c.x = STARTING_JULIA_C_X;
	data->julia_c.y = STARTING_JULIA_C_Y;
	if (data->f == &apply_mandelbrot)
	{
		mouse_complex.x = data->center.x + ((mouse_pos_x - WIDTH / 2)
				* data->roi_range / WIDTH);
		mouse_complex.y = -(data->center.y + ((mouse_pos_y - HEIGHT / 2)
					* data->roi_range / HEIGHT));
		data->julia_c = mouse_complex;
	}
	data->f = &apply_julia;
	data->previous_center = data->center;
	data->previous_range = data->roi_range;
	data->previous_max_iter = data->max_iter;
	data->center.x = 0;
	data->center.y = 0;
	data->roi_range = STARTING_ROI_JULIA;
	data->max_iter = STARTING_MAX_ITER;
}

static void	switch_to_burning_ship(t_gdata *data)
{
	data->f = &apply_burning_ship;
	data->center.x = -0.5;
	data->center.y = -0.5;
	data->roi_range = STARTING_ROI_BURNING_SHIP;
}
