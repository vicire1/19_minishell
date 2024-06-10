#include "../../include/minishell.h"

void	print_expand(t_data *data)
{
	t_lexer	*temp;

	temp = data->first;
	while (temp->next)
	{
		printf("----------------------\n");
		printf("***EXPANDER***\n");
		printf("Pos : %i\n", temp->pos);
		printf("string : %s\n", temp->token_str);
		printf("----------------------\n");
		temp = temp->next;
	}
	printf("----------------------\n");
	printf("***EXPANDER***\n");
	printf("Pos : %i\n", temp->pos);
	printf("string : %s\n", temp->token_str);
	printf("----------------------\n");
}

char	*in_env(t_data *data, t_env *env, char *str)
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
	while (env->next)
	{
		if (env_cmp(tempo, env->env_str))
		{
			free(tempo);
			return (env->env_str);
		}
		env = env->next;
	}
	free(tempo);
	return (NULL);
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
		free(prev_str);
		free_all(data, ERR_MAL, 1);
	}
	free(exp->token_str);
	exp->token_str = ft_strjoin_bis(prev_str, post_str);
	free(prev_str);
	free(post_str);
	if (!exp->token_str)
		free_all(data, ERR_MAL, 1);
	return ;
}

int	del_doll_quotes_verif(char *str, int j)
{
	if (j == 0 && (str[j + 1] == '\"' || str[j + 1] == '\''))
		return (1);
	if (str[j + 1] == '\'' && str[j - 1] == '\'')
		return (0);
	if (str[j + 1] == '\"' && str[j - 1] == '\"')
		return (0);
	if (str[j + 1] == '\'' || str[j + 1] == '\"')
		return (1);
	return (0);
}

int	valid_quotes_env(t_data *data, t_lexer *exp)
{
	int	j;

	j = 0;
	while (exp->token_str[j])
	{
		if (exp->token_str[j] == '$' && ft_isalnum(exp->token_str[j + 1]))
		{
			if (check_quotes(exp, j, 0))
				replace_env(data, exp, j, data->expa);
		}
		else if (exp->token_str[j] == '$' && del_doll_quotes_verif
			(exp->token_str, j))
		{
			if (check_quotes(exp, j, 0))
				delete_doll(data, exp, j);
		}
		j++;
	}
	return (0);
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first;
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
	print_expand(data);
	free(data->expa);
	return (0);
}
