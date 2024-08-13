#include "../INCLUDES/minishell.h"

static char	*ft_tilde_handler(char *tmp, char *tmp2, t_parser *parser, t_env *env)
{
    char    *dest;
    char    *home;
    char    *tmp3;

    if (parser->check_tilde == 2)
        dest = ft_strjoin(tmp, tmp2);
    else
    {
        home = ft_env_finder("HOME", env);
        tmp3 = ft_strjoin(tmp, home);
        dest = ft_strjoin(tmp3, tmp2);
        free (tmp3);
        //free(home); burda leak olabilir freeleyince seg yiyorum 
        //freelemek de gerekiyor diye duşunuyorum baksana yegenim
    }
    free(tmp);
    free(tmp2);
    parser->check_tilde = -1;
    return (dest);
}

static char	*ft_check_tilde(char *str, t_parser *prs, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	prs->check_tilde = 1;
	tmp = ft_substr(str, 0, prs->r);
	if (str[prs->r +1] && (str[prs->r +1] == '/' || str[prs->r +1] == ' '))
    	tmp2 = ft_strdup(str + prs->r +1);
	else if (str[prs->r +1] == '\0')
		tmp2 = ft_strdup("");
    else
    {
        tmp2 = ft_strdup(str + prs->r);
        prs->check_tilde = 2; 
    }
    return (ft_tilde_handler(tmp, tmp2, prs, env));
}

char	**ft_put_tilde(char **str, t_state *state, t_parser *parser)
{
	int		i;
	t_node	*new_node;
	t_node	*tilde;
	t_env	*env;

	tilde = NULL;
	i = -1;
	env = state->env;
	while (str[++i])
	{
		parser->check_tilde = 0;
		if (ft_count_real_char(str[i], '~', parser))
		{
			parser->r = -1;
			while (str[i][++parser->r] && parser->check_tilde != -1)
				if (str[i][parser->r] == '~' && !ft_quote_check(str[i], parser->r, parser))
					new_node = ft_new_node(ft_check_tilde(str[i], parser, env));
			if (parser->check_tilde == 0)
				new_node = ft_new_node(ft_strdup(str[i]));
		}
		else
			new_node = ft_new_node(ft_strdup(str[i]));
		ft_node_add_back(&tilde, new_node);
	}
    return (ft_node_to_double(&tilde, 0, 0));
}
