all: main Game_SortingRobot Checker_SortingRobot 

AlgoNaif.o: AlgoNaif.c AlgoNaif.h Grille.h Solution.h
	gcc -c AlgoNaif.c

AlgoCirculaire.o: AlgoCirculaire.c AlgoCirculaire.h Grille.h Solution.h AlgoNaif.h
	gcc -c AlgoCirculaire.c

LDC.o: LDC.c LDC.h
	gcc -c LDC.c

AlgoParCouleur.o: AlgoParCouleur.c AlgoParCouleur.h LDC.h AlgoNaif.h
	gcc -c AlgoParCouleur.c

AVL.o : AVL.c AVL.h AlgoNaif.h
	gcc -c AVL.c

TestAVL.o : TestAVL.c AVL.h
	gcc -c TestAVL.c

TestAVL : TestAVL.o AVL.o
	gcc -o TestAVL TestAVL.o AVL.o

AlgoAVL.o : AlgoAVL.c AVL.h AlgoNaif.h
	gcc -c AlgoAVL.c

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c

API_AffGrille.o: API_AffGrille.c API_AffGrille.h Grille.h
	gcc -c API_AffGrille.c

Game_SortingRobot.o: Game_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Game_SortingRobot.c

Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Game_SortingRobot Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL -lm

Checker_SortingRobot.o: Checker_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Checker_SortingRobot.c -lm

Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL -lm

main.o: main.c Grille.h Solution.h AlgoNaif.h AlgoCirculaire.h LDC.h AlgoParCouleur.h AVL.h
	gcc -c main.c

main: main.o Grille.o Solution.o entree_sortie.o AlgoNaif.o AlgoCirculaire.o LDC.o AlgoParCouleur.o AVL.o AlgoAVL.o
	gcc -o main main.o Grille.o Solution.o entree_sortie.o AlgoNaif.o AlgoCirculaire.o LDC.o AlgoParCouleur.o AVL.o AlgoAVL.o -lSDL -lm

clean:
	rm -f *.o main Game_SortingRobot Checker_SortingRobot TestAVL
