/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/27 21:31:45 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  	 ft_pwd(t_command *list)
{

	char *path ;
	if(ft_strcmp(list->content, "oi") == 0)
	{
			
	}
	path = getcwd(NULL, 0);
	if(path == NULL)
		return ;
		
	printf("%s\n", path);	

}
