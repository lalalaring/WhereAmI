#pragma once
#include "Interactive.generated.h"


/**
 * Interface to be implemented 
 */
UINTERFACE(Blueprintable, MinimalAPI)
class UInteractive: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};
class IInteractive
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	void Use(AGameCharacter* from);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	void StartView(AGameCharacter* from);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	void EndView(AGameCharacter* from);
};
