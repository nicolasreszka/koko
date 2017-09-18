#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>

/* TP1 Question 7
  But : comprendre comment gérer les "zombis"
  Zombis : programme mort dont le père n'a pas été mit au courrant de son décès.
*/

void handler(int signal){
  while(waitpid(-1, NULL, WNOHANG) > 0);
  /* -1 signifie n'importe quel fils,
  NULL osef
  WHNOHANG permet à la fonction de ne pas être bloquante
  waitpid renvoie un entier > 0 si on a bien tué le fils
  */
}

int get_one_letter(void){
  int c, first;
  first = c = getchar();
  while(c != '\n' && c != EOF){
    c = getchar();
  }
  return(first);
}

int main(void){

  int x;
  char c;
  struct sigaction sa; // On crée une variable qui va nous permettre de traiter les signaux.
  sa.sa_handler = handler; // On définit la fonction à appeler en cas de signal reçu.
  sigemptyset(&sa.sa_mask); // On ajoute notre masque au masque déjà existant.
  sa.sa_flags = SA_RESTART; // On réactive certaines fonctions de lecture/écritures qui sont habituellement désactivées lorsqu'un signal est traité.
  //Faut toujours mettre ça.
  sigaction(17, &sa, NULL); //On ajoute une réaction au signal numéro 17 (qui correspond au signal SIGCHLD, soit la mort d'un fils).
  //On a accès aux numéros des signaux via la commande "kill -l" dans le bash.
  //C'est un serveur, le processus de base doit toujours être actif.
  //Lorsqu'un utilisateur envoie une demande, elle est traitée dans un fils qui mourra lorsque la demande sera traitée.
  while(1){
    printf("Rentrez un char\n");
    c = get_one_letter(); //Bloquant jusqu'à ce qu'un utilisateur rentre un char
    x = fork(); //L'utilisateur a envoyé une requete en rentrant un char, il faut la traiter.
    // Du coup on fork pour créer un fils.
    if(x == -1){
      perror("Erreur\n");
      exit(1);
    }
    if(x == 0){ //fils
      printf("Demande traitée : Char = %d\n", c); //Le fils traite la demande, et meurt.
      exit(1);
    }
    if(x > 0){ //père
      //Le père boucle simplement et attend la prochaien requete de l'utilisateur (ici, le prochain char).
    }
  }

  return EXIT_SUCCESS;
}

/*Le fils, en mourrant, envoie un signal SIGCHLD au père. Ce signal n'est pas traité par défaut.
Il faut donc le traiter soit même. On a définit à la ligne 36 que lorsque l'on recevait le signal numéro 17
(SIGCHLD donc), le programme devait executer instantanément la fonction handler.
La fonction handler gère le problème du fils en le tuant vraiment grâce à la fonction waitpid.*/
