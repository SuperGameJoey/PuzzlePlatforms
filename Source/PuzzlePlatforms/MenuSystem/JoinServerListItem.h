// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinServerListItem.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UJoinServerListItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;
	
private:

	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerCount;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	void Setup(class UMainMenu* Parent, uint32 Index);

	UFUNCTION()
	void OnClicked();
};
