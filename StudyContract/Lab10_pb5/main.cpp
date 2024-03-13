#include <QtWidgets/QApplication>

#include "disciplina.h"
#include "service.h"
#include "disciplinaGUI.h"
#include "contractGUI.h"
#include "validator.h"

// add some subjects
void add_some(Service& srv)
{
    srv.add("5006", "POO", "1", "seminar", "Czibula Istvan");
    srv.add("5005", "POO", "2", "curs", "Czibula Istvan");
    srv.add("5022", "SDA", "1", "laborator", "Maier Mariana");
    srv.add("0014", "Geometrie", "2", "curs", "Blaga Paul");
}

void runGUI(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //Repo rep;
    RepoFile rep{"discipline.txt"};
    ValidateDisciplina val;
    Service srv{ rep, val };
    //add_some(srv);

    serviceGUI gui{ srv, rep };
    gui.show();

    a.exec();
}

int main(int argc, char *argv[])
{
    test_validator();
    tests_repo();
    tests_service();
    teste_cos();

    runGUI(argc, argv);

    return 0;
}