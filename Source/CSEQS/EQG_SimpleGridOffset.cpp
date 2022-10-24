// Fill out your copyright notice in the Description page of Project Settings.


#include "EQG_SimpleGridOffset.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"


#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UEQG_SimpleGridOffset::UEQG_SimpleGridOffset(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	GenerateAround = UEnvQueryContext_Querier::StaticClass();

	OffsetSpace.DefaultValue = 200.f;
	GridHalfSize.DefaultValue = 500.f;
	SpaceBetween.DefaultValue = 100.f;
}

void UEQG_SimpleGridOffset::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	//将生成器参数绑定到查询实例，以便能够在此生成器上使用数据绑定
	UObject* BindOwner = QueryInstance.Owner.Get();
	GridHalfSize.BindData(BindOwner, QueryInstance.QueryID);
	SpaceBetween.BindData(BindOwner, QueryInstance.QueryID);
	OffsetSpace.BindData(BindOwner, QueryInstance.QueryID);

	//获取这个参数的当前值（一定要使用GetValue函数而不是尝试直接访问该值
	float RadiusValue = GridHalfSize.GetValue();
	float DensityValue = SpaceBetween.GetValue();
	float OffsetValue = OffsetSpace.GetValue();

	
	// 获取每行项目数并计算孔的索引范围
	const int32 ItemsCount = FPlatformMath::TruncToInt((RadiusValue * 2.0 / DensityValue) + 1);
	const int32 ItemsCountHalf = ItemsCount / 2;
	const int32 LeftRangeIndex = ItemsCountHalf - FPlatformMath::TruncToInt(OffsetValue / DensityValue) - 1;
	const int32 RightRangeIndex = ItemsCountHalf + FPlatformMath::TruncToInt(OffsetValue / DensityValue) + 1;
	const int32 OffsetItemsCount = FPlatformMath::TruncToInt((ItemsCount * 2.0 / DensityValue) + 1);

	// 获取每个上下文的位置（我们可能有不止一个上下文）
	TArray<FVector> ContextLocations;
	QueryInstance.PrepareContext(GenerateAround, ContextLocations);

	// 为每个上下文保留项目所需的内存空间。
	//从项目的总列表中减去位于孔中的项目来计算总项目计数。 
	TArray<FNavLocation> GridPoints;
	GridPoints.Reserve(((ItemsCount * ItemsCount) - (OffsetItemsCount * OffsetItemsCount)) * ContextLocations.Num());

	// 计算每个项目的位置
	for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++) {
		for (int32 IndexX = 0; IndexX < ItemsCount; ++IndexX)
		{
			for (int32 IndexY = 0; IndexY < ItemsCount; ++IndexY)
			{
				// 如果物品在洞范围内，跳过它。
				if ((IndexY > LeftRangeIndex && IndexY < RightRangeIndex) && (IndexX > LeftRangeIndex && IndexX < RightRangeIndex)) {
					continue;
				}
				//从上下文位置开始，定义当前项的位置
				// 并将其添加到gridPoints数组中。
				else {
					const FNavLocation TestPoint = FNavLocation(ContextLocations[ContextIndex] - FVector(DensityValue * (IndexX - ItemsCountHalf), DensityValue * (IndexY - ItemsCountHalf), 0));
					GridPoints.Add(TestPoint);
				}
			}
		}
	}

	//投影所有点，删除当前导航网格之外的点并存储结果。
	ProjectAndFilterNavPoints(GridPoints, QueryInstance);
	StoreNavPoints(GridPoints, QueryInstance);
}

FText UEQG_SimpleGridOffset::GetDescriptionTitle() const
{
	return FText::Format(LOCTEXT("GridOffsetDescriptionGenerateAroundContext", "{0}: generate around {1}"),
		Super::GetDescriptionTitle(), UEnvQueryTypes::DescribeContext(GenerateAround));
	
}

FText UEQG_SimpleGridOffset::GetDescriptionDetails() const
{
	FText Desc = FText::Format(LOCTEXT("GridOffseDescription", "radius: {0}, space between: {1}, offset:{2}"),
		FText::FromString(GridHalfSize.ToString()), FText::FromString(SpaceBetween.ToString()), FText::FromString(OffsetSpace.ToString()));

	FText ProjDesc = ProjectionData.ToText(FEnvTraceData::Brief);
	if (!ProjDesc.IsEmpty())
	{
		FFormatNamedArguments ProjArgs;
		ProjArgs.Add(TEXT("Description"), Desc);
		ProjArgs.Add(TEXT("ProjectionDescription"), ProjDesc);
		Desc = FText::Format(LOCTEXT("GridOffsetDescriptionWithProjection", "{Description}, {ProjectionDescription}"), ProjArgs);
	}

	return Desc;
}

#undef LOCTEXT_NAMESPACE