/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:09 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/22 15:33:37 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "expand.h"

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

/*
//	ce que je veux ici : 
//	je check dabord les quotes autour du $..., 
//	[si c'est bon, 
//	{	
//		[si le $....(jusqu'a != lettre) existe, 
//			je le remplace]]
//		[sinon
//			 je le mets a NULL]
//	}
//	sinon je change pas.
*/
void	env_str(t_expand *expand, int w_str)
{
	printf("entre env_str\n");

	int	j = 0;
	int i = 0;
	int nb_env = check_v_env(expand->test[w_str]);
	while (i < nb_env)
	{
		if (valid_quotes_env(expand, expand->test[w_str], i))
		{
			printf("valid quotes\n");
	//		j = realloc et replace(str, j)		//le j sera la position a partir de ou recommencer a check
			
		}
		i++;
	}

	return;
}

int		check_quotes(t_expand *expand, int w_str)
{
	printf("entre check_quotes\n");
	return (0);
}

void	transform_str(t_expand *expand, int w_str)
{
	
	printf("entre transform_str\n");
	return;
}


int	expander(t_expand *expand)
{
	/*
	t_parser exp;
	int	i;

	exp = data->first_parser;
	i = 0;
	while (exp->next)
	{
		i = 0;
		while(exp->cmd[i])				//	while(i < 2) pour les test en dessous;
		{
			if (check_v_env(exp->cmd[i]) == 1)		//ici je check si y a un ou plusieur $			ok?
				env_str(exp->cmd[i]);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
			if(check_quotes(exp->cmd[i]) == 1)		//ici je check si il reste des quotes
				transform_str(exp->cmd[i]);			//ici je tej les quotes que je peu tej
			i++;
		}
	}*/
	
	int	i;

	i = 0;
	while (i < 2)
	{
		printf("\n------\nCMD[%i] == %s\n------\n", i, expand->test[i]);
		reset_init(expand);
		if (check_v_env(expand->test[i]))		//ici je check si y a un ou plusieur $			ok?
			env_str(expand, i);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
		if(check_quotes(expand, i) == 1)		//ici je check si il reste des quotes
			transform_str(expand, i);			//ici je tej les quotes que je peu tej
			i++;
	}
	return (0);
}



/*
CHECK SI $			=======check_v_env

SI $, CHECK QUTOTES,
SI DOUBLE OU RIEN, REMPLACER PAR ENV OU RIEN SI PAS DANS ENV
SI SIMPLE, JUSTE RETIRER LES SIMPLE QUOTES

SI PAS DE $


=================================================
check_v_env				//c heck si y a un ou plusieur $
env_str					// check et remplace les $ dans la string
check_quotes			// check si il y a des quotes
transform_str			// tej les quotes que je peu tej
=================================================





??????????????????????????????????
?????? ECHO $$USER le chiffre
?????? ECHO $$$$USER le chiffre 2 fois 

*/
/*=====================================================ENV===============================================================*/
void	print_env(t_expand *data)
{
	t_env	*temp;

	temp = data->first_env;
	printf("----------------------\n");
	while (temp->next)
	{
		printf("string : %s\n", temp->env_str);
		printf("\033[1;31madr : %p | prev adr : %p | next adr : %p\n\033[0m", temp, temp->prev, temp->next);
		temp = temp->next;
	}
	printf("string : %s\n", temp->env_str);
	printf("\033[1;31madr : %p | prev adr : %p | next adr : %p\n\033[0m", temp, temp->prev, temp->next);
	printf("----------------------\n");
}

int	new_node_env(char *str, t_expand *data)
{
	t_env		*new;
	t_env		*temp;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	new->env_str = str;
	if (data->first_env == NULL)
	{
		new->prev = NULL;
		data->first_env = new;
		return (0);
	}
	temp = data->first_env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}

int	init_env(t_expand	*data, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		new_node_env(envp[i], data);
		i++;
	}
	print_env(data);
	return(0);
}
/*=====================================================ENV===============================================================*/



/*----MAIN DE TEST-----*/

int main(int ac, char **av, char **envp)
{
	
	int i = 0;
	t_expand expand;
	expand.test = malloc(sizeof(char *) * 2);
	expand.test[0] = malloc(sizeof(char) * 50);
	expand.test[1] = malloc(sizeof(char) * 50);
	
	expand.test[0] = "cmd0";
	expand.test[1] = "ou\'i\'u$USER$iSou";

	init_env(&expand, envp);
	expander(&expand);
	printf("[%s]\n", expand.test[1])
	printf("---FIN---\n");
}