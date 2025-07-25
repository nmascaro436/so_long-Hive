/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_optimization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:40:26 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/25 09:53:16 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * Renders a single tile by first drawing the floor,
 * then the specified tile content.
 */
void	render_single_tile(t_game *game, int col, int row, char tile)
{
	mlx_image_to_window(game->mlx, game->textures.floor_image,
		col * TILE_SIZE, row * TILE_SIZE);
	helper_render(game, tile, row, col);
}
/**
 * Clears the old player position by rendering it as floor.
 */
void	clear_old_position(t_game *game, int col, int row)
{
	render_single_tile(game, col, row, '0');
}
/**
 * Updates the new player position.
 * If a collectible is taken, it clears the tile (renders floor),
 * and draws the player image.
 */
void	update_new_position(t_game *game, int col, int row, int collected_item)
{
	if(collected_item)
		render_single_tile(game, col, row, '0');
	render_single_tile(game, col, row, 'P');
}
