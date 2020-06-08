Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе № 6 <br/> по дисциплине "Программирование"
<br/>

студента первого курса ПИ-б-о-191(1)
Мирончук Александры Алексеевны
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/>старший преподователь кафедры<br/>компьютерой инженерии и моделирования<br/>
<td/>(оценка)<td/>
<td/>Чабанов В.В.<td/>
</tr>
</table>
<br/><br/>

Симферополь,2019

***
#### Цель:
*Закрепить навыки разработки многофайловыx приложений;

*Изучить способы работы с API web-сервиса;

*Изучить процесс сериализации/десериализации данных.

1. Подготовка серверной части. Проверка кода на работоспособность.
 
   ![Рисунок номер1](https://sun3.43222.userapi.com/rM5_STcMR7UIJDEkJMBm5C7JGeUqzcXmlfa64g/DYT6flXfuLM.jpg)

   *(Рис.1 Работоспособность программы)*

2. Подготовка к работе с сервисом openweathermap.org.
   Текст в формате JSON.

![Рисунок номер1](https://sun3.43222.userapi.com/q_vdakrD_nwi2l5zJFEYEgpMl7hwpRygFQn32w/wglxj7b_E_g.jpg)

*(Рис.2 Ответ сервиса openweathermap.org)*

3. Подготовка клиента для получения информации от openweathermap.org.

![Рисунок номер1](https://sun2.43222.userapi.com/mWC2r9Pmt62m-2NeIqx7NEnevkDmZO_LHkrjsQ/FkOTO2elJzM.jpg)

*(Рис.3 Код клиента)*

https://sun1.43222.userapi.com/pP-q4exoBqYYhUFP5lRFyIAE9g2E8AVghAcuYw/Bo9_p-x-pA4.jpg

4. Сборка итогового проекта. Код программы:
   
  ```cpp
  #include <httplib/httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool Replace(std::string &box, std::string find, std::string replaceable) {
	int value = box.find(find);
	if (value != -1) {
		box.replace(value, find.length(), replaceable);
		return true;
	}
	else return false;
}

std::string convert_double(double x) {
	std::stringstream wew;
	wew.precision(2);
	wew << std::fixed << x;
	return wew.str();
}

using namespace httplib;
void gen_response(const Request& req, Response& res) {
	char a[] = "api.openweathermap.org";
	char query[] = "/data/2.5/forecast?id=694423&APPID=a067723d6baa017766cb420fcf8c4fad&mode=json&units=metric";
	// IMPORTANT: 1st parameter must be a hostname or an IP adress string.
	httplib::Client cli(a, 80);

	auto info = cli.Get(query);
	if (info && info->status == 200) {
		nlohmann::json zap = nlohmann::json::parse(info->body);
		std::ifstream informer_template("informer_template.html");
		std::string nameCity = zap["city"]["name"];
		std::vector<std::string>date;
		std::vector<std::string>icon;
		std::vector<std::string>temperature;
		std::string last_date;
		for (int i = 0; i < zap["cnt"];i++) {
			std::string temp_date = zap["list"][i]["dt_txt"];
			temp_date = temp_date.substr(0, temp_date.find(' '));
			if (temp_date != last_date) {
				std::string temp_icon = zap["list"][i]["weather"][0]["icon"];
				std::string temp_temperature = convert_double(zap["list"][i]["main"]["temp"]);
				date.push_back(temp_date);
				icon.push_back(temp_icon);
				temperature.push_back(temp_temperature);
				last_date = temp_date;
			}
		}
		std::string box;
		std::string result="";
		int it1=0, it2=0, it3=0;
		while (std::getline(informer_template, box)) {
			Replace(box, "{city.name}", nameCity);
			if (Replace(box, "{list.dt}", date[it1])) it1++;
			if (Replace(box, "{list.weather.icon}", icon[it2])) it2++;
			if (Replace(box, "{list.main.temp}", temperature[it3])) it3++;
			result += box + '\n';
		}
		res.set_content(result, "text/html");
	}
}


	int main(void){
	Server svr;                    // Создаём сервер (пока-что не запущен)
	svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 1234
}
```
Для просмотра погоды я выбрала свой город:

![Рисунок номер1](https://sun1.43222.userapi.com/pP-q4exoBqYYhUFP5lRFyIAE9g2E8AVghAcuYw/Bo9_p-x-pA4.jpg)

(Рис.3 Информация о запрашиваемом городе)

![Рисунок номер1](https://sun2.43222.userapi.com/juf6JNa0f9bfSln0yWrSkugkckc8WfBcdvkCYw/_ZOtFcoCMo4.jpg)

(Рис.4 Заполненный виджет)

Мой  API ключ от openweathermap.org:``` a067723d6baa017766cb420fcf8c4fad```

### Вывод: в ходе лабораторной работы были изучены способы работы с API web-сервиса, также изучен процесс сериализации/десериализации данных.

