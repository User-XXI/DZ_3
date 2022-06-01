#include "Sotrudnik.h"
#include <utility>

Sotrudnik::Sotrudnik()=default;
Sotrudnik::Sotrudnik(std::string i, std::string f, std::string o) {
	m_firstname = std::move(i);
	m_secondname = std::move(f);
	m_patronymic = std::move(o);
}
Sotrudnik::Sotrudnik(std::string i, std::string f, std::string o, int numberinlist) {
	m_firstname = std::move(i);
	m_secondname = std::move(f);
	m_patronymic = std::move(o);
	m_numberinlist = numberinlist;
}
Sotrudnik::Sotrudnik(std::string i, std::string f, std::string o, unsigned int m1, unsigned int m2, unsigned int m3,
				 unsigned int m4, unsigned int m5) {
	m_firstname = std::move(i);
	m_secondname = std::move(f);
	m_patronymic = std::move(o);
	if(m1<=5 && m2<=5 && m3<=5 && m4<=5 && m5<=5){
		marks["Maths"] = m1;
		marks["Geometry"] = m2;
		marks["DisMaths"] = m3;
		marks["C++"] = m4;
		marks["English"] = m5;
	}
}
Sotrudnik::Sotrudnik(std::string i, std::string f, std::string o, int numberinlist, unsigned int m1, unsigned int m2,
				 unsigned int m3, unsigned int m4, unsigned int m5) {
	m_firstname = std::move(i);
	m_secondname = std::move(f);
	m_patronymic = std::move(o);
	m_numberinlist = numberinlist;
	if(m1<=5 && m2<=5 && m3<=5 && m4<=5 && m5<=5){
		marks["Maths"] = m1;
		marks["Geometry"] = m2;
		marks["DisMaths"] = m3;
		marks["C++"] = m4;
		marks["English"] = m5;
	}
}
Sotrudnik::Sotrudnik(Sotrudnik &A) {
	m_firstname = A.m_firstname;
	m_secondname = A.m_secondname;
	m_patronymic = A.m_patronymic;
	m_numberinlist = A.m_numberinlist;
	this->marks = A.marks;
}
Sotrudnik::Sotrudnik(Sotrudnik &&A)  noexcept {
	std::swap(m_firstname, A.m_firstname);
	std::swap(m_secondname, A.m_secondname);
	std::swap(m_patronymic, A.m_patronymic);
	std::swap(m_numberinlist, A.m_numberinlist);
	std::swap(this->marks, A.marks);
}
Sotrudnik::Sotrudnik(const Sotrudnik &A) {
	m_firstname = A.m_firstname;
	m_secondname = A.m_secondname;
	m_patronymic = A.m_patronymic;
	m_numberinlist = A.m_numberinlist;
	marks = A.marks;
}
Sotrudnik::~Sotrudnik()=default;
std::ostream &operator<<(std::ostream& out, Sotrudnik &A){
	out << A.m_secondname << "; " << A.m_firstname << "; " << A.m_patronymic << "; " << A.m_numberinlist << "; ";
	for (const auto& i:A.marks){
		out<<i.first<<"-"<<i.second<<"; ";
	}
	return out;
}
std::istream &operator>>(std::istream& in, Sotrudnik& A){
	std::string f;
	unsigned int k;
	std::getline(in, A.m_secondname, ';');
	in.ignore();
	std::getline(in, A.m_firstname, ';');
	in.ignore();
	std::getline(in, A.m_patronymic, ';');
	in.ignore();
	in>>A.m_numberinlist;
	in.ignore(2);
	for(int i=0; i<5; i++) {
		getline(in, f, '-');
		in >> k;
		if(k<0 || k>5){
//            in.ignore(32767, '\n');
			f.pop_back();
			A.marks[f] = k;
			throw SotrudnikError("Wrong marks", A);
		}
		in.ignore(2);
		A.marks[f] = k;
		f.clear();
		k=0;
	}
	return in;
}
Sotrudnik &Sotrudnik::operator=(const Sotrudnik &A) = default;
Sotrudnik &Sotrudnik::operator=(Sotrudnik &&A)  noexcept {
	std::swap(m_firstname, A.m_firstname);
	std::swap(m_secondname, A.m_secondname);
	std::swap(m_patronymic, A.m_patronymic);
	std::swap(m_numberinlist, A.m_numberinlist);
	std::swap(this->marks, A.marks);
	return *this;
}
bool Sotrudnik::operator<(const Sotrudnik &A) const{
	if(m_firstname == A.m_firstname && m_secondname == A.m_secondname){
		return m_patronymic < A.m_patronymic;
	}
	else if(m_secondname==A.m_secondname){
		return m_firstname<A.m_firstname;
	}
	else {
		return m_secondname<A.m_secondname;
	}
}
bool Sotrudnik::operator<(Sotrudnik &A) {
	if(m_firstname == A.m_firstname && m_secondname == A.m_secondname){
		return m_patronymic < A.m_patronymic;
	}
	else if(m_firstname == A.m_firstname){
		return m_secondname<A.m_secondname;
	}
	else{
		return m_firstname<A.m_firstname;
	}
}
bool Sotrudnik::operator== (const Sotrudnik& w) const {
	return this->m_firstname == w.m_firstname &&
	this->m_secondname == w.m_secondname &&
    this->m_patronymic == w.m_patronymic &&
	this->m_numberinlist == w.m_numberinlist;
}
float Sotrudnik::sAverageMark() {
	unsigned int s = 0;
	for(const auto& i:marks){
		s+=i.second;
	}
	return s/5.;
}
unsigned int Sotrudnik::getmark(const std::string& a) {
	return marks[a];
}
std::map<std::string, unsigned int> Sotrudnik::getallmarks() {
	return marks;
}
std::ostream& Sotrudnik::getfio(std::ostream out) {
	out<<m_firstname<<'\n'<<m_secondname<<'\n'<<m_patronymic<<'\n';
	return out;
}
std::string Sotrudnik::geti() {
	return m_firstname;
}
std::string Sotrudnik::getf() {
	return m_secondname;
}
std::string Sotrudnik::geto() {
	return m_patronymic;
}
void Sotrudnik::setNumberinlist(int &numberinlist) {
	m_numberinlist = numberinlist;
}
int Sotrudnik::getnumberinlist() const {
	return m_numberinlist;
}
void Sotrudnik::setfirstname(std::string &data) {
	m_firstname = data;
}
void Sotrudnik::setsecondname(std::string &data) {
	m_secondname = data;
}
void Sotrudnik::setpatronymic(std::string &data) {
	m_patronymic = data;
}
void Sotrudnik::setmark(std::string &data, unsigned int mark) {
	marks[data] = mark;
}
SotrudnikError::SotrudnikError(const std::string& errror, std::string& i, std::string& f, std::string& o, int numberinlist,
						   unsigned int m1, unsigned int m2, unsigned int m3, unsigned int m4, unsigned int m5) :std::invalid_argument(errror){
	m_firstname = i;
	m_secondname = f;
	m_patronymic = o;
	m_numberinlist = numberinlist;
	marks["Maths"] = m1;
	marks["Geometry"] = m2;
	marks["DisMaths"] = m3;
	marks["C++"] = m4;
	marks["English"] = m5;
}
void SotrudnikError::print() {
	std::cerr << "Exception: " << what() << std::endl << "Data:\n "<<m_firstname<<'\n'<<m_secondname<<'\n'<<m_patronymic<<'\n'<<m_numberinlist<<'\n';
	for (const auto& i:marks){
		std::cerr<<i.first<<" - "<<i.second<<'\n';
	}
}
SotrudnikError::SotrudnikError(const std::string &s, Sotrudnik &A) : invalid_argument(s) {
	m_firstname = A.geti();
	m_secondname = A.getf();
	m_patronymic = A.geto();
	m_numberinlist = A.getnumberinlist();
	this->marks = A.getallmarks();
}

#include "Sotrudnik.h"
