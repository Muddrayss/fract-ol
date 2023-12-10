/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:16:54 by claudio           #+#    #+#             */
/*   Updated: 2023/12/10 18:09:26 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

static void	switch_to_mandelbrot(t_gdata *data);
static void	switch_to_julia(t_gdata *data, t_wdata *win_data);

int	key_hook(int keycode, t_gdata *data)
{
	if (keycode == ESC_KEY)
		quit(0, data);
	if (keycode == LEFT_ARR_KEY || keycode == A_KEY)
		data->center.x -= data->roi_range * STEP_SIZE;
	else if (keycode == RIGHT_ARR_KEY || keycode == D_KEY)
		data->center.x += data->roi_range * STEP_SIZE;
	if (keycode == UP_ARR_KEY || keycode == W_KEY)
		data->center.y -= data->roi_range * STEP_SIZE;
	else if (keycode == DOWN_ARR_KEY || keycode == S_KEY)
		data->center.y += data->roi_range * STEP_SIZE;
	else if (keycode == PLUS_KEY)
	{
		data->roi_range /= ZOOM_FACTOR;
		if (data->max_iter < MAX_ITER_MAX)
			data->max_iter *= MAX_ITER_CHANGE_FACTOR;
		else
			data->max_iter = MAX_ITER_MAX;
	}
	else if (keycode == MINUS_KEY)
	{
		data->roi_range *= ZOOM_FACTOR;
		data->max_iter /= MAX_ITER_CHANGE_FACTOR;
	}
	else if (keycode == ENTER_KEY)
		data->max_iter *= MAX_ITER_CHANGE_FACTOR;
	else if (keycode == BACKSPACE_KEY)
		data->max_iter /= MAX_ITER_CHANGE_FACTOR;
	else if (keycode == M_KEY && data->f != &apply_mandelbrot)
		switch_to_mandelbrot(data);
	else if (keycode == J_KEY && data->f != &apply_julia)
		switch_to_julia(data, data->win_data);
	else
		return (0);
	printf("max_iter: %.16f\n", data->max_iter);
	call_threads(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_gdata *data)
{
	double	dx;
	double	dy;
	double	old_roi;

	old_roi = data->roi_range;
	if (button == 4)
	{
		dx = (x - WIN_WIDTH / 2) * (1 - ZOOM_FACTOR);
		dy = (y - WIN_HEIGHT / 2) * (1 - ZOOM_FACTOR);
		data->roi_range /= ZOOM_FACTOR;
		if (data->max_iter < MAX_ITER_MAX)
			data->max_iter *= MAX_ITER_CHANGE_FACTOR;
		else
			data->max_iter = MAX_ITER_MAX;
	}
	else if (button == 5)
	{
		dx = (x - WIN_WIDTH / 2) * (1 - 1 / ZOOM_FACTOR);
		dy = (y - WIN_HEIGHT / 2) * (1 - 1 / ZOOM_FACTOR);
		data->roi_range *= ZOOM_FACTOR;
		data->max_iter /= MAX_ITER_CHANGE_FACTOR;
	}
	else
		return (0);
	data->center.x -= dx * old_roi / WIN_WIDTH;
	data->center.y -= dy * old_roi / WIN_HEIGHT;
	printf("max_iter: %.16f\n", data->max_iter);
	call_threads(data);
	return (0);
}

static void	switch_to_mandelbrot(t_gdata *data)
{
	data->center.x = data->previous_center.x;
	data->center.y = data->previous_center.y;
	data->roi_range = data->previous_range;
	data->f = &apply_mandelbrot;
}

static void	switch_to_julia(t_gdata *data, t_wdata *win_data)
{
	t_dcoord	mouse_complex;
	int			mouse_pos_x;
	int			mouse_pos_y;

	mlx_mouse_get_pos(win_data->mlx, win_data->win, &mouse_pos_x, &mouse_pos_y);
	mouse_complex.x = data->center.x + ((mouse_pos_x - WIN_WIDTH / 2)
			* data->roi_range / WIN_WIDTH);
	mouse_complex.y = data->center.y + ((mouse_pos_y - WIN_HEIGHT / 2)
			* data->roi_range / WIN_HEIGHT);
	data->julia_c = mouse_complex;
	data->previous_center = data->center;
	data->previous_range = data->roi_range;
	data->center.x = 0;
	data->center.y = 0;
	data->roi_range = STARTING_ROI_JULIA;
	data->f = &apply_julia;
}
