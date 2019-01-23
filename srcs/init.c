/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:22:58 by lguiller          #+#    #+#             */
/*   Updated: 2019/01/23 13:33:49 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_init_player(char map[MAPY][MAPX], t_player *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < MAPY)
	{
		x = -1;
		while (++x < MAPX)
		{
			if (map[y][x] == 's')
			{
				p->x = (double)x * BLOCK_SIZE + (BLOCK_SIZE / 2.0);
				p->y = (double)y * BLOCK_SIZE + (BLOCK_SIZE / 2.0);
				p->a = ft_rad(180.0);
				break ;
			}
		}
	}
}

void		ft_init_keys_tab(int (*keys_tab)[KEYS_TAB_SIZE])
{
	int i;

	i = -1;
	while (++i < KEYS_TAB_SIZE)
		keys_tab[0][i] = 0;
	keys_tab[0][KEY_H] = 1;
	keys_tab[0][KEY_T] = 1;
}

static void	ft_init_textures(t_all *all, t_textures *textures)
{
	textures->img_n.img = mlx_xpm_file_to_image(all->ptr.mlx,
		TEXT_NORTH, &textures->width, &textures->height);
	textures->img_s.img = mlx_xpm_file_to_image(all->ptr.mlx,
		TEXT_SOUTH, &textures->width, &textures->height);
	textures->img_e.img = mlx_xpm_file_to_image(all->ptr.mlx,
		TEXT_EAST, &textures->width, &textures->height);
	textures->img_w.img = mlx_xpm_file_to_image(all->ptr.mlx,
		TEXT_WEST, &textures->width, &textures->height);
	if (textures->img_n.img == NULL || textures->img_s.img == NULL
		|| textures->img_e.img == NULL || textures->img_w.img == NULL)
		ft_error("error", 11, perror);
	textures->img_n.data = mlx_get_data_addr(textures->img_n.img,
		&textures->img_n.bpp, &textures->img_n.sl, &textures->img_n.endian);
	textures->img_s.data = mlx_get_data_addr(textures->img_s.img,
		&textures->img_s.bpp, &textures->img_s.sl, &textures->img_s.endian);
	textures->img_e.data = mlx_get_data_addr(textures->img_e.img,
		&textures->img_e.bpp, &textures->img_e.sl, &textures->img_e.endian);
	textures->img_w.data = mlx_get_data_addr(textures->img_w.img,
		&textures->img_w.bpp, &textures->img_w.sl, &textures->img_w.endian);
}

void		ft_init_mlx(t_all *all, char *title)
{
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WINX, WINY, title);
	all->info.img = mlx_xpm_file_to_image(all->ptr.mlx, SPR_PAPYRUS,
		&all->sprites.width, &all->sprites.height);
	all->fp.img = mlx_new_image(all->ptr.mlx, FPX, FPY);
	all->sprites.knife = mlx_xpm_file_to_image(all->ptr.mlx, SPR_KNIFE,
		&all->sprites.width, &all->sprites.height);
	all->sprites.wolf = mlx_xpm_file_to_image(all->ptr.mlx, SPR_WOLF,
		&all->sprites.width, &all->sprites.height);
	all->info.data = mlx_get_data_addr(all->info.img, &all->info.bpp,
		&all->info.sl, &all->info.endian);
	all->fp.data = mlx_get_data_addr(all->fp.img, &all->fp.bpp, &all->fp.sl,
		&all->fp.endian);
	ft_init_textures(all, &all->textures);
}
