#pragma once

#include "GameFramework/Actor.h"
#include "SRBullet.generated.h"

UCLASS()
class SHOOTING_RANGE_API ASRBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRBullet();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Shell;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* EmptyShell;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	float Damage;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	float Speed;
};