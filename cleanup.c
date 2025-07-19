/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:54:42 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 11:49:43 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * Frees memory used for the 2D tile array
 * and the map structure.
 */

void	free_map(t_map *map)
{
	int	row;

	if (!map)
		return ;
	if (map->tiles)
	{
		row = 0;
		while (row < map->height)
		{
			if (map->tiles[row])
				free(map->tiles[row]);
			row++;
		}
		free(map->tiles);
	}
	free(map);
}
/**
* Frees all game_related resources and exits the program.
* Prints error message to stderr.
* Frees the graphic contents, textures, map, and exits program.
*/

void	free_all_and_exit(t_game *game, const char *error_message)
{
	if (error_message)
		ft_putendl_fd(error_message, 2);
	if (game)
	{
		if (game->mlx)
		{
			cleanup_textures(game);
			mlx_terminate(game->mlx);
		}
		if (game->map)
			free_map(game->map);
	}
	exit(1);
}
/**
 * Frees the last line read, the list of all read lines,
 * and closes the file descriptor.
 */

void	read_lines_cleanup(char *line, t_list *head, int fd)
{
	free(line);
	free_list_nodes(head);
	close(fd);
}
/**
 * Frees a partially allocated map structure.
 */

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
