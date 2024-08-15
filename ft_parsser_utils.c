/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:25:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/12 21:58:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_command(*lst);
		last->next = new;
	}
}

t_command	*ft_last_command(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_command	*ft_new_command(int count, t_splitor **tmp_x)
{
	t_command	*new_node;
	int			i;

	i = 0;
	new_node = malloc(sizeof(t_command));
	new_node->arg = malloc(sizeof(char *) * (count + 1));
	if (((*tmp_x) != NULL && (*tmp_x)->type == '|'))
	{
		new_node->arg[i] = ft_strdup((*tmp_x)->in);
		i++;
		new_node->arg[i] = NULL;
		new_node->next = NULL;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->type != '|')
		ft_not_pipe(&new_node, &i, tmp_x);
	new_node->content = new_node->arg[0];
	new_node->doc = NULL;
	ft_check_doc(&new_node);
	return (new_node);
}