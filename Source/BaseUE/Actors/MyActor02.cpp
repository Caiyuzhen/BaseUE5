// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor02.h"

// Sets default values
AMyActor02::AMyActor02() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 🔥【👇相当于用 C++ 写一个静态网格】对StaticMesh 赋予初始值, 生成实例化的组件
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));// 组件是 Actor 的子物体, 【🔥createDefaultSubobject 表示生成一个默认的子物体】, 【 🔥UStaticMeshComponent 表使用模板组件 】, 【 🔥TEXT("MyStaticMesh") 不是名字!! 而是一个标识】
}

// 👇游戏生成时调用, Called when the game starts or when spawned
void AMyActor02::BeginPlay() {
	Super::BeginPlay();
	
}

// 👇每帧调用, Called every frame
void AMyActor02::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

