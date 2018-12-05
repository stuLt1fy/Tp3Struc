#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

struct Node {
	int  data;
	Node *gauche;
	Node *droit;
};

class BST {
private:
	Node * root;  // La racine l’arbre BST
	int niveau;
public:
	BST(int d)						// Construit l’arbre dont la racine contient la donnée d.
	{
		root = new Node;
		root->data = d;
		root->gauche = NULL;
		root->droit = NULL;
		niveau = 0;
	};

	~BST()				// Supprime l’espace mémoire occupé par l’arbre.
	{
		DeleteBST(root);
	};

	void DeleteBST(Node* feuille)
	{
		if (feuille != NULL) {
			if (feuille->droit != NULL) {
				DeleteBST(feuille->droit);
			}

			if (feuille->gauche != NULL) {
				DeleteBST(feuille->gauche);
			}
			feuille->data = 0;
			feuille->droit = NULL;
			feuille->gauche = NULL;
			feuille = NULL;
			delete feuille;
		}
	};

	void Insert(int d, Node *feuille)	// insérer l’élément de valeur d dans l’arbre.
	{
		if (root == NULL)				//S'il n'y a aucun element dans le BST, on le met dans la racine.
		{
			root = new Node;
			root->data = d;
			root->droit = NULL;
			root->gauche = NULL;
		}
		else
		{
			if (d < feuille->data)												//Si d < que la feuille, alors on va dans le sous-arbre gauche
			{
				if (feuille->gauche != NULL)									//On va chercher le dernier élément du BST pour aller insérer notre donnée
					Insert(d, feuille->gauche);
				else															//Lorsqu'on y est, on insere la donnee et on mets ses sous-branches a NULL
				{
					feuille->gauche = new Node;
					feuille->gauche->data = d;
					feuille->gauche->gauche = NULL;
					feuille->gauche->droit = NULL;
				}
			}

			else if (d >= feuille->data)										//Idem mais si d est plus grand on prend le sous-arbre droit...
			{
				if (feuille->droit != NULL)
				{
					Insert(d, feuille->droit);
				}
				else
				{
					feuille->droit = new Node;
					feuille->droit->data = d;
					feuille->droit->gauche = NULL;
					feuille->droit->droit = NULL;
				}
			}
		}
	};

	void afficherNiveau(int i, Node *feuille)									// Affiche le contenu de la file qui contient le niveau i.
	{
		queue<int> file;
		Niveau(i, root, file);
		while (!file.empty())
		{
			cout << file.front() << ", ";
			file.pop();
		}
	}

	void Niveau(int i, Node *feuille, queue<int> &file)							// Trouve les éléments de niveau i.
	{
		file;
		if (i == 0)
		{
			if (feuille != NULL)
			{
				file.push(feuille->data);
				return;
			}

		}
		else
		{
			Niveau(i - 1, feuille->gauche, file);
			Niveau(i - 1, feuille->droit, file);
		}
	}

	void Delete(Node *feuille, int d)				// Supprime l’élément de valeur d de l’arbre.
	{
		Node *suppNode = NULL;
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

		if (suppNode->gauche == NULL && suppNode->droit == NULL)		//Cas 1, le noeud a supprimer est une feuille
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

		else if ((suppNode->droit == NULL && suppNode->gauche != NULL))		//Cas 2.1, le noeud n'a qu'un seul enfant (gauche)
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

		else if (suppNode->droit != NULL && suppNode->gauche == NULL)		//Cas 2.2, le noeud n'a qu'un seul enfant (droit)
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

		else if (suppNode->droit != NULL && suppNode->gauche != NULL)		//Cas 3, le noeud a 2 enfants
		{

			plusGrandEnfantGauche = suppNode->gauche;
			if (plusGrandEnfantGauche->droit != NULL) {
				while (plusGrandEnfantGauche->droit != NULL) {
					if (plusGrandEnfantGauche->droit->droit == NULL)				//Trouve le parent du plusGrandEnfantGauche
					{
						plusGrandEnfantGaucheParent = plusGrandEnfantGauche;
					}
					plusGrandEnfantGauche = plusGrandEnfantGauche->droit;
				}

				suppNode->data = plusGrandEnfantGauche->data;	//Remplace la node a supprimer par le plusGrandEnfantGauche

				if (plusGrandEnfantGauche->gauche != NULL)							//Si le plusGrandEnfantGauche a un node a sa gauche, alors on refait le lien entre le parent et l'enfant de plusGrandEnfantGauche
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

	void recherche(Node *feuille, int d, stack<Node*> &pile)
	{
		if (feuille == NULL)
		{
			cout << "item n'est pas dans l'arbre (fonction recherche)" << endl;

		}
		else if (d < feuille->data)
		{
			pile.push(feuille);
			recherche(feuille->gauche, d, pile);
		}
		else if (d > feuille->data)
		{
			pile.push(feuille);
			recherche(feuille->droit, d, pile);
		}
		else if (feuille->data == d)
		{
			pile.push(feuille);
			cout << "item trouve !" << endl;
		}
	}

	void Imprimer_decroissant(Node* feuille)			// Affiche les éléments de l’arbre dans l’ordre décroissant.
	{
		if (feuille != NULL) {
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
		if (feuille == NULL)					
		{
			return -1;
		}

		int gauche = Print_height(feuille->gauche);	// Fonction récursive qui parcourt la gauche de l'arbre.
		int droite = Print_height(feuille->droit);	// Fonction récursive qui parcourt la droite de l'arbre.

		return max(gauche, droite) + 1;				// Trouve laquelle des deux valeurs est la plus grande pour définir la bonne hauteur.
	}

	void Print_Ancetres(Node *root, int d)			// Affiche les ascendants de l’élément de valeur d (bonus 10pts)
	{
		stack<Node*> pile;
		recherche(root, d, pile);

		if (!pile.empty()) {
			pile.pop();								// Enleve l'element d.
		}
		cout << "Anscendants (en partant du parent de d et en remontant l'arbre) de l'element d: ";
		while (!pile.empty()) {
			cout << pile.top() << " ";
			pile.pop();
		}
		cout << endl << endl;
	}

	void Print_childrens(Node *root, int d)		// Affiche les descendants de l’élément de valeur d
	{
		stack<Node*> pile;
		Node *feuille;
		recherche(root, d, pile);
		if (!pile.empty()) {
			feuille = pile.top();
		}

		cout << "Les enfants de " << d << " sont:" << endl;
		cout << "À gauche: " << feuille->gauche->data << " À droite: " << feuille->droit->data << endl;
		cout << endl;
	}
};


int main()
{
	BST arbre();


	
	system("pause");
}