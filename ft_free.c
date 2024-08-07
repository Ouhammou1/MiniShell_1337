/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:05:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/07 07:21:47 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_splitor *x)
{
	t_splitor	*tmp;

	while (x != NULL)
	{
		tmp = x;
		x = x->next;
		free(tmp->in);
		free(tmp);
	}
}

void	ft_free_command(t_command *lst)
{
	t_command	*tmp;
	int			i;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		i = 0;
		while (tmp->arg[i] != NULL)
		{
			free(tmp->arg[i]);
			i++;
		}
		free(tmp->arg);
		if (tmp->doc != NULL)
		{
			free(tmp->doc->dir_in);
			free(tmp->doc->dir_out);
			free(tmp->doc->doc_here);
			free(tmp->doc->rdir);
			free(tmp->doc);
		}
		free(tmp);
	}
}