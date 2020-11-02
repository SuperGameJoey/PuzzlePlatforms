// Fill out your copyright notice in the Description page of Project Settings.

#include "JoinServerListItem.h"
#include "MainMenu.h"
#include "Components/Button.h"

void UJoinServerListItem::Setup(UMainMenu* InParent, uint32 InIndex)
{
	if (!ensure(SelectButton != nullptr)) return;
	SelectButton->OnClicked.AddDynamic(this, &UJoinServerListItem::OnClicked);

	Parent = InParent;
	Index = InIndex;
}

void UJoinServerListItem::OnClicked()
{
	if (!ensure(Parent != nullptr)) return;
	Parent->SelectIndex(Index);
}
