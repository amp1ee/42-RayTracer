/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:17:34 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/23 18:17:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		debugger(int r, cl_program program, cl_device_id device_id)
{
	size_t	log_size;
	char	*log;

	if (r == CL_BUILD_PROGRAM_FAILURE)
	{
		clGetProgramBuildInfo(program,
			device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = (char *)malloc(log_size);
		clGetProgramBuildInfo(program, device_id,
					CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putendl(log);
		free(log);
		exit(1);
	}
}

static void		read_kernel(const char *filename,
						char **source_str, size_t *source_size)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_message("Failed to read kernel");
	*source_str = (char *)malloc(MAX_SOURCE_SIZE);
	*source_size = read(fd, *source_str, MAX_SOURCE_SIZE);
}

void			cl_start(t_opencl *cl)
{
	int r;

	if ((r = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_plat))))
		exit_message("couldn*t load platform");
	if ((r = clGetDeviceIDs(cl->platform_id,
		CL_DEVICE_TYPE_CPU, 1, &(cl->device_id), &(cl->ret_num_devices))))
		exit_message("couldn*t get device id");
	cl->context = clCreateContext(NULL, 1, &(cl->device_id), NULL, NULL, &r);
	if (r)
		exit_message("couldn*t create context");
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &r);
	if (r)
		exit_message("couldn*t create command queue");
	read_kernel("./opencl/render.cl", &(cl->source_str), &(cl->source_size));
	cl->program = clCreateProgramWithSource(cl->context, 1,
	(const char **)&(cl->source_str), (const size_t *)&(cl->source_size), &r);
	if (r)
		exit_message("couldn*t create binary");
	free(cl->source_str);
	r = clBuildProgram(cl->program, 1, &(cl->device_id),
		"-I ./includes/", NULL, NULL);
	debugger(r, cl->program, cl->device_id);
}

int				count_arr(t_scene sc)
{
	int i;
	int sum;

	i = -1;
	sum = 0;
	while (++i < sc.textures_num)
	{
		sum += sc.textures_info[i].x * sc.textures_info[i].y;
	}
	if (!sum)
		return (1);
	else
		return (sum);
}

void			cl_kernel_buffer_1(t_opencl *cl, t_main *mlx, int memlenth)
{
	int			ret;

	cl->kernel = clCreateKernel(cl->program, "rendering", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				memlenth * sizeof(int), NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		mlx->scene->o_num * sizeof(t_figure), mlx->scene->objects, &ret);
	if (ret)
		exit_message("failed to create buf2");
	cl->memobj_light = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		mlx->scene->l_num * sizeof(t_figure), mlx->scene->lights, &ret);
	if (ret)
		exit_message("failed to create buf3");
	cl->memobj_textures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		count_arr(*mlx->scene) * sizeof(int), mlx->scene->textures, &ret);
	if (ret)
		exit_message("failed to create buf4");
	cl->memobj_textures_sz = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
mlx->scene->textures_num * sizeof(cl_int3), mlx->scene->textures_info, &ret);
	if (ret)
		exit_message("failed to create buf5");
}

void			cl_args_1(t_opencl *cl, t_main *mlx)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(cl_mem), &cl->memobj_light)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(t_figure), &mlx->scene->cam)))
		exit_message("failed to set arg4");
	if ((ret = clSetKernelArg(cl->kernel, 4,
		sizeof(int), &mlx->scene->l_num)))
		exit_message("failed to set arg5");
	if ((ret = clSetKernelArg(cl->kernel, 5,
		sizeof(int), &mlx->scene->o_num)))
		exit_message("failed to set arg6");
	if ((ret = clSetKernelArg(cl->kernel, 6,
		sizeof(cl_mem), &cl->memobj_textures)))
		exit_message("failed to set arg7");
	if ((ret = clSetKernelArg(cl->kernel, 7,
		sizeof(cl_mem), &cl->memobj_textures_sz)))
		exit_message("failed to set arg8");
}

void			cl_kernel_buffer_2(t_opencl *cl, t_main *mlx)
{
	int	ret;

	cl->kernel = clCreateKernel(cl->program, "find_figure", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				sizeof(int), NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context,
		CL_MEM_USE_HOST_PTR,
		mlx->scene->o_num * sizeof(t_figure), mlx->scene->objects, &ret);
	if (ret)
		exit_message("failed to create buf2");
}

void			cl_args_2(t_opencl *cl, t_main *mlx, int i, int j)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0,
		sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(t_figure), &mlx->scene->cam)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(int), &i)))
		exit_message("failed to set arg4");
	if ((ret = clSetKernelArg(cl->kernel, 4,
		sizeof(int), &j)))
		exit_message("failed to set arg5");
	if ((ret = clSetKernelArg(cl->kernel, 5,
		sizeof(int), &mlx->scene->o_num)))
		exit_message("failed to set arg5");
}

int				*random_array(int size)
{
	int *ret;
	int i;

	ret = malloc(sizeof(int) * size);
	i = -1;
	while (++i < size)
		ret[i] = rand() % 255;
	return (ret);
}

void			cl_kernel_buffer_3(t_opencl *cl)
{
	int	ret;
	int	*rand;

	rand = random_array(512);
	cl->kernel = clCreateKernel(cl->program, "create_disruption", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				sizeof(int) * MEM_LENGTH, NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
				512 * sizeof(int), rand, &ret);
	if (ret)
		exit_message("failed to create buf2");
	free(rand);
}

void			cl_args_3(t_opencl *cl, cl_float3 color, int type)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0,
		sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_float3), &color)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(int), &type)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg3");
}
