// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"


UCLASS()
class BASEUE_API AMyPawn : public APawn {
	GENERATED_BODY()

	public:
		// Sets default values for this pawn's properties
		AMyPawn();

			// 👇初始化一个 Pawn 类： ————————————————————
			UPROPERTY(VisibleAnywhere, Category="My MyPawn Components") //UPROPERTY() 表示参与到蓝图的反射系统中, 让蓝图可以编辑, 🔥 组件一般就给 VisibleAnywhere, 让编辑器外也可以看见！！
			class UStaticMeshComponent* MyStaticMesh;// class 表示让 VsCode 认识 UStaticMeshComponent 为一个类  =>  这里的作用是设置组件为一个静态网格, U 开头是继承 Object 类型, 因为 StaticMesh 不是一个基本类型, 所以用指针, * 是一个指针, 🚀 指针类型最好不要用 EditAnywhere !!


			// 👇给 Pawn 类设置摄像机： ————————————————————
			UPROPERTY(VisibleAnywhere, Category="My MyPawn Components")
			class UCameraComponent* MyCamera; //* 为解引用, 把解引用后的值给到 MyCamera, 也就是说 MyCamera 为一个指针变量, 指向 UCameraComponent 类型的变量

			// 👇 【键盘事件三】最大的移动速度
			UPROPERTY(VisibleAnywhere, Category="My MyPawn Movement")
			float MaxSpeed; //最大的速度

			

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 接收玩家的输入


	// 👇 处理轴事件（用键盘控制物体） ———————————————————————————————————————————————————————————————————
	private:

		// 👇【声明键盘事件】
		void MoveForward(float value);
		void MoveRight(float value);

		// 👇 初始化速度(偏移量）变量, 不需要参与反射系统
		FVector Velocity; 
};
