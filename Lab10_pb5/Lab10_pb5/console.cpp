#include "console.h"
#include "disciplina.h"

#include <iostream>
#include <string>
#include <map>

using std::cin;
using std::cout;

void Console::print(const vector<Disciplina>& d_lst)
{
	cout << "\nDiscipline: \n";
	for (const auto& d : d_lst)
	{
		cout << " - " << d.get_id() << ": " << d.get_name() << ", " << d.get_nr_hours() << ", " << d.get_type() << ", " << d.get_teacher() << "\n";
	}
	cout << "\n";
}

void Console::add_UI()
{
	string id, name, type, teacher, nr_hours;
	cout << "\nDati ID-ul: ";
	getline(cin, id);
	cout << "Dati denumirea disciplinei: ";
	getline(cin, name);
	cout << "Dati numarul de ore pe saptamana: ";
	getline(cin, nr_hours);
	cout << "Dati tipul: ";
	getline(cin, type);
	cout << "Dati numele cadrului didactic: ";
	getline(cin, teacher);
	srv.add(id, name, nr_hours, type, teacher);
	cout << "\nAdaugat cu succes!\n\n";
}

void Console::delete_UI()
{
	string id;
	cout << "\nDati ID-ul: ";
	cin >> id;
	//const Disciplina& d = srv.find(id);
	try {
		srv.del(id);
		cout << "\nDisciplina a fost stearsa cu succes!\n\n";
	}
	catch (RepoException& exp) {
		cout << "\n" << exp << "\n\n";
	}
}

void Console::search_UI()
{
	string id;
	cout << "\nDati ID-ul: ";
	cin >> id;
	try {
		const Disciplina& d = srv.find(id);
		cout << " - " << d.get_id() << ": " << d.get_name() << ", " << d.get_nr_hours() << ", " << d.get_type() << ", " << d.get_teacher() << "\n\n";
	}
	catch (RepoException& exp) {
		cout << "\n" << exp << "\n\n";
	}
}

void print_menu()
{
	// Display the main menu of the application
	cout << "-------------------------------\n";
	cout << "-            MENIU:           -\n";
	cout << "-------------------------------\n";
	cout << "- Alegeti o comanda din meniu:-\n";
	cout << "-------------------------------\n";
	cout << "- 1. Adaugare                 -\n";
	cout << "- 2. Stergere                 -\n";
	cout << "- 3. Modificare               -\n";
	cout << "- 4. Cautare                  -\n";
	cout << "- 5. Filtrare                 -\n";
	cout << "- 6. Sortare                  -\n";
	cout << "- 7. Raport                   -\n";
	cout << "- 8. Contract de studiu       -\n";
	cout << "- p. Afisare                  -\n";
	cout << "- u. Undo                     -\n";
	cout << "- x. Iesire                   -\n";
	cout << "-------------------------------\n";
}

void modify_menu()
{
	// Display the menu for the modify opption
	cout << "---------------------------\n";
	cout << "- Modificari disponibile: -\n";
	cout << "---------------------------\n";
	cout << "- 1. Denumire             -\n";
	cout << "- 2. Numar ore/sapt       -\n";
	cout << "- 3. Tip                  -\n";
	cout << "- 4. Cadru didactic       -\n";
	cout << "---------------------------\n";
}

void filter_menu()
{
	// Display the menu for the modify opption
	cout << "-------------------------\n";
	cout << "- Filtrari disponibile: -\n";
	cout << "-------------------------\n";
	cout << "- 1. Numar ore/sapt     -\n";
	cout << "- 2. Cadru didactic     -\n";
	cout << "-------------------------\n";
}

void sort_menu()
{
	// Display the menu for the sort opption
	cout << "--------------------------\n";
	cout << "-  Sortari disponibile:  -\n";
	cout << "--------------------------\n";
	cout << "- 1. Denumire            -\n";
	cout << "- 2. Numar ore/sapt + id -\n";
	cout << "- 3. Cadru didactic + tip-\n";
	cout << "--------------------------\n";
}

void study_contract_menu()
{
	// Display the menu for the study contract opption
	cout << "---------------------------\n";
	cout << "-   Contract de studiu:   -\n";
	cout << "---------------------------\n";
	cout << "- 1. Golire contract      -\n";
	cout << "- 2. Adaugare disciplina  -\n";
	cout << "- 3. Generare contract    -\n";
	cout << "- 4. Vizualizare contract -\n";
	cout << "- 5. Export               -\n";
	cout << "- 0. Iesire               -\n";
	cout << "---------------------------\n";
}

void Console::study_contract_option()
{
	int ok = 1;
	while (ok)
	{
		int opt;
		study_contract_menu();
		cout << "Optiunea: ";
		cin >> opt;
		cin.get();
		if (opt == 1)
		{
			//list.empty_list();
			srv.emptyStudyContract();
			cout << "\nContractul de studiu a fost golit.\n\n";
		}
		else if (opt == 2)
		{
			string id;
			cout << "Dati ID-ul: ";
			getline(cin, id);
			try {
				//const Disciplina& d = srv.find(id);
				//list.add(d);
				srv.addStudyContract(id);
				cout << "\nDisciplina adaugata cu succes in contract.\n\n";
			}
			catch (RepoException& exp) {
				cout << "\n" << exp << "\n\n";
			}
		}
		else if (opt == 3)
		{
			int number;
			cout << "Dati numarul de discipline: ";
			cin >> number;
			//list.generate(number, srv.get_all());
			srv.addRandom(number);
			cout << "\nContract generat cu succes.\n\n";
		}
		else if (opt == 4)
		{
			for (auto l : srv.getAllStudyContract())
				cout << " - " << l.get_id() << ": " << l.get_name() << ", " << l.get_nr_hours() << ", " << l.get_type() << ", " << l.get_teacher() << "\n";
		}
		else if (opt == 5)
		{
			string file_name;
			cout << "Dati numele fisierului: ";
			cin >> file_name;
			srv.exportContractHTML(file_name);
			//list.export_html(file_name);
		}
		else if (opt == 0)
			ok = 0;
		else
			cout << "\nOptiune invalida!\n\n";
	}
}


void Console::start()
{
	int ok = 1;
	while (ok)
	{
		print_menu();
		cout << "Dati comanda: ";
		char cmd;
		cin >> cmd;
		cin.get();
		try {
			if (cmd == '1')
				add_UI();
			else if (cmd == '2')
				delete_UI();
			else if (cmd == '3')
			{
				cout << "\n";
				string id;
				cout << "\nDati ID-ul: ";
				cin >> id;
				try {
					const Disciplina& d = srv.find(id);
					cout << " - " << d.get_id() << ": " << d.get_name() << ", " << d.get_nr_hours() << ", " << d.get_type() << ", " << d.get_teacher() << "\n\n";
					modify_menu();
					cout << "Dati optiunea: ";
					char opt;
					cin >> opt;
					cin.get();
					if (opt == '1')
					{
						string name;
						cout << "Dati denumirea: ";
						getline(cin, name);
						srv.modify(d, name, '1');
					}
					else if (opt == '2')
					{
						string nr_hours;
						cout << "Dati numarul de ore: ";
						getline(cin, nr_hours);
						srv.modify(d, nr_hours, '2');
					}
					else if (opt == '3')
					{
						string type;
						cout << "Dati tipul: ";
						getline(cin, type);
						srv.modify(d, type, '3');
					}
					else {
						string teacher;
						cout << "Dati noua denumirea a disciplinei: ";
						getline(cin, teacher);
						srv.modify(d, teacher, '4');
					}
				}
				catch (RepoException& exp) {
					cout << "\n" << exp << "\n\n";
				}
			}
			else if (cmd == 'p' || cmd == 'P')
				print(srv.get_all());
			else if (cmd == '4')
				search_UI();
			else if (cmd == '5')
			{
				cout << "\n";
				filter_menu();
				cout << "Dati optiunea: ";
				char opt;
				cin >> opt;
				cin.get();
				if (opt == '1')
				{
					string nr_hours;
					cout << "\nDati numarul de ore pe saptamana: ";
					getline(cin, nr_hours);
					print(srv.filter_equal_hours(nr_hours));
				}
				else if (opt == '2')
				{
					string teacher;
					cout << "\nDati numele cadrului didactic: ";
					getline(cin, teacher);
					print(srv.filter_same_teacher(teacher));
				}
				else
					cout << "Optiune invalida!\n\n";
			}
			else if (cmd == '6')
			{
				cout << "\n";
				sort_menu();
				cout << "Dati optiunea: ";
				char opt;
				cin >> opt;
				cin.get();
				if (opt == '1')
					print(srv.sort_name());
				else if (opt == '2')
					print(srv.sort_hours());
				else if (opt == '3')
					print(srv.sort_teacher_type());
				else
					cout << "Optiune invalida!\n\n";
			}
			else if (cmd == '7')
			{
				std::map<string, int>rap;
				rap = srv.raport();
				for (auto it = rap.begin(); it != rap.end(); ++it)
				{
					cout << "Tipul: " << it->first << " - Valoare: " << it->second << "\n";
				}
				cout << "\n";
			}
			else if (cmd == '8')
				study_contract_option();
			else if (cmd == 'u' || cmd == 'U')
				srv.undo();
			else if (cmd == 'x' || cmd == 'X')
			{
				ok = 0;
			}
			else
				cout << "\nComanda invalida!\n\n";
		}
		catch (const RepoException& exp) {
			cout << "\n" << exp << "\n\n";
		}
		catch (const ValidateException& exp) {
			cout << "\n" << exp << "\n\n";
		}
	}
}