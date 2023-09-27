// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"


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
	// 【一】设置摄像机的悬臂（可以掠过障碍物）
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MySpringArm -> SetupAttachment(MyStaticMesh); // 表示把 悬臂(MySpringArm) 附着到 元素(MyStaticMesh）上
	MySpringArm -> SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 🌟RelativeRotation 是变量, 所以是赋值形式！ 表示摄像机的相对旋转, FRotator(-45.0f, 0.0f, 0.0f) 表示摄像机的旋转角度
	MySpringArm -> TargetArmLength = 400.0f; // 摄像机的长度
	MySpringArm -> bEnableCameraLag = true; // 摄像机是否开启平滑跟随
	MySpringArm -> CameraLagSpeed = 3.0f; // 摄像机平滑跟随的速度
	

	// 【二】创建摄像机
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));

	// 【三】将摄像机挂载到根组件上, GetRootComponent() 为附着到根组件 | MySpringArm 表示附着到悬臂上
	MyCamera -> SetupAttachment(MySpringArm);
	// MyCamera -> SetupAttachment(GetRootComponent()); // GetRootComponent 会返回 RootComponent

	// 【四】设置相机跟 Pawn 类的相对位置 （让摄像机跟随主体物跑） | 如果上面设置了【悬臂】, 这里就不用设置相对位置跟旋转了, 因为要【把摄像机附着到悬臂上】!
	// MyCamera -> SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f)); //相对于父组件的位置, 父组件为 SetupAttachment 的那个对象, 也就是 RootComponent, 一开始是 0,0,0, 但是摄像机要拉远一点, 因此设置为 FVector(-300.0f, 0.0f, 300.0f)
	// MyCamera -> SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 摄像机旋转 45 度, 用 FRotator

	// 【五】将摄像机设置为默认的玩家控制器 player0 为默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 👇 初始化移动的速度变量倍率、移动的偏移量, Velocity 为 .h 内定义的移动偏移量
	MaxSpeed = 100.0f;
	Velocity = FVector::ZeroVector; // 等同于 Velocity = FVector(0.0f)
}


// Called when the game starts or when spawned
void AMyPawn::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void AMyPawn::Tick(float DeltaTime) { // DeltaTime 为两帧之间的间隔值, 可以保证移动的帧流畅性
	Super::Tick(DeltaTime);
	AddActorLocalOffset(Velocity * DeltaTime, true); // * DeltaTime 为让物体的移动跟帧率脱绑, true 为详细的扫描
}


// AMyPawn 的键盘输入事件
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 👇【键盘事件一】将键盘输入事件跟轴事件进行绑定绑定！ ———————————————————————————————————————————————————————————————————
	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward); //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight); //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
}


// 👇 【键盘事件二】处理轴事件（在 AMyPawn::SetupPlayerInputComponent 内将键盘输入跟轴事件绑定后, 👇下面具体实现用键盘来控制物体）=> 具体实现 ———————————————————————————————————————————————————————————————————
void AMyPawn::MoveForward(float Value) {
	// 这里边仅更改 Velocity, 真正调用 AddActorLocalOffset 是在上边的 Tick , 因为要用到 DeltaTime 来提升帧的流畅性
	Velocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed; // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入
}

void AMyPawn::MoveRight(float Value) {
	// 这里边仅更改 Velocity, 真正调用 AddActorLocalOffset 是在上边的 Tick , 因为要用到 DeltaTime 来提升帧的流畅性
	Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed; // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入的参数固定在 -0.1 ~ 1.0 之间
}
