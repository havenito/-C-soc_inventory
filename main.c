#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct
{
    char hostname[32];
    char ip[16];
    int criticite;
} Actif;

Actif *actifs = NULL;

int max = 3;

int compteur;
char recherche[50];
int seuil;

int main(void)
{
    actifs = malloc(max * sizeof(Actif));
    menu();
    free(actifs);
}

int menu()
{
    printf("==========================\n");
    printf("||      SOC Inventory   ||\n");
    printf("||1.  Ajouter un actif  ||\n");
    printf("||2.  Lister les actifs ||\n");
    printf("||3. Rechercher un actif||\n");
    printf("||4.  Modifier un actif ||\n");
    printf("||5.  Supprimer un actif||\n");
    printf("||6.       Quitter      ||\n");
    printf("==========================\n");

    int choix;
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        ajouter_actif();
        break;
    case 2:
        lister_actifs();
        break;
    case 3:
        rechercher_actif();
        break;
    case 4:
        modifier_actif();
        break;
    case 5:
        supprimer_actif();
        break;
    case 6:
        quitter();
        break;
    default:
        menu();
    }
    if (choix != 6)
    {
        menu();
    }
}

int ajouter_actif()
{
    if (compteur > 100)

    {
        printf("Votre inventaire est plein !");
        menu();
    }
    if (compteur >= max)
    {
        max++;
        actifs = realloc(actifs, max * sizeof(Actif));
    }
    if (actifs == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }
    printf("Entrer le hostname : ");
    scanf("%31s", &actifs[compteur].hostname);
    printf("Entrer une IP : ");
    do
    {
        printf("Entrer une IP valide : ");
        scanf("%15s", &actifs[compteur].ip);
    } while (!valider_ip(actifs[compteur].ip));
    do
    {
        printf("Entrer le seuil de criticité compris entre 0 à 10 : ");
        scanf("%d", &actifs[compteur].criticite);
    } while (0 >= actifs[compteur].criticite || actifs[compteur].criticite >= 10);
    compteur++;
    printf("Actif entré avec succès !\n");
    return 0;
}

int lister_actifs()
{
    printf("Entrer un seuil de criticité des actifs minimal que vous voulez voir : ");
    scanf("%d", &seuil);
    for (int i = 0; i < compteur; i++)
    {
        if (actifs[i].criticite > seuil)
        {
            printf("%s %s %d\n", &actifs[i].hostname, &actifs[i].ip, actifs[i].criticite);
        }
        printf("%p\n", actifs[i]);
    }
    return 0;
}

int rechercher_actif()
{
    printf("Entrer l'actif que vous voulez rechercher: ");
    scanf("%31s", &recherche);
    for (int i = 0; i < compteur; i++)
    {
        if (strcmp(&actifs[i].hostname, recherche) == 0)
        {
            printf("%s %s %d\n trouvé", &actifs[i].hostname, &actifs[i].ip, actifs[i].criticite);
        }
    }
    return 0;
}

int modifier_actif()
{
    printf("Veuiller saisir l'ip de l'actif à modifier : ");
    scanf("%15s", &recherche);
    for (int i = 0; i < compteur; i++)
    {
        if (strcmp(&actifs[i].ip, recherche) == 0)
        {
            printf("ip de l'actif trouvé, veuillez saisir par quoi vous voulez modifier son ip : ");
            scanf("%15s", actifs[i].ip);
            printf("L'ip a bien été modifié ! ");
        }
    }
    return 0;
}

int supprimer_actif()
{
    printf("Veuillez saisir l'actif à supprimer : ");
    scanf("%31s", &recherche);
    for (int i = 0; i < compteur; i++)
    {
        if (strcmp(&actifs[i].hostname, recherche) == 0)
        {
            printf("%s %s %d\n trouvé, supprimons le", &actifs[i].hostname, &actifs[i].ip, actifs[i].criticite, "\n");
            for (int j = i; j < (compteur)-1; j++)
            {
                actifs[j] = actifs[j + 1];
            }
            compteur--;
            actifs = realloc(actifs, compteur * sizeof(Actif));
            if (actifs == NULL)
            {
                printf("Échec de la réallocation\n");
                return EXIT_FAILURE;
            }
            printf("L'actif a bien été supprimé !");
            return 1;
        }
    }
    printf("Actif non trouvé.");
    return 0;
}

int quitter()
{
    printf("Au revoir !\n");
    exit(0);
}

int valider_ip(const char *ip_str) {
    int octet1, octet2, octet3, octet4;
    char extra;
    int resultat = sscanf(ip_str, "%d.%d.%d.%d%c", &octet1, &octet2, &octet3, &octet4, &extra);

    if (resultat != 4) {
        return 0;
    }
    if (octet1 < 0 || octet1 > 255) return 0;
    if (octet2 < 0 || octet2 > 255) return 0;
    if (octet3 < 0 || octet3 > 255) return 0;
    if (octet4 < 0 || octet4 > 255) return 0;

    return 1;
}