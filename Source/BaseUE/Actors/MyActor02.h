// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor02.generated.h"

UCLASS()
class BASEUE_API AMyActor02 : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyActor02();

    // 👇记得在声明完后都需要在 .cpp 内赋予初始值！！
    UPROPERTY(VisibleAnywhere, Category="My Actor Components") //UPROPERTY() 表示参与到蓝图的反射系统中, 让蓝图可以编辑, 🔥🔥 组件一般就给 VisibleAnywhere, 让编辑器外也可以看见！！
    UStaticMeshComponent* StaticMesh;//U 开头是继承 Object 类型, 因为 StaticMesh 不是一个基本类型, 所以用指针 *是一个指针

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
