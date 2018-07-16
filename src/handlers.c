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

char			*screen_shoot_name(void)
{
	static int	num = 0;
	char		*s;
	char		*f;
	char		*ret;

	num++;
	s = ft_itoa(num);
	f = ft_strjoin("/Users/mstorcha/Desktop/screen_shoot_", s);
	free(s);
	ret = ft_strjoin(f, ".ppm");
	free(f);
	return (ret);
}

void			screen_shoot(t_main mlx)
{
	FILE			*fp;
	int				i;
	int				j;
	unsigned char	*arr;
	char			*name;

	name = screen_shoot_name();
	!(fp = fopen(name, "wb")) ? ft_putendl("cant do picture") : 0;
	free(name);
	if (!fp)
		return ;
	fprintf(fp, "P6\n%d %d\n255\n", HEIGHT, WIDTH);
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			arr = return_ppm_color(mlx.image.ptr[1200 * j + i]);
			fwrite(arr, 1, 3, fp);
			free(arr);
		}
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

void	find_figure(int x, int y, t_main *mlx)
{
	(void)x;
	(void)y;
	(void)mlx;
}

int		mouse(int key_code, int x, int y, t_main *mlx)
{
	int e;

	e = 0;
	(key_code == 1 && ++e) ? (find_figure(x, y, mlx)) : (0);
	e ? (rendering(mlx)) : 0;
	return (0);
}

int				key(int key_code, t_main *mlx)
{
	char		e;

	e = 0;
	(key_code == 53) ? exit(1) : 0;
	(key_code == 13 && ++e) ? (mlx->scene->cam.p.z += 0.5) : 0;
	(key_code == 1 && ++e) ? (mlx->scene->cam.p.z -= 0.5) : 0;
	(key_code == 2 && ++e) ? (mlx->scene->cam.p.x += 0.5) : 0;
	(key_code == 0 && ++e) ? (mlx->scene->cam.p.x -= 0.5) : 0;
	(key_code == 126 && ++e) ? (mlx->scene->cam.d.x += 5) : 0;
	(key_code == 125 && ++e) ? (mlx->scene->cam.d.x -= 5) : 0;
	(key_code == 123 && ++e) ? (mlx->scene->cam.d.y += 5) : 0;
	(key_code == 124 && ++e) ? (mlx->scene->cam.d.y -= 5) : 0;
	(key_code == 12 && ++e) ? (mlx->scene->cam.p.y -= 0.5) : 0;
	(key_code == 14 && ++e) ? (mlx->scene->cam.p.y += 0.5) : 0;
	(key_code == 69 && ++e) ? (add_figure(&mlx->scene->objects,
		mlx->scene->cam, &mlx->scene->o_num)) : 0;
	(key_code == 82 && ++e) ? (screen_shoot(*mlx)) : 0;
	e ? (rendering(mlx)) : 0;
	return (0);
}
