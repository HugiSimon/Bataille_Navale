#include <stdio.h>
#include <string>
#include <string.h>

#define TAILLE 10

typedef struct Case {

	int n_ligne = -1;
	int n_colonne = -1;

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

int main();

Case createCase(int, int);
Bateau createBateau(Case* tablo[TAILLE * TAILLE], int, int, int, int);
int detectCase(Case* tablo[TAILLE * TAILLE], int, int);
int detectBateau(Case* tablo[TAILLE * TAILLE], int, int, int, int);
int emplacementVide(Case* tablo[TAILLE * TAILLE]);
Case entreAttack();
void affich(Case* tablo[TAILLE * TAILLE], Case* visee[TAILLE * TAILLE]);

int main() {

	Case* tablo[TAILLE * TAILLE] = {};
	Case* visee[TAILLE * TAILLE] = {};

	Flotte equip;

	equip.t_PA = (Bateau*)malloc(sizeof(Bateau));
	*equip.t_PA = createBateau(tablo, 2, 2, 0, 5);

	equip.t_Cr = (Bateau*)malloc(sizeof(Bateau));
	*equip.t_Cr = createBateau(tablo, 4, 5, 1, 4);

	equip.t_SM1 = (Bateau*)malloc(sizeof(Bateau));
	*equip.t_SM1 = createBateau(tablo, 6, 7, 0, 3);

	equip.t_SM2 = (Bateau*)malloc(sizeof(Bateau));
	*equip.t_SM2 = createBateau(tablo, 9, 2, 0, 3);

	equip.t_To = (Bateau*)malloc(sizeof(Bateau));
	*equip.t_To = createBateau(tablo, 1, 6, 1, 2);



	*visee[emplacementVide(visee)] = entreAttack();
	affich(tablo, visee);
	*visee[emplacementVide(visee)] = entreAttack();
	affich(tablo, visee);
	*visee[emplacementVide(visee)] = entreAttack();
	affich(tablo, visee);
	*visee[emplacementVide(visee)] = entreAttack();
	affich(tablo, visee);

	return 0;
}

Case createCase(int n_l, int n_c) {

	Case temp;

	temp.n_ligne = n_l;
	temp.n_colonne = n_c;

	return temp;

}

Bateau createBateau(Case* tablo[TAILLE * TAILLE], int n_l, int n_c, int n_r, int n_n) { //n_r est la rotation (Vertical ou Horizontal) //n_n est la longeur de case du bateau

	Bateau temp{};

	if (detectBateau(tablo, n_l, n_c, n_r, n_n) == 1) { //Si la position est compromise, on annule
		return temp;
	}

	temp.t_pos = (Case*)malloc(sizeof(Case));
	*temp.t_pos = createCase(n_l, n_c); //Enregistre directement la premiere case de la position du bateau
	tablo[emplacementVide(tablo)] = temp.t_pos; //Puis l'enregiste dans le tablo

	temp.n_rota = n_r; //Enregiste la rotation et la longeur
	temp.n_case = n_n;

	for (int n_i = 1; n_i < n_n ;n_i++) { //Repete le nombre de fois la taille du bateau

		if (n_r == 0) { //En fonction de la rotation

			*tablo[emplacementVide(tablo)] = createCase(n_l + n_i, n_c); //Vertical

		}
		else {

			*tablo[emplacementVide(tablo)] = createCase(n_l, n_c + n_i); //Horizontal

		}

	}

	return temp;

}

int detectCase(Case* tablo[TAILLE * TAILLE], int n_l, int n_c) {

	for (int n_i = 0; n_i < TAILLE * TAILLE; n_i++) { //Vérifie toute la taille du tablo

		if (tablo[n_i] != nullptr) { //On analyse que les case du tableau remplie

			if (tablo[n_i]->n_ligne == n_l && tablo[n_i]->n_colonne == n_c) {

				return 1;

			}

		}

	}

	return 0; //Return 0 si on a jamais return 1
	
}

int detectBateau(Case* tablo[TAILLE * TAILLE], int n_l, int n_c, int n_r, int n_n) {

	for (int n_i = 0; n_i < n_n; n_i++) { //Boucle la longeur du bateau voulu
		
		if (n_r == 0) { //Dans quel sens on verifie (Vertical / Horizontal)
			
			if (detectCase(tablo, n_l + n_i, n_c) == 1) {
				return 1; //Return 1 si c'est detecte
			}

		}
		else {

			if (detectCase(tablo, n_l, n_c + n_i) == 1) {
				return 1;
			}

		}

	}

	return 0; //Si toutes les verification sont bonnes, ont renvoie 0

}

int emplacementVide(Case* tablo[TAILLE * TAILLE]) {

	int n_i = 0;

	while (tablo[n_i] != nullptr) { //Incremente tant que les places dans le tablo sont prises

		n_i++;

	}

	tablo[n_i] = (Case*)malloc(sizeof(Case)); //On en profite pour faire un malloc

	return n_i;

}

Case entreAttack() {

	Case temp;
	int n_x;
	int n_y;

	printf_s("Coordonnes X : "); //Le X sont les colonnes
	scanf_s("%d", &n_x);

	printf_s("Coordonnes Y : "); //Le y sont les lignes
	scanf_s("%d", &n_y);

	temp.n_colonne = n_x-1;
	temp.n_ligne = n_y-1;

	return temp;

}

void affich(Case* tablo[TAILLE * TAILLE], Case* visee[TAILLE * TAILLE]) {

	for (int n_i = 0; n_i < TAILLE; n_i++) { //Pour les lignes

		for (int n_j = 0; n_j < TAILLE; n_j++) { //Pour les colonnes

			if (detectCase(visee, n_i, n_j) == 1) { //Si on a deja visee a ces coordonnes

				if (detectCase(tablo, n_i, n_j) == 1) { //Si il y a aussi un bateau ici

					printf_s("X ");

				}
				else { //Si il y a pas de bateau

					printf_s("0 ");

				}

			}
			else { //Si on a pas visee ici, c'est forcement ~

				printf_s("~ ");

			}

		}

		printf_s("\n");

	}

}