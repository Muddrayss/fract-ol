/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:58:52 by egualand          #+#    #+#             */
/*   Updated: 2023/12/27 14:01:45 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void				*render_fractal(void *data);
static unsigned short	iterate(t_dcoord pix, t_gdata *data);
static void				hud_setup(t_wdata *win_data);

void	call_threads(t_gdata *data)
{
	t_tdata			thread_args[N_THREADS];
	pthread_t		thread_ids[N_THREADS];
	unsigned short	i;

	i = -1;
	while (++i < N_THREADS)
	{
		thread_args[i].start_y = i * HEIGHT / N_THREADS;
		thread_args[i].end_y = (i + 1) * HEIGHT / N_THREADS;
		thread_args[i].data = data;
		thread_args[i].id = i;
		if (pthread_create(&thread_ids[i], NULL, &render_fractal,
				&thread_args[i]) != 0)
			(void)(write(2, "Error creating thread\n", 23) + quit(4, data));
	}
	i = 0;
	while (i < N_THREADS)
		pthread_join(thread_ids[i++], NULL);
	mlx_put_image_to_window(data->win_data->mlx, data->win_data->win,
		data->win_data->img, 0, 0);
	hud_setup(data->win_data);
}

void	reset_to_default(t_gdata *data)
{
	if (data->f == &apply_mandelbrot)
		data->center.x = -0.75;
	else
		data->center.x = 0;
	data->center.y = 0;
	set_roi_range(data);
	data->max_iter = STARTING_MAX_ITER;
}

static void	hud_setup(t_wdata *win_data)
{
	unsigned short	span;

	span = 30;
	mlx_string_put(win_data->mlx, win_data->win, WIDTH / 30, HEIGHT / 2 - span
		* 2, 0xFFFFFF, "Move:   (UP) (DOWN) (LEFT) (RIGHT) or W A S D");
	mlx_string_put(win_data->mlx, win_data->win, WIDTH / 30, HEIGHT / 2 - span
		* 1, 0xFFFFFF, "Switch: M J B");
	mlx_string_put(win_data->mlx, win_data->win, WIDTH / 30, HEIGHT / 2 + span
		* 0, 0xFFFFFF, "Zoom:   Mouse Wheel");
	mlx_string_put(win_data->mlx, win_data->win, WIDTH / 30, HEIGHT / 2 + span
		* 1, 0xFFFFFF, "Reset:  R");
	mlx_string_put(win_data->mlx, win_data->win, WIDTH / 30, HEIGHT / 2 + span
		* 2, 0xFFFFFF, "Quit:   ESC");
}

static void	*render_fractal(void *tdata)
{
	t_dcoord	adj_pix;
	t_dcoord	pix;
	t_icoord	diff;
	t_gdata		*data;

	data = ((t_tdata *)tdata)->data;
	diff.x = ((data->biggest - WIDTH) / 2) * (WIDTH > HEIGHT);
	diff.y = ((data->biggest - HEIGHT) / 2) * (HEIGHT > WIDTH);
	pix.y = ((t_tdata *)tdata)->start_y - 1;
	while (++pix.y < ((t_tdata *)tdata)->end_y)
	{
		pix.x = -1;
		while (++pix.x < WIDTH)
		{
			adj_pix.x = data->center.x + ((pix.x - WIDTH / 2) - diff.x)
				* data->roi_range / data->biggest;
			adj_pix.y = data->center.y + ((pix.y - HEIGHT / 2) - diff.y)
				* data->roi_range / data->biggest;
			put_color(data, pix.x, pix.y, iterate(adj_pix, data));
		}
	}
	return (NULL);
}

static unsigned short	iterate(t_dcoord pix, t_gdata *data)
{
	t_dcoord		new;
	unsigned short	i;
	unsigned short	max_iter;

	t_dcoord (*f)(t_dcoord, t_dcoord, t_gdata *);
	new.x = 0;
	new.y = 0;
	max_iter = data->max_iter;
	f = data->f;
	i = -1;
	while (++i < max_iter && (new.x * new.x + new.y * new.y) <= 4)
