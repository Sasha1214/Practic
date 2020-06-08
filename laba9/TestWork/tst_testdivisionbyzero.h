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






