/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_stock_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:40:30 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/05 15:26:47 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_check_line_length(char *buff)
{
	if (ft_strlen(buff) != BUFF_SIZE)
		ft_error("error: Wrong line length", 1, ft_puterror);
}

static void	ft_check_start(char *buff, short i, char (*start)[2])
{
	while (++i < BUFF_SIZE)
	{
		if (buff[i] == 's')
			++(*start[0]);
		if (buff[i] == '4')
			++(*start[1]);
		if (*start[0] > 1)
			ft_error("error: More than one departure area", 2, ft_puterror);
		if (*start[1] > 1)
			ft_error("error: More than one exit teleportation", 3, ft_puterror);
	}
}

static void	ft_check_char(char *buff, short i)
{
	while (++i < BUFF_SIZE)
		if (buff[i] != FLOOR && buff[i] != WALL && buff[i] != START
			&& buff[i] != SECRET && buff[i] != TP_S && buff[i] != TP_E)
			ft_error("error: Wrong character found", 4, ft_puterror);
}

void		ft_check_map(char *buff, char (*start)[2])
{
	ft_check_line_length(buff);
	ft_check_start(buff, -1, start);
	ft_check_char(buff, -1);
}

void		ft_read_file(char *name, char (*map)[MAPY][MAPX])
{
	t_parse		parse;
	static char	start[2];
	int			test_gnl;

	if ((parse.fd = open(name, O_RDONLY)) == -1)
		ft_error("error", 5, perror);
	parse.i = 0;
	while ((test_gnl = get_next_line(parse.fd, &parse.buff)) > 0)
	{
		if (++parse.i > BUFF_SIZE)
			ft_error("error: Wrong column length", 6, ft_puterror);
		ft_check_map(parse.buff, &start);
		ft_strcpy(map[0][parse.i - 1], parse.buff);
		ft_memdel((void **)&parse.buff);
	}
	ft_memdel((void **)&parse.buff);
	if (test_gnl == -1)
		ft_error("error: Not valid file", 7, ft_puterror);
	if (parse.i < BUFF_SIZE)
		ft_error("error: Wrong column lenght", 8, ft_puterror);
	if (start[0] == 0)
		ft_error("error: No start found", 9, ft_puterror);
	if ((close(parse.fd)) == -1)
		ft_error("error", 10, perror);
}
