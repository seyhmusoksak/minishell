/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:36 by ekose             #+#    #+#             */
/*   Updated: 2024/05/11 18:34:08 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dir_check(t_state **state, char *dir)
{
	struct stat	file_info;
	t_state		*tmp;

	tmp = (*state);
	if (stat(dir, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			if (access(dir, R_OK) == 0)
			{
				if (chdir(dir) != 0)
					perror("CHDIR");
			}
			else
				ft_cd_error(dir);
		}
		else
			ft_cd_error(dir);
	}
	else
		ft_cd_error(dir);
}

static void	ft_select_dir(t_state **state, char *type)
{
	t_env	*tmp_env;
	char	*dir;

	tmp_env = (*state)->env;
	if (ft_strncmp(type, "HOME", ft_strlen(type)) == 0)
		while (tmp_env && ft_strncmp(tmp_env->key, "HOME", ft_strlen("HOME")))
			tmp_env = tmp_env->next;
	else if (ft_strncmp(type, "OLDPWD", ft_strlen(type)) == 0)
		while (tmp_env && ft_strncmp(tmp_env->key,
				"OLDPWD", ft_strlen("OLDPWD")))
			tmp_env = tmp_env->next;
	if (tmp_env == NULL)
	{
		ft_notdefine_dir(type); //notdefine fonkiyonunu geliştirilebilir
		return ;
	}
	dir = tmp_env->value;
	ft_dir_check(state, dir);
}

static void	ft_up_dir(t_state **state)
{
	char		cwd[1024];
	char		*dir;
	size_t		len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	len = ft_strlen(ft_strrchr(cwd, '/'));
	dir = ft_substr(cwd, 0, ft_strlen(cwd) - len);
	if (ft_strlen(dir) == 0)
	{
		free(dir);
		dir = ft_strdup("/");
	}
	ft_dir_check(state, dir);
	free(dir);
}

void	ft_cd(t_state **state)
{
	t_parser	*tmp;

	tmp = (*state)->parser;
	if (tmp->arg == NULL || tmp->arg[0] == NULL)
		ft_select_dir(state, "HOME");
	else if (ft_strncmp(tmp->arg[0], "~", ft_strlen(tmp->arg[0])) == 0)
		ft_select_dir(state, "HOME");
	else if (ft_strncmp(tmp->arg[0], "-", ft_strlen(tmp->arg[0])) == 0)
		ft_select_dir(state, "OLDPWD");
	else if (ft_strncmp(tmp->arg[0], ".", ft_strlen(tmp->arg[0])) == 0)
		return ;
	else if (ft_strncmp(tmp->arg[0], "..", ft_strlen(tmp->arg[0])) == 0)
		ft_up_dir(state);
	else
		ft_dir_check(state, tmp->arg[0]);

}
