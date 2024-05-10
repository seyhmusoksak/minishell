/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekose <ekose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:36 by ekose             #+#    #+#             */
/*   Updated: 2024/05/10 19:14:43 by ekose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_notdefine_dir(char *s)
{
	// GELIŞTIRILEBİLİR bunun yerine yeni bir error fonkiyonu
	//standart çıktı fd ile dğiştirilecek

	write(1, "cd: ", 4);
	write(1, s, ft_strlen(s));
	write(1, " ", 1);
	write(1, "not set\n", ft_strlen("not set\n"));
}

static void	ft_cd_error(char *dir)
{
	//standart çıktı fd ile dğiştirilecek

	write(1, "cd: ", 4);
	perror(dir);
}

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
		ft_notdefine_dir(type);
		return ;
	}
	dir = tmp_env->value;
	ft_dir_check(state, dir);
}


void	ft_cd(t_state **state)
{
	// " ~ " için sonra bakılacak
	t_parser	*tmp;

	tmp = (*state)->parser;
	if (tmp->arg == NULL)
		ft_select_dir(state, "HOME");
	else if (ft_strncmp(tmp->arg[0], "-", ft_strlen(tmp->arg[0])) == 0)
		ft_select_dir(state, "OLDPWD");


}
