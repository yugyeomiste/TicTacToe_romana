# Projet C++ : Jeu du Morpion (Tic-Tac-Toe)

Voici mon projet de **Morpion** réalisé en **C++**. 
Le but était de créer un jeu avec un mode joueur contre joueur et un mode contre une IA.
Le projet intègre une librairie externe (`terminal_ctrl`) pour gérer l'effacement du terminal, qui est téléchargée automatiquement.

## Organisation du code

J'ai découpé mon code pour qu'il soit logique et propre: 

- `Main.cpp` 
  C'est le fichier le plus simple. Il ne contient que deux choses :
  - Il crée une instance de la classe `Game`
  - Il lance game.run()

Pourquoi ? Pour garder le main propre et mettre toute la logique dans classe `Game`.

- `Player.cpp`


  Avant de commencer, il faut créer les joueurs.

  **La fonction `create_player`** demande le nom du joueur : `std::cout << "Entrez votre nom: "; std::cin >> p.name;`
  Ensuite, elle force l'utilisateur à choisir `X` ou `O`. Je gère les minuscules/majuscules automatiquement avec `std::toupper()`.
  Tant que l'utilisateur ne rentre pas un symbole valide, je boucle pour redemander.

- `Game.cpp`

  **L'initialisation de tableau `init_board` :** 
  Au lieu de remplir le tableau avec des espaces vides, je le remplis avec les caractères `1` à `9`. C'est beaucoup plus compréhensible pour le joueur, il voit tout de suite quel numéro taper pour quelle case.


  **La boucle de jeu `run` :** 
  J'ai utilisé une boucle for de `0` à `9` tours maximum. À chaque tour, j'efface le terminal avec `erase_terminal` pour réafficher le plateau proprement, ce qui aère le terminal. Ensuite, je vérifie si c'est au tour du joueur humain ou de l'IA, puis je teste la victoire après chaque coup.

  **Jouer un coup `play_turn` :** 
  L'utilisateur tape un chiffre entre 1 et 9.
  Petit problème technique : le tableau est en indices `0` à `2`.
  Je convertis donc l'entrée : `ligne = (choix - 1) / 3` et `colonne = (choix - 1) % 3`.



## Focus sur l'IA (Amélioration):

Pour le mode solo, j'ai codé une IA qui joue au hasard en premier lieu. Puis j'ai decide de l'ameliorer avec `blocking_ia` qui anticipe et bloque les coups.

Dans la fonction `play_ia_turn`, elle :

- **Attaque** ( pour gagner) : 
  Elle appelle `blocking_ia(p2.symbol)` : si elle peut aligner 3 symboles, elle le fait.

- **Défend** ( elle bloque) : 
  Si elle ne peut pas gagner, elle appelle `blocking_ia(p1.symbol)` : si l'adversaire a 2 symboles alignés, elle bloque la troisième case.

- **Joue au hasard :** 
  Si elle ne toruve rien, elle joue aléatoirement.

J'utilise `std::mt19937` au lieu de `rand()`, car c'est la méthode recommandée dans les retours du projet de l'année dernière .



## Gestion des erreur

J'ai passé du temps à sécuriser les entrées clavier `(std::cin)`. 
Si l'utilisateur tape une lettre "A" au lieu du chiffre "5", le programme détecte l'erreur avec `if (!(std::cin >> choix))`.
Il répare l'entrée avec `cin.clear()` et vide la mémoire avec `cin.ignore()` (sinon le programme partait en boucle infinie au moindre caractères incorrect).



## Bilan

### Difficultés rencontrées

Le plus dur a été de coder la fonction `blocking_ia` : il fallait parcourir toutes les lignes, colonnes et diagonales pour compter les symboles et repérer la case vide. C'était un bon exercice pour comprendre.

J'ai aussi appris à utiliser `FetchContent` dans CMake pour intégrer la librairie externe, où j'ai eu un peu de mal car les noms avaient changé entre temps.