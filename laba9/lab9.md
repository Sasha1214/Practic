Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>


### Отчёт по лабораторной работе № 9 <br/> по дисциплине "Программирование"
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
##### Тема:Тестирование при помощи Google Test Framework
#### Цель: 
*Познакомиться с Google Test и Google Mock Framework;

*Изучить базовые понятия относящийся к тестированию кода;

*Научиться тестировать классы в среде разработки Qt Creator.

1. Запуск начального проекта: 

![Рисунок номер5](https://sun2.43222.userapi.com/vt10olEAMU84jHdt7e9GMdRhJWQeHOMZ5xHNkg/L-nvzHwHY80.jpg)

*(Рис.1 Консоль начального приложения)*

Реализованные тесты:

```cpp
#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

struct MockIKeypad:IKeypad{
     MOCK_METHOD(bool, isActive, (), (override));
     MOCK_METHOD(void, wait, (), (override));
     MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};

struct MockILatch:ILatch{
     MOCK_METHOD(bool,isActive, (), (override));
     MOCK_METHOD(DoorStatus, open, (), (override));
     MOCK_METHOD(DoorStatus, close,(), (override));
     MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};

class  Fixture: public ::testing::Test{
public:
    LockController* lock;
    MockIKeypad key;
    MockILatch latch;
    void SetUp() override{
        lock = new LockController(&key, &latch);
    }
    void TearDown() override{
        delete lock;
    }

};
TEST_F(Fixture, TEST_1){
   EXPECT_CALL(key, wait).Times(1);
    lock->wait();
}

TEST_F(Fixture, TEST_2){
    EXPECT_CALL(latch, getDoorStatus).Times(1).WillOnce(Return(DoorStatus::CLOSE));
    bool a = lock->isDoorOpen();
    EXPECT_FALSE(a);
}

TEST_F(Fixture, TEST_3){
    EXPECT_CALL(latch, getDoorStatus).Times(1).WillOnce(Return(DoorStatus::OPEN));
    bool a = lock->isDoorOpen();
    EXPECT_TRUE(a);
}

TEST_F(Fixture, TEST_4){
    EXPECT_CALL(latch, open).Times(1).WillOnce(Return(DoorStatus::OPEN));
    DoorStatus door = lock->unlockDoor();
    EXPECT_EQ(door, DoorStatus::OPEN);
}

TEST_F(Fixture, TEST_5){
    EXPECT_CALL(latch, close).Times(1).WillOnce(Return(DoorStatus::CLOSE));
    DoorStatus door = lock->unlockDoor();
    EXPECT_EQ(door, DoorStatus::CLOSE);
}

TEST_F(Fixture, TEST_6){
    EXPECT_CALL(key, isActive).Times(1).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive).Times(1).WillOnce(Return(true));
    HardWareStatus status = lock->hardWareCheck() ;
    EXPECT_EQ(status, HardWareStatus::OK );
}

TEST_F(Fixture, TEST_7){
    delete lock;
    lock = new LockController(nullptr, &latch);
    EXPECT_CALL(key, isActive).Times(AtLeast(0)).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive).Times(AtLeast(0)).WillOnce(Return(true));
    HardWareStatus status = lock->hardWareCheck() ;
    EXPECT_EQ(status, HardWareStatus::ERROR );
}

TEST_F(Fixture, TEST_8){
    EXPECT_CALL(key, isActive).Times(AtLeast(0)).WillOnce(Return(true));
    EXPECT_CALL(latch, isActive).Times(AtLeast(0)).WillOnce(Return(false));
    HardWareStatus status = lock->hardWareCheck() ;
    EXPECT_EQ(status, HardWareStatus::ERROR );
}

TEST_F(Fixture, TEST_9){
    PasswordResponse password;
    password.password = "0000";
    password.status = PasswordResponse::Status::OK;
    EXPECT_CALL(key, requestPassword ).Times(1).WillOnce(Return( password));
    bool b = lock->isCorrectPassword();
    EXPECT_TRUE(b);
}

TEST_F(Fixture, TEST_10){
    PasswordResponse password;
    password.status = PasswordResponse::Status::OK;
    password.password = "4534";
    EXPECT_CALL(key, requestPassword ).Times(1).WillOnce(Return( password));
    bool b = lock->isCorrectPassword();
    EXPECT_FALSE(b);
}

TEST_F(Fixture, TEST_11){
    PasswordResponse password1;
    PasswordResponse password2;
    PasswordResponse password3;
    password1.status = PasswordResponse::Status::OK;
    password2.status = PasswordResponse::Status::OK;
    password3.status = PasswordResponse::Status::OK;
    password1.password = "0000";
    password2.password = "7676";
    password3.password = "7676";
    EXPECT_CALL(key, requestPassword ).Times(3).WillOnce(Return(password1)).WillOnce(Return(password2)).WillOnce(Return(password3));
    lock->resetPassword();
    bool b = lock->isCorrectPassword();
    EXPECT_TRUE(b);
}

TEST_F(Fixture, TEST_12){
    PasswordResponse password1;
    PasswordResponse password2;
    PasswordResponse password3;
    PasswordResponse password4;
    PasswordResponse password5;
    password1.status = PasswordResponse::Status::OK;
    password2.status = PasswordResponse::Status::OK;
    password3.status = PasswordResponse::Status::OK;
    password4.status = PasswordResponse::Status::OK;
    password5.status = PasswordResponse::Status::OK;
    password1.password = "0000";
    password2.password = "7676";
    password3.password = "7676";
    password4.password = "9876";
    password5.password = "9876";
    EXPECT_CALL(key, requestPassword ).Times(5).WillOnce(Return(password1)).WillOnce(Return(password2)).WillOnce(Return(password3)).WillOnce(Return(password4)).WillOnce(Return(password5));
    lock->resetPassword();
    lock->resetPassword();
    bool b = lock->isCorrectPassword();
    EXPECT_TRUE(b);
}
#endif // TST_TESTDIVISIONBYZERO_H
```


Результаты тестирования:

![Рисунок номер5](https://sun3.43222.userapi.com/XUbanBwMh6fKPMQohiV_YMf8nvcD4jjzFHYW4g/p88pHX_tKyo.jpg)

(Рис.2 Пройденные тесты)

В файле lockcontroller.cpp в 45 строке содержится ошибка:

```cpp
DoorStatus LockController::lockDoor()
{
    return latch->open();
}
```
Исправленный метод:

 ```cpp
 DoorStatus LockController::lockDoor()
{
    return latch->close();
}
```
Почему могла возникунть ошибка:

Данная ошибка могла быть допущена разработчиками в ходе копирования похожих методов, чтобы не тратить время на переписывания, но из-за невнимательности, забыли изменить тело функции.

Ссылка на папку с итоговым проектом: https://github.com/Sasha1214/Practic/tree/master/laba9/TestWork

#### Вывод: в ходе лабораторной работы я познакомилась с Google Test и Google Mock Framework, изучила базовые понятия относящийся к тестированию кода, научилась тестировать классы в среде разработки Qt Creator.
