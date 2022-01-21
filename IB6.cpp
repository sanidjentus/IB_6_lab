#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int usersAmount = 3; //кол-во пользователей (субъектов)
const int objectsAmount = 3; //кол-во объектов доступа

class Programm {
public:
	int userID;
	int userToID; //передать права userTO
	int objectID;
	int rightDoID; //ID выполняемого права
	int rightGiveID; //ID передаваемого права
	int closeID; //id в конце

	string rightsMatrix[usersAmount][objectsAmount];
	string Users[usersAmount] = { "Admin", "Alex", "Max" };
	string Rights[5] = { "ban", "read", "write", "transfer", "full" };
	string Objects[objectsAmount] = { "object1", "object2", "object3" };

	void fillMatrix() {
		int countRights;
		cout << "Пользователи и их права:\n";
		for (int i = 0; i < usersAmount; i++) {
			cout << endl << Users[i] << " " << endl;
			for (int j = 0; j < objectsAmount; j++) {
				if (i == 0) {
					rightsMatrix[0][j] = Rights[4]; //полные права админу
					cout << Objects[j] << ": " << rightsMatrix[i][j];
					cout << endl;
				}
				else {
					countRights = rand() % 5;

					//нет прав
					if (countRights == 0) {
						rightsMatrix[i][j] = Rights[countRights];
						cout << Objects[j] << ": " << rightsMatrix[i][j] << endl;
					}

					//чтение или запись или передача прав
					if (countRights == 1) {
						int randIndex = rand() % 2 + 1;
						rightsMatrix[i][j] = Rights[randIndex];
						cout << Objects[j] << ": " << rightsMatrix[i][j] << endl;
					}

					//чтение и запись
					if (countRights == 2) {
						rightsMatrix[i][j] = Rights[1];
						rightsMatrix[i][j] = " ";
						rightsMatrix[i][j] = Rights[2];
						cout << Objects[j] << ": " << rightsMatrix[i][j] << endl;
					}

					//чтение и передача прав
					if (countRights == 3) {
						rightsMatrix[i][j] = Rights[1];
						rightsMatrix[i][j] = " ";
						rightsMatrix[i][j] = Rights[3];
						cout << Objects[j] << ": " << rightsMatrix[i][j] << endl;
					}

					//запись и передача прав
					if (countRights == 4) {
						rightsMatrix[i][j] = Rights[2];
						rightsMatrix[i][j] = " ";
						rightsMatrix[i][j] = Rights[3];
						cout << Objects[j] << ": " << rightsMatrix[i][j] << endl;
					}
				}
			}
		}
	}

	int logIn() {

	tryAgain:
		cout << "Введиите ID пользователя:\n(0 - Admin, 1 - Alex, 2 - Max)\n";
		//int inputUserId;
		cin >> userID;
		//userID = inputUserId;
		if (userID >= 0 && userID < usersAmount) {
			cout << "\nВход выполнен. ";
			cout << "\nПользователь: " << Users[userID];
			cout << "\nПрава пользователя:\n";
			for (int i = 0; i < objectsAmount; i++) {
				cout << Objects[i] << ": " << rightsMatrix[userID][i] << endl;
			}
		}
		else {
			cout << "Неправильный ID пользователя\n";
			goto tryAgain;
		}
		return userID;
	}

	void logOut(int userID) {
		cout << "\nВы действительно хотите выйти?\nДа - Введите ID пользователя\nНет - введите любое число";
		cin >> closeID;
		if (closeID == userID)
			cout << "\nВыход выполнен успешно.";
		else {
			cout << "\nВы остались в системе.";
			work();
		}
	}

	void work() {
		cout << endl << endl;
		cout << "Введите ID объекта, над которым проводится операция:" << endl;
		cout << "0 - object1, 1 - object2, 2 - object3" << endl;

		//int objInputID;
		cin >> objectID;
		//objectID = objInputID;
		if (objectID >= 0 && objectID < objectsAmount) {
			cout << "\nВведите ID выполняемого права:" << endl;
			cout << "0 - чтение, 1 - запись, 2 - передача прав" << endl;
			//int rightDoInputID;
			cin >> rightDoID;
			//rightDoID = rightDoInputID;
			if (rightDoID >= 0 && rightDoID < 3 && (rightsMatrix[userID][objectID] != "ban")) {
				//чтение
				if (rightDoID == 0) {
					if (rightsMatrix[userID][objectID] == "read" || rightsMatrix[userID][objectID] == "full") {
						cout << endl << Objects[objectID] << " прочитан\n";
					}
					else
						cout << endl << "У вас нет прав\n";
				}

				//запись
				if (rightDoID == 1) {
					if (rightsMatrix[userID][objectID] == "write" || rightsMatrix[userID][objectID] == "full") {
						cout << endl << "Запись в " << Objects[objectID] << " выполнена\n";
					}
					else
						cout << endl << "У вас нет прав\n";
				}

				//передача прав
				if (rightDoID == 2) {
					if (rightsMatrix[userID][objectID] == "transfer" || rightsMatrix[userID][objectID] == "full") {
						cout << "\nВведите ID передаваемого права\n";
						cout << "0 - чтение, 1 - запись, 2 - полные права\n";
						//int rightGiveIdInput;
						cin >> rightGiveID;
						//rightGiveID = rightGiveIdInput;
						if (rightGiveID >= 0 && rightGiveID < 3) {
							cout << "\nВведите ID пользователя, которому нужно передать права\n";
							//int userToInp;
							cin >> userToID;
							//userToID = userToInp;
							if (userToID >= 0 && userToID < 3) {
								//передача права чтения
								if (rightGiveID == 0) {
									if (rightsMatrix[userToID][rightGiveID] == "write" && rightsMatrix[userToID][rightGiveID] != "read") {
										rightsMatrix[userToID][rightGiveID] += "+ read";
										cout << "\nПраво чтения передано успешно\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "read") {
										cout << "\nУ данного пользователя есть право чтения на этот объект\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "ban") {
										rightsMatrix[userToID][rightGiveID] += "read";
										cout << "\nПраво чтения передано успешно\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "full") {
										cout << "\nУ пользователя полные права на этот объект\n";
										return;
									}

								}

								//передача права записи
								if (rightGiveID == 1) {
									if (rightsMatrix[userToID][rightGiveID] != "write" && rightsMatrix[userToID][rightGiveID] == "read" && rightsMatrix[userToID][rightGiveID] != "full" && rightsMatrix[userToID][rightGiveID] != "ban") {
										rightsMatrix[userToID][rightGiveID] += "+ write";
										cout << "\nПраво записи передано успешно\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "write") {
										cout << "\nУ данного пользователя есть право записи на этот объект\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "ban") {
										rightsMatrix[userToID][rightGiveID] += "read";
										cout << "\nПраво чтения передано успешно\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "full") {
										cout << "\nУ пользователя полные права на этот объект\n";
										return;
									}

								}

								//передача полных прав
								if (rightGiveID == 2) {
									if (rightsMatrix[userToID][rightGiveID] != "full") {
										rightsMatrix[userToID][rightGiveID] = "full";
										cout << "\nПолные права переданы успешно\n";
										return;
									}
									if (rightsMatrix[userToID][rightGiveID] == "full") {
										cout << "\nУ пользователя полные права на этот объект\n";
										return;
									}

								}

							}
							else cout << "\nНеверный ID\n";
						}
						else cout << "\nНеверный ID\n";
					}
					else cout << "\nУ вас нет прав\n";
				}
			}
			else cout << "\nНеверный ID или у вас нет прав\n";
		}
		else cout << "\nНеверный ID\n";
		logOut(userID);
	}

	void runProgramm() {
		userID = logIn();
		while (userID != closeID) {
			work();
		}
	}

};

int main() {
	srand(time(NULL));
	setlocale(0, "");

	Programm prog;
	prog.fillMatrix();
	prog.runProgramm();
	return 0;

}