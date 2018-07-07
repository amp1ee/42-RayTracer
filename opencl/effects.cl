/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    effects.cl                                         :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/07/02 18:29:45 by mstorcha          #+#    #+#              */
/*    Updated: 2018/07/02 18:29:46 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include "rendering.h.cl"

void		e_grades_gray(float3 *c)
{
	float tmp = (c->x + c->y + c->z) / 3;

	c->x = tmp;
	c->y = tmp;
	c->z = tmp;
}

void		e_sepia(float3 *c)
{
	e_grades_gray(c);

	c->x = c->x + 40 * 2;
	c->y = c->y + 40;
	c->z = c->z;
	c->x = clamp((float)c->x, 0.0f, 255.f);
	c->y = clamp((float)c->y, 0.0f, 255.f);
	c->z = clamp((float)c->z, 0.0f, 255.f);
}

void		e_negative(float3 *c)
{
	c->x = 255 - c->x;
	c->y = 255 - c->y;
	c->z = 255 - c->z;
}

void		e_black_white(float3 *c)
{
	float tmp = (c->x + c->y + c->z);
	if (tmp > ((255 - 150)/2)*3)
	{
		c->x = 255;
		c->y = 255;
		c->z = 255;
	}
	else
	{
		c->x = 0;
		c->y = 0;
		c->z = 0;
	}
}

void		gauss_blur(__global int * data, int i, int j)
{
	
}
