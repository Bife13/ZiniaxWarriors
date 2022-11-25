// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "MoveableCharacter.h"
#include "SkillBase.h"
#include "StatsComponent.h"
#include "StatusEffectsComponent.h"
<<<<<<< HEAD
#include "UI_Observer.h"
=======
>>>>>>> master-bife
#include "UsableCharacterSkillSlot.h"
#include "WorldWidget.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"


UCLASS()
class ZINIAXWARRIORS_API APlayableCharacter : public ACharacter, public IUsableCharacterSkillSlot,
												public IMoveableCharacter, public IDamageable, public IBuffable
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
<<<<<<< HEAD
	FORCEINLINE class UDecalComponent* GetCursorToWorld() const { return CursorToWorld; }
=======
>>>>>>> master-bife

	UFUNCTION(BlueprintCallable)
	int GetTeamIdCharacter() const { return TeamID; }
	
	UFUNCTION(Server, Unreliable)
	virtual void MoveVertical(float Value) override;
	UFUNCTION(Server, Unreliable)
	virtual void MoveHorizontal(float Value) override;
	UFUNCTION(Server, Unreliable)
	virtual void MoveMouse(FVector Value) override;

	UPROPERTY(BlueprintReadOnly)
	FRotator CachedMouseRotator;
	UPROPERTY(BlueprintReadOnly)
	FVector CachedMousePosition;

	
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float Amount) override;
	UFUNCTION(BlueprintCallable)
<<<<<<< HEAD
	virtual void AddPowerBuff(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddResistanceBuff(float TimeAmount, float BuffAmount) override;

=======
	virtual void AddEnrage(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddBulk(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddHaste(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddVulnerable(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable)
    virtual void AddSlow(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable)
    virtual void AddWeaken(float TimeAmount, float DebuffAmount) override;
	
>>>>>>> master-bife
	UFUNCTION(BlueprintCallable)
	void SetCastEffect(UParticleSystem* NewParticle);

protected:
	UFUNCTION()
	void LockRotation();
	UFUNCTION()
	void ConfigureCharacterMovement() const;
	UFUNCTION()
	void SetupCameraBoom();
	UFUNCTION()
	void SetupStatsComponent();
	UFUNCTION(BlueprintCallable)
	void SetupStatValues(float PowerValue, float SpeedValue, float MaximumHealthValue, float ResistanceValue,
	                     float ViewRangeValue);
	UFUNCTION(BlueprintCallable)
	void SetupComponentValues();
	UFUNCTION()
	void SetupHealthComponent();
	UFUNCTION()
<<<<<<< HEAD
	void SetupUIObserverComponent();
	UFUNCTION()
=======
>>>>>>> master-bife
	void SetupStatusEffectComponent();
	UFUNCTION()
	void SetupCastParticleSystem();
	UFUNCTION()
	void SetupTopDownCamera();
	UFUNCTION()
	void PopulateSkillArray();


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
	float BaseSpeed;
	UPROPERTY(EditAnywhere)
	int TeamID;
<<<<<<< HEAD
	
	
	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* ShootingPoint;

	UPROPERTY(EditAnywhere,Category = Stats)
=======
	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* ShootingPoint;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = Stats)
>>>>>>> master-bife
	UStatsComponent* StatsComponent;

	UPROPERTY(EditAnywhere,Category = Health)
	UHealthSystem* HealthComponent;

	UPROPERTY(EditAnywhere, Category = Status)
	UStatusEffectsComponent* StatusEffectsComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Particle)
	UParticleSystemComponent* CastParticleSystem;
<<<<<<< HEAD

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = UIObserver)
	UUI_Observer* UIObserver;
=======
>>>>>>> master-bife

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

<<<<<<< HEAD
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* CursorToWorld;
=======
>>>>>>> master-bife
};
