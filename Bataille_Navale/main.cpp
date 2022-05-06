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
void affichBoat(Case* tablo[TAILLE * TAILLE], int, Case* tablo2[TAILLE * TAILLE]);
Bateau createFlotte(int, Case* tablo[TAILLE * TAILLE]);
void cleanTablo(Case* tablo[TAILLE * TAILLE]);
void attackTablo(Case* tablo[TAILLE * TAILLE]);
void affichAttak(Case* tablo[TAILLE * TAILLE], Case* tablo2[TAILLE * TAILLE], int, int);

int main() {

	Case* tablo[TAILLE * TAILLE] = {};
	tablo[0] = nullptr;

	Case* tablo2[TAILLE * TAILLE] = {};
	tablo2[0] = nullptr;


	Flotte equip1{};

	while(posiTab(tablo, 0) != 17) {

		cleanTablo(tablo);
		
		affichBoat(tablo, 0, tablo2);
		equip1.t_PA = (Bateau*)malloc(sizeof(Bateau));
		*equip1.t_PA = createFlotte(5, tablo);

		affichBoat(tablo, 0, tablo2);
		equip1.t_Cr = (Bateau*)malloc(sizeof(Bateau));
		*equip1.t_Cr = createFlotte(4, tablo);

		affichBoat(tablo, 0, tablo2);
		equip1.t_SM1 = (Bateau*)malloc(sizeof(Bateau));
		*equip1.t_SM1 = createFlotte(3, tablo);

		affichBoat(tablo, 0, tablo2);
		equip1.t_SM2 = (Bateau*)malloc(sizeof(Bateau));
		*equip1.t_SM2 = createFlotte(2, tablo);

		affichBoat(tablo, 0, tablo2);
		equip1.t_To = (Bateau*)malloc(sizeof(Bateau));
		*equip1.t_To = createFlotte(1, tablo);

		affichBoat(tablo, 0, tablo2);
	}

	while (posiTab(tablo, 0) != 0) {

		affichBoat(tablo, 1, tablo2);
		attackTablo(tablo2);

	}

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
			return n_i;
		}
	}

	return -1;
}


/*****************

verifBoat

Utilise detect case, permet de connaitre si un bateau est deja sur la position d'un futur bateau 

*****************/

int verifBoat(int n_l, int n_c, int n_rot, int n_cas, Case* tablo[TAILLE * TAILLE]) {

	for (int n_i = 0; n_i < n_cas; n_i++) {
		if (n_rot == 0) {
			if (detectCase(n_l + n_i, n_c, tablo) != -1) {
				return 1;
			}
		}
		else{
			if (detectCase(n_l, n_c + n_i, tablo) != -1) {
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
		temp.n_case = -1;
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

void affichBoat(Case* tablo[TAILLE * TAILLE], int bol, Case* tablo2[TAILLE * TAILLE]) {

	system("cls");

	for (int n_i = 0; n_i < TAILLE ;n_i++) {
		for (int n_j = 0; n_j < TAILLE; n_j++) {
			if (bol == 0) {
				if (detectCase(n_i, n_j, tablo) != -1) {
					printf_s("1 ");
				}
				else {
					printf_s("0 ");
				}
			}
			else {
				affichAttak(tablo, tablo2, n_i, n_j);
			}
		}
		printf_s("  %d", n_i+1);
		if (n_i == 0) {
			printf(" ligne");
		}
		printf_s("\n");
	}

	printf_s("\n");
	for (int n_i = 1; n_i <= TAILLE; n_i++) {
		printf_s("%d ", n_i);
	}
	printf_s("\ncolonne\n");

}


/*****************

createFlotte

Demande au joueur de positionner les bateau

*****************/

Bateau createFlotte(int n_cas, Case* tablo[TAILLE * TAILLE]) {

	Bateau temp{};
	int n_case{};
	int n_li;
	int n_co;
	int n_ve;

	printf_s("\nOu voulez vous placer votre ");
	switch (n_cas)
	{
	case 5:
		printf_s("porte avion (5 cases) ");
		n_case = 5;
		break;
	case 4:
		printf_s("croiseur (4 cases) ");
		n_case = 4;
		break;
	case 3:
		printf_s("premier sous-marin (3 cases) ");
		n_case = 3;
		break;
	case 2:
		printf_s("deuxième sous-marin (3 cases) ");
		n_case = 3;
		break;
	case 1:
		printf_s("torpilleur (2 cases) ");
		n_case = 2;
		break;
	default:
		break;
	}

	printf_s("\n\nQuel ligne ? ");
	scanf_s("%d", &n_li);

	printf_s("Quel colonne ? ");
	scanf_s("%d", &n_co);

	printf_s("Vertiacal ou horizontal ? (0/1) ");
	scanf_s("%d", &n_ve);

	temp = createBoat(n_case, n_ve, n_li-1, n_co-1, tablo);

	return temp;
}


/*****************

cleanTablo

Rend le tablo comme neuf

*****************/

void cleanTablo(Case* tablo[TAILLE * TAILLE]) {

	Case *vide{};

	for (int n_i = 0; n_i < TAILLE*TAILLE; n_i++) {
		tablo[n_i] = vide;
	}

}


/*****************

attackTablo

Demande au joueur la position ou il veut attacker

*****************/

void attackTablo(Case* tablo[TAILLE * TAILLE]) {

	int n_l{};
	int n_c{};
	Case* temp{};

	printf_s("\nQuel ligne ? ");
	scanf_s("%d", &n_l);

	printf_s("Quel colonne ? ");
	scanf_s("%d", &n_c);

	temp = (Case*)malloc(sizeof(Case));

	temp->n_ligne = n_l-1;
	temp->n_colonne = n_c-1;

	tablo[posiTab(tablo, 1)] = temp;

}


/*****************

affichAttak

Pour afficher directement ou on a tire et ou en a touche

*****************/

void affichAttak(Case* tablo[TAILLE * TAILLE], Case* tablo2[TAILLE * TAILLE], int n_l, int n_c) {

	int temp = 0;

	for (int n_i = 0; n_i < posiTab(tablo2, 0); n_i++) {
		if (detectCase(n_l, n_c, tablo2) != -1) {
			if (detectCase(n_l, n_c, tablo) != -1) {
				temp = 2;
			}
			else {
				temp = 1;
			}
		}
	}

	switch (temp)
	{
	case 0:
		printf_s("O ");
		break;
	case 1:
		printf_s("0 ");
		break;
	case 2:
		printf_s("X ");
		break;
	default:
		break;
	}

}