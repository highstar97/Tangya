#pragma once

#include "SREmptyBullet.h"
#include "EmptyBullet762x39.generated.h"

UCLASS()
class SHOOTING_RANGE_API AEmptyBullet762x39 : public ASREmptyBullet
{
	GENERATED_BODY()
	
public:
	AEmptyBullet762x39();

	virtual void BounceOff(const FVector& ShootDirection) override;
};