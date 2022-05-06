#include <stdio.h>
#include <string>
#include <string.h>

#define TAILLE 10

typedef struct Case {

	int n_ligne;
	int n_colonne;

};

typedef struct Bateau {

	int n_case;
	int n_rota;
	Case* t_pos;

};

typedef struct Flotte {

	Bateau* t_PA;
	Bateau* t_Cr;
	Bateau* t_SM1;
	Bateau* t_SM2;
	Bateau* t_To;

};

Case creatCase(int, int);
int detectCase(int, int, Case* tablo[TAILLE * TAILLE]);
int verifBoat(int, int, int, int, Case* tablo[TAILLE * TAILLE]);
Bateau createBoat(int, int, int, int, Case* tablo[TAILLE * TAILLE]);
int posiTab(Case* tablo[TAILLE * TAILLE], int);
void affichBoat(Case* tablo[TAILLE * TAILLE]);

int main() {

	Case* tablo[TAILLE * TAILLE] = {};
	tablo[0] = nullptr;

	Bateau salut = createBoat(3, 0, 3, 5, tablo);
	Bateau erreur = createBoat(5, 1, 4, 3, tablo); //Essaie pour une erreur !!MARCHE!!
	createBoat(5, 1, 7, 2, tablo);

	affichBoat(tablo);

}


/*****************

CreatCase

Creer une variable de type case

*****************/

Case creatCase(int n_l, int n_c) {

	Case temp;

	temp.n_ligne = n_l;
	temp.n_colonne = n_c;

	return temp;

}


/*****************

detectCase

Explore le tableau de case en recherche si la position cherché est déjà prise

*****************/

int detectCase(int n_l, int n_c, Case* tablo[TAILLE * TAILLE]) {

	for (int n_i = 0; n_i < posiTab(tablo, 0); n_i++) {
		if (tablo[n_i]->n_ligne == n_l && tablo[n_i]->n_colonne == n_c) {
			return 1;
		}
	}

	return 0;
}


/*****************

verifBoat

Utilise detect case, permet de connaitre si un bateau est deja sur la position d'un futur bateau 

*****************/

int verifBoat(int n_l, int n_c, int n_rot, int n_cas, Case* tablo[TAILLE * TAILLE]) {

	for (int n_i = 0; n_i < n_cas; n_i++) {
		if (n_rot == 0) {
			if (detectCase(n_l + n_i, n_c, tablo) == 1) {
				return 1;
			}
		}
		else{
			if (detectCase(n_l, n_c + n_i, tablo) == 1) {
				return 1;
			}
		}
	}

	return 0;
}


/*****************

createBoat

utilise verifBoat, puis apres utilise createCase sur ca permiere position jusqu'a la longeur du bateau

*****************/

Bateau createBoat(int n_cas, int n_rot, int n_l, int n_c, Case* tablo[TAILLE * TAILLE]) {
	
	Bateau temp{};

	if (verifBoat(n_l, n_c, n_rot, n_cas, tablo) == 1) {
		return temp;
	}

	temp.n_case = n_cas;
	temp.n_rota = n_rot;

	temp.t_pos = (Case*)malloc(sizeof(Case));
	*temp.t_pos = creatCase(n_l, n_c);
	tablo[posiTab(tablo, 0)] = temp.t_pos;
	
	for (int n_i = 1; n_i < n_cas; n_i++) {
		if (n_rot == 0) {
			*tablo[posiTab(tablo, 1)] = creatCase(n_l + n_i, n_c);
		}
		else{
			*tablo[posiTab(tablo, 1)] = creatCase(n_l, n_c + n_i);
		}
	}

	return temp;

}


/*****************

posiTab

return une position libre dans le tableau, si le bol est 1, il malloc une nouvelle position

*****************/

int posiTab(Case* tablo[TAILLE * TAILLE], int bol) {

	int n_i = 0;

	while (tablo[n_i] != nullptr) {
		n_i++;
	}

	if (bol == 1) {
		tablo[n_i] = (Case*)malloc(TAILLE * TAILLE * sizeof(Case));
	}

	return n_i;
}


/*****************

affichBoat

print un 1 si la case est prise, 0 si elle est vide

*****************/

void affichBoat(Case* tablo[TAILLE * TAILLE]) {

	for (int n_i = 0; n_i < TAILLE ;n_i++) {
		for (int n_j = 0; n_j < TAILLE; n_j++) {
			if (detectCase(n_i, n_j, tablo) == 1) {
				printf_s("1  ");
			}
			else {
				printf_s("0  ");
			}
		}
		printf_s("\n");
	}

}