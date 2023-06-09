/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:18:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/22 15:19:29 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redict_args_tool(int i, int j, int type, char *cmd)
{
	if (type == T_GREATGREAT || type == T_LESSLESS)
		j = i + 2;
	else
		j = i + 1;
	while (cmd[j] && (cmd[j] == ' ' || cmd[j] == '\t'))
		j++;
	return (j);
}

char	**get_redict_args(char *cmd, int i, int type)
{
	char	**args;
	int		j;

	j = 0;
	j = redict_args_tool(i, j, type, cmd);
	args = ft_calloc(sizeof(char *), redict_word_count(cmd, j));
	if (!args)
		return (malloc_fail_proc(), NULL);
	if (redict_word_count(cmd, j) == 1)
		return (args);
	args[0] = ft_calloc(sizeof(char), (count_letters(cmd, j) + 1));
	if (!args[0])
		return (free(args), malloc_fail_proc(), NULL);
	i = 0;
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\t'
		&& cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>')
	{
		if (cmd[j] == '"')
			command_double_quotes(cmd, &j, args[0], &i);
		else if (cmd[j] == '\'')
			command_simple_quotes(cmd, &j, args[0], &i);
		else
			args[0][i++] = cmd[j++];
	}
	return (args);
}

char	**cmd_args_tools(char **args, char *cmd, int *i, int j)
{
	int	k;

	args[j] = ft_calloc(sizeof(char), (count_letters(cmd, *i) + 1));
	if (!args[j])
		return (malloc_fail_proc(), NULL);
	k = 0;
	while (cmd[*i] && cmd[*i] != ' ' && cmd[*i] != '\t'
		&& cmd[*i] != '|' && cmd[*i] != '<' && cmd[*i] != '>')
	{
		if (cmd[*i] == '$' && (cmd[(*i) + 1] == '"' || cmd[(*i) + 1] == '\''))
			(*i)++;
		if (cmd[*i] && cmd[*i] == '"')
			command_double_quotes(cmd, i, args[j], &k);
		else if (cmd[*i] && cmd[*i] == '\'')
			command_simple_quotes(cmd, i, args[j], &k);
		else
			args[j][k++] = cmd[(*i)++];
	}
	return (args);
}

char	**get_cmd_args(char *cmd, int i)
{
	char	**args;
	int		word_count;
	int		j;

	word_count = count_words(cmd, i);
	args = ft_calloc(sizeof(char *), (word_count + 1));
	if (!args)
		return (malloc_fail_proc(), NULL);
	j = 0;
	while (j < word_count)
	{
		args = cmd_args_tools(args, cmd, &i, j);
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		j++;
	}
	return (args);
}
