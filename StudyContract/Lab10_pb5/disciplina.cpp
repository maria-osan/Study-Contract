#include "disciplina.h"

bool cmp_name(const Disciplina& d1, const Disciplina& d2)
{
	return d1.get_name() < d2.get_name();
}