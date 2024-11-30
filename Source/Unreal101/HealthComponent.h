// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableInterface.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta = (BlueprintSpawnableComponent, IsBlueprintBase = "true"))
class UNREAL101_API UHealthComponent : public UActorComponent, public IDamageableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float m_CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;

	virtual void DoDamage_Implementation(float amount, bool& isDead) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeathSignature OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, float, DamageAmount);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamageSignature OnDamage;
};
