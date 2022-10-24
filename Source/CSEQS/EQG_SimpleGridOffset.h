// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EnvironmentQuery/EnvQueryContext.h"
#include "Runtime/AIModule/Classes/DataProviders/AIDataProvider.h"

#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "EQG_SimpleGridOffset.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Points: Grid_Offset"))
class CSEQS_API UEQG_SimpleGridOffset : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_UCLASS_BODY()

	/** 生成项目并将其放置在环境中 */
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;

	/** context */
	UPROPERTY(EditDefaultsOnly, Category = Generator, DisplayName = "周围生成")
	TSubclassOf<UEnvQueryContext> GenerateAround;

	UPROPERTY(EditDefaultsOnly, Category = Grid_Parameters, DisplayName = "偏移空间")
	FAIDataProviderFloatValue OffsetSpace;

	UPROPERTY(EditDefaultsOnly, Category = Grid_Parameters, DisplayName = "网格半径")
	FAIDataProviderFloatValue GridHalfSize;

	UPROPERTY(EditDefaultsOnly, Category = Grid_Parameters, DisplayName = "间距")
	FAIDataProviderFloatValue SpaceBetween;


	
};