#include "../../include/minishell.h"

int	delete_quotes_single_db(t_data *data, t_lexer *exp, int i, int quote)
{
	char	*first_part;
	char	*sec_part;
	char	*s1;
	char	*s2;

	s1 = ft_substr(exp->token_str, 0, i, data);
	s2 = ft_substr(exp->token_str, i + 1, ft_strlen(exp->token_str), data);
	first_part = ft_strjoin(s1, s2, data);
	free(s1);
	free(s2);
	i++;
	while (exp->token_str[i] != quote)
		i++;
	s1 = ft_substr(first_part, 0, i - 1, data);
	sec_part = ft_strjoin(s1, exp->token_str + i + 1, data);
	free(s1);
	free(exp->token_str);
	exp->token_str = ft_strdup(sec_part, data);
	free(first_part);
	free(sec_part);
	i -= 2;
	return (i);
}

int	delete_quotes(t_data *data, t_lexer *exp)
{
	int	i;
	int	ret;

	i = 0;
	while (exp->token_str[i])
	{
		if (exp->token_str[i] == '\"')
		{
			ret = delete_quotes_single_db(data, exp, i, '\"');
			i = ret;
		}
		else if (exp->token_str[i] == '\'')
		{
			ret = delete_quotes_single_db(data, exp, i, '\'');
			i = ret;
		}
		i++;
	}
	return (0);
}

int	check_quotes_db(char *str, int j, int i)
{
	i++;
	if (j == i)
		return (0);
	while (str[i] != '\'')
	{
		i++;
		if (j == i)
			return (0);
	}
	return (i);
}

int	check_quotes_single(t_lexer *exp, int j, int i)
{
	i++;
	if (j == i)
		return (0);
	while (exp->token_str[i] != '\'')
	{
		i++;
		if (j == i)
			return (0);
	}
	return (i);
}

int	check_quotes(t_lexer *exp, int j, int i)
{
	int	ret;

	while (exp->token_str[i])
	{
		if (exp->token_str[i] == '\"')
		{
			i++;
			while (exp->token_str[i] != '\"')
			{
				if (i == j)
					return (1);
				i++;
			}
		}
		else if (exp->token_str[i] == '\'')
		{
			ret = check_quotes_single(exp, j, i);
			if (!ret)
				return (0);
			i = ret;
		}
		i++;
	}
	return (1);
}
