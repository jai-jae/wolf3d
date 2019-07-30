/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viccarau <viccarau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:51:37 by viccarau          #+#    #+#             */
/*   Updated: 2019/07/29 10:46:50 by viccarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int print_map(int **map, t_obj obj, t_player *player)
{
	int	lines;
	int	i;
	int	j;

	lines = (obj.size / obj.len);
	i = 0;
	printf("\n \t0  1  2  3  4  5  6  7  8  9  10 11\n\n");
	while (i < lines)
	{
		j = 0;
		while (j < obj.len)
		{
			if (j == 0)
				printf("%d\t", i);
			if (map[i][j] == 2)
			{
				player->position.x = (i * 64) + 32;
				player->position.y = (j * 64) + 32;
			}
			printf("%d  ", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	return (0);
}

int		my_function(int keycode, t_wolf *wolf)
{
	if (keycode == SDL_SCANCODE_R)
		printf("\nYou pressed R\n\n");
	if (keycode == SDL_SCANCODE_ESCAPE)
		is_alloc(NULL, *wolf, 0);
	return (1);
}

void	ft_raycast(t_wolf *wolf, t_player *player)
{
	if (facing up)
		player.ray.y = (p.position.y >> 8) * (64) - 1;
	if (facing down)
		ray.y = (p.position.y >> 8) * (64) + 64;
	ray.x = (p.position.x) + (p.position.y - ray.y) / tan(FOV);
	if (facing up)
		Ya = -64;
	else
		Ya = 64;

	Xa = 64 / tan(FOV);
	while (!hit)
	{
		C.x = (ray.x + Xa);
		C.y = (ray.y + Ya);
		if (wall[ray.y >> 8][ray.x >> 8] == WALL)
			hit = 1;
	}
}

void	ft_wolf_init(t_wolf *wolf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wolf->sdl.win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, 0);
	wolf->img = ft_memalloc(W * H * sizeof(unsigned int));
}

int		main(int ac, char **av)
{
	int		i;
	t_wolf	wolf;
	int		fd;
	//float	avg_fps;
	t_player p;

	p.direction.x = 0;
	p.direction.y = -1.0f;
	//p.plane.x = 0;
	//p.plane.y = 80;

	/*
 center of projection plane = (640, 360);
 distance to the projection plane = 426;
 angle between rays = FOV / 1280;
 */

	mem_init(&wolf);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("test.map", O_RDONLY);
	if (fd > 0)
	{
		tkneizer(fd, &wolf);
		print_map(int_to_tab(wolf.obj), wolf.obj, &p);
		printf("\nplayer = %d, %d\n", p.position.x, p.position.y);
		ft_wolf_init(&wolf);
		wolf.sdl.renderer = SDL_CreateRenderer(wolf.sdl.win, -1, 0);
		wolf.sdl.texture = SDL_CreateTexture(wolf.sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
		//ft_raycast(&wolf);
		i = 0;
		while (1)
		{
			//avg_fps = i / ( SDL_GetTicks() / 1000.f );
			while (SDL_PollEvent(&wolf.sdl.event))
			{
				if (wolf.sdl.event.type == SDL_QUIT)
					exit(0);
				if (wolf.sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					exit(0);
				my_function(wolf.sdl.event.key.keysym.scancode, &wolf);
			}
			//if (i % 100 == 0)
			//printf("fps = %f\n", avg_fps);
			i++;
			if (i % 6 == 0)
			{
				SDL_UpdateTexture(wolf.sdl.texture, NULL, wolf.img, W * sizeof(unsigned int));
				SDL_RenderCopy(wolf.sdl.renderer, wolf.sdl.texture, NULL, NULL);
				SDL_RenderPresent(wolf.sdl.renderer);
			}
		}
	}
	return (0);
}
