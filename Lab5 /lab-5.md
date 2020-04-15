ИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе № 5 <br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(1)
Мирончук Александры Алексеевны
направления подготовки 09.03.04 "Программная инженерия" 
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019
***
#### Тема: Работа с текстовыми файлами

### Цель: 

*Научиться работать с текстовыми файлами;

*Закрепить навыки работы со структурами.

1. Для начала из определенного репозитория из папки data был скачан файл train.csv.
 
 ![Рисунок номер1](https://sun9-24.userapi.com/c856032/v856032266/21f433/tZECAxbyAdc.jpg)
 
 (Рис.1 Скачанный репозиторий) 
 
2. Далее для выполнения задания был реализован код :

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int main()
{
	setlocale(LC_ALL, "RUS");
	struct data {
	int	passengerId;
	bool survival;
	int	pclass;
	string	name;
	string	sex;
	double age;
	int	sibsp; //кол-во братьев и сестер/супругов
	int	parch;//кол-во родителей, детей
	string	ticket;
	double	fare;//плата
	string	cabin;
	char	embarked;//штат 
	};
	vector<data>datav;

	ifstream read;
	read.open("train.csv");
	//vector<string>str;
	read.seekg(80);
	int i = 0;
	while (!read.eof()) {
		datav.push_back(data());
		string str2;
		getline(read, str2, '\r');
		int l = str2.length();//длина строки
		int pozi = 0;
		bool change = true;
		while (pozi < l) {
			if (str2[pozi] == '"') change = !change;
			if (change) {
				if (str2[pozi] == ',') str2[pozi] = '%';
			}
			pozi++;
		}
		string split;
		stringstream stream(str2);//переводим строку в поток//чтобы не было конфликта типов
		getline(stream,split,'%');
		int Case = 0;
		while (stream) {
			stringstream info(split);
			switch (Case) {
			case 0: info >> datav[i].passengerId;
				break;
			case 1: info >> datav[i].survival;
				break;
			case 2: info >> datav[i].pclass;
				break;
			case 3: getline(info, datav[i].name);
				break;
			case 4: getline(info, datav[i].sex);
				break;
			case 5: info >> datav[i].age;
				break;
			case 6: info >> datav[i].sibsp;
				break;
			case 7: info >> datav[i].parch;
				break;
			case 8: getline(info, datav[i].ticket);
				break;
			case 9: info >> datav[i].fare;
				break;
			case 10: getline(info, datav[i].cabin);
				break;
			case 11: info >> datav[i].embarked;
				break;
			}
			Case++;
			getline(stream, split, '%');
		}
		i++;
	}
	int vse = 0, vse1 = 0, vse2 = 0, vse3 = 0, women = 0, men = 0, C=0, Q=0, S=0;
	double mid = 0, mid_women = 0, mid_men = 0, summ=0, count = 0, countW = 0, countM = 0, summW=0, summM=0;
	string stat;
	vector<double>kids;
	for (int k = 0; k < i; k++) {
		if (datav[k].survival) {
			vse++;
			if (datav[k].pclass == 1) vse1++;
			if (datav[k].pclass == 2) vse2++;
			if (datav[k].pclass == 3) vse3++;
			if (datav[k].sex == "male") men++;
			if (datav[k].sex == "female") women++;
		}
		if (datav[k].age) {
			count++;
			summ = datav[k].age+summ;
			if (datav[k].sex=="male") {
				summM = summM + datav[k].age;
				countM++;
			}
			else if (datav[k].sex == "female") {
				summW = summW + datav[k].age;
				countW++;
			}
			if (datav[k].age < 18) kids.push_back(datav[k].passengerId);
		}
		if (datav[k].embarked) {
			if (datav[k].embarked == 'S') S++;
			if (datav[k].embarked == 'C') C++;
			if (datav[k].embarked == 'Q') Q++;
		}
	}
	if (S > C && S > Q) stat = "Southampton";
	else if (C > S && C > Q) stat = "Cherbourg";
	else if (Q > S && Q > C) stat = "Queenstown";
	mid = summ / count;
	mid_women = summW / countW;
	mid_men = summM / countM;

	ofstream exitt("exit.txt");
	exitt << "Общее число выживших: " << vse << endl;
	exitt << "Выживших из первого класса: " << vse1<< endl;
	exitt << "Выживших из второго класса: " << vse2 << endl;
	exitt << "Выживших их третьего класса: " << vse3 << endl;
	exitt << "Выживших женщин: " << women<< endl;
	exitt << "Выживших мужчин: " << men << endl;
	exitt << "Средний возраст всех пассажиров: " << mid << endl;
	exitt << "Средний возраст женщин: " << mid_women << endl;
	exitt << "Средний возраст мужчин: " << mid_men << endl;
	exitt << "Штат, в котором село больше всего пассажиров: " << stat << endl;
	exitt << "Список идентификаторов несовершеннолетних пассажиров: " << kids[0];
	for (int g = 1; g < kids.size(); g++) {
		exitt << " " << kids[g];
	}
}

```
В результате программы в созданный файл exit.txt были занесены следующие значени:

![Рисунок номер1](https://sun9-32.userapi.com/c856032/v856032266/21f446/wh4CKBp1DOI.jpg)

(Рис.2 Результат программы)

Ссылка на полученный файл: https://github.com/Sasha1214/Practic/blob/master/Lab5/exit.txt

3. На основе данных была получена таблица :

| Характеристика | Результат |
| —---------— | —---------— |
|Общее число выживших: | 342 |
| Выживших из первого класса: | 136 |
| Выживших из второго класса: | 87 |
| Выживших их третьего класса: | 119 |
| Выживших женщин: | 233 |
| Выживших мужчин: | 109 |
| Средний возраст всех пассажиров: | 29.6991 |
| Средний возраст женщин: | 27.9157 |
| Средний возраст мужчин: | 30.7266 |
| Штат, в котором село больше всего пассажиров: | Southampton |

Список идентификаторов несовершеннолетних пассажиров: 8, 10, 11, 15, 17, 23, 25, 40, 44, 51, 59, 60, 64,
69, 72,79, 85, 87, 112,115, 120, 126, 139, 148, 157, 164, 165, 166, 172, 173, 183, 184, 185,194, 206, 209, 
221, 234, 238, 262, 267, 279, 283, 298, 306, 308, 330, 334, 341, 349, 353, 375, 382, 387, 390, 408, 
420, 434, 436, 446, 447, 449, 470, 480, 481, 490, 501, 505, 531, 533, 536, 542, 543, 550, 551, 575,
619, 635, 643, 645, 684, 687, 690, 692, 721, 722, 732, 747, 751, 752, 756, 765, 778, 781, 782, 788, 789,
792, 803, 804, 814, 820, 825, 828, 831, 832, 842, 845, 851, 853, 854, 870, 876 <br/>

*Вывод*: В ходе лабораторной работы я научилась работать с текстовыми файлами и закрепила навык работы со структурами.


| Характеристика  | Результат |
| ------------- | ------------- |
| Общее число выживших | 342  |
| Число выживших из 1 класса  | 136  |
| Число выживших из 2 класса  | 87  |
| Число выживших из 3 класса  | 119  |
| Количество выживших женщин  | 233  |
| Количество выживших мужчин  | 109  |
| Средний возраст пассажира  | 28.3241  |
| Средний возраст мужчин  | 27.2366  |
|Средний возраст женщин  | 28.8376  |
|Штат, в котором село больше всего пассажиров | Southampton  |





















