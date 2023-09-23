// Fill out your copyright notice in the Description page of Project Settings.
#include "MyActor02.h"


// 👇 用来设置 Actor 的默认值(初始值), AMyActor02 为 AMyActor02 的构造函数, 在类实例化后自动调用！
AMyActor02::AMyActor02() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 🔥【👇相当于用 C++ 写一个静态网格】对StaticMesh 赋予初始值, 生成实例化的组件
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));// 组件是 Actor 的子物体, 【🔥createDefaultSubobject 表示生成一个默认的子物体】, 【 🔥UStaticMeshComponent 表使用模板组件 】, 【 🔥TEXT("MyStaticMesh") 不是名字!! 而是一个标识】
    InitLocation = FVector(0.0f); //🔥🔥 设置 Actor 组件的 InitLocation 参数的默认值（位置） FVector(0.0f)
    PlacedLocation = FVector(0.0f); //🔥🔥 设置 Actor 组件的 InitLocation 参数的默认值（位置） FVector(0.0f)
    bGotoInitLocation = false; // 默认留在原初位置
}



// 👇游戏生成时调用, Called when the game starts or when spawned
void AMyActor02::BeginPlay() {
	Super::BeginPlay();

    // 🚩🚩 Actor (BeginPlay 出生点)的初始化位置
    PlacedLocation = GetActorLocation(); //【获取】 Actor 的出生点位置

    if(bGotoInitLocation) {
        SetActorLocation(InitLocation); //【设置】默认出生点在 0,0,0  //SetActorLocation(FVector(0.0f)); //默认出生点在 0,0,0
    }
}




// 👇每帧调用, Called every frame
void AMyActor02::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

