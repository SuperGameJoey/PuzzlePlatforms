// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "JoinServerListItem.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerItemBPClass(TEXT("/Game/MenuSystem/WBP_ServerListItem"));
	if (!ensure(ServerItemBPClass.Class != nullptr)) return;
	ServerItemClass = ServerItemBPClass.Class;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClicked);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnCancelClicked);

	if (!ensure(ConnectButton != nullptr)) return false;
	ConnectButton->OnClicked.AddDynamic(this, &UMainMenu::OnConnectClicked);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);

	return true;
}

void UMainMenu::OnHostClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::AddServerEntries(TArray<FString> ServerNames)
{
	if (!ensure(ServerItemClass != nullptr)) return;
	if (!ensure(ServerScrollBox != nullptr)) return;

	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerScrollBox->ClearChildren();

	uint32 i = 0;

	for (const FString& ServerName : ServerNames)
	{
		UJoinServerListItem* NewItem = CreateWidget<UJoinServerListItem>(World, ServerItemClass);
		if (!ensure(NewItem != nullptr)) return;

		ServerScrollBox->AddChild(NewItem);
		NewItem->ServerName->SetText(FText::FromString(ServerName));
		NewItem->Setup(this, i);
		++i;
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerScrollBox->GetChildrenCount(); ++i)
	{
		UJoinServerListItem* Row = Cast<UJoinServerListItem>(ServerScrollBox->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = SelectedIndex.IsSet() && (SelectedIndex.GetValue() == i);
		}
	}
}

void UMainMenu::OnJoinClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (MenuInterface != nullptr)
	{
		MenuInterface->FindSessions();
	}
}

void UMainMenu::OnCancelClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OnConnectClicked()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d"), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is not set"));
	}

	if (MenuInterface != nullptr && SelectedIndex.IsSet())
	{
		MenuInterface->Join(SelectedIndex.GetValue());
		return;
	}
}

void UMainMenu::OnQuitClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->QuitGame();
	}
}
