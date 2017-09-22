#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>

/* Ce programme permet de comprendre comment gérer les "zombies"
 * Zombie = programme mort dont le père n'a pas été mis au courant de son décès.
*/

void handler(int signal){
	/* La  fonction  waitpid(pid_t pid, int *status, int options)  
	 * suspend  l'exécution  du  processus courant  jusqu'à  ce  
	 * que  le processus fils correspondant au pid se termine, 
	 * ou jusqu'à ce qu'un signal à intercepter  arrive.
	 *
	 * Arguments :
	 *	pid : le pid du fils, ici -1 signifie n'importe quel fils
	 *	status : sert à stocker les infos sur la terminaison du fils, ici NULL on s'en fout
	 *	options : WHNOHANG permet à la fonction de ne pas être bloquante
	 *
	 * Return :	
	 * 	waitpid renvoie un entier > 0 si on a bien tué le fils
	*/
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

int get_one_letter(void){
	int c, first;
	first = c = getchar();
	while(c != '\n' && c != EOF){
		c = getchar();
	}
	return(first);
}

int main(){
	int x;
	char c;

	/* On crée une variable qui va nous permettre de traiter les signaux */
	struct sigaction sa; 

	/* On définit la fonction à appeler en cas de signal reçu */
	sa.sa_handler = handler; 

	/* On ajoute notre masque au masque déjà existant. */
	sigemptyset(&sa.sa_mask); 

	/* On réactive certaines fonctions de lecture/écritures qui sont 
	* habituellement désactivées lorsqu'un signal est traité. 
	*/
	sa.sa_flags = SA_RESTART; 

	/* On ajoute une réaction au signal numéro 17 (qui correspond au signal SIGCHLD, soit la mort d'un fils).
	 * On a accès aux numéros des signaux via la commande "kill -l" dans le bash.
	*/
	sigaction(17, &sa, NULL);
 
 	/* C'est un serveur, le processus de base doit toujours être actif.
	 * Lorsqu'un utilisateur envoie une demande, elle est traitée dans 
	 * un fils qui mourra lorsque la demande sera traitée.
	*/
	while(1) {
		printf("Rentrez un char :\n");

		/* Bloquant jusqu'à ce qu'un utilisateur rentre un char */
		c = get_one_letter(); 

		/* L'utilisateur a envoyé une requete en rentrant un char, 
		 * il faut la traiter, du coup on fork pour créer un fils.
		*/
		x = fork(); 
		
		/* Erreur */
		if(x == -1){
			perror("Erreur\n");
			exit(1);
		}
		
		/* Fils */
		if(x == 0){ 
			/* Le fils traite la demande, et meurt. */
			printf("Demande traitée : Char = %d\n", c); 
			exit(1);
		}
		
		/* Père */
		if(x > 0){ 
		  /* Le père boucle simplement et attend la prochaine requete 
		   * de l'utilisateur (ici, le prochain char).
		  */
		}
	}

	return EXIT_SUCCESS;
}

/* Le fils, en mourrant, envoie un signal SIGCHLD au père. 
 * Ce signal n'est pas traité par défaut, il faut donc le traiter soit même. 
 * On a définit à la ligne 36 que lorsque l'on recevait le signal numéro 17 (soit SIGCHLD)
 * le programme doit executer instantanément la fonction handler().
 * La fonction handler gère le problème du fils en le tuant vraiment grâce à la fonction waitpid().
*/