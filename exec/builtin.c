/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:54:03 by amejia            #+#    #+#             */
/*   Updated: 2023/04/25 16:40:51 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtinexec(t_token *token)
{
	if (ft_strncmp(token->args[0], "cd", -1) == 0)
		builtin_cd(token);
	if (ft_strncmp(token->args[0], "export", -1) == 0)
		builtin_export(token);
	if (ft_strncmp(token->args[0], "unset", -1) == 0)
		builtin_unset(token);
	if (ft_strncmp(token->args[0], "env", -1) == 0)
		ft_envprint();
	if (ft_strncmp(token->args[0], "pwd", -1) == 0)
		builtin_pwd();
	if (ft_strncmp(token->args[0], "exit", -1) == 0)
		builtin_exit(token);
}

int	builtin_error(void)
{
	perror("Minishell");
	g_state.last_return = 1;
	return (1);
}

int	builtin_cd(t_token *token)
{
	int		error;
	t_env	*direnv;

	if (token->args[1] == NULL)
	{
		direnv = ft_envfind("HOME");
		if (direnv == NULL)
			error = -1;
		else
			error = chdir(direnv->args);
	}
	else
		error = chdir(token->args[1]);
	if (error == -1)
		return (builtin_error());
	direnv = ft_envnew("PWD", token->args[0]);
	if (direnv == NULL)
		return (builtin_error());
	ft_envset(direnv);
	return (0);
}

int	builtin_export(t_token *token)
{
	int		error;
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], '=');
		env = ft_envnew(localsplit[0], localsplit[1]);
		if (env == NULL)
			return (builtin_error());
		ft_envset(env);
		ft_free_split(localsplit);
		ct++;
	}
	return (0);
}