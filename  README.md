
1) COMMENT COMPILER ET UTILISER MON PROGRAMME:

taper en ligne de commande:

make       (pour compiler)
make run   (pour lancer la partie)
make clean (pour supprimer les executables et les .o)



2) NIVEAU D'EXIGEANCE ATTEINT:

Je n'ai pas codé l'echec et mat, ni le pat, je m'y suis pris un peu tard pour cela.
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



4) DIFFICULTÉES RENCONTRÉES:

    4.1)  DIFFICULTÉES SPÉCIFIQUES

    Pour commencer, je n'ai pas su voir l'utilité de la classe Square, qui s'est petit à petit transformée
    en classe Coup dans mon projet.

    Ensuite, pour tester si un coup met en echec mon propre roi, j'ai décidé de jouer le coup, de tester l'echec, 
    puis d'annuler le coup avant de jouer vraiment.
    
    Comme je n'ai pas eu les bonnes idées aux bon moments, je me suis retrouvé à annuler des prises en passant et des roques, 
    avec toutes les modifications que ça impliques, ce qui s'est révélé plus ardu que prévu.
    
    J'ai introduit un argument booléen dans jouer_le_coup() pour m'éviter ce calvaire avec la promotion.
    
    Cependant, comme la fonction jouer_le_coup() est utilisée dans le test d'auto-echec (echec à soi même), 
    je n'ai pas pu afficher le message d'echec à l'adversaire dedans, ce qui m'a obligé à le mettre dans le main.
    
    Voila pour les difficultés spécifiques.


    4.2)  DIFFICULTÉES GÉNÉRALES

    La longueur du code, qui n'est peut être pas justifiée, m'a un peu géné vers la fin.
    Le debuging n'a pas été trop dur, mais je constate un manque d'efficacité tout de même.

    J'ai essayé d'être le plus clair possible dans mes explications en commentaire mais je me retrouve quand même
    avec quelque chose d'assez compliqué au final, je trouve.
    Mais l'univers n'est pas simple après tout, pourquoi mon code le serait-il.








