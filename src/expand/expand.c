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
	int	i;
	char *tempo;

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

int	valid_quotes_env(t_data *data, t_lexer *exp)
{
	int		j;
	char	*tempo_val;
	char	*tempo;
	int		val_len;
	int		name_len;
	char	*first_part;
	char	*sec_part;
	char	*third_part;

	j = 0;
	val_len = 0;
	name_len = 0;
	while (exp->token_str[j])
	{
		if (exp->token_str[j] == '$' && ft_isalnum(exp->token_str[j + 1]))
		{
			if (check_quotes(exp, j, 0))
			{
				tempo_val = in_env(data, data->first_env, exp->token_str + j + 1);
				name_len = size_env_doll(exp->token_str + j + 1);
				val_len = 0;
				if (tempo_val)
				{
					val_len = size_env_value(tempo_val);
					name_len = size_env_name(tempo_val);
				}
				tempo = ft_strdup(exp->token_str);
				if (!tempo)
					free_all(data, ERR_MAL, 1);
				first_part = ft_substr(tempo, 0, j, data);
				sec_part = ft_substr(tempo_val, name_len, val_len, data);
				if (sec_part)
					third_part = ft_substr(tempo, j + name_len, ft_strlen(tempo), data);
				else
					third_part = ft_substr(tempo, j + name_len + 1, ft_strlen(tempo), data);
				free(exp->token_str);
				free(tempo);
				tempo = ft_strjoin(first_part, sec_part);
				if (tempo)
					exp->token_str = ft_strjoin(tempo , third_part);
				else
					exp->token_str = ft_strjoin(first_part , third_part);
				free(tempo);
			}
		}
		j++;
	}
	return (0);
}

int	delete_quotes(t_data *data, t_lexer *exp)
{
	int	i;
	char *first_part;
	char *sec_part;

	i = 0;
	while (exp->token_str[i])
	{
		if(exp->token_str[i] == '\"')
		{
			first_part = ft_strjoin(ft_substr(exp->token_str, 0, i, data), ft_substr(exp->token_str, i + 1, ft_strlen(exp->token_str), data));
			i++;
			while (exp->token_str[i] != '\"')
				i++;
			sec_part = ft_strjoin(ft_substr(first_part, 0, i - 1, data), exp->token_str + i + 1);
			free(exp->token_str);
			exp->token_str = ft_strdup(sec_part);
			free(first_part);
			free(sec_part);
			i-=2;
		}
		else if (exp->token_str[i] == '\'')
		{
			first_part = ft_strjoin(ft_substr(exp->token_str, 0, i, data), ft_substr(exp->token_str, i + 1, ft_strlen(exp->token_str), data));
			i++;
			while (exp->token_str[i] != '\'')
				i++;
			sec_part = ft_strjoin(ft_substr(first_part, 0, i - 1, data), exp->token_str + i + 1);
			free(exp->token_str);
			exp->token_str = ft_strdup(sec_part);
			free(first_part);
			free(sec_part);
			i-=2;
		}
		i++;
	}
	return (0);
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first;
	data->expand = malloc(sizeof(t_expander));
	while (exp->next)
	{
		if(check_v_env(exp->token_str))
			valid_quotes_env(data, exp);
		delete_quotes(data, exp);
		exp = exp->next;
	}
	if(check_v_env(exp->token_str))
		valid_quotes_env(data, exp);
	delete_quotes(data, exp);
	print_expand(data);
	return (0);
}