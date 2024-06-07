#include "../../include/minishell.h"

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
			i += ret;
		}
		i++;
	}
	return (1);
}
