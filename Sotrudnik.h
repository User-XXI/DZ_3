#ifndef DZ_3_SOTRUDNIK_H
#define DZ_3_SOTRUDNIK_H

#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>
class Sotrudnik{
private:
	std::string m_firstname;
	std::string m_secondname;
	std::string m_patronymic;
	int m_numberinlist = 0;
	std::map<std::string, unsigned int> marks {{"Maths", 0}, {"Geometry", 0}, {"DisMaths", 0}, {"C++", 0}, {"English", 0} };
public:
	Sotrudnik();
	Sotrudnik(std::string i, std::string f, std::string o);
	Sotrudnik(std::string i, std::string f, std::string o, int numberinlist);
	Sotrudnik(std::string i, std::string f, std::string o, unsigned int m1, unsigned int m2, unsigned int m3, unsigned int m4, unsigned int m5);
	Sotrudnik(std::string i, std::string f, std::string o, int numberinlist ,unsigned int m1, unsigned int m2, unsigned int m3, unsigned int m4, unsigned int m5);
	Sotrudnik(Sotrudnik &A);
	Sotrudnik(Sotrudnik && A) noexcept ;
	~Sotrudnik();
	friend std::ostream &operator<<(std::ostream& out, Sotrudnik& A);
	friend std::istream &operator>>(std::istream& in, Sotrudnik& A);
	Sotrudnik(const Sotrudnik &A);
	bool operator<(const Sotrudnik& A) const;
	bool operator<(Sotrudnik& A);
	bool operator== (const Sotrudnik& w) const;
	Sotrudnik &operator=(const Sotrudnik &A);
	Sotrudnik &operator=(Sotrudnik &&A) noexcept ;
	float sAverageMark();
	unsigned int getmark(const std::string& a);
	std::map<std::string, unsigned int> getallmarks();
	std::ostream& getfio(std::ostream out);
	std::string geti();
	std::string getf();
	std::string geto();
	void setNumberinlist(int &numberinlist);
	[[nodiscard]] int getnumberinlist() const;
	void setfirstname(std::string &data);
	void setsecondname(std::string &data);
	void setpatronymic(std::string &data);
	void setmark(std::string &data, unsigned int mark);
	friend struct Hasher;
};
class SotrudnikError: public std::invalid_argument{
private:
	std::string m_firstname;
	std::string m_secondname;
	std::string m_patronymic;
	int m_numberinlist = 0;
	std::map<std::string, unsigned int> marks {{"Maths", 0}, {"Geometry", 0}, {"DisMath", 0}, {"C++", 0}, {"English", 0} };
public:
	SotrudnikError();
	SotrudnikError(const std::string& errror, std::string& i, std::string& f, std::string& o, int numberinlist ,unsigned int m1, unsigned int m2, unsigned int m3, unsigned int m4, unsigned int m5);
	SotrudnikError(const std::string &s, Sotrudnik &A);
	void print();
};


#endif //DZ_3_SOTRUDNIK_H
