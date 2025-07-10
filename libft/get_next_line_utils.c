/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:48:13 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 11:34:10 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_help_strjoin(char *joinedstr, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		joinedstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joinedstr[i++] = s2[j++];
	joinedstr[i] = '\0';
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*joinedstr;

	if (!s1)
	{
		s1 = (char *) malloc (1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	joinedstr = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinedstr)
	{
		free(s1);
		return (NULL);
	}
	ft_help_strjoin(joinedstr, s1, s2);
	free(s1);
	return (joinedstr);
}
