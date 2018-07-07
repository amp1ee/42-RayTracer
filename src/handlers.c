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

int		key(int key_code, t_main *mlx)
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
	e ? (rendering(*mlx)) : 0;
	return (0);
}
