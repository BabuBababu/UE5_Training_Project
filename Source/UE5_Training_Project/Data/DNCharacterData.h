#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNCharacterData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNCharacterStatusData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							hp=0.f;
	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							damage=0.f;
	// 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							armor=0.f;
	// 장탄 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int64							max_ammo=0;

	// 장전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							reload_speed = 0.f;

	// 사격 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							fire_speed = 0.f;


	// 병과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_MOS					mos = E_CHARACTER_MOS::CM_NONE;
	// 추천 포지션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_POSITION			recommend_position = E_CHARACTER_POSITION::CP_NONE;
	// 캐릭터 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_GRADE				grade = E_CHARACTER_GRADE::CG_NONE;
	// 레벨업시 오르는 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							hp_up=0.f;
	// 레벨업시 오르는 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							damage_up=0.f;
	// 레벨업시 오르는 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							armor_up=0.f;


	FDNCharacterStatusData& operator=(const FDNCharacterStatusData& data)
	{
		hp = data.hp;
		damage = data.damage;
		armor = data.armor;
		max_ammo = data.max_ammo;
		reload_speed = data.reload_speed;
		fire_speed = data.fire_speed;
		mos = data.mos;
		recommend_position = data.recommend_position;
		grade = data.grade;
		hp_up = data.hp_up;
		damage_up = data.damage_up;
		armor_up = data.armor_up;

		return *this;
	}


};


USTRUCT(Atomic, BlueprintType)
struct FDNCharacterMentalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 침착성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			composure = 0;
	// 적극성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			positiveness = 0;
	// 도덕성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			morality = 0;
	// 호감도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			friendship = 0;

	FDNCharacterMentalData& operator=(const FDNCharacterMentalData& data)
	{
		composure = data.composure;
		positiveness = data.positiveness;
		morality = data.morality;
		friendship = data.friendship;

		return *this;
	}
};



USTRUCT(Atomic, BlueprintType)
struct FDNEXPTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP Data")		//해당 레벨
	int64			level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP Data")		//필요 경험치
	int64			exp = 0;

};











USTRUCT(Atomic, BlueprintType)
struct FDNCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
		int64							character_id = 0;												// 캐릭터 ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
		FString							character_name = TEXT("");										// 캐릭터 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
		FDNCharacterStatusData			character_status_data;											// 캐릭터 스테이터스 데이터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
		FDNCharacterMentalData			character_mental_data;											//  캐릭터 멘탈 데이터


	FDNCharacterData& operator=(const FDNCharacterData& data)
	{
		character_id = data.character_id;
		character_name = data.character_name;
		character_status_data = data.character_status_data;
		character_mental_data = data.character_mental_data;

		return *this;
	}
};






//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentVoteLeftTimeData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							has_right_count = 0;											// 소유 진행권 개수
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							policy_left_time_to_next = 0;									// 다음 입안까지 남은 시간 = FNUIParliamentVoteData.vote_left_time
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							slogan_left_time_to_vote = 0;									// 슬로건 투표 남은 기간 = FNUIParliamentVoteData.vote_left_time
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")								// 다음 슬로건 투표까지 남은 기간
//	int64							slogan_left_time_to_next = 0;
//
//	//의원 투표관련 시간도 여기에 추가하면 됩니다.
//
//	FNUIParliamentVoteLeftTimeData& operator=(const FNUIParliamentVoteLeftTimeData& data)
//	{
//		has_right_count = data.has_right_count;
//		policy_left_time_to_next = data.policy_left_time_to_next;
//		slogan_left_time_to_vote = data.slogan_left_time_to_vote;
//		slogan_left_time_to_next = data.slogan_left_time_to_next;
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentPolicyVoteData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64								policy_id = 0;													// 정책 id
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString								policy_icon_path = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString								policy_name = TEXT("");											// 투표 남은 시간, 8일이 남았다면 초로 환산한 값을 넣어둔다.
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString								policy_info = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString								policy_area = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32								policy_date = 0;
//
//	//day 또는 month인지 가르쳐주는 변수 하나 있어야할듯
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32								policy_price = 0;
//
//	FNUIParliamentPolicyVoteData& operator=(const FNUIParliamentPolicyVoteData& data)
//	{
//		policy_id = data.policy_id;
//		policy_icon_path = data.policy_icon_path;
//		policy_name = data.policy_name;
//		policy_info = data.policy_info;
//		policy_area = data.policy_area;
//		policy_date = data.policy_date;
//		policy_price = data.policy_price;
//
//		return *this;
//	}
//};
//
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentActivityData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64					activity_id = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	E_NUI_ACTIVITY_TYPE		activity_type = E_NUI_ACTIVITY_TYPE::NAT_NONE;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	E_NUI_POLICY_DETAIL		policy_detail = E_NUI_POLICY_DETAIL::NPD_NONE;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	E_NUI_OWNERSHIP_DETAIL	ownership_detail = E_NUI_OWNERSHIP_DETAIL::NOD_NONE;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	E_NUI_AUTHORITY_DETAIL	authority_detail = E_NUI_AUTHORITY_DETAIL::NAD_NONE;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32					activity_date_hour = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32					activity_date_min = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32					activity_date_year = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32					activity_date_month = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int32					activity_date_day = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString					activity_info = TEXT("");
//
//
//	FNUIParliamentActivityData& operator=(const FNUIParliamentActivityData& data)
//	{
//		activity_id = data.activity_id;
//		activity_type = data.activity_type;
//		policy_detail = data.policy_detail;
//		ownership_detail = data.ownership_detail;
//		authority_detail = data.authority_detail;
//		activity_date_hour = data.activity_date_hour;
//		activity_date_min = data.activity_date_min;
//		activity_date_year = data.activity_date_year;
//		activity_date_month = data.activity_date_month;
//		activity_date_day = data.activity_date_day;
//		activity_info = data.activity_info;
//
//		return *this;
//	}
//};
//
////Koo
////의원 자격 획득했다는 팝업 알림창 데이터 송/ 수 신용
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentQualitifyPopupData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32	vote_end_date = 0;												//투표 기간이라는게 중요하니 어떤 투표인지는 정보가 필요 없을 것 같음
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32	guild_id = 0;													//어떤 길드의
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString	guild_name = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32	user_id = 0;													//어떤 유저가
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString	user_name = TEXT("");											//권한을 얻었다
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		bool	is_never_show_again_checked = false;							//다시 볼건가?
//
//	FNUIParliamentQualitifyPopupData& operator=(const FNUIParliamentQualitifyPopupData& data)
//	{
//		guild_id = data.guild_id;
//		guild_name = data.guild_name;
//		
//		user_id = data.user_id;
//		user_name = data.user_name;
//
//		vote_end_date = data.vote_end_date;
//
//		is_never_show_again_checked = data.is_never_show_again_checked;
//
//		return *this;
//	}
//};
//
////임시로 대부분의 의원 관련 데이터들은 SeatData를 활용함
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentSeatData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		seat_index = 0;										//의석 번호
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		seat_type = 0;										//의석 타입?
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		member_uid = 0;										//대상 uid
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString		member_name = TEXT("");								//대상 이름
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		guild_uid = 0;										//대상 길드 uid
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString		guild_name = TEXT("");								//대상 길드 이름
//
//	FNUIParliamentSeatData& operator=(const FNUIParliamentSeatData& data)
//	{
//		seat_index = data.seat_index;
//		seat_type = data.seat_type;
//		member_uid = data.member_uid;
//		member_name = data.member_name;
//		guild_uid = data.guild_uid;
//		guild_name = data.guild_name;
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentSeatVoteSlotData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FNUIParliamentSeatData	seat_data;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString					broacher_name = TEXT("");														//발의자 이름 이거 후보 등록 투표에선 굳이 필요하진 않을 것 같음 거슬리면 그냥 의원 투표 / 해임 투표 구조체 분할하기
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")											//투표 정보 -> 플레이어가 어떤 투표를 했는지 저장하는 변수
//		E_NUI_PARLIAMENT_VOTE_TYPE					vote_type = E_NUI_PARLIAMENT_VOTE_TYPE::NPVT_ABSTENTION;	//찬성 / 반대 / 기권 중 하나
//	//해임 / 의석 투표의 형태가 동일하니 구조체 그냥 하나로 씀
//
//	FNUIParliamentSeatVoteSlotData& operator=(const FNUIParliamentSeatVoteSlotData& data)
//	{
//		seat_data = data.seat_data;
//		broacher_name = data.broacher_name;
//		vote_type = data.vote_type;
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentSeatVoteListData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentSeatVoteSlotData>	seat_vote_data_array;
//
//	FNUIParliamentSeatVoteListData& operator=(const FNUIParliamentSeatVoteListData& data)
//	{
//		for (FNUIParliamentSeatVoteSlotData slot_data : data.seat_vote_data_array)
//		{
//			seat_vote_data_array.Emplace(slot_data);
//		}
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentTotalSeatVoteData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	//키값 - 의석 타입, 밸류값 - 각 타입별 의석 투표 정보
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		TMap<int32, FNUIParliamentSeatVoteListData>	total_vote_data_map;
//
//	FNUIParliamentTotalSeatVoteData& operator=(const FNUIParliamentTotalSeatVoteData& data)
//	{
//		total_vote_data_map.Empty(total_vote_data_map.Num());
//
//		for (TPair<int32, FNUIParliamentSeatVoteListData> data_pair : data.total_vote_data_map)
//		{
//			FNUIParliamentSeatVoteListData new_data = data_pair.Value;
//
//			total_vote_data_map.Emplace(data_pair.Key, new_data);
//		}
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentVoteResultData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FNUIParliamentSeatData	seat_data;										//기본 의석 정보
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")			//해임 투표 결과 정보 -> 투표 결과가 집계된 정보들
//		int32		vote_agree_count = 0;										//찬성, 반대, 기권표 총합
//	//결과에 대한 데이터는 필요 없어도 될 것 같음
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")			//그 외에 투표 마감 날짜가 필요
//		int32		vote_disagree_count = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		vote_abstention_count = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		FString		broacher_name = TEXT("");									//발의자 이름
//
//	//6자리 정수형으로 저장? ex ) 220810 -> 22년 08월 10일		
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//		int32		vote_finish_date = 0;
//
//	FNUIParliamentVoteResultData& operator=(const FNUIParliamentVoteResultData& data)
//	{
//		seat_data = data.seat_data;
//		vote_agree_count = data.vote_agree_count;
//		vote_disagree_count = data.vote_disagree_count;
//		vote_abstention_count = data.vote_abstention_count;
//		broacher_name = data.broacher_name;
//		vote_finish_date = data.vote_finish_date;
//
//		return *this;
//	}
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentOwnershipNodData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							ownership_id = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	E_NUI_OWNERSHIP_DETAIL	ownership_type = E_NUI_OWNERSHIP_DETAIL::NOD_NONE;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							ownership_left_time = 0;											// 남은 시간, 8일이 남았다면 초로 환산한 값을 넣어둔다.
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							guild_name = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							nod_name = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							ownership_image_path = TEXT("");
//
//
//	FNUIParliamentOwnershipNodData& operator=(const FNUIParliamentOwnershipNodData& data)
//	{
//		ownership_id = data.ownership_id;
//		ownership_type = data.ownership_type;
//		ownership_left_time = data.ownership_left_time;
//		guild_name = data.guild_name;
//		nod_name = data.nod_name;
//		ownership_image_path = data.ownership_image_path;
//
//		return *this;
//	}
//};
//
//
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentSloganData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	bool							slogan_active = false;											
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							slogan_id = 0;									
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_name = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_icon_path = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_simply_info = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_current_effect_info = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_to_max_effect_info = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString							slogan_max_effect_info = TEXT("");
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							slogan_cost = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64							slogan_activating_percent = 0;
//
//
//	FNUIParliamentSloganData& operator=(const FNUIParliamentSloganData& data)
//	{
//		slogan_active = data.slogan_active;									
//		slogan_id = data.slogan_id;											
//		slogan_name = data.slogan_name;										
//		slogan_icon_path = data.slogan_icon_path;							
//		slogan_simply_info = data.slogan_simply_info;						
//		slogan_current_effect_info = data.slogan_current_effect_info;		
//		slogan_to_max_effect_info = data.slogan_to_max_effect_info;			
//		slogan_max_effect_info = data.slogan_max_effect_info;				
//		slogan_cost = data.slogan_cost;
//		slogan_activating_percent = data.slogan_activating_percent;			
//
//		return *this;
//	}
//
//	bool operator==(const FNUIParliamentSloganData& data)
//	{
//		if (this == &data)
//			return true;
//		return false;
//
//	}
//};
//
//
//
//USTRUCT(Atomic, BlueprintType)
//struct FNUIParliamentData
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		faction_id = 0;												// 가문 ID
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString		faction_name = TEXT("");									// 가문 이름
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FString		faction_icon_path = TEXT("");								// 가문 아이콘
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		faction_goods = 0;											// 가문 재화
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		faction_session_count = 0;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		faction_policy_count = 0;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		round_left_time = 0;										// 현재 회기 남은 시간 ex) 8일이 남았다면 초로 환산한 값을 넣어둔다.
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FNUIParliamentVoteLeftTimeData vote_left_time_data;
//
//	//후보 등록 투표 남은 시간
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		seat_vote_left_time = 0;										
//
//	//해임 투표 남은 시간
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	int64		dismissal_vote_left_time = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentVoteData> now_vote_data_array;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentVoteData> affiliation_vote_data_array;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentPolicyVoteData>  policy_vote_data_array;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentOwnershipNodData>  ownership_data_array;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentSloganData>  slogan_data_array;
//
//	//Koo
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentSeatData>  parliament_seat_data_array;			//의원 리스트
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	FNUIParliamentTotalSeatVoteData  total_seat_vote_data;					//의원 후보 등록 투표 리스트		- 그냥 TMap<int32, FNUIParliamentSeatVoteListData>로 바뀔 수 있음
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NUI|Data")
//	TArray<FNUIParliamentVoteResultData>  dismissal_vote_result_data_array;	//의원 후보 해임 투표 결과 리스트
//
//	void set_now_vote_data_array(TArray<FNUIParliamentVoteData> data_in) { now_vote_data_array = data_in; };
//	void set_affiliation_vote_data_array(TArray<FNUIParliamentVoteData> data_in) { affiliation_vote_data_array = data_in; };
//	void set_policy_vote_data_array(TArray<FNUIParliamentPolicyVoteData> data_in) { policy_vote_data_array = data_in; };
//	void set_ownership_data_array(TArray<FNUIParliamentOwnershipNodData> data_in) { ownership_data_array = data_in; };
//	void set_slogan_data_array(TArray<FNUIParliamentSloganData> data_in) { slogan_data_array = data_in; };
//	void set_vote_left_time_data(FNUIParliamentVoteLeftTimeData data_in) { vote_left_time_data = data_in; };
//
//	//의원 리스트
//	void set_parliament_member_data(TArray<FNUIParliamentSeatData>& parliament_member_data_array_in) { parliament_seat_data_array = parliament_member_data_array_in; }
//	
//	//의원 - 후보 등록 투표 데이터
//	void set_total_seat_vote_data(FNUIParliamentTotalSeatVoteData& total_seat_vote_data_in) { total_seat_vote_data  = total_seat_vote_data_in; }
//
//	//의원 - 후보 해임 투표 결과 리스트
//	void set_dismissal_vote_data(TArray<FNUIParliamentVoteResultData>& dismissal_vote_result_data_array_in) { dismissal_vote_result_data_array = dismissal_vote_result_data_array_in; }
//
//	FNUIParliamentData& operator=(const FNUIParliamentData& data)
//	{
//		faction_id = data.faction_id;
//		faction_name = data.faction_name;
//		faction_icon_path = data.faction_icon_path;
//		faction_goods = data.faction_goods;
//		faction_session_count = data.faction_session_count;
//		faction_policy_count = data.faction_policy_count;
//		round_left_time = data.round_left_time;
//
//		vote_left_time_data = data.vote_left_time_data;
//		now_vote_data_array = data.now_vote_data_array;
//		affiliation_vote_data_array = data.affiliation_vote_data_array;
//		policy_vote_data_array = data.policy_vote_data_array;
//		ownership_data_array = data.ownership_data_array;
//		slogan_data_array = data.slogan_data_array;
//
//		seat_vote_left_time = data.seat_vote_left_time;
//		dismissal_vote_left_time = data.dismissal_vote_left_time;
//		parliament_seat_data_array = data.parliament_seat_data_array;
//		total_seat_vote_data = data.total_seat_vote_data;
//		dismissal_vote_result_data_array = data.dismissal_vote_result_data_array;
//
//		return *this;
//	}
//};
