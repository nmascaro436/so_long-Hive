/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:14:23 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/25 09:25:09 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
* Handles keyboard input for the game.
* Checks if a key was pressed and then calls
* move_player with direction depending on WASD/arrow.
* If Esc is pressed it exits the game cleanly.
*/
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			free_all_and_exit(game, "Game closed");
		else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			move_player(game, 0, -1);
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			move_player(game, -1, 0);
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			move_player(game, 0, 1);
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			move_player(game, 1, 0);
	}
}
/**
* Prints the current move count to standard output.
*/

static void	print_moves(t_game *game)
{
	game->move_count++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->move_count, 1);
	ft_putendl_fd("", 1);
}
/**
* Updates the game state after a valid player move.
* Decreases collectibles count if the move is to 'C'.
* Increments move counter.
* Updates the map tiles to reflect the new and old positions.
* Updates the player's stored coordinates.
* Calls rendering functions to clear the old position and update new one.
* Prints the updated move count.
*/

static void	update_game_state(t_game *game, t_move move)
{
	int	collected_item;

	collected_item = (move.target_tile == 'C');
	if (collected_item)
		game->collectibles_left--;
	game->move_count++;
	game->map->tiles[move.old_y][move.old_x] = '0';
	game->map->tiles[move.target_y][move.target_x] = 'P';
	game->player_x = move.target_x;
	game->player_y = move.target_y;
	clear_old_position(game, move.old_x, move.old_y);
	update_new_position(game, move.target_x, move.target_y, collected_item);
	print_moves(game);
}
/**
* Attempts to move the player in the given direction.
* Returns immediately if target position is out of bounds or a wall.
* If the target is an exit, and no collectibles left, moves player
* and ends game.
* If the target is a collectible, decreases collectible count
* and removes it from map.
* Updates the player position on the map tiles.
* Updates move count and redraws the map.
*/

void	move_player(t_game *game, int horizontal_move, int vertical_move)
{
	t_move	move;

	move.old_x = game->player_x;
	move.old_y = game->player_y;
	move.target_x = game->player_x + horizontal_move;
	move.target_y = game->player_y + vertical_move;
	if (move.target_x < 0 || move.target_y < 0 || move.target_x >= game->map->width
		|| move.target_y >= game->map->height)
		return ;
	move.target_tile = game->map->tiles[move.target_y][move.target_x];
	if (move.target_tile == '1')
		return ;
	if (move.target_tile == 'E')
	{
		if (game->collectibles_left == 0)
		{
			update_game_state(game, move);
			free_all_and_exit(game, "You win!");
		}
		return ;
	}
	update_game_state(game, move);
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
