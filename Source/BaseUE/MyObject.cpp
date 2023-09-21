// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

UMyObject::UMyObject() //用 UMuObject 来完全限定 UMyObject()  这个函数
{
    MyFloat = 0.0f; //定义一个浮点数，然后记得在 MyObject.h 中声明 UPROPERTY(BlueprintReadWrite) , 让蓝图可以调用
}

void UMyObject::MyFunction()
{
    UE_LOG(LogTemp, Log, TEXT("你好 👋")); // UE_LOG 是 Unreal Engine 的日志系统，可以打印日志, TEXT() 是 UE 的文本宏
    UE_LOG(LogTemp, Warning,  TEXT("警告 ⚠️")); // UE_LOG 是 Unreal Engine 的日志系统，可以打印日志
    UE_LOG(LogTemp, Error,  TEXT("错误 ❌")); // UE_LOG 是 Unreal Engine 的日志系统，可以打印日志
}