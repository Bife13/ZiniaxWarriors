// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "HealthSystem.h"
#include "MoveableCharacter.h"
#include "PassiveBase.h"
#include "SkillBase.h"
#include "StatsComponent.h"
#include "StatusEffectsComponent.h"
#include "UsableCharacterSkillSlot.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillCasted, float, Cooldown);

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
	UFUNCTION(NetMulticast, Reliable)
	void StartBeginPlay();
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;


	/** Returns TopDownCameraComponent SubObject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom SubObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld SubObject **/

	UFUNCTION(BlueprintCallable)
	int GetServerTeamIdCharacter() const { return ServerTeamID; }

	UFUNCTION(Server, Reliable)
	void SetServerTeamId(float Value);

	UFUNCTION()
	void SetSkills(TSubclassOf<USkillBase> Ability1, TSubclassOf<USkillBase> Ability2,
	               TSubclassOf<USkillBase> Ability3);


	UFUNCTION(BlueprintImplementableEvent)
	void OnRoundStartedEventSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnVictorySound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnDefeatSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFinalVictorySound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFinalDefeatSound();
	
	UFUNCTION()
	void CallRoundStartSound();
	UFUNCTION()
	void CallVictorySound();
	UFUNCTION()
	void CallDefeatSound();

	UFUNCTION()
	void AnnounceVictory();
	UFUNCTION()
	void AnnounceDefeat();
	
	UFUNCTION(NetMulticast, Unreliable)
	virtual void MoveVertical(float Value) override;
	UFUNCTION(NetMulticast, Unreliable)
	virtual void MoveHorizontal(float Value) override;
	UFUNCTION(Server, Unreliable)
	virtual void MoveMouse(FVector Value) override;


	UPROPERTY(BlueprintReadOnly)
	FRotator CachedMouseRotator;
	UFUNCTION(BlueprintCallable)
	FVector GetMousePos();
	UPROPERTY(BlueprintReadOnly, Replicated)
	FVector CachedMousePosition;

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpecialAbilityCast(int Index);
	
	UFUNCTION(BlueprintImplementableEvent)
    void OnHandleAbilitySound();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitSound();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnGotHitSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnLowHealthSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealedSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnCatchphraseSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnAbilityOnCooldownSound();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFootstepsSound();
	UFUNCTION(BlueprintCallable)
	void OnSpecialAbility(int Index);
	UFUNCTION(BlueprintImplementableEvent)
	void OnResetMeshEvent();

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float Amount) override;
	UFUNCTION(BlueprintCallable)
	virtual void RecoverHealth(float Amount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddEnrage(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddBulk(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddHaste(float TimeAmount, float BuffAmount) override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void AddHastePassive(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddVulnerable(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	virtual void AddVulnerableMulticast(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddSlow(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	virtual void AddSlowMulticast(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddWeaken(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	virtual void AddWeakenMulticast(float TimeAmount, float DebuffAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddRoot(float TimeAmount) override;
	UFUNCTION(BlueprintCallable)
	virtual void AddShield(float TimeAmount, float BuffAmount) override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void AddShieldPassive(float TimeAmount, float BuffAmount) override;
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	virtual void AddCastingSlow(float TimeAmount, float BuffAmount) override;

	UFUNCTION(BlueprintCallable)
	void SetCastEffect(UParticleSystem* NewParticle);

	UFUNCTION(NetMulticast, Reliable)
	void StartRootEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndRootEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void Shielded() const;
	UFUNCTION(NetMulticast, Reliable)
	void ShieldOver() const;
	UFUNCTION(NetMulticast, Reliable)
	void StartEnrageEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndEnrageEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void StartVulnerableEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndVulnerableEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void StartHasteEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndHasteEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void StartSlowEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndSlowEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void StartWeakenEffect() const;
	UFUNCTION(NetMulticast, Reliable)
	void EndWeakenEffect() const;
	UFUNCTION()
	void SetSpawnLocation(FVector newLocation) { SpawnLocation = newLocation; }

	UFUNCTION()
	void CallBPDeathEvent();
	UFUNCTION()
	void CallBPGotHitEvent();
	UFUNCTION()
	void CallBPLowHealthEvent();
	UFUNCTION()
	void CallBPHealedEvent();


	UFUNCTION()
	virtual bool GetIsCasting() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void SetIsCasting(bool Value) override;

	UFUNCTION(BlueprintCallable)
	bool GetIsDead();

	UFUNCTION(NetMulticast, Reliable)
	void SetIsDead(bool Value);

	UFUNCTION(BlueprintCallable)
	TArray<USkillBase*> GetRunTimeSkill();

	UFUNCTION()
	void ResetCharacter();
	UFUNCTION()
	void PlayCatchphrase();

	UFUNCTION(Server, Reliable)
	void ResetMesh();

	UPROPERTY(BlueprintAssignable)
	 FSkillCasted  CastEventBasic;
	UPROPERTY(BlueprintAssignable)
	 FSkillCasted  CastEventAbility1;
	UPROPERTY(BlueprintAssignable)
	 FSkillCasted  CastEventAbility2;
	UPROPERTY(BlueprintAssignable)
	 FSkillCasted  CastEventAbility3;

	UFUNCTION(Client, Reliable)
	void HandleCastEvent1(float Value);
	UFUNCTION(Client, Reliable)
	void HandleCastEvent2(float Value);
	UFUNCTION(Client, Reliable)
	void HandleCastEvent3(float Value);
	UFUNCTION(Client, Reliable)
	void HandleCastEvent4(float Value);
	

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
	void SetupStatusEffectComponent();
	UFUNCTION()
	void SetupCastParticleSystem();
	UFUNCTION()
	void SetupRootParticleSystem();
	UFUNCTION()
	void SetupShieldParticleSystem();
	UFUNCTION()
	void SetupEnrageParticleSystem();
	UFUNCTION()
	void SetupVulnerableParticleSystem();
	UFUNCTION()
	void SetupHasteParticleSystem();
	UFUNCTION()
	void SetupSlowParticleSystem();
	UFUNCTION()
	void SetupWeakenParticleSystem();
	UFUNCTION()
	void SetupTopDownCamera();
	UFUNCTION(Server, Unreliable)
	void PopulateSkillArray();
	UFUNCTION(NetMulticast,Reliable)
	void ObserveSpeedBuffs();
	UFUNCTION(Server, Reliable)
	void ChangeServerSpeed();


	UFUNCTION()
	void ObserverResistanceBuffs();
	UFUNCTION()
	void ObserverShieldBuffs();

	UFUNCTION(Server, Unreliable)
	virtual void UseBasicAttack() override;
	UFUNCTION(Server, Unreliable)
	virtual void UseFirstAbility() override;
	UFUNCTION(Server, Unreliable)
	virtual void UseSecondAbility() override;
	UFUNCTION(Server, Unreliable)
	virtual void UseThirdAbility() override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<USkillBase>> Skills;
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<USkillBase*> RuntimeSkills;
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadOnly)
	TArray<UAnimMontage*> AttackAnimations;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPassiveBase> Passive;
	UPROPERTY(VisibleAnywhere)
	UPassiveBase* RunTimePassive;
	IPassive* CachedPassiveInterface;

	UFUNCTION(NetMulticast, Unreliable)
	void PassiveInitializeFunction();

	UFUNCTION(BlueprintCallable)
	void OnHit();
	UFUNCTION(BlueprintCallable)
	float CheckDistance(float Damage, APawn* OwnerPassive, APawn* Target);
	UFUNCTION()
	void OnTickPassive(float DeltaTime) const;
	UPROPERTY()
	UWorld* CachedWorld;
	UPROPERTY()
	FRotator RuntimeLookRotator;

	UPROPERTY()
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	float BaseSpeed;

	UPROPERTY(Replicated)
	bool bIsCasting = false;

	UPROPERTY(Replicated)
	bool bIsDead = false;

	UPROPERTY(Replicated, VisibleAnywhere)
	int ServerTeamID;
	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* ShootingPoint;
	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* FeetPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Stats)
	UStatsComponent* StatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	UHealthSystem* HealthComponent;

	UPROPERTY(EditAnywhere, Category = Status)
	UStatusEffectsComponent* StatusEffectsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* CastParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* RootParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* ShieldParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* ShieldParticleSystemOver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* EnrageParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* VulnerableParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* WeakenParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* SlowParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Particle)
	UParticleSystemComponent* HasteParticleSystem;


	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
};
