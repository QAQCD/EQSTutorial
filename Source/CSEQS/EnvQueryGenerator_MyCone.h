// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EnvQueryGenerator_MyCone.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Points: MyCone"))
class CSEQS_API UEnvQueryGenerator_MyCone : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()

public:

	/** 在圆锥体中生成项目并将其放置在环境中 */
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;


	//最好不要用float，UE4设的有FAIDataProviderFloatValue具体参考EQG_SimpleGridOffset.h
	UPROPERTY(EditAnywhere, Category = ConeProperties, DisplayName = "点与点的距离")
	float PointsDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = ConeProperties, DisplayName = "圆锥体角度")
	float ConeDegrees = 140.f;

	UPROPERTY(EditAnywhere, Category = ConeProperties, DisplayName = "角度步长")
	float AngleStep = 40.f;

	UPROPERTY(EditAnywhere, Category = ConeProperties, DisplayName = "圆锥体的半径")
	float ConeRadius = 150.f;
};
