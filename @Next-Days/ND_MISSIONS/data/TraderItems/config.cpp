class CfgPatches
{
	class ND_MISSIONS_data_TraderItems
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"ND_MISSIONS_data"
		};
	};
};
class CfgVehicles
{
	class Static;
	class Inventory_Base: Static
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Edible_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Container_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemOptics: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Box_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemSuppressor: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SeedBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pelt_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Trap_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ExplosivesBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=110;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Powered_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WorldContainer_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_CarKey_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_HouseKey_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Transmitter_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Dynamite_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=110;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Book_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=190;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Clothing_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FishingRod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Atlasbipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FGrip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AlarmClock_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_AccesCard_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=0;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BarbedBaseballBat: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bark_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AFG_02_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BaseballBat: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BrassKnuckles_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Flag_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=164;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_sight_mount_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Bipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GhillieAtt_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=1;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Chemlight_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Kabar_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMPX_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=114;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NailedBaseballBat: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CigarettePack_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pen_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=190;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_PKPBIPOD_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Shotgunchoke_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=115;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_VSSKbipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=121;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M200Bipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=121;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M200Stock_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=121;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M249Bipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M249Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M249HG_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M249Stock_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Sightcraft_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Spraycan_ColorBase: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SKS_Bayonet_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=116;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_AccessCard_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_BurningShard_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Bipod_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_AdapterBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AN94_AdapterBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AN94_PlasticBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MAR10_Bttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_ADARBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_CMMG_RIPBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_Mk20Bttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_StndBttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SAW_RIS_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AFG_RIS_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AFG_MLOCK_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_BCM_MLOCK_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_RVG_RIS_Grip_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_ADDHndgrd_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_CMMG15Hndgrd_MLOCK_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_CMMG9Hndgrd_MLOCK_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_ADAR_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_DD12_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_DD9_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_DD_FSP_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_SMR13_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Handguard_M4_SMR9_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_Hndgrd_RIS_FDE_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_MREXHndgrd_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_StndHndgrd_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M16_Bttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_MagpulPRSGen3Bttstck_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M16_KACHndgrd_RIS_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B47HelmetCover_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=37;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MICH2000Helmet_Cover_Base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=37;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Clothing: Clothing_Base
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarDoor: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_hndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_rail_hndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBags: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBud: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarWheel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_Empty: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CombinationLock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Cash: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_RollingPapers: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Spear: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=178;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemCompass: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=133;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemMap: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=132;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RemoteDetonator: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TFH_rail_hndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_PlasticHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_RISHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Card: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=138;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Workbench: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Flashlight: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GardenLime: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hacksaw: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemBarrel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemGPS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Paper: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=190;
			Price=1500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_PistolGripColtA2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Torch: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_RailHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Fal_OeBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magnum_Cylinder: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magnum_Ejector: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_geiger_counter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=197;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_556_Barrel10: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_556_Barrel14: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_556_Barrel16: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_556_Barrel14_DV: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Battery9V: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_printer_filament_abs: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ACR_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_GADAR: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SADAR_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AK19_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AK_AR_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Ramrod_Brush: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AK_HG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Ramrod_AK74: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Ramrod_AK_With_Brush: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AK19Muzzel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AK308Muzzel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AN94_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_module_surge: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR10: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK10: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR13: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK13: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR15: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK15: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_HGGS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_HG625: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR07: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK7: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR08: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MCMR09: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK9: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_HGMlok: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GorkaHelmetVisor: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=41;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena3_exp1: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena3_exp2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena3_august: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena3_october: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AtlasBipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BandageDressing: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BarbedWire: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BatteryCharger: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PP19_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BloodBagFull: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BloodBagEmpty: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BloodTestKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Blowtorch: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoneBait: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoneHook: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoneKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bone: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=193;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BrakeFluid: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=1200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Broom: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BurlapSack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BurlapStrip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ButaneCanister: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Button_Pin_Radioactive: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CableReel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=162;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CamoNet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CamoNetShelter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=186;
			Price=4500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Tripod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CanOpener: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Candle: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CannabisSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Workbench_Kit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Paddle: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarBattery: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarRadiator: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class carbine_base: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=35;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Cassette: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Relief_Balm: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Cigarette: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Cleaver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CombatKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Spotlight: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=162;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CookingStand: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CoreClass: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_FGCR_Grip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Crowbar: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CrudeMachete: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Defibrillator: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=197;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TrumpetParts: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=116;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DoorTestCamera: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_DryPost_Kit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_DryPost: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_DSAHG2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_DSAHG1: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUDSASA58_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DuctTape: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class EasterEgg: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ElectronicRepairKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_module_ext: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_module_ext2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_EmptyBag: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Empty: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class EpoxyPutty: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FangeKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FarmingHoe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FenceKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=165;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FieldShovel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FireExtinguisher: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FirefighterAxe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=179;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Firewood: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FireworksLauncher: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bait: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hook: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TerritoryFlagKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=165;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mace: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=178;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FryingPan: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=184;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PortableGasLamp: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GP5GasMask_Filter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=18;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GasMask_Filter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=18;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PortableGasStove: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GiftWrapPaper: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=190;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GlowPlug: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Golden_Winged_Pin: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GrozaGL_LowerReceiver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Groza_LowerReceiver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WeaponCleaningKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=127;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hammer: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HandDrillKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HandSaw: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HandcuffKeys: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Handcuffs: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=179;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HayHook: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HeadlightH7: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Heatpack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_HeramuzzelF: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HockeyStick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HumanSkull: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HuntingKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_oxygenated_blood: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChickenFeather: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=193;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Iceaxe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=179;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NewHockeyStick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena_action1: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GasMask_Filter_Improvised: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=18;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AntiPestsSpray: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BloodBagIV: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SalineBagIV: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class StartKitIV: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_FoldingBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_PlasticBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_PlasticHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_WoodBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK74_WoodBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_WoodHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK74_Hndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_FGKAC_Grip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=114;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AKS74U_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KitchenKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KitchenTimer: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KukriKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_module_lantia: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Fal_FoldingBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LargeGasCanister: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Stone: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherSewingKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lehs_battery: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_blueprint_lehs: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=165;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lehs_helmet_visor: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=41;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lehs_o2tank: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PetrolLighter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Lockpick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=189;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LongWoodenStick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_LVOAHG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_M16_rail_mount: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GCGN_M1Garand_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M249_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M249_Hndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M249_RisHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SCQR_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MOE_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_PRSGen3_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SBA_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M4SS_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_UBR_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M9A1_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_CQBBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_MPBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_MPHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_OEBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M60_ScopeMount: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M60_Handguard_E3: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M60_Handguard_E4: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Machete: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Matchbox: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MeatTenderizer: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=184;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Thermometer: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=197;
			Price=1600;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_MediumBox: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MediumGasCanister: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Megaphone: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MessTin: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MetalWire: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK47HG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK47Muzzel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MK47_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_raid_driver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MOEFS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MOELS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mosin_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=116;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class EngineOil: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_detector: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_module_card: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Nail: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=25;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena_action2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Netting: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class OrientalMachete: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackBlue: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackBlackFrost: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackFuture: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackNomad: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackSkunk: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackStardawg: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PepperSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PumpkinSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackKush: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsPackS1: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_TobaccoSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TomatoSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ZucchiniSeedsPack: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Debitcard: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=139;
			Price=100;
			CanBuy=1;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_netanyas_log: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_log_1: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_log_2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_log_3: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_log_4: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_log_5: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pickaxe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pipe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PipeWrench: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pitchfork: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoodenPlank: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_meme_banana: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_PlasticRoll: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pliers: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_PlotPoleKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=164;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_PlotPole: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=164;
			Price=5000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PoliceBaton: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PowerGenerator: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=162;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_athena_planning: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lantia_december: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lantia_vega7: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Radio: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rag: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Red9Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Refridgerator: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=162;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Roadflare: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=2400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rope: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SA58_Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SalineBag: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Screwdriver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SewingKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MP5k_StockBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MP5_PlasticHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MP5_RailHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SharpWoodenStick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=90;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Whetstone: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=175;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MetalPlate: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ShelterKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=165;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sheriff_Badge: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoodenStick: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shovel: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_PlasticWrapper: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sickle: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SKS_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=116;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SledgeHammer: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_SmallBox: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmallGasCanister: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=185;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmallStone: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUChiappaRhino_Cylinder: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUChiappaRhino_Ejector: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMagnum500_Cylinder: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMagnum500_Ejector: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUSWM629_Cylinder: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUSWM629_Ejector: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class InjectionVial: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SparkPlug: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Splint: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=1200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoodAxe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=179;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SR3Grip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SR3HG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_WSR3Stock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR47_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MuzzelFF: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SteakKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class StoneKnife: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=177;
			Price=500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sword: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=178;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ClearSyringe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BloodSyringe: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TannedLeather: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Fabric: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TelescopicBaton: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_vinyl_bubson: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LugWrench: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TireRepairKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=210;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Tobacco: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TruckBattery: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CBDCrudeOil: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_UZI_rail_mount: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=114;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Bagger: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Saiga_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=115;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_vega7_enzyme: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=137;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WatchtowerKit: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=165;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HescoBox: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoodenLog: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Wrench: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_tool_watch: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_tool_watch2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class XmasLights: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=162;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMount: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Preload2DTTC_G28_Optic: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_OpticMount_M16: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_bttstk: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Barrel_76239: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Barrel_76254: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_RifleFrame: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMOD_AFG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_AFG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_VFG: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock3: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock_Morty: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock_CAR15: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock_AK12: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_Barrel_556: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_Barrel_762: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_RifleFrame: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_ButtstockHK: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Buttstock_Honey: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_MPXMCX1_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_MPXMCX1_Bttstck2: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_MPXMCXSPEAR_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_SVT40_Bayonet: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=116;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_MPXMCX2_Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_MVRIBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_Zenit_PT1Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_VadapterBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AKS74U_WoodHndgrd: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AKS74U_CAAHndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AKS74U_ZenitB11PlasticHndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_ZenitB30B31Hndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_Tactica_Tula10000Receiver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_B33Receiver: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M14_Adapter: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_EBR_butt: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_MagpulZhukovBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_B5PrecisionBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_FABDGLCoreBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_CNCC39Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_ZenitPT2Bttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_WoodBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKP_PlasticBttstck: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_ZenitRK1B25U_RIS_Grip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Zenit_RK4_RIS_Grip: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_MagpulMOEHndgrd_MLOCK: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_MagpulZhukovHndgrdU_MLOCK: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_ZenitB10MB19Hndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_KACHndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_LancerHndgrd_MLOCK: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_NoveskeHndgrd_Short_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_NoveskeHndgrd_Long_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AR10_URXHndgrd_MLOCK: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_ZenitB50Hndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKP_CNCC46Hndgrd_RIS: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M240_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M249_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKP_Bipod: Inventory_Base
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MushroomBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bottle_Base: Edible_Base
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_ColorBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FoodCan_250g_ColorBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FoodCan_100g_ColorBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Snack_ColorBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=172;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Zagorky_ColorBase: Edible_Base
	{
		class TraderItem
		{
			CategoryID=172;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DisinfectantSpray: Edible_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class VitaminBottle: Edible_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Apple: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DisinfectantAlcohol: Edible_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Banana: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BearSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CowSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bitterlings: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoarSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Cannabis: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TacticalBaconCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BakedBeansCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PeachesCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SardinesCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SpaghettiCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TunaCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Carp: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarpFilletMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoxCerealCrunchin: Edible_Base
	{
		class TraderItem
		{
			CategoryID=172;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PainkillerTablets: Edible_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Worm: Edible_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SambucusBerry: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Lard: Edible_Base
	{
		class TraderItem
		{
			CategoryID=193;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FoxSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Guts: Edible_Base
	{
		class TraderItem
		{
			CategoryID=193;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RabbitLegMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Honey: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HumanSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CharcoalTablets: Edible_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GoatSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChickenBreastMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PurificationTablets: Edible_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class IodineTincture: Edible_Base
	{
		class TraderItem
		{
			CategoryID=194;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Kiwi: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mackerel: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MackerelFilletMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MouflonSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SheepSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Orange: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pear: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Potato: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GreenBellPepper: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Plum: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PigSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PowderedMilk: Edible_Base
	{
		class TraderItem
		{
			CategoryID=172;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pumpkin: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SlicedPumpkin: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=30;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rice: Edible_Base
	{
		class TraderItem
		{
			CategoryID=172;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CaninaBerry: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sardines: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmallGuts: Edible_Base
	{
		class TraderItem
		{
			CategoryID=193;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Marmalade: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TetracyclineAntibiotics: Edible_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Tomato: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class UnknownFoodCan: Edible_Base
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DeerSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WolfSteakMeat: Edible_Base
	{
		class TraderItem
		{
			CategoryID=191;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Zucchini: Edible_Base
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemOptics_Base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Tango6T_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WaterPouch_ColorBase: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Aimpoint_ACO_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Aimpoint_M5_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Docter_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Elcan_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_EOTech_EXPS3_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Leupold_Mark8_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Kahles_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Nightforce_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Trijicon_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Kobra_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Walther_Base: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Bandit_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Facemask_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Scarf_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNP45_MRDSOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NBCBootsBase: Clothing
	{
		class TraderItem
		{
			CategoryID=29;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NBCGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=26;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NBCHoodBase: Clothing
	{
		class TraderItem
		{
			CategoryID=21;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NBCJacketBase: Clothing
	{
		class TraderItem
		{
			CategoryID=25;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NBCPantsBase: Clothing
	{
		class TraderItem
		{
			CategoryID=28;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BallisticHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bandana_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MilitaryBeret_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=36;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoonieHat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CargoPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class UKAssVest_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TaloonBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BalaclavaMask_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TacticalShirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HighCapacityVest_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WorkingGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_LNormalized_Suppressor_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Normalized_Suppressor_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUSR3_SuppBase: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PUScopeOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BUISOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Canteen: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Armband_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AssaultBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MilitaryBoots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=46;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AthleticShoes_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SportGlasses_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Balaclava3Holes_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PressVest_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=155;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BaseballCap_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BeanieHat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Blouse_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BomberJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Breeches_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MiniDress_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class OMNOGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=43;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTsKOJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CowboyHat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CanvasPantsMidi_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class USMCJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class USMCPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Defender_Vest_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ShortJeans_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Skirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BubbleGoose_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DressShoes_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DryBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DirtBikeHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AliceBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=7000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M65Jacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FirefightersHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FirefighterJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FirefightersPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FlatCap_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ballerinas_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Galife_Pants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GhillieTop_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=8;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GhillieHood_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=1;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GhillieBushrag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=8;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GhillieSuit_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=8;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ConstructionHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HikingBoots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HikingJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CanvasPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HockeyHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hoodie_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CombatBoots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HuntingJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HunterPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Jeans_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Kneepads_Jeans_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JPC_Vest_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JumpsuitJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JumpsuitPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JungleBoots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=46;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Layered_Shirt_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherSack_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherBelt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=152;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Leather_Cloak_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherHat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherShirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherShoes_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherStorageVest_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=155;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ManSuit_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_chestrig_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MotoHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DarkMotoHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MountainBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NurseDress_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Kirza_Boots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ParamedicJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ParamedicPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GorkaEJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GorkaPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoolCoat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Plague_Mask_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class QuiltedJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RadarCap_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Raincoat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RidersJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Round_Glasses_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=41;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JoggingShoes_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Scarf_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MedicalScrubsHat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MedicalScrubsPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MedicalScrubsShirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChildBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SkateHelmet_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SK8_Sneakers_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Skinny_Jeans_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Slouch_Hat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sneakers_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Leggings_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SlacksPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SurgicalGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sweater_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CoyoteBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TacticalGloves_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=43;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Tactical_Leg_Holster_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TrackSuitJacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TrackSuitPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HikingBootsLow_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TShirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tt_vest_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ushanka_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Wellies_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winter_Parka_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WitchHood_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=146;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WomanSuit_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Wool_GreatCoat_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WorkingBoots_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ZmijovkaCap_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Maska1sh_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=39;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6sh112_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_CamelBakBag_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pants_6sh122_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_CargoPantsShort_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_G3CombatPants_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6sh122Jacket_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_G3CombatShirt_ColorBase: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AVS_Zipper_Panel_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=49;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MAP_Backpacks_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B43Vest_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Vest_AVS_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Vest_IMTV_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Vest_JPC_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Vest_LV_MBAV_Base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUAR15_SPR_SQSIL_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUAR15_SPR_SIL_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUKivaari_338_Supp_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK74_Compensator_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Snafu_ScarH_SIL_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_50bmg_Suppressor_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Agram_Suppressor_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_MPX_Suppressor_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMDAR_SuppBase: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SR25_Supp_Base: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KazuarOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ACOGOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ACOGOptic_6x: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ReflexOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M68Optic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Crossbow_RedpointOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PistolOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HuntingOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KobraOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LongrangeOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_CarryHandleOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class StarlightOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class KashtanOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GrozaOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PSO1Optic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PSO11Optic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_T3NRDSOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_HuntingOptic: ItemOptics_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=25000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Cauldron: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=184;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pot: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=184;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Vodka: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CanisterGasoline: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=204;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WaterBottle: Bottle_Base
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Grenade_Base: ExplosivesBase
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mich2001Helmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PlateCarrierHolster: Clothing
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GasMask: Clothing
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PlateCarrierVest: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GorkaHelmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NylonKnifeSheath: Clothing
	{
		class TraderItem
		{
			CategoryID=159;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WeldingMask: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_apsi: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmershVest: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class assault_pack_base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AviatorGlasses: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ballistic_earcover_base: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Medium_Sleeves_Shirt: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_Bayonet_Sheath: Clothing
	{
		class TraderItem
		{
			CategoryID=51;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BDUJacket: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BDUPants: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivilianBelt: Clothing
	{
		class TraderItem
		{
			CategoryID=152;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ImprovisedBag: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CourierBag: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BurlapSackCover: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class camelback_base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class carrier_backpack_base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DesignerGlasses: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ThickFramesGlasses: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TortillaBag: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTSKOBoots: Clothing
	{
		class TraderItem
		{
			CategoryID=46;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ssh68Helmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTSKOPants: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CrookedNose: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DenimJacket: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NioshFaceMask: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DirtBikeHelmet_Mouthguard: Clothing
	{
		class TraderItem
		{
			CategoryID=148;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DirtBikeHelmet_Visor: Clothing
	{
		class TraderItem
		{
			CategoryID=148;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Eyepatch: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class facemask_base: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class falconbelt_base: Clothing
	{
		class TraderItem
		{
			CategoryID=44;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ZSh3PilotHelmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FlipFlops_Colorbase: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FurImprovisedBag: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FurCourierBag: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GP5GasMask: Clothing
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GreatHelm: Clothing
	{
		class TraderItem
		{
			CategoryID=145;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class heavyvest_base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=25000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HockeyMask: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HuntingBag: Clothing
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HuntingVest: Clothing
	{
		class TraderItem
		{
			CategoryID=155;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChestHolster: Clothing
	{
		class TraderItem
		{
			CategoryID=158;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class EyePatch_Improvised: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FaceCover_Improvised: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HandsCover_Improvised: Clothing
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HeadCover_Improvised: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LegsCover_Improvised: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PumpkinHelmet: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class High_Knee_Sneakers: Clothing
	{
		class TraderItem
		{
			CategoryID=154;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LabCoat: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LargeTentBackPack: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LeatherKnifeSheath: Clothing
	{
		class TraderItem
		{
			CategoryID=159;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lehs: Clothing
	{
		class TraderItem
		{
			CategoryID=126;
			Price=150000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_lehs_helmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Military_Sweater: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mk5_vest_base: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_patch_rubber_base: Clothing
	{
		class TraderItem
		{
			CategoryID=35;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_patch_fabric_base: Clothing
	{
		class TraderItem
		{
			CategoryID=35;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_armored_helmet_visor_up: Clothing
	{
		class TraderItem
		{
			CategoryID=41;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_armored_helmet_visor_down: Clothing
	{
		class TraderItem
		{
			CategoryID=41;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_tactical_pants_base: Clothing
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_tactical_shirt_base: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmps_bag_base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AirborneMask: Clothing
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NVGHeadstrap: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class OfficerHat: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class operatorshirt_base: Clothing
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PoliceJacketOrel: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PolicePantsOrel: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_gorkahood_colorbase: Clothing
	{
		class TraderItem
		{
			CategoryID=38;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PilotkaCap: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PMK_5A_Gas_Mask: Clothing
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PoliceCap: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PoliceJacket: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PolicePants: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WindstridePoncho: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PrisonerCap: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PrisonUniformJacket: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PrisonUniformPants: Clothing
	{
		class TraderItem
		{
			CategoryID=153;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MouthRag: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ragged_Eyepatch: Clothing
	{
		class TraderItem
		{
			CategoryID=143;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ReflexVest: Clothing
	{
		class TraderItem
		{
			CategoryID=155;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RopeBelt: Clothing
	{
		class TraderItem
		{
			CategoryID=152;
			Price=1000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SantasBeard: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SantasHat: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SkullMask: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ThinFramesGlasses: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChernarusSportShirt: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PoliceVest: Clothing
	{
		class TraderItem
		{
			CategoryID=155;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class supplybag_base: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SurgicalMask: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tac_goggles_blue_base: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tac_goggles_clear_base: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tac_goggles_red_base: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MilitaryBelt: Clothing
	{
		class TraderItem
		{
			CategoryID=44;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TacticalGoggles: Clothing
	{
		class TraderItem
		{
			CategoryID=149;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tactical_visor_base: Clothing
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TankerHelmet: Clothing
	{
		class TraderItem
		{
			CategoryID=37;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TelnyashkaShirt: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Gekoseasteregg: Clothing
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmershBag: Clothing
	{
		class TraderItem
		{
			CategoryID=48;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winter_Parka_Green: Clothing
	{
		class TraderItem
		{
			CategoryID=150;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WitchHat: Clothing
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PMK4GasMask: Clothing
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Maska1Visor: Clothing
	{
		class TraderItem
		{
			CategoryID=39;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Maska1SchVisor: Clothing
	{
		class TraderItem
		{
			CategoryID=39;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B43PelvisArmor: Clothing
	{
		class TraderItem
		{
			CategoryID=35;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Foil_base: Clothing
	{
		class TraderItem
		{
			CategoryID=36;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6kh5KnifeSheath: Clothing
	{
		class TraderItem
		{
			CategoryID=51;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_FannyPack_Coyote: Clothing
	{
		class TraderItem
		{
			CategoryID=44;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B23_112Vest: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B23Vest: Clothing
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_308_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_VSS_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HB_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ACR_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK74_Suppressor_2: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKM_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKS74U_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AN94_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_APS_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SMG_Suppressor1: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_EVO_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK74_Zen_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Groza_Barrel_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Groza_Barrel_Grip: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Groza_Barrel_Short: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR47_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GCGN_M1Garand_Supp: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GCGN_M1Garand_FlashHider: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MakarovPBSuppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mosin_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK74_Suppressor_1: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PistolSuppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ImprovisedSuppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=5000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_PP19_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MP5_Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR1_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR25_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDK_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVD_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_TT_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUGevar_Suppressor_Black: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SPMOD: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_PistolSuppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Honey_Suppressor_BASE: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_MCX_Spear_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_M14Suppressor_BASE: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Universal_Suppressor_BASE: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MakarovPB_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_OTs_14_Groza_Suppressor: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_OTs_14_Groza_Barrel_Grip: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_6ch43Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_6ch63Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_6ch76Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_6p20Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_ZenitDTK1Compensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PKM_SAICompensator: ItemSuppressor
	{
		class TraderItem
		{
			CategoryID=120;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickBase: Container_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Switchable_Base: Powered_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GiftBox_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TentBase: Container_Base
	{
		class TraderItem
		{
			CategoryID=136;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M18SmokeGrenade_ColorBase: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=107;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Barrel_ColorBase: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WaterproofBag_ColorBase: Container_Base
	{
		class TraderItem
		{
			CategoryID=157;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mag_pouch_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Bear_ColorBase: Container_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FishingRod_Base_New: FishingRod_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RDG2SmokeGrenade_ColorBase: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=107;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Bipod_Base: SNAFU_Atlasbipod_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_LStandardized_Suppressor_Base: SNAFU_LNormalized_Suppressor_Base
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Standardized_Suppressor_Base: SNAFU_Normalized_Suppressor_Base
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Tango6T_AR_Base: SNAFU_Tango6T_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Tango6T_AK_Base: SNAFU_Tango6T_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_Tango6T_M_Base: SNAFU_Tango6T_Base
	{
		class TraderItem
		{
			CategoryID=123;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Headtorch_ColorBase: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=148;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_PEQ1_Base: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BaseRadio: Transmitter_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MOE_Grip_Base: TF_AR_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_OMRG_Grip_Base: TF_AR_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_TDS_Grip_Base: TF_AR_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_KGB_MG47_Grip_Base: TF_AK_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_MOE_Base: TF_AK_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_TAPCO_Base: TF_AK_Grip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Buttpack_6sh112_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Mag3_AVS_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Mag3_FastMag_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Med_AFAK_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Gren2_AVS_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Utility_Large_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Mag3_JPC_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Dump_Mag_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Gren_3g_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Gren_2g_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_LMG_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_LMG_M4Pouch_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Mag2_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Mag3_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Med_v1_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_Pouch_Med_v2_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MedPouch3_Base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ClaymoreMine: ExplosivesBase
	{
		class TraderItem
		{
			CategoryID=109;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ImprovisedExplosive: ExplosivesBase
	{
		class TraderItem
		{
			CategoryID=110;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Plastic_Explosive: ExplosivesBase
	{
		class TraderItem
		{
			CategoryID=110;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_storage_openable_noLock_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_storage_placeable_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_storage_openable_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox: Container_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Epinephrine: Container_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PlateCarrierPouches: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmallProtectorCase: Container_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PersonalRadio: Transmitter_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TLRLight: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JPC_Bottle_Base: Canteen
	{
		class TraderItem
		{
			CategoryID=35;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FireplaceBase;
	class BarrelHoles_ColorBase: FireplaceBase
	{
		class TraderItem
		{
			CategoryID=165;
			Price=8000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AD_Pilad_Base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_VORTEX_Base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JPCsheath_Base: NylonKnifeSheath
	{
		class TraderItem
		{
			CategoryID=51;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PlateCarrierHolster_ColorBase: PlateCarrierHolster
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Canvas_Backpack_Base: TaloonBag_ColorBase
	{
		class TraderItem
		{
			CategoryID=156;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ShelterBase: TentBase
	{
		class TraderItem
		{
			CategoryID=186;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_ElcanSpecterDROptic_Base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_ElcanSpecterDR_6xOptic_Base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_EOTechXPSOptic_Base: FNP45_MRDSOptic
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PK122_ValdayOptic_Base: FNP45_MRDSOptic
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_SCAR_Suppressor_Base: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=25000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_PBS1Suppressor_Base: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_SOCOMSuppressor_Base: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MAR_10_Suppressor_Base: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B47Helmet_Base: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_LSHZHelmet_ColorBase: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_MICH2000Helmet_Base: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_WeldingMask_Base: WeldingMask
	{
		class TraderItem
		{
			CategoryID=39;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_AdminCarKey: alp_CarKey_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_CarKey: alp_CarKey_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=3500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Dynamite: alp_Dynamite_Base
	{
		class TraderItem
		{
			CategoryID=110;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_AdminHouseKey: alp_HouseKey_Base
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_HouseKey: alp_HouseKey_Base
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ItemBook: Book_Base
	{
		class TraderItem
		{
			CategoryID=190;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_22_50Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AACBLK_AmmoBox_20rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_308Win_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_308WinTracer_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_357_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=94;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_380_35rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_45ACP_25rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=101;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_00buck_10rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_12gaSlug_10Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_12gaRubberSlug_10Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 57x28_AmmoBox_25rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 57x28AP_AmmoBox_25rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_545x39_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=79;
			Price=30;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_545x39Tracer_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=79;
			Price=30;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_556x45_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_556x45Tracer_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 792x57FOX_AmmoBox_20rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=88;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 762x25fox_AmmoBox_35rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_762x39_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_762x39Tracer_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_762x54_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_762x54Tracer_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 93x64_AmmoBox_20rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=89;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 9x18_AmmoBox_35rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_9x19_25rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class 9x21FOX_AmmoBox_25rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_9x39AP_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_9x39_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HeadlightH7_Box: Box_Base
	{
		class TraderItem
		{
			CategoryID=205;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NailBox: Box_Base
	{
		class TraderItem
		{
			CategoryID=160;
			Price=25;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_12gaBeanbag_10Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Pouch: Container_Base
	{
		class TraderItem
		{
			CategoryID=157;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarTent: Container_Base
	{
		class TraderItem
		{
			CategoryID=186;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CompostBin: Container_Base
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class double_magpouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FirstAidKit: Container_Base
	{
		class TraderItem
		{
			CategoryID=157;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class holster_pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JPCammo_pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class JPCMed_Pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LargeTent: Container_Base
	{
		class TraderItem
		{
			CategoryID=186;
			Price=4500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MediumTent: Container_Base
	{
		class TraderItem
		{
			CategoryID=186;
			Price=4500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mk5_grenade_pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mk5_utility_pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_gun_rack_planks: Container_Base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_tent_placeable_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Morphine: Container_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AntiChemInjector: Container_Base
	{
		class TraderItem
		{
			CategoryID=195;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SeaChest: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tactical_pouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class triple_magpouch_base: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WoodenCrate: Container_Base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SA58_FGrip: FGrip_Base
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GiftBox_Large: GiftBox_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=600;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GiftBox_Medium: GiftBox_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GiftBox_Small: GiftBox_Base
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M67Grenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FlashGrenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RGD5Grenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Grenade_ChemGas: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_PolarBearPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BearPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WildboarPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CowPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DeerPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GoatPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RabbitPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MouflonPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FoxPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PigPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SheepPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WolfPelt: Pelt_Base
	{
		class TraderItem
		{
			CategoryID=192;
			Price=6000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CattleProd: Powered_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class StunBaton: Powered_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Chainsaw: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUUniversalLight: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class UniversalLight: Switchable_Base
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BearTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FishNetTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LandMineTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=109;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SmallFishTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RabbitSnareTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=174;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TripwireTrap: Trap_Base
	{
		class TraderItem
		{
			CategoryID=109;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RefrigeratorMinsk: WorldContainer_Base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Refrigerator: WorldContainer_Base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TrashCan: WorldContainer_Base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_50AE: Box_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_3006_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_300blk_20rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_303_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_338mm_10Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=91;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_4570_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=101;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_50Beo_20rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Ammobox_50BMG_10rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_8mm_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=90;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_277_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=85;
			Price=70;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_792x33_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=88;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_4630_20Rnd: Box_Base
	{
		class TraderItem
		{
			CategoryID=78;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AmmoBox_44Mag: Box_Base
	{
		class TraderItem
		{
			CategoryID=100;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_EMPGrenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PhosphorusGrenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_TeargasGrenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_ChemicalGrenade: Grenade_Base
	{
		class TraderItem
		{
			CategoryID=108;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B43MagPouch: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_6B43GrenPouch: Container_Base
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money: alp_Cash
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Coin: alp_Cash
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Door_1_1: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NVGoggles: ItemOptics
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Door_1_1: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanDoors_Driver: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Door_1_1: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_Wheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_CoinRare: alp_Coin
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackDoors_Driver: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_Door_1_1: CarDoor
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Wheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Wheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanWheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Wheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Door_1_2: Hatchback_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_box_kit: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_old_table_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_WheelDouble: Truck_01_Wheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Fingerless_Gloves: WorkingGloves_ColorBase
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_LifeInsuranceExclusive: alp_Card
	{
		class TraderItem
		{
			CategoryID=138;
			Price=50000;
			CanBuy=1;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Coin1: alp_Coin
	{
		class TraderItem
		{
			CategoryID=141;
			Price=1;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Coin2: alp_Coin
	{
		class TraderItem
		{
			CategoryID=141;
			Price=2;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Coin5: alp_Coin
	{
		class TraderItem
		{
			CategoryID=141;
			Price=5;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_CoinRare1: alp_CoinRare
	{
		class TraderItem
		{
			CategoryID=140;
			Price=500000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money10: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=10;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money20: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=20;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money50: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money100: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money500: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Money1000: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD1: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=20;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD5: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD10: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD20: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=400;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD50: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD100: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD500: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_USD1000: alp_Money
	{
		class TraderItem
		{
			CategoryID=141;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_POX: AmmoBox
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_Explosive: AmmoBox
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmmoBox_556: AmmoBox
	{
		class TraderItem
		{
			CategoryID=126;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class balaclava_base: BalaclavaMask_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_BallisticHelmet_White: BallisticHelmet_ColorBase
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_bandana_wintercamopattern: Bandana_ColorBase
	{
		class TraderItem
		{
			CategoryID=39;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_boonie_base: BoonieHat_ColorBase
	{
		class TraderItem
		{
			CategoryID=144;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackHood: CarDoor
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackTrunk: CarDoor
	{
		class TraderItem
		{
			CategoryID=209;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Hood: CarDoor
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Trunk: CarDoor
	{
		class TraderItem
		{
			CategoryID=209;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_Hood: CarDoor
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanHood: CarDoor
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanTrunk: CarDoor
	{
		class TraderItem
		{
			CategoryID=209;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Hood: CarDoor
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Trunk: CarDoor
	{
		class TraderItem
		{
			CategoryID=209;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class combatpants_base: CargoPants_ColorBase
	{
		class TraderItem
		{
			CategoryID=45;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackWheel: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackWheel_Ruined: CarWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanDoors_CoDriver: CivSedanDoors_Driver
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanDoors_BackLeft: CivSedanDoors_Driver
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanDoors_BackRight: CivSedanDoors_Driver
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CivSedanWheel_Ruined: CivSedanWheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CombinationLock4: CombinationLock
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CodeLock: CombinationLock
	{
		class TraderItem
		{
			CategoryID=161;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagBlackFrost: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagBlue: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagFuture: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagNomad: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagKush: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagS1: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagSkunk: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBagStardawg: CP_CannabisBags
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickBlackFrost: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickBlue: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickFuture: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickNomad: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickKush: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickS1: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickSkunk: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBrickStardawg: CP_CannabisBrickBase
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBlackFrost: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisBlue: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisFuture: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisNomad: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisKush: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisS1: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSkunk: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisStardawg: CP_CannabisBud
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CigarettePack_Chernamorka: CP_CigarettePack_Empty
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CigarettePack_Merkur: CP_CigarettePack_Empty
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CigarettePack_Partyzanka: CP_CigarettePack_Empty
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointBlackFrost: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointBlue: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointFuture: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointNomad: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointKush: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointS1: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointSkunk: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_JointStardawg: CP_JointBase
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisS1: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisBlackFrost: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisBlue: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisFuture: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisNomad: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisKush: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisSkunk: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CigarettePack_CannabisStardawg: CP_JointPack
	{
		class TraderItem
		{
			CategoryID=173;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_RollingPapers_Green: CP_RollingPapers
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_RollingPapers_Silver: CP_RollingPapers
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Workbench_Holo: CP_Workbench
	{
		class TraderItem
		{
			CategoryID=196;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_DecontaminationSpray: DisinfectantSpray
	{
		class TraderItem
		{
			CategoryID=194;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_Anabolic: Epinephrine
	{
		class TraderItem
		{
			CategoryID=195;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Syringe: Epinephrine
	{
		class TraderItem
		{
			CategoryID=194;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Fingerless_Gloves_Wool: Fingerless_Gloves
	{
		class TraderItem
		{
			CategoryID=151;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Raycaster: Flashlight
	{
		class TraderItem
		{
			CategoryID=182;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BrisketSpread: FoodCan_100g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pate: FoodCan_100g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pajka: FoodCan_100g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PorkCan: FoodCan_250g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CatFoodCan: FoodCan_250g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DogFoodCan: FoodCan_250g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Lunchmeat: FoodCan_250g_ColorBase
	{
		class TraderItem
		{
			CategoryID=171;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_BttstckTac: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_Bttstck_Metal_Folding: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_Bttstck_Polimer_Folding: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_Bttstck_Wood: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HB_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_Bttstck_Zenit: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_ALPHA_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKM_Bttstck_Adapter: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ASVAL_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_EVO_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_BttstckPara: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_BttstckPolimer: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416A7_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416D_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK417_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KOMRAD_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_MP153_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SLR_AR15_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDK_Bttstck: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_UZI_Bttstck_metal: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=114;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_UZI_Bttstck_wood: FOX_Bttstck
	{
		class TraderItem
		{
			CategoryID=114;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_magpull_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_polimer_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_wood_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKM_wood_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKS74U_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_EVO_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_hndgrd_para: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_M16A3_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_PP19_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SOK94_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDS_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVD_hndgrd: FOX_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HB_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_rail_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_ALPHA_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKS74URIS_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FNFAL_hndgrd_rail: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416A7_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416D_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK417_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KOMRAD_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_M16A3_RIShndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_PP19_hndgrd_rail: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=113;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SLR_AR15_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=117;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR25_hndgrd: FOX_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_Compost: GardenLime
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_GasMaskCamo: GasMask
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_GasMaskWhite: GasMask
	{
		class TraderItem
		{
			CategoryID=22;
			Price=5000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_GorkaHelmet_White: GorkaHelmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_raidsaw: Hacksaw
	{
		class TraderItem
		{
			CategoryID=176;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Door_2_1: Hatchback_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Hood: Hatchback_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=208;
			Price=10500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Trunk: Hatchback_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=209;
			Price=9000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Door_2_2: Hatchback_02_Door_1_2
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Hatchback_02_Wheel_Ruined: Hatchback_02_Wheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HatchbackDoors_CoDriver: HatchbackDoors_Driver
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class HighCapacityVest_Black: HighCapacityVest_ColorBase
	{
		class TraderItem
		{
			CategoryID=47;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Aug_Barrel: ItemBarrel
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Compass: ItemCompass
	{
		class TraderItem
		{
			CategoryID=133;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class OrienteeringCompass: ItemCompass
	{
		class TraderItem
		{
			CategoryID=133;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GPSReceiver: ItemGPS
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_map_namalsk: ItemMap
	{
		class TraderItem
		{
			CategoryID=132;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ChernarusMap: ItemMap
	{
		class TraderItem
		{
			CategoryID=132;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AugOptic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Binoculars: ItemOptics
	{
		class TraderItem
		{
			CategoryID=135;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_IRONMODOptic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M14Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M79DummyOptics: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class GCGN_M84_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=25000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_gp_nvg_base: ItemOptics
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rangefinder: ItemOptics
	{
		class TraderItem
		{
			CategoryID=135;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SSG82Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M18SmokeGrenade_Red: M18SmokeGrenade_ColorBase
	{
		class TraderItem
		{
			CategoryID=107;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class striker_helmet_base: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_armored_helmet_base: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class tactical_helmet_base: Mich2001Helmet
	{
		class TraderItem
		{
			CategoryID=37;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MilitaryBeret_Red: MilitaryBeret_ColorBase
	{
		class TraderItem
		{
			CategoryID=36;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_woodbox_kit_base: mmg_box_kit
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_old_table: mmg_old_table_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_armored_cabinet_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_lockable_gun_rack_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_locker_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_locker02_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_old_safe_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_solo_locker_base: mmg_storage_openable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_army_box_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_crate03_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_crate03_unfinished_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=187;
			Price=1800;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_fridge_minsk_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_grenade_case_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_military_case_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_trashcan_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_wall_shelf_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_weapon_crate_base: mmg_storage_openable_noLock_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_craftable_gun_rack_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_gear_stand_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_gun_rack_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_gun_wall_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_palette_storage_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class mmg_toolwagon_base: mmg_storage_placeable_base
	{
		class TraderItem
		{
			CategoryID=163;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AgaricusMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AmanitaMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PsilocybeMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PleurotusMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class MacrolepiotaMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoletusMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LactariusMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AuriculariaMushroom: MushroomBase
	{
		class TraderItem
		{
			CategoryID=168;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCBootsCamo: NBCBootsBase
	{
		class TraderItem
		{
			CategoryID=29;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCBootsWhite: NBCBootsBase
	{
		class TraderItem
		{
			CategoryID=29;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCGlovesCamo: NBCGloves_ColorBase
	{
		class TraderItem
		{
			CategoryID=26;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCGlovesWhite: NBCGloves_ColorBase
	{
		class TraderItem
		{
			CategoryID=26;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCJacketCamo: NBCJacketBase
	{
		class TraderItem
		{
			CategoryID=25;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCJacketWhite: NBCJacketBase
	{
		class TraderItem
		{
			CategoryID=25;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCPantsCamo: NBCPantsBase
	{
		class TraderItem
		{
			CategoryID=28;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCPantsWhite: NBCPantsBase
	{
		class TraderItem
		{
			CategoryID=28;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCHoodCamo: NBCHoodBase
	{
		class TraderItem
		{
			CategoryID=21;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_NBCHoodWhite: NBCHoodBase
	{
		class TraderItem
		{
			CategoryID=21;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Door_2_1: Offroad_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Door_1_2: Offroad_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Door_2_2: Offroad_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Offroad_02_Wheel_Ruined: Offroad_02_Wheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PunchedCard: Paper
	{
		class TraderItem
		{
			CategoryID=137;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class headphones_base: PersonalRadio
	{
		class TraderItem
		{
			CategoryID=40;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KAR98_Optic: PUScopeOptic
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RemoteDetonatorReceiver: RemoteDetonator
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RemoteDetonatorTrigger: RemoteDetonator
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Door_2_1: Sedan_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Door_1_2: Sedan_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Door_2_2: Sedan_02_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Sedan_02_Wheel_Ruined: Sedan_02_Wheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsBlackFrost: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsBlue: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CannabisSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsFuture: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsNomad: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PepperSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PotatoSeed: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PumpkinSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsKush: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsS1: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsSkunk: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_CannabisSeedsStardawg: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CP_TobaccoSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TomatoSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class ZucchiniSeeds: SeedBase
	{
		class TraderItem
		{
			CategoryID=166;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Bandit_Green_color: Shemagh_Bandit_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Bandit_Black_color: Shemagh_Bandit_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Bandit_Checkered_Red_color: Shemagh_Bandit_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Bandit_Checkered_White_color: Shemagh_Bandit_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Green_color: Shemagh_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Black_color: Shemagh_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Checkered_Red_color: Shemagh_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Checkered_White_color: Shemagh_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Facemask_Green_color: Shemagh_Facemask_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Facemask_Black_color: Shemagh_Facemask_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Facemask_Checkered_Red_color: Shemagh_Facemask_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Facemask_Checkered_White_color: Shemagh_Facemask_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Scarf_Green_color: Shemagh_Scarf_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Scarf_Black_color: Shemagh_Scarf_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Scarf_Checkered_Red_color: Shemagh_Scarf_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shemagh_Scarf_Checkered_White_color: Shemagh_Scarf_ColorBase
	{
		class TraderItem
		{
			CategoryID=147;
			Price=300;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class dzn_phoenix_stash: SmallProtectorCase
	{
		class TraderItem
		{
			CategoryID=137;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_TACGripColtA2_BK: SNAFU_PistolGripColtA2
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_SR3Vikhr_Supp: SNAFUSR3_SuppBase
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Fronta: SodaCan_ColorBase
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Kvass: SodaCan_ColorBase
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Cola: SodaCan_ColorBase
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Pipsi: SodaCan_ColorBase
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SodaCan_Spite: SodaCan_ColorBase
	{
		class TraderItem
		{
			CategoryID=169;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SpearBone: Spear
	{
		class TraderItem
		{
			CategoryID=178;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SpearStone: Spear
	{
		class TraderItem
		{
			CategoryID=178;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class combatshirt_base: TacticalShirt_ColorBase
	{
		class TraderItem
		{
			CategoryID=42;
			Price=4000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PartyTent: TentBase
	{
		class TraderItem
		{
			CategoryID=186;
			Price=4500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ACR_hndgrd: TFH_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR47_hndgrd: TFH_rail_hndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LongTorch: Torch
	{
		class TraderItem
		{
			CategoryID=185;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_Door_2_1: Truck_01_Door_1_1
	{
		class TraderItem
		{
			CategoryID=207;
			Price=8500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_Wheel_Ruined: Truck_01_Wheel
	{
		class TraderItem
		{
			CategoryID=206;
			Price=6500;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Truck_01_WheelDouble_Ruined: Truck_01_WheelDouble
	{
		class TraderItem
		{
			CategoryID=206;
			Price=15000;
			CanBuy=0;
			CanSell=0;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class UKAssVest_Camo: UKAssVest_ColorBase
	{
		class TraderItem
		{
			CategoryID=47;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class alp_radboxtablets: VitaminBottle
	{
		class TraderItem
		{
			CategoryID=195;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class WaterPouch_Natural: WaterPouch_ColorBase
	{
		class TraderItem
		{
			CategoryID=170;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Aimpoint2000: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_VortexSE_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_VortexRHDAMG_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Matrix: Apple
	{
		class TraderItem
		{
			CategoryID=167;
			Price=200;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_EotechVudu_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_EotechVudu_AK_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_G28_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_G3_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_HAMR: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_HAMR_AK: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Elcan: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Elcan_AK: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Holo: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_BugBuster: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Pistol_Optic: FNP45_MRDSOptic
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Razor: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_SVT40_Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_Pistol_Light: TLRLight
	{
		class TraderItem
		{
			CategoryID=134;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Hndguard: AK_RailHndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_DMR_Hndguard: M4_RISHndgrd
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_FAL_RIS_Hndgrd: M4_RISHndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_FAL_Wood_Hndgrd: M4_PlasticHndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_FAL_Poly_Hndgrd: M4_PlasticHndgrd
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_FAL_Wood_Bttstck: Fal_OeBttstck
	{
		class TraderItem
		{
			CategoryID=119;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_44Mag_Cylinder: Magnum_Cylinder
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_44Mag_Ejector: Magnum_Ejector
	{
		class TraderItem
		{
			CategoryID=112;
			Price=750;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_DeltaPointOptic: FNP45_MRDSOptic
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_HAMROptic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_OKP7Optic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_OTs_14_GrozaOptic: ItemOptics
	{
		class TraderItem
		{
			CategoryID=123;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_6kh5Bayonet: AK_Bayonet
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4_ColtA2Optic: BUISOptic
	{
		class TraderItem
		{
			CategoryID=118;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AEK999_Suppressor: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AK_Rotor43Suppressor: M4_Suppressor
	{
		class TraderItem
		{
			CategoryID=125;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TFRifleSling_ColorBase;
	class TF_RifleSling_Black: TFRifleSling_ColorBase
	{
		class TraderItem
		{
			CategoryID=48;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_RifleSling_Brown: TFRifleSling_ColorBase
	{
		class TraderItem
		{
			CategoryID=48;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_RifleSling_OD: TFRifleSling_ColorBase
	{
		class TraderItem
		{
			CategoryID=48;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierVest_EMR: PlateCarrierVest
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierPouches_EMR: PlateCarrierPouches
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierHolster_EMR: PlateCarrierHolster
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierVest_Coyote: PlateCarrierVest
	{
		class TraderItem
		{
			CategoryID=47;
			Price=15000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierPouches_Coyote: PlateCarrierPouches
	{
		class TraderItem
		{
			CategoryID=49;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_PlateCarrierHolster_Coyote: PlateCarrierHolster
	{
		class TraderItem
		{
			CategoryID=50;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_NVGoggles_PVS14: NVGoggles
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_NVGoggles_PVS15: NVGoggles
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_NVGoggles_AVS9: NVGoggles
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_NVGoggles_PNV10T: NVGoggles
	{
		class TraderItem
		{
			CategoryID=124;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
};
