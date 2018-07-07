/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:09:26 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/26 13:09:28 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		*norming(cl_float3 *p)
{
	*p = num_dil(*p, v_length(*p));
	return (p);
}

cl_float3		num_dil(cl_float3 p, float n)
{
	return (cl_float3){ .x = p.x / n, .y = p.y / n, .z = p.z / n };
}

float		v_length(cl_float3 p)
{
	return (sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
}

int			return_color(cl_float3 c)
{
	return ((int)c.x * 0x10000 + (int)c.y * 0x100 + (int)c.z);
}
