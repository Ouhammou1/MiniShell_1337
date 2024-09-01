/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:05:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/30 08:15:54 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lexer(t_splitor **x)
{
	t_splitor	*tmp;

	while (*x != NULL)
	{
		tmp = *x;
		*x = (*x)->next;
		free(tmp->in);
		free(tmp);
	}
}

void	ft_free_split(char **list)
{
	int	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list[j] != NULL)
	{
		free(list[j]);
		j++;
	}
	free(list);
}

void	ft_free_doc(t_redirect **doc)
{
	t_redirect	*tmp;

	while (*doc != NULL)
	{
		tmp = *doc;
		*doc = (*doc)->next;
		free(tmp->store);
		free(tmp);
	}
}

void	ft_free_env(t_envarment **my_env)
{
	t_envarment	*tmp;

	while (*my_env != NULL)
	{
		tmp = *my_env;
		*my_env = (*my_env)->next;
		free(tmp);
	}
}
void	free_command(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->arg)
		{
			for (int i = 0; cmd->arg[i]; i++)
				free(cmd->arg[i]);
			free(cmd->arg);
		}
		if (cmd->store_her)
		{
			for (int i = 0; cmd->store_her[i]; i++)
				free(cmd->store_her[i]);
			free(cmd->store_her);
		}
		if (cmd->doc)
			ft_free_doc(&cmd->doc);
		free(cmd);
	}
}

void	ft_free_command(t_command *lst)
{
	t_command	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free_command(tmp);
	}
}
