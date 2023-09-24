// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor02.generated.h" // .h 文件新增引入都是向前新增


//??声明一个类, 用来继承 Actor
UCLASS()
class BASEUE_API AMyActor02 : public AActor {
	GENERATED_BODY()
	
    public:
        // 👇 用来设置 Actor 的默认值
        AMyActor02(); // AMyActor02 为 AMyActor02 的构造函数, 在类实例化后

        // ⚡️UPROPERTY() 为 UE 的宏(让属性可以在编辑器内进行控制), VisibleAnywhere 为各种全县 ————————————————————
        // 👇【声明一个 Actor 组件】记得在声明完后都需要在 .cpp 内赋予初始值！！ UPROPERTY 为宏定义
        UPROPERTY(VisibleAnywhere, Category="My Actor Components") //UPROPERTY() 表示参与到蓝图的反射系统中, 让蓝图可以编辑, 🔥🔥 组件一般就给 VisibleAnywhere, 让编辑器外也可以看见！！
        UStaticMeshComponent* MyStaticMesh;// 👈 设置 Actor 组件为一个静态网格, U 开头是继承 Object 类型, 因为 StaticMesh 不是一个基本类型, 所以用指针 *是一个指针, 🚀 UStaticMeshComponent 指针类型最好不要用 EditAnywhere !!

        // 👇【出现在实例 detail 菜单内！！】支持更改 MyActor02 在游戏开始后的位置(自定义默认值) -> 【可以编辑的版本】 -> 默认值为 FVector(0.0f)
        UPROPERTY(EditInstanceOnly, Category="My Actor Properties | Vector(更改 MyActor02 的初始化位置)") // EditInstanceOnly 表示仅仅在实例上可编辑（可以在 UE 中进行编辑(在蓝图属性内不可编辑！), 会显示在 Deatil 面板中）
        FVector InitLocation; //在类中声明一个初始值 => 然后回到 .cpp 文件内进行填充！

        // 👇【出现在实例 detail 菜单内！！】记录 MyActor02 的更改前的位置 => 只能显示, 无法修改
        UPROPERTY(VisibleInstanceOnly, Category="My Actor Properties | Vector 向量 | 记录 MyActor02 的更改前的位置")
        FVector PlacedLocation;

        // 👇 【蓝图类的 default 属性内！】用来判断是否要去到初始位置
        UPROPERTY(EditDefaultsOnly, Category="My Actor Properties | Vector 向量 | 判断是否需要去到初始位置")
        bool bGotoInitLocation; //必须以小写 b 开头！

        // 👇 VisibleDefaultOnly 只用来显示初始值, 无法修改
        UPROPERTY(VisibleDefaultsOnly, Category="My Actor Properties | Vector 向量 | 测试用-只读")
        FVector WorldOrigin; //记录世界原点的位置

        // 👇 到处都可以编辑
        UPROPERTY(EditAnywhere, Category="My Actor Properties | Vector 向量 | 任意可编辑,记录每一帧的偏移的向量, 从而不断的改变物体位置", meta = (ClampMin=-5.0f, ClampMax=5.0f, UIMin=-5.0f, UIMax=5.0f)) //meta 表示元数据, 用来限制输入的值的范围
        FVector TickLocationOffset; //用来记录每一帧的偏移量的向量！

        // 👇 到处都可以编辑
        UPROPERTY(EditAnywhere, Category="My Actor Properties | Vector 向量 | 任意可编辑,开关实例的自动偏移")
        bool bShouldMove; //是否移动 -> 开关, 开启后实例就会一直移动


        // 👇给 【Actor03 实例】增加重力 + 模拟力矩 —————————————————————————————————————
        UPROPERTY(EditInstanceOnly,Category="My Actor Properties | 重力&力矩 | Physics(重力）")
        FVector initForce; //初始重力

        UPROPERTY(EditInstanceOnly,Category="My Actor Properties | 重力&力矩 |Physics(力矩）")
        FVector initTorque; //初始力矩

        UPROPERTY(EditInstanceOnly, Category="My Actor Properties | 重力&力矩 |Physics(忽略质量）")
        bool bAccelChange; //是否忽略质量（让物体不受重力影响）



    protected:
        // 👇 在 Actor 生成时（ Actor 生成为用 spawned, Object 生成为用 Constructor ）
        virtual void BeginPlay() override;

    public:
        // 👇每帧都会调用
        virtual void Tick(float DeltaTime) override;

};
