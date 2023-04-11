
1) COMMENT COMPILER ET UTILISER MON PROGRAMME:

taper en ligne de commande:

make       (pour compiler)
make run   (pour lancer la partie)
make clean (pour supprimer les executables et les .o)



2) NIVEAU D'EXIGEANCE ATTEINT:

Je n'ai pas codé l'echec et mat, ni le pat,
Le reste fonctionne bien à ma connaissance.



3) CONCEPTION:

Mon programme tourne autour de 2 fonctions principales: demander_coup(), dans Jeu.cc et joue_le_coup(), dans Echiquier.cc.
Le reste des fonctions ne sont globalement que des sous fonctions.

demander_coup() demande le coup, mais test aussi si le coup est valide dans tous les sens du terme.
On trouvera donc des sous-fonctions de demander_coup() pour chaque aspect de la validité d'un coup (echec, prise en passant et roque compris).
On trouvera aussi des sous fonctions pour tester si la pièce à déplacer a la propriété de se déplacer selon ce coup.
Ces dernières se trouves dans Piece.cc.

joue_le_coup() permet de modifier la grille de l'echiquier conformément au coup valide voulu.
On trouvera donc des sous fonctions de joue_le_coup() pour gérer la prise en passant, le roque et la promotion. 
(à noté que pour la promotion, la lettre correspondant au Cheval est N)

4) POUR JOUER

Pour jouer un coup écrire en minuscule la case départ et la case destination du coup, exemple: pour avancer le pion de la case e2 en e4, écrire en ligne de commande "e2e4"











