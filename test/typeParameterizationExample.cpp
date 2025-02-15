#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Types;

class ITempSensor{
    public:
    virtual int getOutSideTemp()=0;
};
class ModelATempSensor:public ITempSensor{
    public:
    int getOutSideTemp(){ return  23;}
};
class ModelBTempSensor:public ITempSensor{
    public:
    int getOutSideTemp(){ return  23;}
};
class AutoTempRegulator{
    ITempSensor* tempSensorPtr;
    public:
    AutoTempRegulator(ITempSensor* address):tempSensorPtr{address} {}
    void  regulateTemp(){
         this->tempSensorPtr->getOutSideTemp();
    }  
};

template <typename T>
ITempSensor* createObject();
template <>
ITempSensor* createObject<ModelATempSensor>() { return new ModelATempSensor(); }
template <>
ITempSensor* createObject<ModelBTempSensor>() { return new ModelBTempSensor(); }

template <typename T>
class TempSensorFixture:public testing::Test{
    protected:
    TempSensorFixture():objUnderTest{ createObject<T>()}{}
    //arrange
    ITempSensor* objUnderTest;

};

typedef Types<ModelATempSensor,ModelBTempSensor> Implementations;

TYPED_TEST_SUITE(TempSensorFixture, Implementations);

TYPED_TEST(TempSensorFixture,GetTempTest){
    ASSERT_EQ(this->objUnderTest->getOutSideTemp(),23);
}

class FakeTempSensor:public ITempSensor{
    

     public:
     int getOutSideTempCallCount=0;
     int getOutSideTemp(){ getOutSideTempCallCount+=1; return  0;}

};

TEST(AutoTempRegulatorTestSuite,RegulateTempInteractionTest){
    FakeTempSensor mockObj;
    AutoTempRegulator codeUnderTest(&mockObj);
    codeUnderTest.regulateTemp();
    ASSERT_EQ(mockObj.getOutSideTempCallCount,1);

    
}
