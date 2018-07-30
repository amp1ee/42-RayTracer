/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 15:29:39 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/16 15:29:41 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	new_sphere(t_figure cam)
{
	t_figure f;

	f.type = SPHERE;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	return (f);
}

t_figure	new_cylinder(t_figure cam)
{
	t_figure f;

	f.type = CYLINDER;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).z };
	return (f);
}

t_figure	new_cone(t_figure cam)
{
	t_figure f;

	f.type = CONE;
	f.angle = 10;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).z };
	return (f);
}

t_figure	new_plane(t_figure cam)
{
	t_figure f;

	f.type = PLANE;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).z };
	return (f);
}

void		add_figure(t_figure **figures, t_figure cam, int *o_num)
{
	t_figure	*new;
	int			i;
	int			index;

	if (!(new = (t_figure *)malloc(sizeof(t_figure) * (*o_num + 1))))
		exit_message("failed");
	i = -1;
	while (++i < *o_num)
		new[i] = (*figures)[i];
	index = (*figures)[i - 1].index;
	new[i] = new_sphere(cam);
	new[i].index = index + 1;
	new[i].matirial = 0;
	new[i].text = 0;
	free(*figures);
	*figures = new;
	*o_num = i + 1;
}
