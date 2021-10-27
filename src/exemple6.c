#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t evt;
//déclaration du sémaphore représentant
void *tache1(void *arg)
{
    int i = 0;
    while (i < 10)
    {
        printf("La tache %s s'execute\n", (char *)arg);
        //suite du code
        sem_post(&evt);
        //la tâche 1 émet l'événement à la fin de son

        i++;
    }
}
void *tache2(void *arg)
{
    int i = 0;
    while (i < 10)
    {
        sem_wait(&evt);
        //la tâche 2 est bloquée en attente de l'émission de
        printf("La tache %s s'execute enfin\n", (char *)arg);
        //suite du code
        i++;
    }
}
int main()
{
    pthread_t th1, th2;
    sem_init(&evt, 0, 0);
    // le sémaphore est local au processus issu de
    // la fonction main() et a un compteur initialisé a 0
    pthread_create(&th1, NULL, tache1, "1");
    pthread_create(&th2, NULL, tache2, "2");
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}