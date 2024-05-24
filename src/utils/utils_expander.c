#include "../../include/minishell.h"

int	size_env_doll(char *str)
{
	int	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

int	size_env_name(char *env_line)
{
	int	i;

	i = 0;
	while(env_line[i] != '=')
		i++;
	return (i + 1);
}

int	size_env_value(char *env_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(env_line[i] && env_line[i] != '=')
		i++;
	while(env_line[i])
	{
		j++;
		i++;
	}
	return(j - 1);
}

int	env_cmp(char *str, char *str_env)
{
	int	i;
	
	i = 0;
	while (str[i] && str_env[i])
	{
		if (str[i] != str_env[i])
			return (0);
		i++;
	}
	if (str_env[i] != '=')
		return (0);
	return (1);
}

int count_l_quotes(t_data *data, t_lexer *exp, int start)
{
	while (start > 0)
	{
		if (exp->token_str[start] == '\"')
			data->expand->l_db_quotes++;
		else if (exp->token_str[start] == '\'')
			data->expand->l_s_quotes++;
		start--;
	}
	return (0);
}

int count_r_quotes(t_data *data, t_lexer *exp, int start)
{
	while (exp->token_str[start])
	{
		if (exp->token_str[start] == '\"')
			data->expand->r_db_quotes++;
		else if (exp->token_str[start] == '\'')
			data->expand->r_s_quotes++;
		start++;
	}
	return (0);
}

int count_quotes(t_data *data, t_lexer *exp, int start)
{
	data->expand->l_s_quotes = 0;
	data->expand->l_db_quotes = 0;
	data->expand->r_s_quotes = 0;
	data->expand->r_db_quotes = 0;
	count_l_quotes(data, exp, start);
	count_r_quotes(data, exp, start);
	if (data->expand->l_db_quotes == 0 && data->expand->l_s_quotes == 0 && data->expand->r_db_quotes == 0 && data->expand->r_s_quotes == 0)
		return (1);
	if ((data->expand->l_s_quotes % 2 == 0) || (data->expand->r_s_quotes % 2 == 0))
		return (1);
	return (0);
}

int	check_longuest_q(char *str, int j)
{
	int	i;
	int left;
	int	right;

	i = 0;
	left = -1;
	right = -1;
	int	len = ft_strlen(str);
	while (i != j)
	{
		if (str[i] == 39)	//single quotes ascii
		{
			left = 0;
			break;
		}
		else if (str[i] == 34) //double quotes ascii
		{
			left = 1;
			break;
		}
		i++;
	}
	while (len != j)
	{
		if (str[len] == 39)	//single quotes ascii
		{
			right = 0;
			break;
		}
		else if (str[len] == 34) //double quotes ascii
		{
			right = 1;
			break;
		}
		len--;
	}
	if (right == 1 && left == 1)
		return (1);
	return (0);
}

int	check_v_env(char *str)
{
	printf("entre check_v_env\n");
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if(str[i ]== '$')
			j++;
		i++;
	}
	return (j);
}