/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/06 18:33:45 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_count_commands(char *command)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] == '|')
		i++;
	}
}

void	ft_free_command(char *command)
{
	return ;
}

t_token	*ft_parsing(char *command)
{
	int nb;


	// nb = ft_count_commands(command); /* count how many commands  */
	// while (nb)
	// {

	// 	ft_get_type()
	// 	ft_get_args()
	// 	nb--;
	// }
	return (NULL);
}
