/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:34:52 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 10:10:56 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Checks if the map is rectangular by ensuring each row's length,
 * matches the width of the first row.
 * Returns 1 if the map is rectangular, 0 otherwise.
 */
static int	is_rectangular(t_map *map)
{
	int		row;
	size_t	len;

	row = 0;
	while (row < map->height)
	{
		len = ft_strlen(map->tiles[row]);
		if (len != (size_t)map->width)
			return (0);
		row++;
	}
	return (1);
}
/**
 * Validates a single map tile and updates counts of special characters.
 */

static int	update_counts_check_tile(char tile, int *starting_pos_count,
		int *exit_count, int *collectible_count)
{
	if (tile != '0' && tile != '1' && tile != 'P' && tile != 'C' && tile != 'E')
		return (0);
	if (tile == 'P')
		(*starting_pos_count)++;
	else if (tile == 'E')
		(*exit_count)++;
	else if (tile == 'C')
		(*collectible_count)++;
	return (1);
}
/**
 * Checks if the map contains only valid characters
 * and correct counts of required items.
 * Returns 1 if all characters are valid and counts are correct, 0 otherwise.
 */

static int	has_valid_chars(t_map *map)
{
	int	row;
	int	col;
	int	exit_count;
	int	starting_pos_count;
	int	collectible_count;

	exit_count = 0;
	starting_pos_count = 0;
	collectible_count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (!update_counts_check_tile(map->tiles[row][col],
					&starting_pos_count, &exit_count, &collectible_count))
				return (0);
			col++;
		}
		row++;
	}
	if (starting_pos_count != 1 || exit_count != 1 || collectible_count < 1)
		return (0);
	return (1);
}
/**
 * Verifies that the map is fully enclosed by walls.
 * Checks the entire first and last rows, and the first
 * and last characters of every row in between (edges).
 * Returns 1 if the map is surrounded by walls, 0 otherwise.
 */

static int	check_walls(t_map *map)
{
	int	row;
	int	col;

	col = 0;
	while (col < map->width)
	{
		if (map->tiles[0][col] != '1')
			return (0);
		col++;
	}
	col = 0;
	while (col < map->width)
	{
		if (map->tiles[map->height - 1][col] != '1')
			return (0);
		col++;
	}
	row = 0;
	while (row < map->height)
	{
		if (map->tiles[row][0] != '1' || map->tiles[row][map->width - 1] != '1')
			return (0);
		row++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!is_rectangular(map))
	{
		ft_putendl_fd("Error: map isn't rectangular ", 2);
		return (0);
	}
	if (!check_walls(map))
	{
		ft_putendl_fd("Error: map isn't surrounded by walls", 2);
		return (0);
	}
	if (!has_valid_chars(map))
	{
		ft_putendl_fd("Error: invalid characters "
						"or wrong number of E, C or P",
						2);
		return (0);
	}
	if (!path_validation(map))
	{
		ft_putendl_fd("Error: map isn't solvable", 2);
		return (0);
	}
	return (1);
}
