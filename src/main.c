/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:20:54 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/23 13:21:42 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
{
	t_main		mlx;

	if (argc != 2)
		return (0);
	mlx.scene = scene_create(argv);
	cl_init(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "RT");
	mlx.image.data = mlx_new_image(mlx.mlx_ptr, HEIGHT, WIDTH);
	mlx.image.ptr = (int *)mlx_get_data_addr(mlx.image.data,
			&mlx.image.bits, &mlx.image.sz_l, &mlx.image.endi);
	mlx_clear_window(mlx.mlx_ptr, mlx.win_ptr);
	rendering(&mlx);
	mlx_mouse_hook(mlx.win_ptr, &mouse, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, &key, &(mlx));
	mlx_hook(mlx.win_ptr, 17, 0, (int (*)())exit, NULL);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
