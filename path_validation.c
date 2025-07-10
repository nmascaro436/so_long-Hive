/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:57:30 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 12:39:46 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
* Frees the 2D char array previously allocated.
* Frees each row individually, then frees the array of row pointers.
*/

static void	free_copy(char **copy, int rows_allocated)
{
	int	i;

	i = 0;
	while (i < rows_allocated)
	{
		free(copy[i]);
		i++;
	}
	free (copy);
}
/**
* Creates a copy of the map's tile array, allocates memory for a 2D array 
* with the same dimensions as the original map.
* Copies each row string from the original map into the copy.
* Returns a pointer to the copy on success, 
* or NULL if any memory allocation fails.
*/

static char	**map_copy(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * map->height);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[i])
		{
			free_copy(copy, i);
			return (NULL);
		}
		ft_strlcpy(copy[i], map->tiles[i], map->width + 1);
		i++;
	}
	
	return (copy);
}
/**
* Loops through each row and each column, 
* finds the player ands saves its position;
* Returns 1 when found, 0 otherwise.
*/

int	find_player(t_map *map, int *x, int *y)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->tiles[row][col] == 'P')
			{
				*x = col;
				*y = row;
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}
/**
* Recursively explores all reachable tiles (up, down, left, right)
* from the player's position.
* Marks seen tiles with 'S' to prevent going there again.
* Stops recursion if the position is out of bounds, is a wall or already seen.
*/

static void	flood_fill(char **map_copy, int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ;
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'S')
		return ;
	map_copy [y][x] = 'S';
	flood_fill(map_copy, x + 1, y, map);
	flood_fill(map_copy, x - 1, y, map);
	flood_fill(map_copy, x, y + 1, map);
	flood_fill(map_copy, x, y - 1, map);
}
/**
* Validates if all collectibles and the exit are reachable from the player.
* Finds the player's coordinates.
* Creates a copy of the map to avoid modifying the original.
* Performs flood fill from the player's position.
* Scans the copied map: if any C or E remains, the map isn't solvable.
* Frees the copied map and returns 1 if solvable, 0 otherwise.
*/

int	path_validation(t_map *map)
{
	int		player_x;
	int		player_y;
	char	**copy;
	int		row;
	int		col;

	copy = map_copy(map);
	if (!find_player(map, &player_x, &player_y) || !copy)
		return (0);
	flood_fill(copy, player_x, player_y, map);
	row = -1;
	while (++row < map->height)
	{
		col = -1;
		while (++col < map->width)
		{
			if (copy[row][col] == 'C' || copy[row][col] == 'E')
			{
				free_copy(copy, map->height);
				return (0);
			}
		}
	}
	free_copy(copy, map->height);
	return (1);
}
