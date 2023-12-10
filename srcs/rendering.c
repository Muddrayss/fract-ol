/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:44:30 by egualand          #+#    #+#             */
/*   Updated: 2023/12/10 18:00:31 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

static void				*render_fractal(void *data);
static unsigned short	iterate(t_dcoord pix, t_gdata *data);

void	call_threads(t_gdata *data)
{
	t_tdata			thread_args[N_THREADS];
	pthread_t		thread_ids[N_THREADS];
	unsigned short	i;

	i = -1;
	while (++i < N_THREADS)
	{
		thread_args[i].start_y = i * WIN_HEIGHT / N_THREADS;
		thread_args[i].end_y = (i + 1) * WIN_HEIGHT / N_THREADS;
		thread_args[i].data = data;
		if (pthread_create(&thread_ids[i], NULL, &render_fractal,
				&thread_args[i]) != 0)
			(void)(write(2, "Erorr creating thread\n", 23) + quit(4, data));
	}
	i = 0;
	while (i < N_THREADS)
		pthread_join(thread_ids[i++], NULL);
	mlx_put_image_to_window(data->win_data->mlx, data->win_data->win,
		data->win_data->img, 0, 0);
}

static void	*render_fractal(void *data)
{
	t_dcoord		adj_pix;
	t_dcoord		pix;
	t_icoord		diff;
	unsigned short	biggest;
	t_tdata			*threads_data;

	threads_data = (t_tdata *)data;
	biggest = (WIN_WIDTH > WIN_HEIGHT) * WIN_WIDTH + (WIN_WIDTH <= WIN_HEIGHT)
		* WIN_HEIGHT;
	diff.x = ((biggest - WIN_WIDTH) / 2) * (WIN_WIDTH > WIN_HEIGHT);
	diff.y = ((biggest - WIN_HEIGHT) / 2) * (WIN_HEIGHT > WIN_WIDTH);
	pix.x = -1;
	pix.y = threads_data->start_y - 1;
	while (++pix.y < threads_data->end_y)
	{
		while (++pix.x < WIN_WIDTH)
		{
			adj_pix.x = threads_data->data->center.x + ((pix.x - WIN_WIDTH / 2)
					- diff.x) * threads_data->data->roi_range / biggest;
			adj_pix.y = threads_data->data->center.y + ((pix.y - WIN_HEIGHT / 2)
					- diff.y) * threads_data->data->roi_range / biggest;
			my_mlx_pixel_put(threads_data->data, pix.x, pix.y, iterate(adj_pix,
					threads_data->data));
		}
		pix.x = -1;
	}
	return (NULL);
}

static unsigned short	iterate(t_dcoord pix, t_gdata *data)
{
	t_dcoord		(*f)(t_dcoord, t_dcoord, t_gdata *);
	t_dcoord		new;
	unsigned short	i;
	unsigned short	max_iter;

	new.x = 0;
	new.y = 0;
	max_iter = data->max_iter;
	f = data->f;
	i = -1;
	while (++i < max_iter && (new.x *new.x + new.y *new.y) <= 16)
		new = f(new, pix, data);
	return (i);
}
