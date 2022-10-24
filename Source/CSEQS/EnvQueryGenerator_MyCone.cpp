// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryGenerator_MyCone.h"



void UEnvQueryGenerator_MyCone::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	//此数组将保存对所有生成项的引用，即锥形项
	TArray<FNavLocation> ItemCandidates;

	//获取我们AI典当的参考
	AActor* AIPawn = Cast<AActor>((QueryInstance.Owner).Get());

	//存储其位置及其前向矢量
	FVector PawnLocation = AIPawn->GetActorLocation();
	FVector PawnForwardVector = AIPawn->GetActorForwardVector();

	//如果角度步长为零，我们将进入一个无限循环。
	//因为我们不希望这样，所以不要执行以下逻辑
	if (AngleStep == 0) return;

	for (float Angle = -ConeDegrees; Angle < ConeDegrees; Angle += AngleStep)
	{
		//从棋子的左侧开始，将其向前矢量旋转角度+1
		FVector LeftVector = PawnForwardVector.RotateAngleAxis(Angle + 1, FVector(0, 0, 1));
		//左向量显示了该角度的直线。我们唯一需要的
		//是生成该行中的项目

		//为当前线生成所有点（LeftVector）
		for (int32 Point = 0; Point < ConeRadius; Point++)
		{
			//生成此特定角度和距离的点
			FNavLocation NavLoc = FNavLocation(PawnLocation + LeftVector * Point * PointsDistance);

			//将新点添加到数组中
			ItemCandidates.Add(NavLoc);
		}
	}

	//将所有导航点投影到我们的Viewport中，并删除导航网格之外的导航点
	ProjectAndFilterNavPoints(ItemCandidates, QueryInstance);

	//将生成的点存储为查询结果
	StoreNavPoints(ItemCandidates, QueryInstance);
}

