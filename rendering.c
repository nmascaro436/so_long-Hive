/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:46:07 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 11:22:20 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	helper_render(t_game *game, char tile, int row, int col)
{
	if (tile == '1')
		mlx_image_to_window(game->mlx, game->textures.wall_image,
			col * TILE_SIZE, row * TILE_SIZE);
	else if (tile == 'C')
		mlx_image_to_window(game->mlx, game->textures.collectible_image,
			col * TILE_SIZE, row * TILE_SIZE);
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->textures.exit_image,
			col * TILE_SIZE, row * TILE_SIZE);
	else if (tile == 'P')
		mlx_image_to_window(game->mlx, game->textures.player_image,
			col * TILE_SIZE, row * TILE_SIZE);
}
/**
* For each tile, the function first draws the floor image as the base. 
* And then depending on the character, it draws accordingly.
* Each image is placed at the corresponding position scaled by TILE_SIZE.
*/

void	render_map(t_game *game)
{
	int		row;
	int		col;
	char	tile;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			tile = game->map->tiles[row][col];
			mlx_image_to_window(game->mlx, game->textures.floor_image,
				col * TILE_SIZE, row * TILE_SIZE);
			helper_render(game, tile, row, col);
			col++;
		}
		row++;
	}
}
/**
* Initializes the player's starting coordinates in the game, 
* so that the player can be rendered and moved correctly during the game.
* If the player isn't found, it cleans up and terminates the game.
*/

void	init_player_position(t_game *game)
{
	if (!find_player(game->map, &game->player_x, &game->player_y))
		free_all_and_exit(game, "Error: player not found in map");
}
