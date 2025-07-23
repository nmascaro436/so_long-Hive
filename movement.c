/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:14:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/23 10:47:27 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
* Handles keyboard input events.
* Reacts only to key press events, ignores release or repeat.
* It calls move_player with direction depending on WASD/arrow.
* If Esc is pressed it exits the game cleanly.
*/

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(game, 0, -1);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(game, -1, 0);
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(game, 0, 1);
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0);
	if (keydata.key == MLX_KEY_ESCAPE)
		free_all_and_exit(game, "Game closed");
}
/**
* Increments the move count, prints the current move count to standard output
* and redraws the game map to reflect any changes. 
*/

static void	print_and_render_moves(t_game *game)
{
	game->move_count++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->move_count, 1);
	ft_putendl_fd("", 1);
	render_map(game);
}
/**
* If the player has all collectibles, prints moves,
* frees resources and exits the game with winning message.
* Returns 1 if the game ends, 0 otherwise.
*/

static int	handle_exit_tile(t_game *game)
{
	if (game->collectibles_left == 0)
	{
		print_and_render_moves(game);
		free_all_and_exit(game, "You win!");
		return (1);
	}
	return (0);
}
/**
* Attempts to move the player in the given direction.
* Returns immediately if target position is out of bounds or a wall.
* If the target is an exit, calls handle_exit_tile to check win condition.
* If the target is a collectible, decreases collectible count
* and removes it from map.
* Updates the player position on the map tiles.
* Calls print_and_render_moves to update move count and redraw the map.
*/

void	move_player(t_game *game, int horizontal_move, int vertical_move)
{
	int		target_x;
	int		target_y;
	char	target_tile;

	target_x = game->player_x + horizontal_move;
	target_y = game->player_y + vertical_move;
	if (target_x < 0 || target_y < 0 || target_x >= game->map->width
		|| target_y >= game->map->height)
		return ;
	target_tile = game->map->tiles[target_y][target_x];
	if (target_tile == '1')
		return ;
	if (target_tile == 'E')
	{
		handle_exit_tile(game);
		return ;
	}
	if (target_tile == 'C')
		game->collectibles_left--;
	game->map->tiles[game->player_y][game->player_x] = '0';
	game->map->tiles[target_y][target_x] = 'P';
	game->player_x = target_x;
	game->player_y = target_y;
	print_and_render_moves(game);
}
/**
* Counts the total number of collectibles present on the map.
* Returns the count of collectible items. 
*/

int	count_collectibles(t_map *map)
{
	int	count;
	int	row;
	int	col;

	count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->tiles[row][col] == 'C')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}
