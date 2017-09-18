#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>


/* But: comprendre le fonctionnement des threads.
    TP1, question 4.
    RESULTAT DU PROGRAMME : on observe que chaque printf nous affiche
                            que la variable "i" a la valeur 3.
*/


pid_t gettid(void){
  return syscall(__NR_gettid);
}

void* start_routine(void* arg){
  int x = *(int*) arg; //Ici, on récupère l'argument. Bon cette ligne la,
  // elle est un peu chaude donc je l'explique à la fin du code.
  while(1){
    printf("Numéro du thread = %d, PID = %d, TID = %d, PTHID = %lu\n", x, getpid(), gettid(), pthread_self());
    sleep(5);
  }
  return NULL;
}

int main(void){

  pthread_t th[3]; //On crée trois variables threads
  for(int i = 0; i < 3; i++){
    pthread_create(&th[i], NULL, start_routine, (void*)&i); //On caste notre variable vers un void*.
    //void* permet donc de donner l'adresse de la variable i, sans type.


    /* A chaque tour de boucle, on crée un thread auquel on associe la routine
     * "start_routine", et on passe en argument la variable i, qui vaut donc
     * 0 au premier tour, 1 au suivant, et 2 pour le dernier thread.
     */
  }
  pthread_join(th[0], NULL); /*On attend que le thread 1 soit terminé pour quitter.

  Le but est d'afficher la valeur de la variable i, et de comprendre pourquoi elle
  vaut toujours 3, donc pas besoin d'attendre que tous les threads aient terminés leur sleep(5)*/

  return EXIT_SUCCESS;
}

/*Pourquoi le i vaut toujours 3 à l'affichage?
Parce que les threads peuvent s'executer dans n'importe quel ordre.
Du coup les 3 threads sont créés, et ils ont tous un pointeur vers une variable i.
Celle ci est incrémentée à chaque tour de boucle.
Donc une fois que tous les threads sont créés, la variable i vaut 3.
Mais le fait que les threads soient créés ne veut pas dire que les threads ont terminé
d'executer leur code.
Ainsi quand la variable i arrive à 3, les threads n'ont pas encore affiché la valeur de la variable.
Ils l'affiche donc, et affichent donc tous 3.
*/




/*
Explication de la ligne 21 : int x = *(int*) arg;

Lorsque l'on passe une variable via une adresse à une fonction, on a ça :


void ma_fonction(int* var){
  printf("La valeur de ma variable est : %d\n", *var);
}


/!\ Pour accéder à la valeur de var, on met l'étoile devant. /!\
Parce qu'on pointe vers ce qu'il y a à l'adresse donnée, et ce qu'il y a à l'adresse donnée,
c'est la valeur. Ici je pointe vers l'adresse de var. Je sais que c'est un int.
Le pointeur va donc pointer vers l'adresse de var en indiquant que c'est un int,
et que la variable fera donc 4 octets.

Sauf que nous, ce qu'on veut, c'est pouvoir mettre n'importe quel type de variable.
Pour ça, on oublie le typage grâce au void*, qui pointe juste vers une adresse sans indiquer
le type de la variable vers laquelle on pointe.
Sauf qu'un void*, c'est inexploitable, parce qu'on ne sait pas combien d'octets fait
nortre variable en mémoire. Donc pour éviter les segfault, il faut indiquer un type.

Pour cela:

1) je crée une variable du type de ma variable (ici je veux passer un int, donc ça sera int)

void ma_routine(void* var){
  int x;
}

2) Je sais que ma variable est accessible grâce à la notation "*" qui permet de pointer vers
   l'adresse de ma variable. Je devrais donc y avoir accès comme ça :

void ma_routine(void* var){
 int x = *var;
}

3) Le problème, c'est qu'on a pas le droit de mettre un void* directement dans un int.
  Le programme ne sait pas quelle est la taille de notre variable void* et ne peux donc
  pas bêtement copier ce qui est contenu dans void* dans la variable x.
  Pour faire une analogie :
    X, c'est un meuble qui a 4 tiroirs vides.
    X = [ ][ ][ ][ ]
    Var, c'est un meuble dont on ne connait pas le nombre de tiroirs.
    Var = [.][.][.][.]...[.][.]

    On voit bien que si on ne connait pas le nombre de tiroirs de var,
    il nous est impossible de savoir si on pourra transferer tout le contenu
    du meuble "var" dans le meuble "x".

    Var = [.][.][.][.][.][.]...[.][.]
           |  |  |  |  |  | ... |  |
      X = [.][.][.][.] ?  ?     ?  ?

    Bon ça c'est le cas général, nous on sait qu'on veut un int, donc on sait qu'on
    veut stocker dans un meuble de 4 tiroirs.
    C'est pour ça qu'il faut indiquer au programme de prendre les 4 premiers tiroirs.
    En vrai nous, on sait que notre variable "var" ne comporte que 4 tiroirs, parce
    qu'on a passé un int en argument de la fonction ma_routine.

    On l'a juste passé en void* parce qu'on a pas le choix, mais on sait qu'elle
    fait 4 octets, que c'est un int quoi.
    Du coup, on indique au programme en lui donnant le type (int *).

    Du coup, on a :

    void ma_routine(void* var){
     int x = *(int*)var;
    }


    On retrouve l'étoile de tout à l'heure pour accéder au contenu à l'adresse de la variable,
    et on voit qu'on a transformé le void* en int*. On a "casté" en int*.

    Si on n'avait pas été dans un thread, on aurait tout simplement fait :

    void ma_fonction(int* var){
     int x = *var;
    }

    On voit bien que le void* est devenu un int*. C'est à ça que sert le : (int*)var,
    on transforme le type de la variable de (void*) en (int*).
    Puis on accède au contenu à l'adresse grâce à l'étoile habituelle :
    *var.
