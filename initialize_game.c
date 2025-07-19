/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:47 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 11:54:41 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
* Calculates the window size based on map dimensions and defined tile size,
* then creates a window titled "so_long" that can't be resized.
* Stores the MLX context pointer and the map pointer in the provided game struct.
* Returns 0 on success and 1 if MLX initialization or window creation fails.
*/

int	initialize_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init(map->width * TILE_SIZE, map->height * TILE_SIZE,
			"so_long", false);
	if (!game->mlx)
		return (1);
	game->map = map;
	return (0);
}

static int	helper_textures(t_game *game, mlx_texture_t **texture,
mlx_image_t **image, const char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		return (1);
	*image = mlx_texture_to_image(game->mlx, *texture);
	if (!*image)
		return (1);
	return (0);
}
/**
* Uses the helper to load each PNG from the assets folder
* and convert it into an image that can be rendered in the MLX window.
* Returns 0 on success, 1 if any texture or image fails to load.
*/

int	load_textures(t_game *game)
{
	if (helper_textures(game, &game->textures.player_texture,
			&game->textures.player_image, "assets/player.png"))
		return (1);
	if (helper_textures(game, &game->textures.wall_texture,
			&game->textures.wall_image, "assets/wall.png"))
		return (1);
	if (helper_textures(game, &game->textures.floor_texture,
			&game->textures.floor_image, "assets/floor.png"))
		return (1);
	if (helper_textures(game, &game->textures.collectible_texture,
			&game->textures.collectible_image, "assets/collectible.png"))
		return (1);
	if (helper_textures(game, &game->textures.exit_texture,
			&game->textures.exit_image, "assets/exit.png"))
		return (1);
	return (0);
}

static void	cleanup(t_game *game, mlx_texture_t **texture, mlx_image_t **image)
{
	if (*image)
	{
		mlx_delete_image(game->mlx, *image);
		*image = NULL;
	}
	if (*texture)
	{
		mlx_delete_texture(*texture);
		*texture = NULL;
	}
}
/**
* Calls the helper (which frees the memory used by the image and texture)
* to ensure proper memory cleanup before game exits.
*/

void	cleanup_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	cleanup(game, &game->textures.player_texture, &game->textures.player_image);
	cleanup(game, &game->textures.wall_texture, &game->textures.wall_image);
	cleanup(game, &game->textures.floor_texture, &game->textures.floor_image);
	cleanup(game, &game->textures.collectible_texture,
		&game->textures.collectible_image);
	cleanup(game, &game->textures.exit_texture, &game->textures.exit_image);
}
