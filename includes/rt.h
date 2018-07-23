/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:21:58 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/23 13:24:38 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define HEIGHT 1200
# define WIDTH 1200
# define MAX_SOURCE_SIZE 0x100000

# include "../libft/libft.h"
# include "../libTFD/tinyfiledialogs.h"
# include <math.h>
# include <pwd.h>

# ifdef linux
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# else
#  include "SDL.h"
#  include "SDL_image.h"
# endif

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  include <CL/cl.h>
# endif

/*
** 1 - cam
** 2 - light
** 3 - sphere
** 4 - cone
** 5 - cylinder
** 6 - plane
*/
# define PLANE 6
# define CYLINDER 5
# define CONE 4
# define SPHERE 3

typedef struct	s_point
{
	int x;
	int y;
	int z;
}				t_point;

typedef struct	s_figure
{
	int			index;
	int			type;
	float		radius;
	float		angle;
	float		rfl;
	float		rfr;
	cl_float3	color;
	cl_float3	p;
	cl_float3	d;
}				t_figure;

typedef struct	s_slist
{
	void				*data;
	struct s_slist		*next;
}				t_slist;

typedef struct	s_scene
{
	t_figure	*lights;
	t_figure	*objects;
	int			l_num;
	int			o_num;
	t_figure	cam;
}				t_scene;

typedef struct	s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	unsigned int		ret_num_plat;
	unsigned int		ret_num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	size_t				source_size;
	char				*source_str;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				memobj_data;
	cl_mem				memobj_figures;
	cl_mem				memobj_light;
	cl_mem				memobj_textures;
	cl_int2				memobj_textures_sz;
}				t_opencl;

typedef struct	s_sdl
{
	SDL_Window		*wind;
	SDL_Renderer	*rend;
	SDL_Surface		*sur;
	SDL_Texture		*text;
	SDL_Event		event;
}				t_sdl;

typedef struct	s_main
{
	t_scene		*scene;
	t_opencl	*cl;
	t_sdl		*sdl;
}				t_main;

typedef struct	s_texture
{
	int		*pix;
	int		h;
	int		w;
}				t_texture;

/*
** ADD Figure
*/

t_figure		new_sphere(t_figure cam);
t_figure		new_cylinder(t_figure cam);
t_figure		new_cone(t_figure cam);
t_figure		new_plane(t_figure cam);
void			add_figure(t_figure **figures, t_figure cam, int *o_num);
cl_float3		rotate_ort(cl_float3 point, cl_float3 rot);

/*
**	CL parsing
*/

void			cl_start(t_opencl *cl);
void			cl_kernel_buffer_1(t_opencl *cl, t_main *mlx, int memlenth);
void			cl_kernel_buffer_2(t_opencl *cl, t_main *mlx);
void			cl_args_1(t_opencl *cl, t_main *mlx);
void			cl_args_2(t_opencl *cl, t_main *mlx, int i, int j);
void			cl_init(t_main *mlx);
void			rendering(t_main *mlx);
int				find_figure(t_main *mlx, int i, int j);

void			exit_message(const char *str);
t_slist			*readf(char *argv);

float			v_length(cl_float3 p);
cl_float3		num_dil(cl_float3 p, float n);
float			v_length(cl_float3 p);
int				return_color(cl_float3 c);
t_scene			*scene_create(char *argv);

/*
** HANDLERS
*/

int				key(int key_code, t_main *mlx);
int				mouse(int key_code, int x, int y, t_main *mlx);
void			figure_actions(t_main *mlx, int x, int y);
void			screen_shoot(t_main mlx);
void			call_dialog(t_main *mlx);

void			ft_list_push_back(t_slist **begin_list, void *data);

t_slist			*list_objects(char **argv);
void			*free_lst(t_slist *list);

t_slist			*get_lights(t_slist *strs);
int				get_camera(t_slist *strs, t_figure *cam);
t_figure		*get_figure(t_slist *strs);
int				count_elems(char **str);
t_slist			*no_empty(t_slist *lst);
int				return_point(char **splitted, char *value, cl_float3 *p);
int				return_value(char **splitted, char *value, float *val);
cl_float3		p_to_c(cl_float3 p);
int				return_color_t(char **splitted, char *value, cl_float3 *p);

cl_float3		*norming(cl_float3 *p);
int				ft_list_count(t_slist *begin_list);
int				na(char *name);

#endif
