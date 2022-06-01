#include "Hasher.h"
std::hash<std::string> shash;
std::hash<int> ihash;
size_t Hasher::operator()(const Sotrudnik & ob) const
{
	const size_t coef = 2'946'901;
	return (
			coef * coef * coef * shash(ob.m_firstname) +
			coef * coef * shash(ob.m_secondname) +
			coef * shash(ob.m_patronymic) +
			ihash(ob.m_numberinlist)
	);
}
