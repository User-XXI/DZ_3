#ifndef DZ_3_PODRAZDELENIE_H
#define DZ_3_PODRAZDELENIE_H

#include <unordered_set>
#include <set>
#include <string>
#include <iostream>
#include <mutex>
#include <fstream>
#include "Sotrudnik.h"
#include "Hasher.h"
static std::exception_ptr eptr = nullptr;
class Podrazdelenie{
private:
	std::unordered_set<Sotrudnik, Hasher> m_list;
	std::string m_name;
	unsigned int m_number = 0;
	int m_ident = 0;
public:
	Podrazdelenie();
	explicit Podrazdelenie(std::string a);
	Podrazdelenie(std::string a, unsigned int number);
	Podrazdelenie(std::string a, int ident);
	Podrazdelenie(std::string a, unsigned int number, int ident);
	~Podrazdelenie();
	Podrazdelenie(Podrazdelenie &B);
	Podrazdelenie(const Podrazdelenie&);
	Podrazdelenie(Podrazdelenie && B) noexcept ;
	Podrazdelenie &operator=(const Podrazdelenie &B);
	Podrazdelenie &operator=(Podrazdelenie &&B) noexcept ;
	void addSotrudnik(Sotrudnik& B);
	Podrazdelenie &operator+(Sotrudnik &B);
	double gAverageMarkAll();
	double gAverageMarkSub(std::string a);
	void printBest();
	void printDuty();
	std::ostream& findi(std::ostream &out, std::string &data);
	std::ostream& findf(std::ostream &out, std::string &data);
	std::ostream& findo(std::ostream &out, std::string &data);
	std::ostream& findmark(std::ostream &out, std::string &data, unsigned int &datamark);
	void newNumbers();
	void changefirstname(std::string &data, int &numberinlist);
	void changesecondname(std::string &data, int &numberinlist);
	void changepatronymic(std::string &data, int &numberinlist);
	void changemark(std::string &data, unsigned int &mark ,int &numberinlist);
	void deleteSotrudnik(int &numberinlist);
	void printSotrudniks();
	void outToFile(std::fstream& out);
	void inFromFile(std::fstream& in);
	std::string getname();
	unsigned int getnumber() const;
	int getident() const;
	std::unordered_set<Sotrudnik, Hasher> getlist();
	void clear();
	friend std::ostream &operator<<(std::ostream & out, Podrazdelenie&B);
	friend std::istream &operator>>(std::istream& in, Podrazdelenie&B);
};
class PodrazdelenieError: public std::invalid_argument{
private:
	std::unordered_set<Sotrudnik, Hasher> m_list;
	std::string m_name;
	unsigned int m_number = 0;
	int m_ident = 0;
public:
	PodrazdelenieError();
	PodrazdelenieError(const std::string &s, Podrazdelenie &B);
	void print();
};


#endif //DZ_3_PODRAZDELENIE_H
