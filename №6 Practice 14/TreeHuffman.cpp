#include <iostream>
#include <vector>
#include <map>
#include <list>
using namespace std;

class node {
public:
    int count;
    char symbol;
    node* left;
    node* right;

    node() {}
    node(char symbol, int count) { //создание узла базового, хранящего в себе информацию о символе
        this->symbol = symbol;
        this->count = count;
    }
    node(node* left, node* right) { // создание узла при объединении двух узлов
        symbol = 0;
        this->left = left;
        this->right = right;
        count = left->count + right->count;
    }


    void print(node* root, int depth = 0)
    {
        if (!root) return;

        if (root->symbol)
        {
            for (int i = 0; i < depth; i++)
                cout << ".";
            cout << root->symbol << endl;
        }
        else depth++;
        print(root->left, depth);
        print(root->right, depth);
    }
};

void Build(node* root, vector<bool>& code, map<char, vector<bool>>& characters_codes) { //Строим словарь с парами значений символ-код. 
    if (root->left) {
        code.push_back(0);
        Build(root->left, code, characters_codes);
    }

    if (root->right) {
        code.push_back(1);
        Build(root->right, code, characters_codes);
    }

    if (root->symbol) {
        characters_codes[root->symbol] = code;
    }
    if (code.size()) {
        code.pop_back();
    }
}

bool SortSymbols(node* a, node* b) {
    return a->count < b->count;
}

int main()
{
    string input = "subbotin ivan еvgenyevich"; //Сюда вписываем строку, которую надо закодировать
    map<char, int> symbols_count;

    for (int i = 0; i < input.length(); i++) { 
        symbols_count[input[i]]++;
    } //разбиваем стартовую строку на словарь символ - кол-во вхождений

    list<node*> firstLine; //Все символы собираем в однй линию, от которой начнем строить дерево
    map<char, int>::iterator symbols_iterator;
    for (symbols_iterator = symbols_count.begin(); symbols_iterator != symbols_count.end(); symbols_iterator ++ ) {
        node* symbol_node = new node(symbols_iterator->first, symbols_iterator->second);
        firstLine.push_back(symbol_node);
    }

    while (firstLine.size() != 1) { //формируем новые узлы, пока не придем к одному. новые узлы - узлы с наименьшим количеством вхождений
        firstLine.sort(SortSymbols);

        node* left = firstLine.front();
        firstLine.pop_front();
        node* right = firstLine.front();
        firstLine.pop_front();

        node* link = new node(left, right);
        firstLine.push_back(link);
    }

    node* root = firstLine.front();
    root->print(root); //выводим глубину каждого символа. одна точка = 1 шаг в глубину

    vector<bool> code;
    map<char, vector<bool>> characters_codes;
    Build(root, code, characters_codes);

    for (symbols_iterator = symbols_count.begin(); symbols_iterator != symbols_count.end(); symbols_iterator++) //выводим коды каждого символа
    {
        cout << symbols_iterator->first << " - ";
        for (int j = 0; j < characters_codes[symbols_iterator->first].size(); j++)
            cout << characters_codes[symbols_iterator->first][j];
        cout << endl;
    }

    string out; // теперь выводим закодированную строку

    for (int i = 0; i < input.length(); i++) {
        for (int j = 0; j < characters_codes[input[i]].size(); j++)
        {
            out += characters_codes[input[i]][j] + '0';
        }
        out += " ";
    }
    cout << endl;
    cout << out.c_str() << endl;
}

