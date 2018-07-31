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

t_figure	new_sphere(t_figure cam, float radius)
{
	t_figure f;

	f.type = SPHERE;
	f.radius = 0.5f;
	f.radius = radius;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
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
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_cone(t_figure cam)
{
	t_figure f;

	f.type = CONE;
	f.angle = 10;
	f.rfl = 0.f;
	f.radius = 0.f;
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
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_plane(t_figure cam)
{
	t_figure f;

	f.type = PLANE;
	f.rfl = 0.f;
	f.radius = 0.f;
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
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_hyperboloid(t_figure cam)
{
	t_figure f;

	f.type = HYPERBOLOID;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_twosheet_hyperboloid(t_figure cam)
{
	t_figure f;

	f.type = TWOSHEET_HYPERBOLOID;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_paraboloid(t_figure cam)
{
	t_figure f;

	f.type = PARABOLOID;
	f.radius = 0.1f;
	f.rfl = 0.f;
	f.cap = 5.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).z };
	f.d = (cl_float3){.x=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).x,
						.y=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).y,
						.z=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_ellipsoid(t_figure cam)
{
	t_figure f;

	f.type = ELLIPSOID;
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
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_disk(t_figure cam)
{
	t_figure f;

	f.type = DISK;
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
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_cube(t_figure cam)
{
	t_figure f;

	f.type = CUBE;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=0, .y=0, .z=0};
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	f.min = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).z };
	f.max = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).z};
	return (f);
}

void		add_figure(t_main *mlx, t_figure **figures, t_figure cam, int *o_num, char type)
{
	t_figure	*new;
	int			i;
	int			index;

	if (!(new = (t_figure *)malloc(sizeof(t_figure) * (*o_num + 1))))
		exit_message("failed");
	i = -1;
	mlx->sdl->ui.show_info = 0;
	while (++i < *o_num)
		new[i] = (*figures)[i];
	index = (*figures)[i - 1].index;
	if (type == 's')
		new[i] = new_sphere(cam, 0.3f);
	else if (type == 'p')
		new[i] = new_plane(cam);
	else if (type == 'c')
		new[i] = new_cone(cam);
	else if (type == 'y')
		new[i] = new_cylinder(cam);
	else if (type == 'd')
		new[i] = new_disk(cam);
	else if (type == 'k')
		new[i] = new_cube(cam);
	else if (type == 'e')
		new[i] = new_ellipsoid(cam);
	else if (type == 'a')
		new[i] = new_paraboloid(cam);
	else if (type == 't')
		new[i] = new_twosheet_hyperboloid(cam);
	else if (type == 'h')
		new[i] = new_hyperboloid(cam);
	new[i].index = index + 1;
	new[i].matirial = 0;
	new[i].text = 0;
	new[i].scale = 1;
	if (*o_num > 1)
		free(*figures);
	*figures = new;
	*o_num = i + 1;
}

