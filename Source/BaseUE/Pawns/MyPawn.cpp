// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


// 创建一个 Pawn 类
AMyPawn::AMyPawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 👇初始化一个 Pawn 类： 蓝图类里边的组件结构 (RootComponent -> MyStaticMesh) ———————————————————————————————————————————————————————————————————
	// 【一】创建默认根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); // CreateDefaultSubobject：创建默认子对象, USenceComponent：场景组件作为根组件

	// 【二】创建 UStaticMeshComponent
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));

	// 【三】将创建好的 UStaticMeshComponent 挂载到【根组件】上, -> 为访问类里边的成员变量
	MyStaticMesh -> SetupAttachment(GetRootComponent()); // SetupAttachment：挂载到根组件上, -> 表示指针调用方法, GetRootComponent 会返回 RootComponent


	// 👇初始化摄像机 ———————————————————————————————————————————————————————————————————
	// 【一】创建摄像机
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));

	// 【二】将摄像机挂载到根组件上
	MyCamera -> SetupAttachment(GetRootComponent()); // GetRootComponent 会返回 RootComponent

	// 【三】设置相机跟 Pawn 类的相对位置 （让摄像机跟随主体物跑）
	MyCamera -> SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f)); //相对于父组件的位置, 父组件为 SetupAttachment 的那个对象, 也就是 RootComponent, 一开始是 0,0,0, 但是摄像机要拉远一点, 因此设置为 FVector(-300.0f, 0.0f, 300.0f)
	MyCamera -> SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// 【四】将摄像机设置为默认的玩家控制器 player0 为默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// AMyPawn 的键盘输入事件
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 👇将键盘输入事件跟轴事件进行绑定绑定！ ———————————————————————————————————————————————————————————————————
	PlayerInputComponent.BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward) //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
	PlayerInputComponent.BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight) //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
}


// 👇 处理轴事件（在 AMyPawn::SetupPlayerInputComponent 内将键盘输入跟轴事件绑定后, 👇下面具体实现用键盘来控制物体）=> 具体实现 ———————————————————————————————————————————————————————————————————
void AMyPawn::MoveForward(float value) {
	
}

void AMyPawn::MoveRight(float value) {

}
