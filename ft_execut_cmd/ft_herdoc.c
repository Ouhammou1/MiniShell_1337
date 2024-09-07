/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/07 15:18:46 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc_exist(t_command *list)
{
	t_command	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp && tmp->her)
	{
		if (tmp->her->store != NULL)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_expand_in_her(char *line, t_envarment *my_env)
{
	int i = 0;
	int len = 0;
	int j = 0;
	char *s;
	char *final;

	while (line[i])
	{
		len = 0;
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[i] && ft_isalnum(line[i]))
			{
				i++;
				len++;
			}
			j--;
			len++;
			s = ft_expand(ft_substr(line, j, len), my_env);
			final = ft_strjoin(final, s);
			if(line[i] != '\0')
				final = ft_strjoin(final , " ");
			free(s);
		}
		else
		{
			j = i;
			while (line[i] && line[i] != '$')
			{
				i++;
				len++;
			}
			final = ft_strjoin(final, ft_substr(line, j, len));
			i--;
		}
			i++;
	}
	return (final);
}




void	write_in_file(t_here_doc *tmp, char *line, char **env)
{
	char		*tmp_line;
	char		*path_file;
	t_envarment	*my_env;

	my_env = ft_stock_envarment(env);
	tmp_line = ft_strjoin_1(tmp->store, ft_itoa(tmp->idx));
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	tmp->fd = open(tmp->heredoc_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		perror("open");
		return ;
	}
	if (tmp->expad == 1)
	{
		ft_putstr_fd(ft_expand_in_her(line, my_env), tmp->fd);
	}
	else
		ft_putstr_fd(line, tmp->fd);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
}

int	count_herdoc(t_command *tmp)
{
	int			count;
	t_command	*cmd;
	t_here_doc	*her;

	if (tmp == NULL || tmp->her == NULL)
		return (0);
	count = 0;
	cmd = tmp;
	while (cmd != NULL)
	{
		her = cmd->her;
		while (her != NULL)
		{
			if (her->store != NULL)
				count++;
			her = her->next;
		}
		cmd = cmd->next;
	}
	return (count);
}

void	ft_cmp_delimeter(t_command *tmp_cmd, int *i, char **env)
{
	t_here_doc	*tmp_her;
	char		*line;

	line = NULL;
	tmp_her = tmp_cmd->her;
	while (tmp_cmd != NULL && tmp_her != NULL)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, tmp_her->store) == 0)
		{
			(*i)++;
			tmp_her = tmp_her->next;
		}
		else
			write_in_file(tmp_her, line, env);
	}
}
void	handle_here_doc(t_command *cmd, char **env)
{
	t_command	*tmp_cmd;
	int			count;
	int			i;

	(void)env;
	tmp_cmd = cmd;
	if (cmd == NULL || tmp_cmd == NULL)
		return ;
	count = count_herdoc(tmp_cmd);
	// printf("list->her->store   == %s \n", cmd->her->store);
	// printf("list->her->store   == %s \n", tmp_cmd->her->store);
	i = 0;
	while (1)
	{
		while (tmp_cmd != NULL)
		{
			ft_cmp_delimeter(tmp_cmd, &i, env);
			tmp_cmd = tmp_cmd->next;
		}
		if (i == count)
			break ;
	}
	// printf("___%p\n", cmd->her);
}
