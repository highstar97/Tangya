#pragma once

#include "SRBullet.h"
#include "Bullet762x39.generated.h"

UCLASS()
class SHOOTING_RANGE_API ABullet762x39 : public ASRBullet
{
	GENERATED_BODY()
	
public:
	ABullet762x39();

	virtual void FireInDirection(const FVector& ShootDirection) override;
};