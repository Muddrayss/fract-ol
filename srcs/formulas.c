/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:56:53 by craimond          #+#    #+#             */
/*   Updated: 2023/12/09 18:16:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

t_dcoord	apply_mandelbrot(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	(void)data;
	new.x = old.x *old.x - old.y *old.y + c.x;
	new.y = 2 * old.x *old.y + c.y;
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
	new.x = old.x *old.x - old.y *old.y
		+ c.x;
	new.y = 2 * old.x *old.y + c.y;
	return (new);
}
