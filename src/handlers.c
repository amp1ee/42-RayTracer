/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:11:32 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/26 13:11:37 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned char	*return_ppm_color(int c)
{
	t_point			p;
	unsigned char	*arr;

	p.x = (c >> 16) & 255;
	p.y = (c >> 8) & 255;
	p.z = c & 255;
	arr = (unsigned char *)malloc(sizeof(unsigned char) * 3);
	arr[0] = p.x % 256;
	arr[1] = p.y % 256;
	arr[2] = p.z % 256;
	return (arr);
}

static char		*get_user_dir(void)
{
	struct passwd	*pw;
	const char		*homedir;

	pw = getpwuid(getuid());
	homedir = pw->pw_dir;
	return (char *)(homedir);
}

char			*screen_shoot_name(void)
{
	static int	num = 0;
	char		*s;
	char		*f;
	char		*t;
	char		*ret;

	num++;
	t = ft_strjoin(get_user_dir(), "/Desktop/screen_shoot_");
	s = ft_itoa(num);
	f = ft_strjoin(t, s);
	free(t);
	free(s);
	ret = ft_strjoin(f, ".ppm");
	free(f);
	return (ret);
}

void			screen_shoot(t_main mlx)
{
	FILE			*fp;
	int				j;
	unsigned char	*arr;
	char			*name;
	int				*pixels;

	pixels = mlx.sdl->sur->pixels;
	name = screen_shoot_name();
	!(fp = fopen(name, "wb")) ? ft_putendl("cant do picture") : 0;
	free(name);
	if (!fp)
		return ;
	fprintf(fp, "P6\n%d %d\n255\n", HEIGHT, WIDTH);
	j = -1;
	while (++j < HEIGHT * WIDTH)
	{
		arr = return_ppm_color(pixels[j]);
		fwrite(arr, 1, 3, fp);
		free(arr);
	}
}

cl_float3		rotate_ort(cl_float3 point, cl_float3 rot)
{
	cl_float3 od;
	cl_float3 dv;
	cl_float3 tr;
	cl_float3 rot_rad;

	rot_rad.x = rot.x * M_PI / 180.0;
	rot_rad.y = rot.y * M_PI / 180.0;
	rot_rad.z = rot.z * M_PI / 180.0;
	od.x = point.x;
	od.y = point.y * cos(rot_rad.x) + point.z * sin(rot_rad.x);
	od.z = point.z * cos(rot_rad.x) - point.y * sin(rot_rad.x);
	dv.x = od.x * cos(rot_rad.y) - od.z * sin(rot_rad.y);
	dv.y = od.y;
	dv.z = od.z * cos(rot_rad.y) + od.x * sin(rot_rad.y);
	tr.x = dv.x * cos(rot_rad.z) + dv.y * sin(rot_rad.z);
	tr.y = dv.y * cos(rot_rad.z) - dv.x * sin(rot_rad.z);
	tr.z = dv.z;
	return (tr);
}

/*
**   void	delete_figure()
*/

int			figure_actions(t_main *mlx, int x, int y)
{
	int index;

	index = find_figure(mlx, x - SIDE_W, y - MEN_H);
	if (index == -1)
		mlx->sdl->ui.show_info = 0;
	return (index);
}

void			call_dialog(t_main *mlx)
{
	const char	*open;
	const char	*format[1] = { "*.j" };

	open = tinyfd_openFileDialog("", "./scenes/", 1, format, NULL, 0);
	if (open == NULL)
		return ;
	free(mlx->scene->textures);
	free(mlx->scene->textures_info);
	free(mlx->scene->objects);
	free(mlx->scene->lights);
	free(mlx->scene);
	mlx->sdl->ui.show_info = 0;
	mlx->scene = parse_json((char *)open, mlx->cl);
}

t_figure		new_ambient(float intensity)
{
	t_figure	light;

	light.type = 1;
	light.angle = intensity;
	return (light);
}

t_scene			*zero_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	if (!(scene->lights = (t_figure *)malloc(sizeof(t_figure))))
		exit_message("Memallocation error");
	if (!(scene->objects = (t_figure *)malloc(sizeof(t_figure))))
		exit_message("Memallocation error");
	scene->l_num = 1;
	scene->o_num = 1;
	scene->cam.p = (cl_float3){.x = 0, .y = 0, .z = 0};
	scene->cam.d = (cl_float3){.x = 0, .y = 0, .z = 0};
	*scene->lights = new_ambient(0.5);
	*scene->objects = new_sphere(scene->cam, 0);
	return (scene);
}

void			del_scene(t_main *mlx)
{
	free(mlx->scene->objects);
	free(mlx->scene->lights);
	free(mlx->scene);
	mlx->scene = zero_scene();
	mlx->sdl->ui.show_info = 0;
	mlx->scene = parse_json((char *)open, mlx->cl);
}

t_scene			*empty_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	scene->l_num = 1;
	scene->o_num = 1;
	scene->cam.p = (cl_float3){.x = 0, .y = 0, .z = 0};
	scene->cam.d = (cl_float3){.x = 0, .y = 0, .z = 0};
	scene->lights = (t_figure *)malloc(sizeof(t_figure));
	scene->lights->type = 1;
	scene->lights->radius = 0;
	scene->objects = (t_figure *)malloc(sizeof(t_figure));
	scene->objects->type = 1;
	scene->objects->radius = 0.01;
	scene->objects->p = (cl_float3){.x = 100, .y = 100, .z = 100};
	scene->objects->color = (cl_float3){.x = 0, .y = 0, .z = 0};
	return (scene);
}
