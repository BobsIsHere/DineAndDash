// Fill out your copyright notice in the Description page of Project Settings.


#include "SatisfactionBar.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void USatisfactionBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (StarBox)
	{
		for (UWidget* Child : StarBox->GetAllChildren())
		{
			UImage* StarImage = Cast<UImage>(Child);

			if (StarImage)
			{
				StarImages.Add(StarImage);
			}
		}
	}

	CurrentThreshold = 0;
	SatisfactionThreshold = 30;

	YellowColor = FLinearColor(1, 0.5, 0, 1);
	WhiteColor = FLinearColor(1, 1, 1, 1);  
}

void USatisfactionBar::UpdateSatisfaction(int32 Score)
{
	if (!ProgressBar || StarImages.Num() == 0)
	{
		return;
	}

	// Update Satisfaction Bar
	ProgressBar->SetPercent(static_cast<float>(Score / SatisfactionThreshold));

	if (Score >= CurrentThreshold + SatisfactionThreshold)
	{
		CurrentThreshold += SatisfactionThreshold;

		if (CurrentStarIndex < StarImages.Num())
		{
			if (StarImages[CurrentStarIndex]->GetColorAndOpacity() == WhiteColor)  
			{
				StarImages[CurrentStarIndex]->SetColorAndOpacity(YellowColor); 

				ProgressBar->SetPercent(0);
			}
		}
	}
}
