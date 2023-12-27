/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:56:30 by egualand          #+#    #+#             */
/*   Updated: 2023/12/21 16:25:52 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_dcoord	apply_mandelbrot(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	(void)data;
	new.x = old.x * old.x - old.y * old.y + c.x;
	new.y = 2 * old.x * old.y + c.y;
	return (new);
}

t_dcoord	apply_julia(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	if (old.x == 0 && old.y == 0)
	{
		old.x = c.x;
		old.y = c.y;
	}
	c.x = data->julia_c.x;
	c.y = data->julia_c.y;
	new.x = old.x * old.x - old.y * old.y + c.x;
	new.y = 2 * old.x * old.y + c.y;
	return (new);
}

t_dcoord	apply_burning_ship(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	(void)data;
	old.x = fabs(old.x);
	old.y = fabs(old.y);
	new.x = old.x * old.x - old.y * old.y + c.x;
	new.y = 2 * old.x * old.y + c.y;
	return (new);
}
