// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ++PlayerCount;
    UE_LOG(LogTemp, Warning, TEXT("New Login. There are %d Players"), PlayerCount);

    if (PlayerCount >= 3)
    {
        bUseSeamlessTravel = true;
        
        UE_LOG(LogTemp, Warning, TEXT("3 Players joined. Starting Game!"), PlayerCount);
        UWorld* World = GetWorld();
        
        if (!ensure(World != nullptr)) return;
        World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    
    --PlayerCount;
    UE_LOG(LogTemp, Warning, TEXT("New logout. There are %d Players"), PlayerCount);
}
