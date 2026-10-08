# Étape 3a — Audit de `soc-audit.c`

On vous fournit un programme d'inventaire SOC écrit « vite fait ». Il **compile et
tourne**, mais contient plusieurs failles mémoire. Votre travail : les trouver, les
expliquer, les corriger.

## Consignes

1. Lisez le code `soc-audit.c`. Les repères `(A)`, `(B)`, … en commentaire marquent
   des points à examiner (certains cachent une faille, à vous de le dire).
2. Compilez et observez les avertissements — mais **ne vous fiez pas qu'au
   compilateur** : la plupart des failles ne déclenchent aucun warning.
   ```bash
   gcc -m32 -Wall -Wextra -g soc-audit.c -o soc-audit
   ```
3. Aidez-vous d'un essai à l'exécution et de `valgrind` :
   ```bash
   valgrind --leak-check=full ./soc-audit
   ```
4. Rendez un fichier **`AUDIT.md`** : pour **chaque faille**, indiquez
   - le **repère** et la **ligne**,
   - le **type** (dépassement de tampon, lecture/écriture hors limites, fuite,
     use-after-free, format string, allocation non vérifiée…),
   - le **mécanisme** en une ou deux phrases,
   - le **correctif** proposé (quelques lignes de C).

## Modèle de rapport (`AUDIT.md`)

```markdown
## Faille 1 — (repère) ligne N
- Type :
- Mécanisme :
- Correctif :

## Faille 2 — (repère) ligne N
...
```

## Barème (6 pts)
~0,75 pt par faille correctement identifiée **avec** mécanisme et correctif.
Bonus : classement par gravité (corruption mémoire exploitable > hors limites > fuite).

> Astuce : concentrez-vous sur les **entrées utilisateur** (`scanf`) et la **gestion
> mémoire** (`malloc` / `free`, tailles, indices, bornes de boucle).
