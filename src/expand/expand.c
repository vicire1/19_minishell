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
		if (exp->token_str[j] == '$')
		{
			if (count_quotes(data, exp, j))
			{
				printf("VALID_QUOTES_FAUT REPLACE [$%c]\n", exp->token_str[j+1]);
				tempo_val = in_env(data, data->first_env, exp->token_str + j + 1);
				printf("[1] [%s]\n", tempo_val);
				name_len = size_env_doll(exp->token_str + j + 1);
				printf("[2] [%d]\n", name_len);
				val_len = 0;
				if (tempo_val)
				{
					val_len = size_env_value(tempo_val);
				printf("[3] [%d]\n", val_len);
					name_len = size_env_name(tempo_val);
				printf("[4] [%d]\n", name_len);
				}
				tempo = ft_strdup(exp->token_str);
				printf("[5] [%s]\n", tempo);
				if (!tempo)
					free_all(data, ERR_MAL, 1);
				first_part = ft_substr(tempo, 0, j, data);
				printf("[6] [%s]\n", first_part);
				sec_part = ft_substr(tempo_val, name_len, val_len, data);
				printf("[7] [%s]\n", sec_part);
				if (sec_part)
				{
					third_part = ft_substr(tempo, j + name_len, strlen(tempo), data);
					printf("[8] [%s]\n", third_part);
				}
				else
				{
					third_part = ft_substr(tempo, j + name_len + 1, strlen(tempo), data);
					printf("[8] [%s]\n", third_part);
				}
				free(exp->token_str);
				free(tempo);
				tempo = ft_strjoin(first_part, sec_part);
				printf("[9] [%s]\n", tempo);
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
//		if(check_quotes(exp) == 1)		//ici je check si il reste des quotes
//			transform_str(exp);			//ici je tej les quotes que je peu tej
		exp = exp->next;
	}
	printf("=======EXP : %s=======\n", exp->token_str);
	if(check_v_env(exp->token_str))
		env_str(data, exp);
	return (0);
}