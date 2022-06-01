#include <iostream>
#include <string>
#include "Podrazdelenie.h"
#include <thread>

int main() {
	std::fstream fs ("input1.txt");
	Podrazdelenie IU8("Podrazdelenie for test");
	bool flag = false;
	std::cout << "Hello! \nStart working with Podrazdelenie IU8:\n";
	while(!flag) {
		std::cout << "Operating mode:\n"
				  << "1: Adding new Sotrudnik to Podrazdelenie\n"
				  << "2: Sotrudnik search\n"
				  << "3: Editing Sotrudnik data\n"
				  << "4: Remove Sotrudnik\n"
				  << "5: Output Podrazdelenie to file\n"
				  << "6: Input Podrazdelenie from file\n"
				  << "7: Output Sotrudniks to console\n"
				  << "8: Exit\n"
				  << "Enter mode: ";
		unsigned int rezh;
		std::cin >> rezh;
		std::cin.ignore(32767, '\n');
		switch (rezh) {
			case 1: {
				Sotrudnik A;
//                std::cout<< "Enter Sotrudnik:\n ("
				try {
					std::cin >> A;
					IU8.addSotrudnik(A);
				}
				catch (SotrudnikError & Error){
					Error.print();
				}
				break;
			}
			case 2: {
				unsigned int k;
				std::cout << "Search parameters:\n"
						  << "1: Firstname\n"
						  << "2: Secondname\n"
						  << "3: Patronimic\n"
						  << "4: Mark for subject\n"
						  << "Enter parameter: ";
				std::cin >> k;
				switch (k) {
					case 1: {
						std::string data;
						std::cout << "Enter Firstname: ";
						std::cin.ignore(32767, '\n');
						std::getline(std::cin, data);
						IU8.findi(std::cout, data);
						break;
					}
					case 2: {
						std::string data;
						std::cout << "Enter Secondname: ";
						std::cin.ignore(32767, '\n');
						std::getline(std::cin, data);
						IU8.findf(std::cout, data);
						break;
					}
					case 3: {
						std::string data;
						std::cout << "Enter Patronimic: ";
						std::cin.ignore(32767, '\n');
						std::getline(std::cin, data);
						IU8.findo(std::cout, data);
						break;
					}
					case 4: {
						std::string data;
						unsigned int datamark;
						std::cout << "Enter Subject: ";
						std::cin.ignore(32767, '\n');
						std::getline(std::cin, data);
						std::cout << "Enter mark: ";
						std::cin >> datamark;
						IU8.findmark(std::cout, data, datamark);
						break;
					}
				}
				break;
			}
			case 3: {
				unsigned int k;
				int numberinlist;
				std::cout << IU8;
				std::cout << "Enter the Sotrudnik number from the list: ";
				std::cin >> numberinlist;
				std::cout << "Select a field to edit:\n";
				std::cout << "1: Firstname\n"
						  << "2: Secondname\n"
						  << "3: Patronimic\n"
						  << "4: Mark for subject\n"
						  << "Select a field to edit: ";
				std::cin >> k;
				std::cin.ignore(32767, '\n');
				switch (k) {
					case 1: {
						std::string data;
						std::cout << "Enter new firstname: ";
						std::getline(std::cin, data);
						IU8.changefirstname(data, numberinlist);
						break;
					}
					case 2: {
						std::string data;
						std::cout << "Enter new secondname: ";
						std::getline(std::cin, data);
						IU8.changesecondname(data, numberinlist);
						break;
					}
					case 3: {
						std::string data;
						std::cout << "Enter new patronimic: ";
						std::getline(std::cin, data);
						IU8.changepatronymic(data, numberinlist);
						break;
					}
					case 4: {
						std::string data;
						unsigned int datamark;
						std::cout << "Enter subject: ";
						std::getline(std::cin, data);
						std::cout << "Enter new mark: ";
						std::cin >> datamark;
						IU8.changemark(data, datamark, numberinlist);
					}
				}
				break;
			}
			case 4: {
				int numberinlist;
				std::cout << IU8;
				std::cout << "Enter the Sotrudnik number from the list: ";
				std::cin >> numberinlist;
				std::thread th (&Podrazdelenie::deleteSotrudnik, std::ref(IU8), std::ref(numberinlist));
				th.join();
				break;
			}
			case 5: {
				std::cout << "Enter filename to output (format: *name*.txt):\n";
				std::string fileName;
				std::cin >> fileName;
				std::fstream os(fileName.c_str());
				std::thread th(&Podrazdelenie::outToFile, std::ref(IU8), std::ref(os));
				th.join();
				break;
			}
			case 6: {
				std::cout << "Enter filename to input (format: *name*.txt):\n";
				std::string fileName;
				std::cin >> fileName;
				std::fstream is(fileName.c_str());
				std::thread th(&Podrazdelenie::inFromFile, std::ref(IU8), std::ref(is));
				th.join();
				break;
			}
			case 7: {
				IU8.printSotrudniks();
				break;
			}
			case 8:{
				flag = true;
				break;
			}
		}
	}
}
