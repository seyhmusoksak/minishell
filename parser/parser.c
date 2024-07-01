/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmyilm <mehmyilm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:01 by mehmyilm          #+#    #+#             */
/*   Updated: 2024/07/01 15:38:43 by mehmyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_state *state)
{
	char	*line;

	line = ft_strtrim(state->line, " ");
	free(state->line);
	if (ft_quote_len_check(line, (int) ft_strlen(line)) > 0)
	{
		free(line);
		ft_error_mesage("Error: open quotation mark");
		return (1);
	}
	state->clean_argv = ft_clean_quatition(ft_pipe_split(line));
	//	bu kısımda ilk tırnak temizliğini gormek için
	int i = -1;
	printf("-------cleaned_argv---------\n");
	while (state->clean_argv[++i])
		printf("i(%d): %s\n",i,state->clean_argv[i]);
	state->clean_thrd_argv = ft_parser_to_lexer(state->clean_argv);
	// bu kısım 3d diziye attığım ve tenizlenen değerleri yazdırmak için
	printf("-------cleaned_thrd_argv---------\n");
	int	j;
	i  = -1;
	while (state->clean_thrd_argv[++i])
	{
		j = -1;
		while (state->clean_thrd_argv[i][++j])
				printf("i(%d) j(%d): %s\n",i,j,state->clean_thrd_argv[i][j]);
	}
	free(line);
	return (0);
}

char	**ft_clean_quatition(char **str)
{
	int		i;
	int		len;
	char	**trim_str;
	char	**clean_str;

	i = -1;
	len = ft_double_str_len(str);
	trim_str = malloc(sizeof(char *) * (len + 1));
	clean_str = malloc(sizeof(char *) * (len + 1));
	if (!trim_str || !clean_str)
		return (NULL);
	while (str[++i])
	{
		trim_str[i] = ft_strtrim(str[i], " ");
		clean_str[i] = malloc(sizeof(char) * (ft_strlen(trim_str[i])  + 1));
	}
	trim_str[i] = NULL;
	clean_str[i] = NULL;
	i = -1;
	while (trim_str[++i])
		ft_clean_str(trim_str[i], clean_str[i], 0, -1, 0);
	ft_free_double_str(str);
	ft_free_double_str(trim_str);
	return (clean_str);
}

char	***ft_parser_to_lexer(char **str)
{
	int		i;
	int		j;
	char	***dest;

	i = -1;
	dest = malloc(sizeof(char **) * (ft_double_str_len(str) + 1));
	if (!dest)
		return (NULL);
	while (str[++i])
		dest[i] = ft_split(str[i], ' '); // bu split yerine mustafanın yazzdığı split gelecek. tırnak içindeki boşlukarı bolmemesi lazım
	dest[i] = NULL;
	i = -1;
	while (dest[++i])
	{
		j = -1;
		while (dest[i][++j])
			dest[i][j] = ft_clean_first_last_quote(dest[i][j]);
	}
	return (dest);
}

char	*ft_clean_first_last_quote(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = -1;
	if ((str[0] == '"' && str[ft_strlen(str) -1] == '"')
		|| (str[0] == '\'' && str[ft_strlen(str) -1] == '\''))
	{
		dest = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!dest)
			return (NULL);
		while (str[++i] && (i < ((int )ft_strlen(str))))
			dest[++j] = str[i];
		dest[j] = '\0';
		return (dest);
	}
	return (str);
}

