// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "SkillBase.h"
#include "UsableCharacterSkillSlot.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class ZINIAXWARRIORS_API APlayableCharacter : public ACharacter, public IUsableCharacterSkillSlot
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Returns TopDownCameraComponent SubObject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom SubObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld SubObject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() const { return CursorToWorld; }


	UFUNCTION()
	FRotator CalculateLookingDirection() const;

protected:
	UFUNCTION(BlueprintCallable)
	void SetupHealthSystem(UHealthSystem* NewHealthSystem, float MaxHealth, float Resistance);
	UFUNCTION()
	void LockRotation();
	UFUNCTION()
	void ConfigureCharacterMovement() const;
	UFUNCTION()
	void SetupCameraBoom();
	UFUNCTION()
	void SetupTopDownCamera();
	UFUNCTION(Client, Unreliable)
	void CalculateCursorPosition() const;
	UFUNCTION()
	void PopulateSkillArray();

	UFUNCTION()
	void MoveVertical(float Value);
	UFUNCTION()
	void MoveHorizontal(float Value);

	virtual void UseBasicAttack() override;
	virtual void UseFirstAbility() override;
	virtual void UseSecondAbility() override;
	virtual void UseThirdAbility() override;

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
