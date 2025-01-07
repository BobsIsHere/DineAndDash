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
	// Fmod -> Returns the floating-point remainder of the division operation
	float Progress{static_cast<float>(FMath::Fmod(static_cast<float>(Score), SatisfactionThreshold) / SatisfactionThreshold)};
	ProgressBar->SetPercent(Progress);

	// If score increases beyond threshold
	if (Score >= CurrentThreshold + SatisfactionThreshold)
	{
		CurrentThreshold += SatisfactionThreshold;

		if (CurrentStarIndex < StarImages.Num())
		{
			if (StarImages[CurrentStarIndex]->GetColorAndOpacity() == WhiteColor)  
			{
				StarImages[CurrentStarIndex]->SetColorAndOpacity(YellowColor); 
				++CurrentStarIndex;
			}
		}
	}
	// If score decreases below threshold
	else if (Score < CurrentThreshold)
	{
		if (CurrentStarIndex > 0)
		{
			// move to previous star
			--CurrentStarIndex;

			if (StarImages[CurrentStarIndex]->GetColorAndOpacity() == YellowColor)
			{
				StarImages[CurrentStarIndex]->SetColorAndOpacity(WhiteColor);
			}
		}

		CurrentThreshold -= SatisfactionThreshold;

		if (CurrentThreshold < 0)
		{
			CurrentThreshold = 0;
		}
	}
}
