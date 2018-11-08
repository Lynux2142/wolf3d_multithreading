/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:24:19 by bede-fre          #+#    #+#             */
/*   Updated: 2018/11/08 17:30:55 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_moving(t_all *all, double dir)
{
	t_coord		p;
	t_fcoord	sh;
	double		speed;

	if (all->keys_tab[KEY_CTRL] == TRUE)
		speed = CROUCH_SPEED;
	else if (all->keys_tab[KEY_SHIFT] == TRUE && all->keys_tab[KEY_W] == TRUE)
		speed = RUN_SPEED;
	else
		speed = MOVE_SPEED;
	sh.x = (cos(all->p.a) >= 0.0) ? dir * HIT_BOX : -dir * HIT_BOX;
	sh.y = (sin(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	p.x = (sh.x + all->p.x + dir * ((cos(all->p.a) * speed)));
	p.y = (sh.y + all->p.y + -dir * ((sin(all->p.a) * speed)));
	all->p.x += (all->p.y >= 0.0 && to_map(all->p.y) < 32.0)
		&& (p.x >= HIT_BOX && p.x < (MAPX * (int)BLOCK_SIZE - HIT_BOX))
		&& (all->rc.map[to_map((all->p.y - HIT_BOX))][to_map(p.x)] != '1' &&
		all->rc.map[to_map((all->p.y + HIT_BOX))][to_map(p.x)] != '1') ?
		dir * (cos(all->p.a) * speed) : 0.0;
	all->p.y += (all->p.x >= 0.0 && to_map(all->p.x) < 32.0)
		&& (p.y >= HIT_BOX && p.y < (MAPY * (int)BLOCK_SIZE - HIT_BOX))
		&& (all->rc.map[to_map(p.y)][to_map((all->p.x + HIT_BOX))] != '1' &&
		all->rc.map[to_map(p.y)][to_map((all->p.x - HIT_BOX))] != '1') ?
		-dir * (sin(all->p.a) * speed) : 0.0;
}

static void	ft_strafing(t_all *all, double dir)
{
	t_coord		p;
	t_fcoord	sh;
	double		speed;

	if (all->keys_tab[KEY_CTRL] == TRUE)
		speed = CROUCH_SPEED;
	else
		speed = MOVE_SPEED;
	sh.x = (sin(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	sh.y = (cos(all->p.a) >= 0.0) ? -dir * HIT_BOX : dir * HIT_BOX;
	p.x = (sh.x + all->p.x + -dir * (sin(all->p.a) * speed));
	p.y = (sh.y + all->p.y + -dir * (cos(all->p.a) * speed));
	all->p.x += (all->p.y >= 0.0 && to_map(all->p.y) < 32.0)
		&& (p.x >= HIT_BOX && p.x < (MAPX * (int)BLOCK_SIZE - HIT_BOX))
		&& (all->rc.map[to_map((all->p.y - HIT_BOX))][to_map(p.x)] != '1' &&
		all->rc.map[to_map((all->p.y + HIT_BOX))][to_map(p.x)] != '1') ?
		-dir * (sin(all->p.a) * speed) : 0.0;
	all->p.y += (all->p.x >= 0.0 && to_map(all->p.x) < 32.0)
		&& (p.y >= HIT_BOX && p.y < (MAPY * (int)BLOCK_SIZE - HIT_BOX))
		&& (all->rc.map[to_map(p.y)][to_map((all->p.x + HIT_BOX))] != '1' &&
		all->rc.map[to_map(p.y)][to_map((all->p.x - HIT_BOX))] != '1') ?
		-dir * (cos(all->p.a) * speed) : 0.0;
}

static void	ft_teleport(t_all *all)
{
	int	y;
	int	x;

	if (all->rc.map[to_map(all->p.y)][to_map(all->p.x)] == '3')
	{
		y = -1;
		while (++y < MAPY)
		{
			x = -1;
			while (++x < MAPX)
			{
				if (all->rc.map[y][x] == '4')
				{
					all->p.x = x * (int)BLOCK_SIZE + 32;
					all->p.y = y * (int)BLOCK_SIZE + 32;
				}
			}
		}
	}
}

static void	ft_refresh_images(t_all *all)
{
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->info.img, 0, 0);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->fp.img, INFOX, 0);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->sprites.knife,
		INFOX - 0 + FPX / 2, FPY - 239);
	mlx_put_image_to_window(all->ptr.mlx, all->ptr.win, all->sprites.wolf, 3,
		300);
}

int			ft_movements(t_all *all)
{
	if (all->keys_tab[KEY_A] == TRUE)
		ft_strafing(all, 1.0);
	if (all->keys_tab[KEY_D] == TRUE)
		ft_strafing(all, -1.0);
	if (all->keys_tab[KEY_W] == TRUE)
		ft_moving(all, 1.0);
	if (all->keys_tab[KEY_S] == TRUE)
		ft_moving(all, -1.0);
	if (all->keys_tab[KEY_Q] == TRUE)
		all->p.a += ft_rad(ROT_SPEED);
	if (all->keys_tab[KEY_E] == TRUE)
		all->p.a -= ft_rad(ROT_SPEED);
	all->skip = (all->keys_tab[KEY_ENTER] == TRUE) ? 1 : 0;
	all->wall_gap1 = (all->keys_tab[KEY_CTRL] == TRUE) ? 1.333333333333f : 2.0f;
	all->wall_gap2 = (all->keys_tab[KEY_CTRL] == TRUE) ? 4.0f : 2.0f;
	ft_teleport(all);
	mlx_destroy_image(all->ptr.mlx, all->info.img);
	all->info.img = mlx_xpm_file_to_image(all->ptr.mlx, SPR_PAPYRUS,
		&all->sprites.width, &all->sprites.height);
	ft_print_all(all);
	ft_refresh_images(all);
	return (1);
}
