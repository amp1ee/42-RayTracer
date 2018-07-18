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

#define KEY_KODE event.key.keysym.scancode
#define E_TYPE event.type

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((sdl->wind = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, WIDTH,
						HEIGHT, SDL_WINDOW_SHOWN)))
			if ((sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
				if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32 , 0, 0, 0, 0)))
					exit(1);
				return ;
	ft_putendl("Error in init_sdl()");
	exit(0);
}

void	sdl_event(t_main *mlx)
{
	(void)mlx;
}

int		main(int argc, char **argv)
{
	t_main		mlx;

	if (argc != 2)
		return (0);
	mlx.scene = scene_create(argv[1]);
	cl_init(&mlx);
	
	/*mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "RT");
	mlx.image.data = mlx_new_image(mlx.mlx_ptr, HEIGHT, WIDTH);
	mlx.image.ptr = (int *)mlx_get_data_addr(mlx.image.data,
			&mlx.image.bits, &mlx.image.sz_l, &mlx.image.endi);
	mlx_clear_window(mlx.mlx_ptr, mlx.win_ptr);
	rendering(&mlx);
	mlx_mouse_hook(mlx.win_ptr, &mouse, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, &key, &(mlx));
	mlx_hook(mlx.win_ptr, 17, 0, (int (*)())exit, NULL);
	mlx_loop(mlx.mlx_ptr);*/

	SDL_Event	event;

	init_sdl(mlx.sdl);
	while (1) {
        while (SDL_PollEvent(&event)) {
            if ((SDL_QUIT == E_TYPE)
            	|| (SDL_KEYDOWN == E_TYPE && KEY_KODE == SDL_SCANCODE_ESCAPE))
                exit(0);
            else if (SDL_KEYDOWN == E_TYPE && KEY_KODE == SDL_SCANCODE_UP)
                mlx.scene->cam.d.x += 5;
        }
        rendering(&mlx);
    }
	
	return (0);
}
