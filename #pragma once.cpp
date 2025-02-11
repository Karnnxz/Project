#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class YOURPROJECT_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Settings")
	float MoveSpeed = 300.0f;

	// Floating Height and Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Settings")
	float FloatHeight = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Settings")
	float FloatSpeed = 1.0f;

private:
	// Original location of the coin
	FVector OriginalLocation;
};
