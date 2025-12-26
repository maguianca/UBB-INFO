#include "service.h"
#include<algorithm>
vector<Elev> Service::sortare()
{
	vector<Elev>s{ repo.get_all() };
	sort(s.begin(), s.end(), [](const Elev& a, const Elev& b) {
		return a.get_nume() < b.get_nume();
		});
	return s;
}

