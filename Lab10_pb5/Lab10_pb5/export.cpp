#include "export.h"
#include "repository.h"

#include <fstream>

using std::ofstream;

void export_to_html(string name_file, const vector<Disciplina>& all)
{
	ofstream out(name_file, std::ios::trunc);
	if (!out.is_open())
	{
		throw RepoException("Nu s-a putut deschide fisierul: " + name_file);
	}

	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	out << "<tr>" << std::endl;
	out << "<td>" << "ID" << "</td>" << std::endl;
	out << "<td>" << "Denumire" << "</td>" << std::endl;
	out << "<td>" << "Nr ore/sapt" << "</td>" << std::endl;
	out << "<td>" << "Tip" << "</td>" << std::endl;
	out << "<td>" << "Profesor" << "</td>" << std::endl;
	out << "</tr>" << std::endl;
	for (const auto& d : all) {
		out << "<tr>" << std::endl;
		out << "<td>" << d.get_id() << "</td>" << std::endl;
		out << "<td>" << d.get_name() << "</td>" << std::endl;
		out << "<td>" << d.get_nr_hours() << "</td>" << std::endl;
		out << "<td>" << d.get_type() << "</td>" << std::endl;
		out << "<td>" << d.get_teacher() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;

	out.close();
}