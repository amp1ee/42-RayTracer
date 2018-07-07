/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:41:38 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/19 21:41:40 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define MEM_LENGTH 1440000

void			exit_message(const char *str)
{
	ft_putendl(str);
	exit(1);
}

void			init_cl(t_main *mlx)
{
	t_opencl *cl;

	cl = malloc(sizeof(t_opencl));
	start_cl(cl);
	mid_cl(cl, mlx, MEM_LENGTH);
	mlx->cl = cl;
}

void			rendering(t_main *mlx)
{
	size_t		global_work_size[3];
	int			ret;

	global_work_size[0] = 1200;
	global_work_size[1] = 1200;
	global_work_size[2] = 0;
	args_cl(mlx->cl, mlx);
	if ((ret = clEnqueueNDRangeKernel(mlx->cl->command_queue,
				mlx->cl->kernel, 2, NULL,
				global_work_size, NULL, 0, NULL, NULL)))
		exit_message("failed to execute kernel");
	if ((ret = clEnqueueReadBuffer(mlx->cl->command_queue,
				mlx->cl->memobj_data, CL_TRUE, 0, MEM_LENGTH * sizeof(int),
				mlx->image.ptr, 0, NULL, NULL)))
		exit_message("failed to get buf data");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image.data, 0, 0);
}
