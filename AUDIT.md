# Étape 3a — Audit de `soc-audit.c` - MARTINEZ Enzo

## Problème A 

### 1. Le **repère** et la **ligne**

Ligne 37 :
```c
    printf(titre);                              /* (A) */
```

### 2. Le **type**

`Absence format`

### 3. Le **mécanisme** en une ou deux phrases

Le format ne possède pas de limite et l'utilisateur pourra donc entrer tout ce qu'il désire que ce soit des caractères où même des chiffres. Il pourrait afficher cela comme étant l'adresse sachant qu'il n'y a pas de type implémenté.

4. Le **correctif** proposé

## Problème B

### 1. Le **repère** et la **ligne**

Ligne 47 :
```c
    inventaire = realloc(inventaire, capacite * sizeof(Actif));   /* (B) */
```

### 2. Le **type**

`Fuite de mémoire`

### 3. Le **mécanisme** en une ou deux phrases

En écrivant inventaire = realloc() on écrase le pointeur inventaire avec NULL et on va donc perdre l'accès total à notre inventaire.

### 4. Le **correctif** proposé

```c
Actif *tmp = realloc(inventaire, capacite * sizeof(Actif));   /* (B) */
    if (tmp != NULL) {
    inventaire = tmp;
}
```

## Problème C

### 1. Le **repère** et la **ligne**

Ligne 57
```c
    scanf("%s", a->hostname);                   /* (C) */
```

### 2. Le **type**

`Dépassement de tampon`

### 3. Le **mécanisme** en une ou deux phrases

Avec seulement en scanf("%s) sans limite si nous avons mis une limite de tableau à 32 caractères, et que l'utilisateur en tape 50, le scanf va écrire tous les autres caractères restants dans les cases mémoires

### 4. Le **correctif** proposé
```c
scanf("%31s", a->hostname);  
```
## Problème D

### 1. Le **repère** et la **ligne**

Ligne 60
```c
    scanf("%s", a->ip);                         /* (D) */
```

### 2. Le **type**

`Dépassement de tampon`

### 3. Le **mécanisme** en une ou deux phrases

Avec seulement en scanf("%s) sans limite si nous avons mis une limite de tableau à 32 caractères, et que l'utilisateur en tape 50, le scanf va écrire tous les autres caractères restants dans les cases mémoires

### 4. Le **correctif** proposé
```c
scanf("%31s", a->hostname);  
```
## Problème E

### 1. Le **repère** et la **ligne**

Ligne 77
```c
    scanf("%d", &idx);                          /* (E) */
```

### 2. Le **type**

`Dépassement de tampon`

### 3. Le **mécanisme** en une ou deux phrases

Ne vérifie pas toujours bien les débordements et cela peut poser problème car si l'utilisateur entre des caractères à la place de chiffre => la valeur ne sera toujours pas initié

### 4. Le **correctif** proposé

Mettre une limite scanf("%4d")
```c
    scanf("%4d", &idx);                          /* (E) */
```

## Problème F

### 1. Le **repère** et la **ligne**

Ligne 82
```c
    inventaire[idx].note = malloc(strlen(saisie));    /* (F) */
```

### 2. Le **type**

`Allocation insuffisante`

### 3. Le **mécanisme** en une ou deux phrases

Problème d'allocation de la note. Sachant qu'il n'y a pas de +1, la taille de la mémoire ne sera pas bonne d'un octet sachant qu'on utilise strcpy qui utilisera +1 octet par rapport au strlen car il y a le caractère de fin de chaîne.

### 4. Le **correctif** proposé
```c
inventaire[idx].note = malloc(strlen(saisie) + 1);
```
## Problème G

### 1. Le **repère** et la **ligne**

Ligne 83
```c
    strcpy(inventaire[idx].note, saisie);            /* (G) */
```

### 2. Le **type**

`Allocation insuffisante`

### 3. Le **mécanisme** en une ou deux phrases

Problème d'allocation de la note. Sachant qu'il n'y a pas de +1, la taille de la mémoire ne sera pas bonne d'un octet sachant qu'on utilise strcpy qui utilisera +1 octet par rapport au strlen car il y a le caractère de fin de chaîne.

### 4. Le **correctif** proposé

```c
    strcpy(inventaire[idx].note, saisie);            /* (G) */
```

## Problème H

### 1. Le **repère** et la **ligne**

Ligne 92
```c
    free(a->note);                              /* (H) */
```

### 2. Le **type**

`Problème mémoire libre`

### 3. Le **mécanisme** en une ou deux phrases

Le pointeur ptr pointe toujours vers la même adresse, mais cette mémoire ne lui appartient plus quand on ne met pas de NULL

### 4. Le **correctif** proposé
```c
a->note = NULL;       
```
## Problème I

### 1. Le **repère** et la **ligne**

Ligne 100
```c
    for (int i = 0; i <= nb_actifs; i++)       /* (I) */
```

### 2. Le **type**

`Problème opérateur`

### 3. Le **mécanisme** en une ou deux phrases

 il ne sera jamais <= au nombre d'actifs donc si l'utilisateur veut accéder à la liste sans avoir ajouté le moindre actif auparavant => erreur 

### 4. Le **correctif** proposé

```c
    for (int i = 0; i < nb_actifs; i++)       /* (I) */
```

## Problème J

### 1. Le **repère** et la **ligne**

Ligne 125
```c
    free(inventaire);                           /* (J) */
```

### 2. Le **type**



### 3. Le **mécanisme** en une ou deux phrases



### 4. Le **correctif** proposé



