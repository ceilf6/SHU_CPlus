#include "set.h"
using namespace Set;

void f(Plateau &dest, const Plateau &source)
{
	dest = source;
}

int main()
{
	try
	{
		// Test 1: Display all possible values
		cout << "=== Test 1: Display characteristic values ===" << endl;
		printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();
		cout << endl;

		// Test 2: Get Jeu instance and display some cards
		cout << "=== Test 2: Display some cards from Jeu ===" << endl;
		Jeu &j = Jeu::getInstance();
		for (size_t i = 0; i < 10; i++)
			cout << j.getCarte(i) << "\n";
		cout << endl;

		// Test 3: Use Iterator
		cout << "=== Test 3: Iterate using Iterator ===" << endl;
		Jeu::Iterator it = j.first();
		int count = 0;
		while (!it.isDone() && count < 10)
		{
			cout << it.getCurrentItem();
			it.next();
			count++;
		}
		cout << "\n"
			 << endl;

		// Test 4: Use const_iterator with range-based for loop
		cout << "=== Test 4: Range-based for loop ===" << endl;
		count = 0;
		for (const Carte &c : j)
		{
			cout << c << "\n";
			if (++count >= 10)
				break;
		}
		cout << endl;

		// Test 5: Test Plateau operations
		cout << "=== Test 5: Plateau operations ===" << endl;
		Plateau p1;
		p1.ajouter(j.getCarte(0));
		p1.ajouter(j.getCarte(1));
		p1.ajouter(j.getCarte(2));
		cout << "Plateau p1:" << endl;
		cout << p1;

		Plateau p2;
		p2.ajouter(j.getCarte(3));
		p2.ajouter(j.getCarte(4));
		cout << "Plateau p2:" << endl;
		cout << p2;

		// Test copy constructor
		Plateau p3(p1);
		cout << "Plateau p3 (copy of p1):" << endl;
		cout << p3;

		// Test assignment operator
		p2 = p1;
		cout << "Plateau p2 after p2 = p1:" << endl;
		cout << p2;
		cout << endl;

		// Test 6: Combinaison and estUnSet
		cout << "=== Test 6: Test Combinaison ===" << endl;
		Combinaison combo1(j.getCarte(0), j.getCarte(1), j.getCarte(2));
		cout << "Combinaison: " << combo1 << endl;
		cout << "Est un SET? " << (combo1.estUnSet() ? "Oui" : "Non") << endl;
		cout << endl;

		// Test 7: Controleur
		cout << "=== Test 7: Test Controleur ===" << endl;
		Controleur ctrl;
		ctrl.distribuer();
		cout << ctrl.getPlateau();
		cout << "Nombre de cartes dans la pioche: " << ctrl.getPioche().getNbCartes() << endl;
	}
	catch (SetException &e)
	{
		std::cout << "Exception: " << e.getInfo() << "\n";
	}

	return 0;
}