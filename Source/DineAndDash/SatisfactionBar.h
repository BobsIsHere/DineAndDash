// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SatisfactionBar.generated.h"

class UProgressBar;
class UHorizontalBox;
class UImage;

/**
 * 
 */
UCLASS()
class DINEANDDASH_API USatisfactionBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Progress Bar reference
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar; 

	// Horizontal Box containing stars
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* StarBox;

	// Star Images
	TArray<UImage*> StarImages;

	// Color Variables
	FLinearColor YellowColor;
	FLinearColor WhiteColor; 

	// Current star index
	int32 CurrentStarIndex;

	// Threshold for satisfaction
	float SatisfactionThreshold;

	// Current theshold value
	float CurrentThreshold;

	// Override NativeConstruct
	virtual void NativeConstruct() override;

public:
	// Update satisfaction bar
	UFUNCTION(BlueprintCallable, Category = "Satisfaction")
	void UpdateSatisfaction(int32 Score);
};
