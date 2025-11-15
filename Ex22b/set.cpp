#include "set.h"
#include <cstdlib>

namespace Set
{
	std::initializer_list<Couleur> Couleurs = {Couleur::rouge, Couleur::mauve, Couleur::vert};
	std::initializer_list<Nombre> Nombres = {Nombre::un, Nombre::deux, Nombre::trois};
	std::initializer_list<Forme> Formes = {Forme::ovale, Forme::vague, Forme::losange};
	std::initializer_list<Remplissage> Remplissages = {Remplissage::plein, Remplissage::vide, Remplissage::hachure};

	string toString(Couleur c)
	{
		switch (c)
		{
		case Couleur::rouge:
			return "R";
		case Couleur::mauve:
			return "M";
		case Couleur::vert:
			return "V";
		default:
			throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v)
	{
		switch (v)
		{
		case Nombre::un:
			return "1";
		case Nombre::deux:
			return "2";
		case Nombre::trois:
			return "3";
		default:
			throw SetException("Nombre inconnue");
		}
	}

	string toString(Forme f)
	{
		switch (f)
		{
		case Forme::ovale:
			return "O";
		case Forme::vague:
			return "~";
		case Forme::losange:
			return "\004";
		default:
			throw SetException("Forme inconnue");
		}
	}

	string toString(Remplissage r)
	{
		switch (r)
		{
		case Remplissage::plein:
			return "P";
		case Remplissage::vide:
			return "_";
		case Remplissage::hachure:
			return "H";
		default:
			throw SetException("Remplissage inconnu");
		}
	}

	std::ostream &operator<<(std::ostream &f, Couleur c)
	{
		f << toString(c);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Nombre v)
	{
		f << toString(v);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Forme x)
	{
		f << toString(x);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Remplissage r)
	{
		f << toString(r);
		return f;
	}

	void printCouleurs(std::ostream &f)
	{
		for (auto c : Couleurs)
			f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream &f)
	{
		for (auto v : Nombres)
			f << v << " ";
		f << "\n";
	}

	void printFormes(std::ostream &f)
	{
		for (auto x : Formes)
			f << x << " ";
		f << "\n";
	}

	void printRemplissages(std::ostream &f)
	{
		for (auto r : Remplissages)
			f << r << " ";
		f << "\n";
	}

	ostream &operator<<(ostream &f, const Carte &c)
	{
		f << "[" << c.getCouleur() << c.getForme()
		  << c.getNombre() << c.getRemplissage() << "]";
		return f;
	}

	Jeu::Jeu()
	{
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto n : Nombres)
				for (auto f : Formes)
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, n, f, r);
	}

	const Carte &Jeu::getCarte(size_t i) const
	{
		if (i >= 81)
			throw SetException("carte iexistante");
		return *cartes[i];
	}

	Jeu::~Jeu()
	{
		for (size_t i = 0; i < 81; i++)
			delete cartes[i];
	}

	const Carte &Pioche::piocher()
	{ // get a random carte from the pioche
		// test if the pioche is not empty
		if (estVide())
			throw SetException("empty pioche");
		// choose a carte
		size_t i = rand() % nb; // get a random number between 0 and nb
		const Carte *chosenCarte = cartes[i];
		// remove the card from the array
		cartes[i] = cartes[nb - 1]; // replace carte i by the last carte of the pioche
		nb--;
		return *chosenCarte; // returns a reference over the chosen carte
	}

	void Plateau::ajouter(const Carte &c)
	{
		if (nb == nbMax)
		{ // all the cells of the array are already used
			// we have to resize the array to have more places
			const Carte **newarray = new const Carte *[nbMax + 5]; // create a larger array
			// we recopy all the adresses of cartes inside the new array
			for (size_t i = 0; i < nb; i++)
				newarray[i] = cartes[i];
			const Carte **old = cartes;
			cartes = newarray; // the newarray becomes the one to be used
			nbMax += 5;		   // update the number of places
			delete[] old;	   // deallocate the old array
		} // now, we know we have enough places to store more cartes
		cartes[nb] = &c; // store the adress of the new carte
		nb++;			 // increment the number of stored cartes
	}

	void Plateau::retirer(const Carte &c)
	{
		// searching for the carte to remove inside the array
		size_t i = 0;
		while (i < nb && cartes[i] != &c)
			i++;
		if (i == nb)
			throw SetException("this card does not exist");
		cartes[i] = cartes[nb - 1]; // replace the carte to be removed by the last one
		nb--;						// one carte removed
	}

	Plateau::Plateau(const Plateau &p)
	{
		/* we can't use the default copy constructor because if we do it,
		we will have two objects Plateau with the same value inside the attribute cartes,
		it means two Plateaus which point exactly on the same array : we don't want it
		because each Plateau should have its own array */
		cartes = new const Carte *[p.nbMax]; // allocate another independant array
		// copy all the adresses of the cartes inside Plateau p
		nb = p.nb;
		nbMax = p.nbMax;
		for (size_t i = 0; i < p.nb; i++)
			cartes[i] = p.cartes[i];
		// now, each Plateau has its own array but containing the same cartes
	}

	Plateau &Plateau::operator=(const Plateau &p)
	{
		if (this != &p)
		{ // protecting ourselve from auto-assignment
			/* becareful : both *this and p have their own array of pointers */
			nb = 0; // we consider that don't have carte anymore in the array
					// but we keep the capacity of the array in which we can
					// store new pointers
			for (size_t i = 0; i < p.nb; i++)
				ajouter(*p.cartes[i]); // add a carte from p
									   // is increasing the size of the array if needed
		}
		return *this; // returns a reference over the plateau itself
	}

	bool Combinaison::estUnSet() const
	{
		/* Les trois cartes forment donc un SET si et seulement si :
.la couleur des symboles est 3 fois strictement identique ou 3 fois totalement di�rente;
.la forme des symboles est 3 fois strictement identique ou 3 fois totalement di�rente;
.le nombre de symboles est 3 fois strictement identique ou 3 fois totalement di�rent;
.le remplissage des symboles est 3 fois strictement identique ou 3 fois totalement di�rent.*/
		bool test1 = (c1->getCouleur() == c2->getCouleur() && c1->getCouleur() == c3->getCouleur()) ||
					 (c1->getCouleur() != c2->getCouleur() && c1->getCouleur() != c3->getCouleur() && c2->getCouleur() == c3->getCouleur());
		bool test2 = (c1->getForme() == c2->getForme() && c1->getForme() == c3->getForme()) ||
					 (c1->getForme() != c2->getForme() && c1->getForme() != c3->getForme() && c2->getForme() == c3->getForme());
		bool test3 = (c1->getNombre() == c2->getNombre() && c1->getNombre() == c3->getNombre()) ||
					 (c1->getNombre() != c2->getNombre() && c1->getNombre() != c3->getNombre() && c2->getNombre() == c3->getNombre());
		bool test4 = (c1->getRemplissage() == c2->getRemplissage() && c1->getRemplissage() == c3->getRemplissage()) ||
					 (c1->getRemplissage() != c2->getRemplissage() && c1->getRemplissage() != c3->getRemplissage() && c2->getRemplissage() == c3->getRemplissage());
		return test1 && test2 && test3 && test4;
	}

	void Controleur::distribuer()
	{
		/* Permet de transf�rer des cartes de la pioche vers le plateau.
			Si le plateau contient moins de 12 cartes, distribuer() tente de compl�ter
			le plateau pour qu'il contienne 12 cartes.
			Si le plateau contient au moins 12 cartes, distribuer() tente d'ajouter
			une seule carte au plateau.
			Ces actions sont effectu�es si la pioche contient des cartes.
			Dans le cas contraire, la m�thode ne fait rien.
			*/
		if (!pioche->estVide())
			plateau.ajouter(pioche->piocher());
		while (!pioche->estVide() && plateau.getNbCartes() < 12)
			plateau.ajouter(pioche->piocher());
	}

	ostream &operator<<(ostream &f, const Combinaison &c)
	{
		f << "[" << c.getCarte1() << " ; " << c.getCarte2() << " ; " << c.getCarte3() << "]";
		return f;
	}

	void Plateau::print(ostream &f) const
	{
		f << "=================== PLATEAU ===================\n";
		for (size_t i = 0; i < nb; i++)
		{
			if (i % 3 == 0)
				f << "\n"; // retour � la ligne toutes les 3 cartes
			f << *cartes[i];
		}
		f << "\n===============================================\n";
	}

	ostream &operator<<(ostream &f, const Plateau &c)
	{
		c.print(f);
		return f;
	}

}