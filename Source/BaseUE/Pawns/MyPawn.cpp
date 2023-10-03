// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"


// 创建一个 Pawn 类
AMyPawn::AMyPawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 👇初始化一个 Pawn 类： 蓝图类里边的组件结构 (RootComponent -> MyStaticMesh) ———————————————————————————————————————————————————————————————————
	// // 【一】创建默认根组件 -> 🚀由于默认创建的根组件无法设置 detail 属性(不是 visiableAnywhere), 所以下面就先创建 Mesh 静态网格体, 然后再把根组件 = 这个 Mesh ！就能把 Mesh 设置为默认的根组件了！(🌟好处是可以具备 sweep 属性, 这样就可以设置给这个根组件设置物理碰撞属性！)
	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); // CreateDefaultSubobject：创建默认子对象, USenceComponent：场景组件作为根组件

	// 【二】创建 UStaticMeshComponent -> 静态网格
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	RootComponent = MyStaticMesh;
	MyStaticMesh -> SetCollisionProfileName(TEXT("Pawn")); //🌟设置 Mesh 的预设继承 Pawn 的碰撞预设！！也可以在蓝图内进行设置

	// 【三】将创建好的 UStaticMeshComponent 挂载到【根组件】上, -> 为访问类里边的成员变量
	MyStaticMesh -> SetupAttachment(GetRootComponent()); // SetupAttachment：挂载到根组件上, -> 表示指针调用方法, GetRootComponent 会返回 RootComponent



	// ⚙️ 让上面的根组件有个默认值, 不然就看不到默认的 Actor 了（摄像机默认对着的那个对象） ———————————————————————————————————————————————————————————————————
	// 【一】把文件加载在内存中, ConstructorHelpers 是一个静态类, 需要用 static 调用 | :: 用来限定作用域 | FObjectFinder 用来查找对象, <UStaticMesh> 为静态网格资源类 | 🔥🔥【🔥StaticMeshAsset】跟【🔥MaterialAsset】为两个变量中！！ 为变量名！！用来存储资源！！我们需要加载【静态网格资源】跟【贴图材质】到这两个变量上！！
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
	if(StaticMeshAsset.Succeeded() && MaterialAsset.Succeeded()) { //🔥判断两个资源是否加载成功
		MyStaticMesh -> SetStaticMesh(StaticMeshAsset.Object); // 设置【静态网格资源】
		MyStaticMesh -> SetMaterial(0, MaterialAsset.Object); // 设置【静态网格资源】, 0 为放在最前面那个插槽
		MyStaticMesh -> SetWorldScale3D(FVector(0.5f)); //设置默认的尺寸
	}

	// 🎥 初始化摄像机(设置的是 BP_MyPawn) ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
	// 【一】设置摄像机的悬臂（可以掠过障碍物）
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm")); // MySpringArm 为摄像机
	MySpringArm -> SetupAttachment(GetStaticMeshComponent()); // 表示把 悬臂(MySpringArm) 附着到 元素(MyStaticMesh）上   =>  📦封装前的写法 MySpringArm -> SetupAttachment(MyStaticMesh);
	MySpringArm -> SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 🌟RelativeRotation 是变量, 所以是赋值形式！ 表示摄像机的相对旋转, FRotator(-45.0f, 0.0f, 0.0f) 表示摄像机的旋转角度
	MySpringArm -> TargetArmLength = 400.0f; // 摄像机的长度
	MySpringArm -> bEnableCameraLag = true; // 摄像机是否开启平滑跟随
	MySpringArm -> CameraLagSpeed = 3.0f; // 摄像机平滑跟随的速度
	
	// 【二】创建摄像机
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));

	// 【三】将摄像机挂载到根组件上, GetRootComponent() 为附着到根组件 | MySpringArm 表示附着到悬臂上
	MyCamera -> SetupAttachment(GetSpringArmComponent()); // 📦📦封装前的写法 MyCamera -> SetupAttachment(MySpringArm);
	// MyCamera -> SetupAttachment(GetRootComponent()); // GetRootComponent 会返回 RootComponent

	// 【四】设置相机跟 Pawn 类的相对位置 （让摄像机跟随主体物跑） | 如果上面设置了【悬臂】, 这里就不用设置相对位置跟旋转了, 因为要【把摄像机附着到悬臂上】!
	// MyCamera -> SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f)); //相对于父组件的位置, 父组件为 SetupAttachment 的那个对象, 也就是 RootComponent, 一开始是 0,0,0, 但是摄像机要拉远一点, 因此设置为 FVector(-300.0f, 0.0f, 300.0f)
	// MyCamera -> SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 摄像机旋转 45 度, 用 FRotator

	// 【五】将摄像机设置为默认的玩家控制器 player0 为默认玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = true; // 🔥开启让 Pawn 继承 Controller!!! 相当于在蓝图中进行勾选 ☑️

	// 🚗 初始化移动的速度变量倍率、移动的偏移量, Velocity 为 .h 内定义的移动偏移量 ———————————————————————————————————————————————————————————————————
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
	// 【定义前后移动】 🔥 Velocity 为在 .h 内声明的变量！！
	AddActorLocalOffset(Velocity * DeltaTime, true); // * DeltaTime 为让物体的移动跟帧率脱绑, true 为详细的扫描, AddActorLocalOffset 为让物体移动的函数

	// 【定义左右旋转】🔥 Yaw 为 Z 轴, 旋转 Z 来实现摄像机的左右旋转, 利用 Controller 来控制 Pawn
	AddControllerYawInput(MouseMoveValue.X);

	// 【定义上下旋转】 🔥 NewSpringArmRotation 为在 .h 内声明的变量！！ 用来记录新的旋转值 => 上下旋转, X Y Z 在虚幻中又称 Row, Pitch, Yaw, Pitch 为 Y 轴
	FRotator NewSpringArmRotation = MySpringArm -> GetComponentRotation();// NewSpringArmRotation 为自定义的变量, 用来让物体进行旋转, MySpringArm 为悬臂, 用悬臂的旋转代替物体自身旋转
	NewSpringArmRotation.Pitch = FMath::Clamp( // 🌟🌟FMath 方法为数学方法, Clamp 为限制的意思, 限制旋转的角度
		NewSpringArmRotation.Pitch += MouseMoveValue.Y, // Pitch 为 Y 轴, 旋转 Y 来实现摄像机的上下旋转
		-80.0f, 0.0f  // ⚡️ 限制旋转的角度范围
	);
	MySpringArm -> SetWorldRotation(NewSpringArmRotation);
}


// AMyPawn 的键盘输入事件 ———————————————————————————————————————————————————————————————————
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 👇将【键盘输入事件】跟【轴事件】进行绑定！ ———————————————————————————————————————————————————————————————————
	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward); //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
	PlayerInputComponent -> BindAxis(TEXT("LookDown"), this, &AMyPawn::LookDown); //MoveForward 为 Axis 的名字, this 为绑定到当前类 &AMyPawn::MoveForward 表示函数的引用
}


// 👇 【键盘前后移动事件】处理轴事件（在 AMyPawn::SetupPlayerInputComponent 内将键盘输入跟轴事件绑定后, 👇下面具体实现用键盘来控制物体）=> 具体实现 ———————————————————————————————————————————————————————————————————
void AMyPawn::MoveForward(float value) {
	// 👇记录值, 这里边仅更改 Velocity, 真正调用 AddActorLocalOffset 是在上边的 Tick , 因为要用到 DeltaTime 来提升帧的流畅性
	Velocity.X = FMath::Clamp(value, -16.0f, 16.0f) * MaxSpeed; // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入
}

// 👇 【键盘上下移动事件】处理轴事件
void AMyPawn::MoveRight(float value) {
	// 👇记录值, 这里边仅更改 Velocity, 真正调用 AddActorLocalOffset 是在上边的 Tick , 因为要用到 DeltaTime 来提升帧的流畅性
	Velocity.Y = FMath::Clamp(value, -16.0f, 16.0f) * MaxSpeed; // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入的参数固定在 -0.1 ~ 1.0 之间
}

// 👇 【键盘左右移动事件】处理轴事件, Math::Clamp 限定夹值范围是因为不能上下旋转超过 360 度
void AMyPawn::LookUp(float value) {
	// 👇记录值
	MouseMoveValue.Y = FMath::Clamp(value, -16.0f, 16.0f); // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入, 这路不用 *MaxSpeed 是因为旋转的话最多就 360度, 不会无限制的旋转
}

// 👇 【键盘左右移动事件】处理轴事件, Math::Clamp 限定夹值范围是因为不能上下旋转超过 360 度
void AMyPawn::LookDown(float value) {
	// 👇记录值
	MouseMoveValue.X = FMath::Clamp(value, -16.0f, 16.0f); // FMath::Clamp(Value, -1.0f, 1.0f) 表示将输入的参数固定在 -0.1 ~ 1.0 之间, 这路不用 *MaxSpeed 是因为旋转的话最多就 360度, 不会无限制的旋转
}


