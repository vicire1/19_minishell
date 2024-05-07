/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:15 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/08 00:57:25 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_struct(t_data *data)
{
    t_lexer *temp;
    
    temp = data->first;
    while(temp->next)
    {
        printf("----------------------\n");
        printf("Pos : %i\n", temp->pos);
        printf("string : %s\n", temp->token_str);
        printf("token : %i\n", temp->token);
        printf("adr : %p\n", temp);
        printf("prev adr : %p\n", temp->prev);
        printf("next adr : %p\n", temp->next);
        printf("----------------------\n");
        temp = temp->next;    
    }
    printf("----------------------\n");
    printf("Pos : %i\n", temp->pos);
    printf("string : %s\n", temp->token_str);
    printf("token : %i\n", temp->token);
    printf("adr : %p\n", temp);
    printf("prev adr : %p\n", temp->prev);
    printf("next adr : %p\n", temp->next);
    printf("----------------------\n");
}

int new_node(char *str, t_token token, t_data *data)
{
    t_lexer *new;
    t_lexer *temp;
    static int i = -1;

    new = malloc(sizeof(t_lexer));
    if (!new)
        return (-1);
    new->token_str = str;
    new->token = token;
    new->pos = ++i;
    new->next = NULL;
    if (data->first == NULL)
    {
        new->prev = NULL;
        data->first = new;
        return (0);
    }
    temp = data->first;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    new->prev = temp;
    return (0);
}

int is_white_space(char c)
{
    if (c == ' ' || (c >= '\t' && c <= '\r'))
        return (1);
    return (0);
}

int tokenize(char *str, int i, t_data *data)
{
    if (str[i] == '|')
        return (new_node(ft_substr(str, i, 1), 1, data), 1);
    else if (str [i] == '<' && str[i + 1] == '<')
        return (new_node(ft_substr(str, i, 2), 5, data), 2);
    else if (str [i] == '>' && str[i + 1] == '>')
        return (new_node(ft_substr(str, i, 2), 3, data), 2);
    else if (str[i] == '<')
        return (new_node(ft_substr(str, i, 1), 4, data), 1);
    else if (str[i] == '>')
        return (new_node(ft_substr(str, i, 1), 2, data), 1);
    else
        return (0);
    
}

int save_cmds(char *str, t_data *data)
{
    int i;
    char    c;

    i = 0;
    while (str[i] && !is_white_space(str[i]) && str[i] != '>' && str[i] != '<' && str[i] != '|')
    {
        if (str[i] == 34 || str[i] == 39)
        {
            c = str[i++];
            while (str[i] && str[i] != c)
                i++;
        }
        i++;
    }
    if (i != 0 && new_node(ft_substr(str, 0, i), 0, data))
    {
        free_all(data, NULL);
        exit (1);
    }
    return (i);
}

int lexer(char *line, t_data *data)
{
    //compter nb de lexer au final

    //malloc tab de strct lexer

    //strlen token_str
    //malloc token_str
    //copier la string dans token_str
    //definir le type de token
    int i;

    i = 0;
    while (line[i])
    {
        while (is_white_space(line[i]))
            i++;
        i += tokenize(line, i, data);
        i += save_cmds(&line[i], data);
    }
    print_struct(data);
    return (0);
}
