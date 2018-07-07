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

void			exit_message(const char *str)
{
	ft_putendl(str);
	exit(1);
}

static void		free_cl_mem(t_opencl cl)
{
	clReleaseMemObject(cl.memobj_data);
	clReleaseMemObject(cl.memobj_figures);
	clReleaseMemObject(cl.memobj_light);
	clReleaseProgram(cl.program);
	clReleaseKernel(cl.kernel);
	clReleaseCommandQueue(cl.command_queue);
	clReleaseContext(cl.context);
}

void			rendering(t_main mlx)
{
	t_opencl	cl;
	int			memlenth;
	size_t		global_work_size[3];
	int			ret;

	memlenth = 1440000;
	global_work_size[0] = 1200;
	global_work_size[1] = 1200;
	global_work_size[2] = 0;
	mlx_clear_window(mlx.mlx_ptr, mlx.win_ptr);
	start_cl(&cl);
	mid_cl(&cl, mlx, memlenth);
	args_cl(&cl, mlx);
	if ((ret = clEnqueueNDRangeKernel(cl.command_queue,
				cl.kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL)))
		exit_message("failed to execute kernel");
	if ((ret = clEnqueueReadBuffer(cl.command_queue,
				cl.memobj_data, CL_TRUE, 0, memlenth * sizeof(int),
				mlx.image.ptr, 0, NULL, NULL)))
		exit_message("failed to get buf data");
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image.data, 0, 0);
	free_cl_mem(cl);
}
