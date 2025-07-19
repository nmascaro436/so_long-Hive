/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:54:42 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 11:08:34 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	row;

	row = 0;
	if (!map)
		return ;
	while (row < map->height)
	{
		free(map->tiles[row]);
		row++;
	}
	free(map->tiles);
	free(map);
}
/**
* Frees all allocated resources and exits the program with an error.
* Frees the map (if allocated), cleans up all loaded textures
* and images and terminates the MLX window context.
*/
void	free_all_and_exit(t_game *game, const char *error_message)
{
	if (error_message)
		ft_putendl_fd(error_message, 2);
	if (game)
	{
		if (game->map)
			free_map(game->map);
		cleanup_textures(game);
		if (game->mlx)
			mlx_terminate(game->mlx);
	}
	exit(1);
}
void	read_lines_cleanup(char *line, t_list *head, int fd)
{
	free(line);
	free_list_nodes(head);
	close(fd);
}
void	free_partial_map_allocations(t_map *map, int alloc_rows)
{
	int	i;

	i = 0;
	while (i < alloc_rows)
	{
		free(map->tiles[i]);
		i++;
	}
	free(map->tiles);
	free(map);
}
