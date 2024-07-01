#include "../../include/minishell.h"

int	in_env(t_data *data, t_env *env, char *str, t_expander *expa)
{
	int		i;
	char	*tempo;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	tempo = ft_substr(str, 0, i, data);
	if (!tempo)
	{
		free(tempo);
		return (0);
	}
	while (env)
	{
		if (env_cmp(tempo, env->name))
		{
			free(tempo);
			expa->tmp_val = ft_strjoin(env->name, env->value, data);
			if (!expa->tmp_val)
				expa->tmp_val = ft_strdup(env->name, data);
			return (1);
		}
		env = env->next;
	}
	free(tempo);
	return (0);
}

void	delete_doll(t_data *data, t_lexer *exp, int j)
{
	int		prev_len;
	int		post_len;
	char	*prev_str;
	char	*post_str;

	prev_len = j;
	post_len = ft_strlen(exp->token_str);
	prev_str = ft_substr(exp->token_str, 0, j, data);
	post_str = ft_substr_bis(exp->token_str, j + 1, post_len);
	if (!post_str)
	{
		if (prev_str)
			free(prev_str);
		free_all(data, ERR_MAL, 1);
	}
	free(exp->token_str);
	exp->token_str = ft_strjoin_bis(prev_str, post_str);
	if (prev_str)
		free(prev_str);
	if (post_str)
		free(post_str);
	if (!exp->token_str)
		free_all(data, ERR_MAL, 1);
	return ;
}

int	del_doll_quotes_verif(t_lexer *exp, char *str, int j)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			ret = check_quotes_db(exp->token_str, j, i);
			if (!ret)
				return (0);
			i = ret;
		}
		else if (str[i] == '\'')
		{
			ret = check_quotes_single(exp, j, i);
			if (!ret)
				return (0);
			i = ret;
		}
		i++;
	}
	if (j == i - 1)
		return (0);
	return (1);
}

int	valid_quotes_env(t_data *data, t_lexer *exp)
{
	int	j;
	int	len_av;
	int	len_ap;

	j = 0;
	while (exp->token_str[j])
	{
		len_av = ft_strlen(exp->token_str);
		if (exp->token_str[j] == '$' && ft_isalnum(exp->token_str[j + 1]))
		{
			if (check_quotes(exp, j, 0))
				replace_env(data, exp, j, data->expa);
		}
		else if (exp->token_str[j] == '$')
		{
			if (del_doll_quotes_verif(exp, exp->token_str, j)
				&& exp->token_str[j + 1] != '$')
				delete_doll(data, exp, j);
		}
		len_ap = ft_strlen(exp->token_str);
		if (len_av == len_ap)
			j++;
	}
	return (0);
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first_lex;
	data->expa = malloc(sizeof(t_expander));
	while (exp->next)
	{
		if (check_v_env(exp->token_str))
			valid_quotes_env(data, exp);
		delete_quotes(data, exp);
		exp = exp->next;
	}
	if (check_v_env(exp->token_str))
		valid_quotes_env(data, exp);
	delete_quotes(data, exp);
	free(data->expa);
	return (0);
}
