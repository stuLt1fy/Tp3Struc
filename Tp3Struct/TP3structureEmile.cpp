// TP3structure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <fstream>

using namespace std;

struct Node {
	int  data;
	Node *gauche;
	Node *droit;
};

class BST {
private:
	Node * root;	// La racine l’arbre BST
	int niveau;
public:
	BST(int d)		// Construit l’arbre dont la racine contient la donnée d.
	{
		root = new Node;
		root->data = d;
		root->gauche = NULL;
		root->droit = NULL;
		niveau = 0;
	};

	BST()	// Constructeur vide pour utilisation dans la fonction main
	{

	};

	~BST()	// Supprime l’espace mémoire occupé par l’arbre.
	{
		DeleteBST(root);
	};

	void DeleteBST(Node* feuille)			// Fonction appelé par le destructeur pour vider l'arbre et l'espace mémoire qu'il occupait.
	{
		if (feuille != NULL) {
			if (feuille->droit != NULL) {
				DeleteBST(feuille->droit);
			}

			if (feuille->gauche != NULL) {
				DeleteBST(feuille->gauche);
			}
			feuille->data = 0;				// Supprime les valeurs contenues dans feuille et ses pointeurs.
			feuille->droit = NULL;
			feuille->gauche = NULL;
			feuille = NULL;
			delete feuille;
		}
	};

	void Insert(int d, Node *feuille)	// Insère l’élément de valeur d dans l’arbre.
	{
		if (root == NULL)				// S'il n'y a aucun element dans le BST, on le met dans la racine.
		{
			root = new Node;
			root->data = d;
			root->droit = NULL;
			root->gauche = NULL;
		}
		else {
			if (d < feuille->data)						// Si d < que la feuille, alors on va dans le sous-arbre gauche.
			{
				if (feuille->gauche != NULL)			// On va chercher le dernier élément du BST pour aller insérer notre donnée.
					Insert(d, feuille->gauche);
				else									// Lorsqu'on y est, on insere la donnee et on mets ses sous-branches a NULL.
				{
					feuille->gauche = new Node;
					feuille->gauche->data = d;
					feuille->gauche->gauche = NULL;
					feuille->gauche->droit = NULL;
				}
			}

			else if (d >= feuille->data)				// Si d > que la feuille, alors on va dans le sous-arbre droit.
			{
				if (feuille->droit != NULL) {			// On va chercher le dernier élément du BST pour aller insérer notre donnée.
					Insert(d, feuille->droit);
				}
				else {									// Lorsqu'on y est, on insere la donnee et on mets ses sous-branches a NULL.
					feuille->droit = new Node;
					feuille->droit->data = d;
					feuille->droit->gauche = NULL;
					feuille->droit->droit = NULL;
				}
			}
		}
	};

	void afficherNiveau(int i, Node *feuille)			// Affiche le contenu de la file qui contient le niveau i.
	{
		queue<int> file;
		Niveau(i, root, file);							// Appel de la fonction Niveau qui trouve tous les éléments de niveau i.
		while (!file.empty()) {							
			cout << file.front() << ", ";
			file.pop();
		}
	}

	void Niveau(int i, Node *feuille, queue<int> &file)	// Trouve les éléments de niveau i.
	{
		file;											// Si le niveau est 0, le seul élément est la racine donc pas besoin de fonction récursive.
		if (i == 0) {
			if (feuille != NULL) {
				file.push(feuille->data);
				return;
			}

		}
		else {											// Sinon, on utilise une fonction récursive pour chercher les éléments de niveau i.
			Niveau(i - 1, feuille->gauche, file);
			Niveau(i - 1, feuille->droit, file);
		}
	}

	void Delete(Node *feuille, int d)					// Supprime l’élément de valeur d de l’arbre.
	{
		Node *suppNode = NULL;							// On crée des pointeurs de type Node pour stocker la position de l'élément à supprimer.
		Node *suppNodeParent = NULL;
		Node *plusGrandEnfantGauche = NULL;
		Node *plusGrandEnfantGaucheParent = NULL;
		stack<Node*> pile;

		if (root == NULL) {
			cout << "Arbre vide" << endl;
		}

		recherche(root, d, pile);

		if (!pile.empty()) {
			suppNode = pile.top();
			pile.pop();
		}
		if (!pile.empty()) {
			suppNodeParent = pile.top();
			pile.pop();
		}

		if (suppNode == NULL) {
			cout << "item n'est pas dans l'arbre (fonction Delete)" << endl;
		}

		if (suppNode->gauche == NULL && suppNode->droit == NULL)		//Cas 1, le noeud à supprimer est une feuille.
		{
			if (suppNode->data >= suppNodeParent->data) {
				delete suppNode;
				suppNodeParent->droit = NULL;
			}
			else {
				delete suppNode;
				suppNodeParent->gauche = NULL;
			}
		}

		else if ((suppNode->droit == NULL && suppNode->gauche != NULL))	//Cas 2.1, le noeud n'a qu'un seul enfant et il est à gauche.
		{
			if (suppNode->data >= suppNodeParent->data) {
				suppNodeParent->droit = suppNode->gauche;
			}
			else {
				suppNodeParent->gauche = suppNode->gauche;
			}
			suppNode->gauche = NULL;
			delete suppNode;
		}

		else if (suppNode->droit != NULL && suppNode->gauche == NULL)	//Cas 2.2, le noeud n'a qu'un seul enfant et il est à sa droite.
		{
			if (suppNode->data >= suppNodeParent->data) {
				suppNodeParent->droit = suppNode->droit;
			}
			else {
				suppNodeParent->gauche = suppNode->droit;
			}
			suppNode->droit = NULL;
			delete suppNode;
		}

		else if (suppNode->droit != NULL && suppNode->gauche != NULL)	//Cas 3, le noeud a deux enfants.
		{

			plusGrandEnfantGauche = suppNode->gauche;
			if (plusGrandEnfantGauche->droit != NULL) {
				while (plusGrandEnfantGauche->droit != NULL) {
					if (plusGrandEnfantGauche->droit->droit == NULL)	//Trouve le parent du plusGrandEnfantGauche.
					{
						plusGrandEnfantGaucheParent = plusGrandEnfantGauche;
					}
					plusGrandEnfantGauche = plusGrandEnfantGauche->droit;
				}

				suppNode->data = plusGrandEnfantGauche->data;			//Remplace la node a supprimer par le plusGrandEnfantGauche.

				if (plusGrandEnfantGauche->gauche != NULL)				//Si le plusGrandEnfantGauche a un node à sa gauche, alors on refait le lien entre le parent et l'enfant de plusGrandEnfantGauche.
				{
					plusGrandEnfantGaucheParent->droit = plusGrandEnfantGauche->gauche;
					plusGrandEnfantGauche->gauche = NULL;
				}
				delete plusGrandEnfantGauche;
			}

			else {
				suppNode->data = plusGrandEnfantGauche->data;
				suppNode->gauche = plusGrandEnfantGauche->gauche;
				plusGrandEnfantGauche->gauche = NULL;
				delete plusGrandEnfantGauche;
			}
		}
	}

	Node* getRoot()
	{
		return root;
	}

	void recherche(Node *feuille, int d, stack<Node*> &pile)	// Recherche une valeur d dans l'arbre.
	{
		if (feuille == NULL) {
			cout << "item n'est pas dans l'arbre (fonction recherche)" << endl;
		}
		else if (d < feuille->data) {							// On appelle récursivement la fonction pour remplir une pile et trouver l'élément de valeur D.
			pile.push(feuille);
			recherche(feuille->gauche, d, pile);
		}
		else if (d > feuille->data) {
			pile.push(feuille);
			recherche(feuille->droit, d, pile);
		}
		else if (feuille->data == d) {
			pile.push(feuille);
			cout << "item trouve !" << endl;
		}
	}

	void Imprimer_decroissant(Node* feuille)			// Affiche les éléments de l’arbre dans l’ordre décroissant.
	{
		if (feuille != NULL) {							// Fonction récursive qui parcourt l'arbre de la valeur la plus à droite vers celle la plus à gauche. 
			if (feuille->droit != NULL) {
				Imprimer_decroissant(feuille->droit);
			}
			cout << feuille->data << " ";
			if (feuille->gauche != NULL) {
				Imprimer_decroissant(feuille->gauche);
			}
		}
		else {
			cout << "L'arbre est vide.\n";
		}
	}

	int Print_height(Node *feuille)					// Affiche la hauteur de l’arbre. 
	{
		if (feuille == NULL) {
			return -1;
		}

		int gauche = Print_height(feuille->gauche);	// Fonction récursive qui parcourt la gauche de l'arbre.
		int droite = Print_height(feuille->droit);	// Fonction récursive qui parcourt la droite de l'arbre.

		return max(gauche, droite) + 1;				// Trouve laquelle des deux valeurs est la plus grande pour définir la bonne hauteur.
	}

	void Print_Ancetres(Node *root, int d)			// Affiche les ascendants de l’élément de valeur d.
	{
		stack<Node*> pile;
		recherche(root, d, pile);

		if (!pile.empty()) {
			pile.pop();								// Enleve l'element d.
		}
		cout << "Anscendants (en partant du parent de d et en remontant l'arbre) de l'element d: ";
		while (!pile.empty()) {
			cout << pile.top()->data << " ";
			pile.pop();
		}
		cout << endl << endl;
	}

	void Print_childrens(Node *node, int d)		// Affiche les descendants de l’élément de valeur d
	{
		stack<Node*> pile;
		Node *feuille = NULL;
		recherche(root, d, pile);
		if (!pile.empty()) {
			feuille = pile.top();
		}

		cout << "Les enfants de " << d << " sont:" << endl;
		cout << "À gauche: " << feuille->gauche->data << " À droite: " << feuille->droit->data << endl;
		cout << endl;
	}

	void lireFichier()
	{
		ifstream fichier;
		char operation; //Operation dans le fichier
		int chiffre;	//Chiffre qui suit l'operation s'il y a lieu

		fichier.open("instructions.txt");

		if (fichier.fail())
			cout << "Impossible d'ouvrir le fichier";

		while (fichier >> operation) {
			//fichier.ignore(1, '\n');

			switch (operation) {
			case 'I':
				fichier >> chiffre;
				Insert(chiffre, root);
				break;
			case 'D':
				fichier >> chiffre;
				Delete(root, chiffre);
				break;
			case 'N':
				fichier >> chiffre;
				afficherNiveau(chiffre, root);
				break;
			case 'P':
				Imprimer_decroissant(root);
				cout << endl;
				break;
			case 'H':
				cout << "La hauteur est de l'arbre est: " << Print_height(root) << endl;
				break;
			case 'A':
				fichier >> chiffre;
				Print_Ancetres(root, chiffre);
				break;
			case 'C':
				fichier >> chiffre;
				Print_childrens(root, chiffre);
				break;
			default:
				cout << "Il ne reste aucune instruction a executer" << endl;
				break;
			}
		}
		fichier.close();
	}
};


int main()
{
	BST arbre;

	arbre.lireFichier();

	system("pause");
}