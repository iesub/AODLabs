#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//В txt файле использовать латинницу

struct user { //Структура с полями по заданию
    string name;
    string adress;
    string number;
};

vector<user*> convertToStruct(ifstream& fileOut, vector<user*> userlist) { //Данные из файла txt заносятся в вектор структур
    int i = -1;                                                            //формат записи как в примере file.txt
    while (!fileOut.eof()) {
        string line;
        getline(fileOut, line);
        int point = line.find("-");
        if (line.substr(0, point) == "User") { 
            i++; 
            user* buff = new user; 
            userlist.push_back(buff); 
        }
        else if (line.substr(0, point) == "CardNumber") { 
        line = line.substr(point + 1, line.length()); 
        userlist[i]->number = line; 
        }
        else if (line.substr(0, point) == "Name") { 
            userlist[i]->name = line.substr(point + 1, line.length()); 
        }
        else if (line.substr(0, point) == "Adress") { 
            userlist[i]->adress = line.substr(point + 1, line.length()); 
        }
    }
    return(userlist);
}

void convertToBinary( vector<user*> userlist) { //Записываем объекты из вектора в бинарный файл
    ofstream fileIn("binary.bin", ios::binary);
    for (int i = 0; i < userlist.size(); i++) {
        user* buff = userlist[i];
        fileIn.write((char*)&buff, sizeof(buff));
    }
    fileIn.close();
}

vector<user*> getFromBin(vector<user*> userlist) { //Выписываем файлы из бинарного файла в вектор структур
    ifstream file_Out("binary.bin", ios::binary);
    userlist.clear();
    while (!file_Out.eof()) {
        user* buff = new user;
        file_Out.read((char*)&buff, sizeof(buff));
        if (buff->name != "") {
            userlist.push_back(buff);
        }
    }
    file_Out.close();
    return(userlist);
}

user* findByName(vector<user*> userlist, string key) { //Поиск по имени
    for (int i = 0; i < userlist.size(); i++) {
        if (userlist[i]->name == key) return(userlist[i]);
    }
}

user* findByAdress(vector<user*> userlist, string key) { //Поиск по адресу
    for (int i = 0; i < userlist.size(); i++) {
        if (userlist[i]->adress == key) return(userlist[i]);
    }
}

user* findByCardNumber(vector<user*> userlist, string key) { //Поиск по номеру
    for (int i = 0; i < userlist.size(); i++) {
        if (userlist[i]->number == key) return(userlist[i]);
    }
}

void showEl(string key, string type, vector<user*> userlist) { //Выводит данные о пользователе с заданным ключом(надо указать тип ключа: имя, адрес, номер)
    user* buff;
    if (type == "name") buff = findByName(userlist, key);
    else if (type == "adress") buff = findByAdress(userlist, key);
    else if (type == "card") buff = findByCardNumber(userlist, key);
    else { cout << "There is not such an element" << endl; return; }
    cout << "Name: " << buff->name << " Adress: " << buff->adress << "Card Number: " << buff->number << endl;
}

vector<user*> deleteElement(string key, string type ,vector<user*> userlist) { //Удаляет данные о пользователе с заданным ключом(надо указать тип ключа: имя, адрес, номер)
    user* buff;
    if (type == "name") buff = findByName(userlist, key);
    else if (type == "adress") buff = findByAdress(userlist, key);
    else if (type == "card") buff = findByCardNumber(userlist, key);
    else return(userlist);
    auto it =  find(userlist.begin(), userlist.end(), buff);
    userlist.erase(it);
    convertToBinary(userlist);
    return(userlist);
}

int main()
{
    ifstream fileOut("file.txt");
    vector<user*> userlist;
    userlist = convertToStruct(fileOut, userlist);
    fileOut.close();
    convertToBinary(userlist);
    userlist = getFromBin(userlist);
    showEl("12345", "card", userlist);
    userlist = deleteElement("12345", "card", userlist);
    userlist = getFromBin(userlist);
}
