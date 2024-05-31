#include "../../include/minishell.h"

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

int	count_quotes_v2(t_data *data, t_lexer *exp, int j)
{
	int	i;

	i = 0;
	(void)data;
	printf("check[%c]%d\n", exp->token_str[j], j);
	while (exp->token_str[i])
	{
		if(exp->token_str[i] == '\"')
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
			i++;
			if (j == i)
				return (0);
			while (exp->token_str[i] != '\'')
			{
				i++;
				if (j == i)
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	valid_quotes_env(t_data *data, t_lexer *exp, int i)
{
	int	j;
	// int	tempo_j = 0;
	char *tempo_val;
	char *tempo;
	int	val_len;
	int	name_len;
	char *first_part;
	char *sec_part;
	char *third_part;
(void)i;
	j = 0;
	val_len = 0;
	name_len = 0;
	while (exp->token_str[j])
	{
		if (exp->token_str[j] == '$' && ft_isalnum(exp->token_str[j + 1]))
		{
			if (count_quotes_v2(data, exp, j))
			{
				printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
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
	printf("STRING FINALE |%s|\n", exp->token_str);
	return (0);
}


void	env_str(t_data *data, t_lexer	*exp)
{
	printf("entre env_str\n");

	int	j = 0;
	int i = 0;
	// int nb_env = check_v_env(exp->token_str);
	// while (i < nb_env)
	// {
		j = valid_quotes_env(data, exp, i);
		
		// if (j == 1)
		// 	printf("cas db quotes\n");
		// else if (j == 2)
		// 	printf("cas singles quotes\n");
		// i++;
	// }
	return;
}

int	delete_quotes(t_data *data, t_lexer *exp)
{
	int	i;
	char *first_part;
	char *sec_part;

	i = 0;
	// printf("ENTRE DELETE QUOTES\n");
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
		}
		else if (exp->token_str[i] == '\'')
		{
			first_part = ft_strjoin(ft_substr(exp->token_str, 0, i, data), ft_substr(exp->token_str, i + 1, ft_strlen(exp->token_str), data));
			// printf("ENTRE SINGLE QUOTES => [%c%c]\n", exp->token_str[i], exp->token_str[i + 1]);
			i++;
			while (exp->token_str[i] != '\'')
				i++;
			// printf("SORT SINGLE QUOTES => [%c%c]\n", exp->token_str[i-1], exp->token_str[i]);
			sec_part = ft_strjoin(ft_substr(first_part, 0, i - 1, data), exp->token_str + i + 1);
			free(exp->token_str);
			exp->token_str = ft_strdup(sec_part);
			free(first_part);
			free(sec_part);
		}
		i++;
	}
	printf("FINAL STRING = [%s]\n", exp->token_str);
	return (0);
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first;
	data->expand = malloc(sizeof(t_expander));
	while (exp->next)
	{
		printf("=======EXP : %s=======\n", exp->token_str);
		if(check_v_env(exp->token_str))
			env_str(data, exp);
		// printf("VIENT\n");
		delete_quotes(data, exp);

//		if(check_quotes(exp) == 1)		//ici je check si il reste des quotes
//			transform_str(exp);			//ici je tej les quotes que je peu tej
		exp = exp->next;
	}
	printf("=======EXP : %s=======\n", exp->token_str);
	if(check_v_env(exp->token_str))
		env_str(data, exp);
	delete_quotes(data, exp);
	return (0);
}