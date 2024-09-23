#include"teste.h"
void teste()
{
	Repo repo{ "teste.txt"};
	Validator val{ repo };
	Service service{ repo,val };
	assert(repo.get_all().size() == 5);
}