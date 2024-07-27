/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:11:58 by ekose             #+#    #+#             */
/*   Updated: 2024/07/26 17:06:21 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}





int	ft_open_input(t_state *state, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (ft_file_open_error(state, file));
	close(fd);
	return (0);
}

int	ft_open_output(t_state *state, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (ft_file_open_error(state, file));
	close(fd);
	return (0);
}
int	ft_args_add(t_state *state, char **cluster, t_cluster *structt)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	structt->files = (t_files *) malloc(sizeof(t_files));
	while (cluster[i])
	{
		if (i == 1)
		{
			structt->files->output = ft_strdup("");
			structt->files->input = ft_strdup("");
		}
		if (ft_strncmp(cluster[i], ">", 1) == 0)
		{
			free(structt->files->output);
			structt->files->output = ft_strdup(cluster[i + 1]);
			if (ft_open_output(state, structt->files->output) == -1)
				return (-1);
			i++;
		}
		else if (ft_strncmp(cluster[i], "<", 1) == 0)
		{
			free(structt->files->input);
			structt->files->input = ft_strdup(cluster[i + 1]);
			if (ft_open_input(state, structt->files->input) == -1)
				return (-1);
			i++;
		}
		else
			structt->arg[j++] = cluster[i];
		i++;
	}
	return (0);
}

void	 ft_cluster_creat(t_state *state)
{
	t_cluster	*head;
	t_cluster	*node;
	int			i;

	i = 0;
	if (state->clean_thrd_argv == NULL)
		return ;
	while (state->clean_thrd_argv[i])
		i++;
	head = (t_cluster *)malloc(sizeof(t_cluster));
	node = head;
	i--;
	while (i)
	{
		node->next = (t_cluster *)malloc(sizeof(t_cluster));
		node = node->next;
		i--;
	}
	node->next = NULL;
	state->cluster = head;
}

void	ft_lenght(t_cluster *structt, char **cluster)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	while (cluster[i])
	{
		if ((ft_strcmp(cluster[i], ">") != 0 && ft_strcmp(cluster[i], "<") != 0)
			&& (ft_strcmp(cluster[i - 1], ">") != 0
				&& ft_strcmp(cluster[i - 1], "<") != 0))
			len++;
		i++;
	}
	structt->arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (structt->arg == NULL)
		perror("arg");
	i = 0;
	while (i < len)
	{
		structt->arg[i] =NULL;
		i++;
	}
	structt->arg[i] = NULL;
}

void	ft_add_cluster(t_state *state)
{
	///ft_cluster_creat yeniden yazılacak
	t_cluster	*tmp;
	int			i;

	i = 0;
	ft_cluster_creat(state);
	tmp = state->cluster;
	while (state->clean_thrd_argv[i])
	{
		tmp->cmd = state->clean_thrd_argv[i][0];
		ft_lenght(tmp, state->clean_thrd_argv[i]);
		if (ft_args_add(state, state->clean_thrd_argv[i], tmp) == -1)
			return ;
		tmp = tmp->next;
		i++;
	}
	//ft_free_thrd_str(state->clean_thrd_argv); leak yiyor
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
int	ft_open_output(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}
int	ft_open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

static t_files *ft_new_files_node(char **arg)
{
	t_files	*node;
	int		i;

	node =(t_files *) malloc(sizeof(t_files));
	i = 0;
	while (arg[i])
	{
		if (i == 1)
		{
			node->output = ft_strdup("");
			node->input = ft_strdup("");
		}
		if(ft_strcmp(arg[i],"<") == 0)
		{
			free(node->input);
			node->input = ft_strdup(arg[i + 1]);
			if (ft_open_input(node->input))
				return (0);
			i++;
		}
		else if(ft_strcmp(arg[i],">") == 0)
		{
			free(node->output);
			node->output = ft_strdup(arg[i + 1]);
			if(ft_open_output(node->output) == -1)
				return (0);
			i++;
		}
		i++;
	}
	return (node);
}
static int ft_len_arg(char **arg)
{
	int	i;
	int	len;

	len = 0;
	if(ft_strcmp(arg[0],"<") == 0 || ft_strcmp(arg[0], ">") == 0)
	{
		i = 3;
		while(arg[i])
		{
			if ((ft_strcmp(arg[i],">") != 0 && ft_strcmp(arg[i],"<") != 0)
				&& ft_strncmp("-",arg[i],1) != 0)
					len++;
			i++;
		}
	}
	i = 1;
	while (arg[i])
	{
		if(ft_strcmp(arg[i],">") == 0 || ft_strcmp(arg[i],"<") == 0)
			i += 2;
		else if(ft_strncmp("-",arg[i],1) != 0)
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static	char	**ft_find_arg(char **arg)
{
	int		i;
	char	**argumans;
	int		j;

	i = 1;
	j = 0;
	argumans = malloc(sizeof(char *) * (ft_len_arg(arg) + 1));
	if(ft_strcmp(arg[0],"<") == 0 || ft_strcmp(arg[0], ">") == 0)
		i += 2;
	while (arg[i])
	{
		if(ft_strcmp(arg[i],">") == 0 || ft_strcmp(arg[i],"<") == 0)
			i += 2;
		else if(ft_strncmp("-",arg[i],1) != 0)
			i++;
		else
			argumans[j++] = arg[i++];
	}
	argumans[j] = NULL;
	return (argumans);
}

static char	**ft_find_flag(char	**arg)
{
	int	i;
	int	j;
	int	len;
	char	**flag;

	i = 0;
	len = 0;
	j = 0;
	while(arg[i])
	{
		if (ft_strncmp("-",arg[i],1) == 0)
			len++;
		i++;
	}
	flag = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while(arg[i])
	{
		if (ft_strncmp("-",arg[i],1) == 0)
		{
			flag[j] = ft_strdup(arg[i]);
			j++;
		}
		i++;
	}
	flag[j] = NULL;
	return (flag);
}

static char	*ft_find_cmd(char	**arg)
{
	if(ft_strcmp(arg[0], ">") == 0 || ft_strcmp(arg[0], "<") == 0)
	{
		return (arg[2]);
	}
	else
		return (arg[0]);
}
static void	ft_cluster_addback(t_cluster **cluster_node, t_cluster *new)
{
	t_cluster	*tmp;

	if (!cluster_node || !new)
		return ;
	if (!*cluster_node)
	{
		*cluster_node = new;
		return ;
	}
	tmp = *cluster_node;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp ->next = new;
}
static t_cluster	*ft_new_cluster_node(char	**arg)
{
	t_cluster	*new;

	new = (t_cluster *)malloc(sizeof(t_cluster));
	new->cmd = ft_find_cmd(arg);
	new->flag = ft_find_flag(arg);
	new->arg = ft_find_arg(arg);
	new->files = ft_new_files_node(arg);
	new->next = NULL;
	return (new);
}


void	ft_cluster(t_state *state)
{
	char	***thrd_arg;
	t_cluster	*tmp_node;
	int		i;

	i = 0;
	tmp_node = NULL;
	thrd_arg = state->clean_thrd_argv;
	while(thrd_arg[i])
	{
		ft_cluster_addback(&tmp_node, ft_new_cluster_node(thrd_arg[i]));
		i++;
	}
	state->cluster = tmp_node;
}


