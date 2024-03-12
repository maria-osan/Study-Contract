#pragma once

#include "disciplina.h"

#include <string>
#include <vector>

using std::vector;

// write in the file name_file the subject list
// HTML format
// throw RepoException if the file can't be open
void export_to_html(string name_file, const vector<Disciplina>& all);