/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:49:19 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/11 17:50:14 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     i;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    *go1(void *pp)
{
    char *str;
    int i = 0;
    t_p *ppp;

    ppp = (t_p *)pp;
    str = "tread 1 : coucou ca va ? \n";
    pthread_mutex_lock(&ppp->mutex); // si on enleve ici
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp;

    pp = (malloc(sizeof(t_p) * 1));
    pp = &p;
    p.i = 3;

    pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);
    sleep(1);
}
/*
int main(int argc, char** argv)
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    
    if (argc != 5 || argc != 6)
    {
        //args error
    }
    if (argc == 6)
        //handle nb time philos must eat
    return (0);
}*/