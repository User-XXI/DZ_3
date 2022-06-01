#include "Podrazdelenie.h"

#include "Podrazdelenie.h"
#include <utility>
std::mutex mx;
Podrazdelenie::Podrazdelenie() = default;
Podrazdelenie::Podrazdelenie(std::string a) {
	m_name = std::move(a);
}
Podrazdelenie::Podrazdelenie(std::string a, unsigned int number) {
	m_name = std::move(a);
	m_number = number;
}
Podrazdelenie::Podrazdelenie(std::string a, int ident) {
	m_name = std::move(a);
	m_ident = ident;
}
Podrazdelenie::Podrazdelenie(std::string a, unsigned int number, int ident) {
	m_name = std::move(a);
	m_number = number;
	m_ident = ident;
}
Podrazdelenie::~Podrazdelenie() = default;
Podrazdelenie::Podrazdelenie(Podrazdelenie &B) {
	m_name = B.m_name;
	m_number = B.m_number;
	m_ident = B.m_ident;
	m_list = B.m_list;
}
Podrazdelenie::Podrazdelenie(const Podrazdelenie &) = default;
Podrazdelenie::Podrazdelenie(Podrazdelenie &&B) noexcept {
	std::swap(m_name, B.m_name);
	std::swap(m_number, B.m_number);
	std::swap(m_ident, B.m_ident);
	std::swap(m_list, B.m_list);
}
void Podrazdelenie::newNumbers() {
	std::set<Sotrudnik> temp(m_list.begin(), m_list.end());
	m_list.clear();
	Sotrudnik temps;
	for(auto &i:temp) {
		temps = i;
		std::ptrdiff_t index(std::distance(temp.begin(), temp.find(i)));
		int numb = index + 1;
		temps.setNumberinlist(numb);
		m_list.insert(temps);
	}
}
void Podrazdelenie::addSotrudnik(Sotrudnik &B) {
	m_number+=1;
	m_list.insert(B);
	std::unordered_set<Sotrudnik, Hasher> temp;
	Sotrudnik temps;
	this->newNumbers();
}
std::ostream &operator<<(std::ostream & out, Podrazdelenie&B){
	out << B.m_name<<';'<<B.m_number<<';'<<B.m_ident<<'\n';
	for(auto i:B.m_list){
		out<<i<<'\n';
	}
	return out;
}
std::istream &operator>>(std::istream& in, Podrazdelenie&B){
	mx.lock();
	std::getline(in, B.m_name, ';');
	mx.unlock();
	mx.lock();
	in >> B.m_number;
	mx.unlock();
	in.ignore();
	mx.lock();
	in>>B.m_ident;
	mx.unlock();
	in.ignore();
	for (int i = 0; i < B.m_number; i++) {
		Sotrudnik A;
		try {
			in >> A;
			mx.lock();
			B.m_list.insert(A);
			mx.unlock();
		}
		catch (SotrudnikError &Error){
			Error.print();
			break;
		}
	}
	mx.lock();
	B.newNumbers();
	mx.unlock();
	return in;
}
Podrazdelenie &Podrazdelenie::operator+(Sotrudnik &B) {
	if(this->m_list.count(B) == 0){
		this->addSotrudnik(B);
		return *this;
	}
	else{
		return *this;
	}
}
Podrazdelenie &Podrazdelenie::operator=(const Podrazdelenie &B) = default;
Podrazdelenie &Podrazdelenie::operator=(Podrazdelenie &&B) noexcept {
	std::swap(m_name, B.m_name);
	std::swap(m_number, B.m_number);
	std::swap(m_ident, B.m_ident);
	std::swap(m_list, B.m_list);
	return *this;
}
double Podrazdelenie::gAverageMarkAll() {
	double k = 0.;
	for (auto i:m_list){
		k+=i.sAverageMark();
	}
	return k/m_number;
}
double Podrazdelenie::gAverageMarkSub(std::string a) {
	double k=0.0;
	for(auto i:m_list){
		k+=i.getmark(a);
	}
	return k/m_number;
}
void Podrazdelenie::printBest() {
	for (auto i:m_list){
		if(i.sAverageMark() == 5){
			std::cout<<i;
		}
	}
}
void Podrazdelenie::printDuty() {
	for(auto i:m_list){
		for(auto j:i.getallmarks()){
			if (j.second<3){
				std::cout<<i;
				continue;
			}
		}
	}
}
std::ostream& Podrazdelenie::findi(std::ostream &out, std::string &data) {
	bool find = false;
	for(auto i:m_list){
		if(i.geti() == data){
			find = true;
			out<<i;
		}
	}
	if(!find) {
		out << "Sotrudnik not found!\n";
	}
	return out;
}
std::ostream& Podrazdelenie::findf(std::ostream &out, std::string &data) {
	bool find = false;
	for(auto i:m_list){
		if(i.getf() == data){
			find = true;
			out<<i;
		}
	}
	if(!find) {
		out << "Sotrudnik not found!\n";
	}
	return out;
}
std::ostream& Podrazdelenie::findo(std::ostream &out, std::string &data) {
	bool find = false;
	for(auto i:m_list){
		if(i.geto() == data){
			find = true;
			out<<i;
		}
	}
	if(!find) {
		out << "Sotrudnik not found!\n";
	}
	return out;
}
std::ostream& Podrazdelenie::findmark(std::ostream &out, std::string &data, unsigned int &datamark) {
	bool find = false;
	for(auto i:m_list){
		if(i.getmark(data) == datamark){
			find = true;
			out<<i;
		}
	}
	if(!find) {
		out << "Sotrudnik not found!\n";
	}
	return out;
}
void Podrazdelenie::changefirstname(std::string &data, int &numberinlist) {
	std::unordered_set<Sotrudnik, Hasher> temp (m_list);
	for(auto i:m_list){
		if (i.getnumberinlist() == numberinlist){
			Sotrudnik temps(i);
			temp.erase(i);
			temps.setfirstname(data);
			temp.insert(temps);
		}
	}
	m_list = temp;
	this->newNumbers();
}
void Podrazdelenie::changesecondname(std::string &data, int &numberinlist) {
	std::unordered_set<Sotrudnik, Hasher> temp (m_list);
	for(auto i:m_list){
		if (i.getnumberinlist() == numberinlist){
			Sotrudnik temps(i);
			temp.erase(i);
			temps.setsecondname(data);
			temp.insert(temps);
		}
	}
	m_list = temp;
	this->newNumbers();
}
void Podrazdelenie::changepatronymic(std::string &data, int &numberinlist) {
	std::unordered_set<Sotrudnik, Hasher> temp (m_list);
	for(auto i:m_list){
		if (i.getnumberinlist() == numberinlist){
			Sotrudnik temps(i);
			temp.erase(i);
			temps.setpatronymic(data);
			temp.insert(temps);
		}
	}
	m_list = temp;
	this->newNumbers();
}
void Podrazdelenie::changemark(std::string &data, unsigned int &mark, int &numberinlist) {
	std::unordered_set<Sotrudnik, Hasher> temp (m_list);
	for(auto i:m_list){
		if (i.getnumberinlist() == numberinlist){
			Sotrudnik temps(i);
			temp.erase(i);
			temps.setmark(data, mark);
			temp.insert(temps);
		}
	}
	m_list = temp;
}
void Podrazdelenie::deleteSotrudnik(int &numberinlist) {
	std::unordered_set<Sotrudnik, Hasher> temp (m_list);
	if (numberinlist>m_number||numberinlist<0){
		try {
			throw PodrazdelenieError("Wrong number of Sotrudnik!", *this);
		}
		catch (PodrazdelenieError &Error){
			mx.lock();
			Error.print();
			mx.unlock();
		}
	}
	for(const auto& i:m_list){
		if (i.getnumberinlist() == numberinlist){
			temp.erase(i);
		}
	}
	m_number-=1;
	mx.lock();
	m_list = temp;
	this->newNumbers();
	mx.unlock();
}
void Podrazdelenie::printSotrudniks() {
	for(auto i:m_list){
		std::cout<<i<<'\n';
	}
}
void Podrazdelenie::outToFile(std::fstream &out) {
	out<<*this;
	out.close();
}
void Podrazdelenie::inFromFile(std::fstream &in) {
	this->clear();
	in>>*this;
	in.close();
}
unsigned int Podrazdelenie::getnumber() const {
	return m_number;
}
std::string Podrazdelenie::getname() {
	return m_name;
}
int Podrazdelenie::getident() const {
	return m_ident;
}
std::unordered_set<Sotrudnik, Hasher> Podrazdelenie::getlist() {
	return m_list;
}
void Podrazdelenie::clear() {
	m_list.clear();
}
PodrazdelenieError::PodrazdelenieError(const std::string &s, Podrazdelenie &B) : invalid_argument(s) {
	m_name = B.getname();
	m_number = B.getnumber();
	m_ident = B.getident();
	m_list = B.getlist();
}
void PodrazdelenieError::print() {
	std::cerr << "Exception: " << what() << std::endl << "Data:\n "<<m_name<<'\n'<<m_number<<'\n'<<m_ident<<'\n';
	for(auto i:m_list){
		std::cerr<<i<<'\n';
	}
}
