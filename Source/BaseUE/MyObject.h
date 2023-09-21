// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable) // Blueprintable 表示可以被蓝图所继承
class BASEUE_API UMyObject : public UObject {
	GENERATED_BODY()

    public:
        UMyObject();

        UPROPERTY(BlueprintReadWrite, Category= "My Variables") // UPROPERTY 表示可以被蓝图所编辑, ⚡️BlueprintReadWrite 表示可以被蓝图所读写, BlueprintReadOnly 表示只读, Category= "XXX" 表示在蓝图里边加个分类
        float MyFloat;

        UFUNCTION(BlueprintCallable, Category= "My Functions") // UFUNCTION 表示可以被蓝图所编辑, ⚡️BlueprintCallable 表示可以被蓝图所调用, Category= "XXX" 表示在蓝图里边加个分类
        void MyFunction();
};
