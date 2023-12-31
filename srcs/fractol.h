/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:58:16 by egualand          #+#    #+#             */
/*   Updated: 2023/12/21 16:35:12 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 600
# define HEIGHT 600
# define STARTING_ROI_MAND 6
# define STARTING_ROI_JULIA 6
# define STARTING_ROI_BURNING_SHIP 6
# define STARTING_JULIA_C_X -0.8
# define STARTING_JULIA_C_Y 0.156
# define STARTING_MAX_ITER 150
# define MAX_ITER_MAX 900
# define ZOOM 1.15
# define MAX_ITER_CHANGE_FACTOR 1.009
# define STEP_SIZE 0.01
# define ESC_KEY 65307
# define LEFT_ARR_KEY 65361
# define RIGHT_ARR_KEY 65363
# define UP_ARR_KEY 65362
# define DOWN_ARR_KEY 65364
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define R_KEY 114
# define J_KEY 106
# define M_KEY 109
# define B_KEY 98
# define SPACE_KEY 32
# define N_THREADS 300
# define PI 3.14159265358979323846

typedef struct s_double_coordinates
{
	double			x;
	double			y;
}					t_dcoord;

typedef struct s_int_coordinates
{
	unsigned short	x;
	unsigned short	y;
}					t_icoord;

typedef struct s_window_data
{
	void			*win;
	void			*img;
	void			*mlx;
	int				endian;
	int				bits_per_pixel;
	int				line_length;
	char			*addr;
}					t_wdata;

typedef struct s_general_data
{
	t_wdata			*win_data;
	t_dcoord		(*f)(t_dcoord, t_dcoord, struct s_general_data *);
	t_dcoord		center;
	t_dcoord		previous_center;
	t_dcoord		julia_c;
	double			roi_range;
	double			previous_range;
	double			max_iter;
	double			previous_max_iter;
	float			frequency;
	unsigned short	biggest;
}					t_gdata;

typedef struct s_threads_data
{
	t_gdata			*data;
	unsigned short	start_y;
	unsigned short	end_y;
	unsigned short	id;
}					t_tdata;

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

t_dcoord			apply_mandelbrot(t_dcoord old, t_dcoord c, t_gdata *data);
t_dcoord			apply_julia(t_dcoord old, t_dcoord c, t_gdata *data);
t_dcoord			apply_burning_ship(t_dcoord old, t_dcoord c, t_gdata *data);
int					check_julia_args(int argc, char **argv);
void				reset_to_default(t_gdata *data);
int					key_hook(int keycode, t_gdata *data);
int					mouse_hook(int button, int x, int y, t_gdata *data);
int					quit(char id, t_gdata *data);
int					press_x(t_gdata *data);
int					ft_strcmp(char *s1, char *s2);
void				call_threads(t_gdata *data);
void				my_mlx_pixel_put(t_gdata *data, int x, int y,
						unsigned int color);
void				put_color(t_gdata *data, int x, int y,
						unsigned short intensity);
void				set_roi_range(t_gdata *data);
double				ft_atod(char *str);

#endif