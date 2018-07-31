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

#define K_K key.keysym.scancode
#define E_TYPE type

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit_message("Error in init sdl");
	if (!(sdl->wind = SDL_CreateWindow("RT",
						SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, WIDTH + SIDE_W, HEIGHT + MEN_H,
						SDL_WINDOW_SHOWN)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
	if (!(sdl->ui.menu_button =
		(SDL_Surface **)malloc(sizeof(SDL_Surface *) * BT_COUNT)))
		exit_message("Error in UI");
	sdl->keyboard_state = SDL_GetKeyboardState(NULL);
}

void	effects(int *a)
{
	(*a)++;
	*a = *a % 5;
	printf("%d\n", *a);
}

void	key_events(t_main *mlx, SDL_Event *event)
{
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit(0) : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (mlx->scene->cam.d.x += 5) : 0;
	(event->K_K == SDL_SCANCODE_DOWN) ? (mlx->scene->cam.d.x -= 5) : 0;
	(event->K_K == SDL_SCANCODE_LEFT) ? (mlx->scene->cam.d.y += 5) : 0;
	(event->K_K == SDL_SCANCODE_RIGHT) ? (mlx->scene->cam.d.y -= 5) : 0;
	(event->K_K == SDL_SCANCODE_A) ? (mlx->scene->cam.p.x -= 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_D) ? (mlx->scene->cam.p.x += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_W) ? (mlx->scene->cam.p.z += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_S) ? (mlx->scene->cam.p.z -= 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_E) ? (mlx->scene->cam.p.y += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_Q) ? (mlx->scene->cam.p.y -= 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_KP_PLUS) ?
(add_figure(mlx, &mlx->scene->objects,
	mlx->scene->cam, &mlx->scene->o_num, 'e')) : 0;
	(event->K_K == SDL_SCANCODE_KP_1) ? effects(&mlx->scene->effect) : 0;
}

void	mouse_events(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (x > 20 && x < 92 && y > 15 && y < BT_H + 15)
		call_dialog(mlx);
	else if (x > 112 && x < 188 && y > 15 && y < BT_H + 15)
		del_scene(mlx);
	else if (x > 208 && x < 278 && y > 15 && y < BT_H + 15)
		write_in_file(*mlx->scene);
	else if (x > 298 && x < 415 && y > 15 && y < BT_H + 15)
		screen_shoot(*mlx);
	else if (x > 435 && x < 520 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects,
			mlx->scene->cam, &mlx->scene->o_num, 's');
	else if (x > 540 && x < 617 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects,
			mlx->scene->cam, &mlx->scene->o_num, 'p');
	else if (x > 637 && x < 709 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects,
			mlx->scene->cam, &mlx->scene->o_num, 'c');
	else if (x > 729 && x < 826 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects,
			mlx->scene->cam, &mlx->scene->o_num, 'y');
	else if (x > SIDE_W && y > MEN_H)
	{
		mlx->sdl->ui.show_info = 1;
		set_curr_fig(&mlx->sdl->ui.curr_figure,
			mlx->scene->objects, figure_actions(mlx, x, y));
	}
	handle_curr_obj(mlx, x, y);
}

cl_float3	vector_add(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

cl_float3	vector_subtract(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3	new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

void	mousewheel_events(t_main *mlx, SDL_Event *event)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (mlx->sdl->keyboard_state[SDL_SCANCODE_LSHIFT]
		&& x > SIDE_W && y > MEN_H)
	{
		if (event->wheel.y > 0)
			mlx->scene->cam.p =
		vector_add(mlx->scene->cam.p, mlx->scene->cam.color);
		else if (event->wheel.y < 0)
			mlx->scene->cam.p =
		vector_subtract(mlx->scene->cam.p, mlx->scene->cam.color);
	}
}

void	mousemove_events(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (mlx->sdl->keyboard_state[SDL_SCANCODE_LSHIFT]
		&& x > SIDE_W && y > MEN_H)
	{
		if (x > mlx->prev.mouse_x)
			mlx->scene->cam.d.y -= 0.5;
		else if (x < mlx->prev.mouse_x)
			mlx->scene->cam.d.y += 0.5;
		if (y > mlx->prev.mouse_y)
			mlx->scene->cam.d.x -= 0.5;
		else if (y < mlx->prev.mouse_y)
			mlx->scene->cam.d.x += 0.5;
	}
	mlx->prev.mouse_x = x;
	mlx->prev.mouse_y = y;
}

void	sdl_events(t_main *mlx, SDL_Event *event)
{
	cl_float3	d;

	d.x = 0;
	d.y = 0;
	d.z = 1;
	mlx->scene->cam.color = rotate_ort(d, mlx->scene->cam.d);
	mlx->scene->cam.color = get_unit_vector(mlx->scene->cam.color);
	while (SDL_PollEvent(event))
	{
		if (event->E_TYPE == SDL_KEYDOWN)
			key_events(mlx, event);
		else if (event->E_TYPE == SDL_MOUSEBUTTONDOWN)
			mouse_events(mlx);
		else if (event->E_TYPE == SDL_MOUSEWHEEL)
			mousewheel_events(mlx, event);
		else if (event->E_TYPE == SDL_MOUSEMOTION)
			mousemove_events(mlx);
		else if (event->E_TYPE == SDL_QUIT)
			exit(1);
	}
}

void	exit_rt(void)
{
	TTF_Quit();
	SDL_Quit();
}

int		main(int argc, char **argv)
{
	t_main		mlx;
	SDL_Event	event;

	if (argc != 2)
		return (0);
	cl_init(&mlx);
	mlx.scene = parse_json(argv[1], mlx.cl);
	init_sdl(mlx.sdl);
	init_ui(mlx.sdl);
	while (1)
	{
		sdl_events(&mlx, &event);
		rendering(&mlx);
	}
	exit_rt();
	return (0);
}
