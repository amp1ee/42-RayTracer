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
						SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
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
(add_figure(&mlx->scene->objects, mlx->scene->cam, &mlx->scene->o_num)) : 0;
	(event->K_K == SDL_SCANCODE_KP_MINUS) ? (call_dialog(mlx)) : 0;
	(event->K_K == SDL_SCANCODE_KP_0) ? screen_shoot(*mlx) : 0;
	(event->K_K == SDL_SCANCODE_KP_1) ? apply_effects(mlx, 1) : 0;
}

void	mouse_events(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	figure_actions(mlx, x, y);
}

void	sdl_events(t_main *mlx, SDL_Event *event)
{
	while (SDL_PollEvent(event))
		if (event->E_TYPE == SDL_KEYDOWN)
			key_events(mlx, event);
		else if (event->E_TYPE == SDL_MOUSEBUTTONDOWN)
			mouse_events(mlx);
		else if (event->E_TYPE == SDL_QUIT)
			exit(1);
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
	while (1)
	{
		sdl_events(&mlx, &event);
		rendering(&mlx);
	}
	return (0);
}
