#include <iostream>
#include <stack>
#include <queue>

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
		root = NULL;
		niveau = 0;
	};
	~BST()				// Supprime l’espace mémoire occupé par l’arbre.
	{
	};
	void Insert(int d, Node *feuille, int niveauSpec)						// insérer l’élément de valeur d dans l’arbre.
	{
		if (root == NULL)									//S'il n'y a aucun element dans le BST, on le met dans la racine.
		{
			root = new Node;
			root->data = d;
			root->droit = NULL;
			root->gauche = NULL;
		}
		else
		{
			if (d < feuille->data)					//Si d < que la feuille, alors on va dans le sous-arbre gauche
			{
				if (feuille->gauche != NULL)		//On va chercher le dernier élément du BST pour aller insérer notre donnée
					Insert(d, feuille->gauche, niveauSpec + 1);
				else								//Lorsqu'on y est, on insere la donnee et on mets ses sous-branches a NULL
				{
					feuille->gauche = new Node;
					feuille->gauche->data = d;
					feuille->gauche->gauche = NULL;
					feuille->gauche->droit = NULL;
				}
			}

			else if (d >= feuille->data)			//Idem mais si d est plus grand on prend le sous-arbre droit...
			{
				if (feuille->droit != NULL)
				{
					Insert(d, feuille->droit, niveauSpec + 1);
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
		if (niveauSpec > niveau)					//niveauSpec est le niveau speculatif dans lors de l'insertion (il varie avec chaque feuille qu'on parcour
		{
			niveau = niveauSpec;
		}
	
	};

	void afficherNiveau(int i, Node *feuille)									// Affiche le contenu de la file qui contient le niveau i.
	{
		queue<int> file;
		Niveau(i, root, file);
	}

	void Niveau(int i, Node *feuille, queue<int> file)							// Trouve les éléments de niveau i.
	{
		file;
		if (i == 0)
		{
			file.push(feuille->data);
			return;
		}
		else
		{
			Niveau(i - 1, feuille->gauche, file);
			Niveau(i - 1, feuille->droit, file);
		}
	}
	void Delete(Node *root, int d);				// Supprime l’élément de valeur d de l’arbre.
	void Imprimer_croissant(Node *root);		// Affiche les éléments de l’arbre dans l’ordre décroissant.
	int Print_height(Node *root);				// Affiche la hauteur de l’arbre. 
	void Print_Ancetres(Node *root, int d);		// Affiche les ascendants de l’élément de valeur d (bonus 10pts)
	void Print_childrens(Node *root, int d);	// Affiche les descendants de l’élément de valeur d
};