// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "MoveableCharacter.h"
#include "SkillBase.h"
#include "StatsComponent.h"
#include "StatusEffectsComponent.h"
#include "UsableCharacterSkillSlot.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class ZINIAXWARRIORS_API APlayableCharacter : public ACharacter, public IUsableCharacterSkillSlot,
                                              public IMoveableCharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	APlayableCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent SubObject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom SubObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld SubObject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() const { return CursorToWorld; }
	
	UFUNCTION(BlueprintCallable)
	int GetTeamIdCharacter() const { return TeamID; }


	UFUNCTION(Server, Unreliable)
	virtual void MoveVertical(float Value) override;
	UFUNCTION(Server, Unreliable)
	virtual void MoveHorizontal(float Value) override;
	UFUNCTION(Server, Unreliable)
	virtual void MoveMouse(FVector Value) override;
	
	UFUNCTION(BlueprintCallable)
	void SetStatComponent(UStatsComponent* StatsComponentToSet) {StatsComponent = StatsComponentToSet;}

	UFUNCTION(BlueprintCallable)
	void SetStatusEffectComponent(UStatusEffectsComponent* StatusEffectComponentToSet) {StatusEffectsComponent = StatusEffectComponentToSet;}

	UPROPERTY(BlueprintReadOnly)
	FRotator CachedMouseRotator;
	UPROPERTY(BlueprintReadOnly)
	FVector CachedMousePosition;
	

protected:

	UFUNCTION()
	void LockRotation();
	UFUNCTION()
	void ConfigureCharacterMovement() const;
	UFUNCTION()
	void SetupCameraBoom();
	UFUNCTION()
	void SetupTopDownCamera();
	UFUNCTION()
	void PopulateSkillArray();


	virtual void UseBasicAttack() override;
	virtual void UseFirstAbility() override;
	virtual void UseSecondAbility() override;
	virtual void UseThirdAbility() override;

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float Amount) override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<USkillBase>> Skills;
	UPROPERTY()
	TArray<USkillBase*> RuntimeSkills;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimations;

	UPROPERTY()
	UWorld* CachedWorld;
	UPROPERTY()
	FRotator RuntimeLookRotator;
	UPROPERTY()
	class UHealthSystem* HealthSystem;
	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* ShootingPoint;
	UPROPERTY()
	float BaseSpeed;

	UPROPERTY(EditAnywhere)
	int TeamID;

	UPROPERTY()
	UStatsComponent* StatsComponent;
	UPROPERTY(BlueprintReadWrite)
	UStatusEffectsComponent* StatusEffectsComponent;

	UFUNCTION(BlueprintCallable)
	void SetupHealthSystem(UHealthSystem* NewHealthSystem){HealthSystem = NewHealthSystem;}
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};
