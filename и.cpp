﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <cctype>

using namespace std;


bool isVowel(char c) {
    c = tolower(c);
    return (c == 'а' || c == 'е' || c == 'ё' || c == 'и' || c == 'о' ||
        c == 'у' || c == 'ы' || c == 'э' || c == 'ю' || c == 'я');
}


bool isConsonant(char c) {
    c = tolower(c);
    return (c >= 'а' && c <= 'я' && !isVowel(c) && c != 'ь' && c != 'ъ');
}


bool isPunctuation(char c) {
    return ispunct(c) || c == '—' || c == '«' || c == '»';
}

int main() {

    {
        setlocale(LC_ALL, "RU");
        cout << "Введите целые числа через пробел: ";
        cin.ignore();
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<int> numbers;
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        sort(numbers.begin(), numbers.end());
        cout << "Отсортированный массив: ";
        for (int n : numbers) {
            cout << n << " ";
        }
        cout << endl;
    }


    {

        cout << "Введите строку: ";
        string text;
        getline(cin, text);

        int vowels = 0, consonants = 0;
        for (char c : text) {
            if (isVowel(c)) vowels++;
            else if (isConsonant(c)) consonants++;
        }
        cout << "Гласных: " << vowels << ", Согласных: " << consonants << endl;
    }




    {

        cout << "Введите число: ";
        int n;
        cin >> n;
        cout << "Таблица умножения для " << n << ":" << endl;
        for (int i = 1; i <= 10; ++i) {
            cout << setw(2) << right << n << " × " << setw(2) << i << " = " << setw(3) << n * i << endl;
        }
        cin.ignore();
    }


    {

        cout << "Введите имя файла: ";
        string filename;
        getline(cin, filename);
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла!" << endl;
        }
        else {
            int lines = 0, words = 0, chars = 0;
            string line;
            while (getline(file, line)) {
                lines++;
                chars += line.length() + 1;
                istringstream iss(line);
                string word;
                while (iss >> word) words++;
            }
            cout << "Строк: " << lines << "\nСлов: " << words << "\nСимволов: " << chars << endl;
        }
    }

    {

        cout << "Введите имя файла: ";
        string filename;
        getline(cin, filename);
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла!" << endl;
        }
        else {
            set<string> uniqueWords;
            string word;
            while (file >> word) {

                word.erase(remove_if(word.begin(), word.end(), isPunctuation), word.end());
                if (!word.empty()) {
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    uniqueWords.insert(word);
                }
            }
            cout << "Уникальные слова (" << uniqueWords.size() << "):" << endl;
            for (const string& w : uniqueWords) {
                cout << "• " << left << setw(20) << w << "•" << endl;
            }
        }
    }





    {

        cout << "Введите строки (для завершения введите пустую строку):" << endl;
        vector<string> lines;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            lines.push_back(line);
        }
        if (!lines.empty()) {
            size_t max_len = max_element(lines.begin(), lines.end(),
                [](const string& a, const string& b) { return a.length() < b.length(); })->length();

            cout << "┌" << string(max_len + 2, '─') << "┐" << endl;
            for (const string& s : lines) {
                cout << "│ " << setw(max_len) << right << s << " │" << endl;
            }
            cout << "└" << string(max_len + 2, '─') << "┘" << endl;
        }
    }


    cout << "Введите числа через пробел: ";
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> numbers;
    int num;
    while (iss >> num) {
        numbers.push_back(num);
    }

    if (!numbers.empty()) {

        double avg = accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();


        sort(numbers.begin(), numbers.end());
        double median = numbers.size() % 2 ? numbers[numbers.size() / 2] :
            (numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2]) / 2.0;


        map<int, int> freq;
        for (int n : numbers) freq[n]++;
        auto mode = max_element(freq.begin(), freq.end(),
            [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; });

        cout << fixed << setprecision(2);
        cout << "Среднее: " << avg << endl;
        cout << "Медиана: " << median << endl;
        cout << "Мода: " << mode->first << " (встречается " << mode->second << " раз)" << endl;
    }
}

