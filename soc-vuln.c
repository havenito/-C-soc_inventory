/*
 * soc-vuln.c — binaire VOLONTAIREMENT VULNÉRABLE (support de TP, Jour 3).
 *
 * Compilation (protections désactivées, voir Makefile) :
 *   gcc -m32 -fno-stack-protector -z execstack -no-pie -g soc-vuln.c -o soc-vuln
 *
 * La fonction acces_admin() n'est JAMAIS appelée par le flux normal :
 * l'objectif de l'étudiant est d'y détourner l'exécution via le dépassement.
 *
 * NB : gets() a été retirée de la norme C (C11) et n'existe plus dans la glibc
 * récente — on utilise donc scanf("%s", ...), tout aussi non bornée, comme
 * fonction vulnérable. Le mécanisme du dépassement est identique.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction cachée : la cible de l'exploitation. */
void acces_admin(void) {
    printf("\n[+] Acces administrateur accorde !\n");
    printf("[+] Ouverture d'un shell (environnement de TP)...\n");
    system("/bin/sh");
    exit(0);
}


/* Lecture volontairement non bornée dans un tampon de pile de taille fixe. */
void enregistrer_actif(void) {
    char hostname[64];          /* tampon cible */

    printf("Nom d'hote de l'actif a enregistrer : ");
    fflush(stdout);
    scanf("%s", hostname);      /* FAILLE : %s sans largeur = aucune limite */

    printf("Actif '%s' enregistre.\n", hostname);
}

int main(void) {
    printf("=== SOC Inventory (edition de demonstration) ===\n");
    enregistrer_actif();
    printf("Fin normale du programme.\n");
    return 0;
}
