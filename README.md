# PracticМИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РАССИЙСКОЙ ФЕДЕРАЦИИ
Федеральное государственное автономное образовательное учреждение высшего образования"
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им.Вернадского"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ 
Кафедра компьютерной инженерии и моделирования
<br / ><br / ><br/>

###Отчет по лабораторной работе №7<br/> по дисциплине "Программироание"
<бром/>

студента первого курса ПИ-б-о-191(1)
Мирончук Александры Алексеевны
направления подготовки 09.03.04 "Программная инженерия"
<бром/>

<стол>
<tr><td>Научный руководитель<br/>старший преподователь кафедры<br/>компьютерой инженерии и моделирования<br/>
<td/>(оценка)<td/>
<td/>Чабанов В.В.<ТД/>
< / tr>
</table>
<br/><br/>

Симферополь,2019


###Цель: изучить основные возможности создания и отладки программ в IDE Qt Creator.

**1.Как создать консольное приложение С++ в IDE Qt Creator без использования компонентов Qt?<br/>**
*Создание консольного приложения происходит следующим образом: Файл->Создать файл или проект->Консольное приложение без QT*

![Рисунок номер1](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)


**2.Как изменить цветовую схему (оформление) среды?**
*Изменение светового оформления Инструменты ->Параметры->Среда 

![Рисунок номер2](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)


**3.Как закомментировать/раскомментировать блок кода средствами Qt Creator?**
*Нажать ПКМ по строке кода и в меню появится Закомментировать/ Раскомментировать. Или же Ctrl+/.

![Рисунок номер3](https://github.com/Sasha1214/Practic/blob/master/scr-7/-rT8zQ439Gc.jpg?raw=true)


**4.Как открыть в проводнике Windows папку с проектом средствами Qt Creator?**
*ПКМ кликнуть по файлу с расширением .pro и выбрать в меню Окрыть в проводнике**

![Рисунок номер4](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)


**5.Какое расширение файла-проекта используется Qt Creator?**
*Файд-проект имеет расширение .pro*

![Рисунок номер5](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)



**6.Как запустить код без отладки?**
*Сборка->Запустить или ctrl+r*

![Рисунок номер6](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)


**7.Как запустить код в режиме отладки?**
*Отладка>Начать*

![Рисунок номер7](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)

**8.Как установить/убрать точку останова (breakpoint)?**
*Для того чтобы поставить точка отстанова нужно кликнуть напротив номера строки*

![Рисунок номер8](https://raw.githubusercontent.com/Sasha1214/repository/master/img/5.png)

**9.Бла создана программа со следующим кодом:
```СРР
#include <iostream>
int main() {
 int i;
 двойной d;
 i = 5;
 d = 5;
 std:: cout << i <;
 возврат 0;
}
```
Были выполнены следующие действия:
*Переключитесь в конфигурацию сборки «Отладка»;
*Установите breakpoint на 5, 6 и 7 строках;


**10.Закройте проект и перейдите на вкладку «Начало» => «Примеры»;**
**11.Выберите проект «Calculator Form Example». Для этого можно воспользоваться строкой поиска;**
**12.Изучите (по желанию) описание проекта в открывшемся окне;**
**13.Сейчас вы находитесь на вкладке «Проекты». Выберите комплект сборки.**
**14.Перейдите на вкладку «Редактор» и запустите сборку проекта;**
**15.В инспекторе проекта выберите файл «main.СРР».
В этом файле установите курсор на слово «show» в строке calculator.show(); и нажмите F1.
Изучите справочную информацию. Таким же образом можно получить справку по любому объекту/методу/полю доступному в Qt;**
**16.В инспекторе проекта выберите файл «Формы» => «calculatorform.ui» и дважды счёлкните ЛКМ;**
**17.Вы попали на вкладку «Дизайн». На форме замените английский текст на русский. Пересоберите проект**
