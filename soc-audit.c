/*
 * soc-audit.c — Inventaire d'actifs SOC (version à AUDITER — TP Jour 3, Étape 3a).
 *
 * Ce programme compile et fonctionne, mais il a été écrit « vite fait ». Votre
 * mission : repérer les failles mémoire, expliquer leur mécanisme, et proposer un
 * correctif pour chacune (livrable AUDIT.md).
 *
 * Compilation :
 *   gcc -m32 -Wall -Wextra -g soc-audit.c -o soc-audit
 *   (Certaines failles déclenchent un avertissement, d'autres NON : lisez le code,
 *    ne vous fiez pas qu'au compilateur. Pensez aussi à valgrind.)
 *
 * Méthode : concentrez-vous sur les ENTRÉES utilisateur et la gestion mémoire
 * (tampons de taille fixe, malloc/free, indices, tailles). Les repères (A), (B)…
 * en commentaire sont là pour structurer votre rapport — à vous de dire, pour
 * chacun, s'il y a une faille, laquelle, et comment la corriger.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char  hostname[32];
    char  ip[16];
    int   criticite;      /* 0 à 10 */
    char *note;           /* commentaire libre, alloué dynamiquement */
} Actif;

static Actif *inventaire = NULL;
static int    nb_actifs  = 0;
static int    capacite   = 0;

/* Affiche une bannière. */
void afficher_banniere(const char *titre)
{
    printf("\n====== ");
    printf(titre);                              /* (A) */
    printf(" ======\n");
}

/* Agrandit l'inventaire si besoin. */
void reserver(void)
{
    if (nb_actifs < capacite)
        return;
    capacite = (capacite == 0) ? 2 : capacite * 2;
    Actif *tmp = realloc(inventaire, capacite * sizeof(Actif));   /* (B) */
    if (tmp != NULL) {
    inventaire = tmp;
}
}

/* Ajoute un actif saisi au clavier. */
void ajouter(void)
{
    reserver();
    Actif *a = &inventaire[nb_actifs];

    printf("Nom d'hote   : ");
    scanf("%31s", a->hostname);                   /* (C) */

    printf("Adresse IP   : ");
    scanf("%15s", a->ip);                         /* (D) */

    printf("Criticite    : ");
    scanf("%d", &a->criticite);

    a->note = NULL;
    nb_actifs++;
    printf("Actif '%s' ajoute.\n", a->hostname);
}

/* Attache une note (commentaire) à un actif donné. */
void definir_note(void)
{
    int  idx;
    char saisie[256];

    printf("Numero de l'actif : ");
    scanf("%4d", &idx);                          /* (E) */

    printf("Note              : ");
    scanf(" %255[^\n]", saisie);

    inventaire[idx].note = malloc(strlen(saisie) + 1);   /* (F) */
    strcpy(inventaire[idx].note, saisie);            /* (G) */
}

/* Supprime le dernier actif ajouté. */
void supprimer_dernier(void)
{
    if (nb_actifs == 0)
        return;
    Actif *a = &inventaire[nb_actifs - 1];
    free(a->note);                                  /* (H) */    
    a->note = NULL;                    
    nb_actifs--;
    printf("Actif '%s' supprime.\n", a->hostname);
}

/* Liste tous les actifs. */
void lister(void)
{
    for (int i = 0; i < nb_actifs; i++) {      /* (I) */
        Actif *a = &inventaire[i];
        printf("#%d  %-20s %-16s crit=%d  %s\n",
               i, a->hostname, a->ip, a->criticite,
               a->note ? a->note : "(aucune note)");
    }
}

int main(void)
{
    int choix;

    afficher_banniere("SOC Inventory");
    do {
        printf("\n1.Ajouter  2.Note  3.Lister  4.Supprimer  0.Quitter\nChoix : ");
        if (scanf("%d", &choix) != 1)
            break;
        switch (choix) {
            case 1: ajouter();            break;
            case 2: definir_note();       break;
            case 3: lister();             break;
            case 4: supprimer_dernier();  break;
        }
    } while (choix != 0);

    free(inventaire);                           /* (J) */
    return 0;
}
