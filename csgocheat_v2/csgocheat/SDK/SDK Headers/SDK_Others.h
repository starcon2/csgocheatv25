#pragma once
#include "stdafx.h"

class IClientModeShared
{
public:
};

inline void VectorSubtract( const Vector& a, const Vector& b, Vector& c )
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//SRC SDK VECTORADD
inline void VectorAdd( const Vector& a, const Vector& b, Vector& c )
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

class bf_write
{
public:
	bf_write();

	// nMaxBits can be used as the number of bits in the buffer. 
	// It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
	bf_write( void* pData, int nBytes, int nMaxBits = -1 );

	bf_write( const char* pDebugName, void* pData, int nBytes, int nMaxBits = -1 );

	// Start writing to the specified buffer.
	// nMaxBits can be used as the number of bits in the buffer. 
	// It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
	void StartWriting( void* pData, int nBytes, int iStartBit = 0, int nMaxBits = -1 );

	// Restart buffer writing.
	void Reset();

	// Get the base pointer.
	unsigned char* GetBasePointer()
	{
		return ( unsigned char* )m_pData;
	}

	// Enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
	// but there may be the occasional buffer that is allowed to overflow gracefully.
	void SetAssertOnOverflow( bool bAssert );

	// This can be set to assign a name that gets output if the buffer overflows.
	const char* GetDebugName();

	void SetDebugName( const char* pDebugName );

	// Seek to a specific position.
public:

	void SeekToBit( int bitPos );

	// Bit functions.
public:

	void WriteOneBit( int nValue );

	void WriteOneBitNoCheck( int nValue );

	void WriteOneBitAt( int iBit, int nValue );

	// Write signed or unsigned. Range is only checked in debug.
	void WriteUBitLong( unsigned int data, int numbits, bool bCheckRange = true );

	void WriteSBitLong( int data, int numbits );

	// Tell it whether or not the data is unsigned. If it's signed,
	// cast to unsigned before passing in (it will cast back inside).
	void WriteBitLong( unsigned int data, int numbits, bool bSigned );

	// Write a list of bits in.
	bool WriteBits( const void* pIn, int nBits );

	// writes an unsigned integer with variable bit length
	void WriteUBitVar( unsigned int data );

	// writes a varint encoded integer
	void WriteVarInt32( uint32 data );

	void WriteVarInt64( uint64 data );

	void WriteSignedVarInt32( int32 data );

	void WriteSignedVarInt64( int64 data );

	int ByteSizeVarInt32( uint32 data );

	int ByteSizeVarInt64( uint64 data );

	int ByteSizeSignedVarInt32( int32 data );

	int ByteSizeSignedVarInt64( int64 data );

	// Copy the bits straight out of pIn. This seeks pIn forward by nBits.
	// Returns an error if this buffer or the read buffer overflows.
	bool WriteBitsFromBuffer( class bf_read* pIn, int nBits );

	void WriteBitAngle( float fAngle, int numbits );

	void WriteBitCoord( const float f );

	void WriteBitCoordMP( const float f, bool bIntegral, bool bLowPrecision );

	void WriteBitFloat( float val );

	void WriteBitVec3Coord( const Vector& fa );

	void WriteBitNormal( float f );

	void WriteBitVec3Normal( const Vector& fa );

	void WriteBitAngles( const Vector& fa );

	// Byte functions.
public:

	void WriteChar( int val );

	void WriteByte( int val );

	void WriteShort( int val );

	void WriteWord( int val );

	void WriteLong( long val );

	void WriteLongLong( int64 val );

	void WriteFloat( float val );

	bool WriteBytes( const void* pBuf, int nBytes );

	// Returns false if it overflows the buffer.
	bool WriteString( const char* pStr );

	// Status.
public:

	// How many bytes are filled in?
	int GetNumBytesWritten() const;

	int GetNumBitsWritten() const;

	int GetMaxNumBits();

	int GetNumBitsLeft();

	int GetNumBytesLeft();

	unsigned char* GetData();

	const unsigned char* GetData() const;

	// Has the buffer overflowed?
	bool CheckForOverflow( int nBits );

	inline bool IsOverflowed() const
	{
		return m_bOverflow;
	}

	void SetOverflowFlag();

public:
	// The current buffer.
	unsigned long* m_pData;
	int m_nDataBytes;
	int m_nDataBits;

	// Where we are in the buffer.
	int m_iCurBit;

private:

	// Errors?
	bool m_bOverflow;

	bool m_bAssertOnOverflow;
	const char* m_pDebugName;
};

enum weapons
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_DUALBERETTA,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_USP,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INC,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1S,
	WEAPON_USPS,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	KNIFE_BAYONET = 500,
	KNIFE_FLIP = 505,
	KNIFE_GUT,
	KNIFE_KARAMBIT,
	KNIFE_M9_BAYONET,
	KNIFE_TACTICAL,
	KNIFE_FALCHION = 512,
	KNIFE_SURVIVAL_BOWIE = 514,
	KNIFE_BUTTERFLY,
	KNIFE_PUSH,
	KNIFE_URSUS = 519,
	KNIFE_GYPSY_JACKKNIFE,
	KNIFE_STILETTO = 522,
	KNIFE_WIDOWMAKER
};

enum EClassIds
{
	_CAI_BaseNPC = 0,
	_CAK47,
	_CBaseAnimating,
	_CBaseAnimatingOverlay,
	_CBaseAttributableItem,
	_CBaseButton,
	_CBaseCombatCharacter,
	_CBaseCombatWeapon,
	_CBaseCSGrenade,
	_CBaseCSGrenadeProjectile,
	_CBaseDoor,
	_CBaseEntity,
	_CBaseFlex,
	_CBaseGrenade,
	_CBaseParticleEntity,
	_CBasePlayer,
	_CBasePropDoor,
	_CBaseTeamObjectiveResource,
	_CBaseTempEntity,
	_CBaseToggle,
	_CBaseTrigger,
	_CBaseViewModel,
	_CBaseVPhysicsTrigger,
	_CBaseWeaponWorldModel,
	_CBeam,
	_CBeamSpotlight,
	_CBoneFollower,
	_CBreakableProp,
	_CBreakableSurface,
	_CC4,
	_CCascadeLight,
	_CChicken,
	_CColorCorrection,
	_CColorCorrectionVolume,
	_CCSGameRulesProxy,
	_CCSPlayer,
	_CCSPlayerResource,
	_CCSRagdoll,
	_CCSTeam,
	_CDEagle,
	_CDecoyGrenade,
	_CDecoyProjectile,
	_CDynamicLight,
	_CDynamicProp,
	_CEconEntity,
	_CEmbers,
	_CEntityDissolve,
	_CEntityFlame,
	_CEntityFreezing,
	_CEntityParticleTrail,
	_CEnvAmbientLight,
	_CEnvDetailController,
	_CEnvDOFController,
	_CEnvParticleScript,
	_CEnvProjectedTexture,
	_CEnvQuadraticBeam,
	_CEnvScreenEffect,
	_CEnvScreenOverlay,
	_CEnvTonemapController,
	_CEnvWind,
	_CFireCrackerBlast,
	_CFireSmoke,
	_CFireTrail,
	_CFish,
	_CFlashbang,
	_CFogController,
	_CFootstepControl,
	_CFunc_Dust,
	_CFunc_LOD,
	_CFuncAreaPortalWindow,
	_CFuncBrush,
	_CFuncConveyor,
	_CFuncLadder,
	_CFuncMonitor,
	_CFuncMoveLinear,
	_CFuncOccluder,
	_CFuncReflectiveGlass,
	_CFuncRotating,
	_CFuncSmokeVolume,
	_CFuncTrackTrain,
	_CGameRulesProxy,
	_CHandleTest,
	_CHEGrenade,
	_CHostage,
	_CHostageCarriableProp,
	_CIncendiaryGrenade,
	_CInferno,
	_CInfoLadderDismount,
	_CInfoOverlayAccessor,
	_CItem_Healthshot,
	_CKnife,
	_CKnifeGG,
	_CLightGlow,
	_CMaterialModifyControl,
	_CMolotovGrenade,
	_CMolotovProjectile,
	_CMovieDisplay,
	_CParticleFire,
	_CParticlePerformanceMonitor,
	_CParticleSystem,
	_CPhysBox,
	_CPhysBoxMultiplayer,
	_CPhysicsProp,
	_CPhysicsPropMultiplayer,
	_CPhysMagnet,
	_CPlantedC4,
	_CPlasma,
	_CPlayerResource,
	_CPointCamera,
	_CPointCommentaryNode,
	_CPoseController,
	_CPostProcessController,
	_CPrecipitation,
	_CPrecipitationBlocker,
	_CPredictedViewModel,
	_CProp_Hallucination,
	_CPropDoorRotating,
	_CPropJeep,
	_CPropVehicleDriveable,
	_CRagdollManager,
	_CRagdollProp,
	_CRagdollPropAttached,
	_CRopeKeyframe,
	_CSCAR17,
	_CSceneEntity,
	_CSensorGrenade,
	_CSensorGrenadeProjectile,
	_CShadowControl,
	_CSlideshowDisplay,
	_CSmokeGrenade,
	_CSmokeGrenadeProjectile,
	_CSmokeStack,
	_CSpatialEntity,
	_CSpotlightEnd,
	_CSprite,
	_CSpriteOriented,
	_CSpriteTrail,
	_CStatueProp,
	_CSteamJet,
	_CSun,
	_CSunlightShadowControl,
	_CTeam,
	_CTeamplayRoundBasedRulesProxy,
	_CTEArmorRicochet,
	_CTEBaseBeam,
	_CTEBeamEntPoint,
	_CTEBeamEnts,
	_CTEBeamFollow,
	_CTEBeamLaser,
	_CTEBeamPoints,
	_CTEBeamRing,
	_CTEBeamRingPoint,
	_CTEBeamSpline,
	_CTEBloodSprite,
	_CTEBloodStream,
	_CTEBreakModel,
	_CTEBSPDecal,
	_CTEBubbles,
	_CTEBubbleTrail,
	_CTEClientProjectile,
	_CTEDecal,
	_CTEDust,
	_CTEDynamicLight,
	_CTEEffectDispatch,
	_CTEEnergySplash,
	_CTEExplosion,
	_CTEFireBullets,
	_CTEFizz,
	_CTEFootprintDecal,
	_CTEFoundryHelpers,
	_CTEGaussExplosion,
	_CTEGlowSprite,
	_CTEImpact,
	_CTEKillPlayerAttachments,
	_CTELargeFunnel,
	_CTEMetalSparks,
	_CTEMuzzleFlash,
	_CTEParticleSystem,
	_CTEPhysicsProp,
	_CTEPlantBomb,
	_CTEPlayerAnimEvent,
	_CTEPlayerDecal,
	_CTEProjectedDecal,
	_CTERadioIcon,
	_CTEShatterSurface,
	_CTEShowLine,
	_CTesla,
	_CTESmoke,
	_CTESparks,
	_CTESprite,
	_CTESpriteSpray,
	_CTest_ProxyToggle_Networkable,
	_CTestTraceline,
	_CTEWorldDecal,
	_CTriggerPlayerMovement,
	_CTriggerSoundOperator,
	_CVGuiScreen,
	_CVoteController,
	_CWaterBullet,
	_CWaterLODControl,
	_CWeaponAug,
	_CWeaponAWP,
	_CWeaponBaseItem,
	_CWeaponBizon,
	_CWeaponCSBase,
	_CWeaponCSBaseGun,
	_CWeaponCycler,
	_CWeaponElite,
	_CWeaponFamas,
	_CWeaponFiveSeven,
	_CWeaponG3SG1,
	_CWeaponGalil,
	_CWeaponGalilAR,
	_CWeaponGlock,
	_CWeaponHKP2000,
	_CWeaponM249,
	_CWeaponM3,
	_CWeaponM4A1,
	_CWeaponMAC10,
	_CWeaponMag7,
	_CWeaponMP5Navy,
	_CWeaponMP7,
	_CWeaponMP9,
	_CWeaponNegev,
	_CWeaponNOVA,
	_CWeaponP228,
	_CWeaponP250,
	_CWeaponP90,
	_CWeaponSawedoff,
	_CWeaponSCAR20,
	_CWeaponScout,
	_CWeaponSG550,
	_CWeaponSG552,
	_CWeaponSG556,
	_CWeaponSSG08,
	_CWeaponTaser,
	_CWeaponTec9,
	_CWeaponTMP,
	_CWeaponUMP45,
	_CWeaponUSP,
	_CWeaponXM1014,
	_CWorld,
	_DustTrail,
	_MovieExplosion,
	_ParticleSmokeGrenade,
	_RocketTrail,
	_SmokeTrail,
	_SporeExplosion,
	_SporeTrail,
};

//USERCMD OFFSETS
#define USERCMDOFFSET 0xEC
#define VERIFIEDCMDOFFSET 0xF0
#define MULTIPLAYER_BACKUP 150
#define CURRENTCOMMANDOFFSET 0x16E8
#define CURRENTPLAYERCOMMANDOFFSET 0x1640
#define PREIDCTIONSEEDOFFSET 0x30
#define PREDICTIONPLAYEROFFSET 0x54
#define GLOBALSOFFSET 0x1B
#define WEAPONDATA_MAXRANGEOFFSET 0x77C
#define WEAPONDATA_DAMAGEOFFSET 0x778
#define WEAPONDATA_RANGEMODIFIEROFFSET 0x780
#define WEAPONDATA_PENETRATIONPOWEROFFSET 0x774
#define INPUTOFFSET 0x5F
#define GETSPREADOFFSET 0x740
#define GETCONEOFFSET 0x744
#define UPDATEACCURACYPENALTYOFFSET 0x748
#define WEAPONIDOFFSET 0x6D8
#define WEAPONDATAOFFSET 0x708
#define GETNAMEOFFSET 0x5CC
#define APPSYSTEMFACTORYOFFSET 0x3D
#define CLIENTFACTORYOFFSET 0x75
#define GLOWINDEXOFFSET 0x1DB8

//LIFESTATE
#define	LIFE_ALIVE				0
#define	LIFE_DYING				1
#define	LIFE_DEAD				2
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

//Player flags
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

//USERCMD BUTTONS
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1, // (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

struct mstudiobbox_t
{
	int bone;
	int group; // intersection group
	Vector bbmin; // bounding box 
	Vector bbmax;
	int hitboxnameindex; // offset to the name of the hitbox.
	int pad[3];
	float radius;
	int pad2[4];

	char* getHitboxName()
	{
		if( hitboxnameindex == 0 )
			return "";

		return ( ( char* )this ) + hitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int sznameindex;

	inline char* const pszName( void ) const
	{
		return ( ( char* )this ) + sznameindex;
	}

	int numhitboxes;
	int hitboxindex;

	inline mstudiobbox_t* pHitbox( int i ) const
	{
		return ( mstudiobbox_t* )( ( ( BYTE* )this ) + hitboxindex ) + i;
	};

	inline mstudiobbox_t* GetHitbox(int i) const
	{
		return (mstudiobbox_t*)(((DWORD)this) + hitboxindex) + i;
	};
};

struct mstudiobone_t
{
	int sznameindex;

	inline char* const GetName( void ) const
	{
		return ( ( char * )this ) + sznameindex;
	}

	int parent;
	int bonecontroller[6];

	Vector pos;
	float quat[4];
	Vector rot;
	Vector posscale;
	Vector rotscale;

	matrix3x4 poseToBone;
	float qAlignment[4];
	int flags;
	int proctype;
	int procindex; // procedural rule
	mutable int physicsbone; // index into physically simulated bone
	inline void* GetProcedure() const
	{
		if( procindex == 0 )
			return nullptr;
		else
			return ( void * )( ( ( byte * )this ) + procindex );
	};

	int surfacepropidx; // index into string tablefor property name
	inline char* const GetSurfaceProps( void ) const
	{
		return ( ( char * )this ) + surfacepropidx;
	}

	int contents; // See BSPFlags.h for the contents flags

	int unused[8]; // remove as appropriate
};

struct studiohdr_t
{
	int id;
	int version;

	int checksum;

	char name[64];
	int length;

	Vector eyeposition;

	Vector illumposition;

	Vector hull_min;
	Vector hull_max;

	Vector view_bbmin;
	Vector view_bbmax;

	int flags;

	int numbones;
	int boneindex;

	inline mstudiobone_t* GetBone( int i ) const
	{
		return ( mstudiobone_t * )( ( ( byte * )this ) + boneindex ) + i;
	};

	//	inline mstudiobone_t *pBone(int i) const { Assert(i >= 0 && i < numbones); return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };

	int numbonecontrollers;
	int bonecontrollerindex;

	int numhitboxsets;
	int hitboxsetindex;

	mstudiohitboxset_t* GetHitboxSet( int i ) const
	{
		return ( mstudiohitboxset_t* )( ( ( byte* )this ) + hitboxsetindex ) + i;
	}

	inline mstudiobbox_t* GetHitbox( int i, int set ) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet( set );

		if( !s )
			return nullptr;

		return s->pHitbox( i );
	}

	inline int GetHitboxCount( int set ) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet( set );

		if( !s )
			return 0;

		return s->numhitboxes;
	}

	int numlocalanim;
	int localanimindex;

	int numlocalseq;
	int localseqindex;

	mutable int activitylistversion;
	mutable int eventsindexed;

	int numtextures;
	int textureindex;

	int numcdtextures;
	int cdtextureindex;

	int numskinref;
	int numskinfamilies;
	int skinindex;

	int numbodyparts;
	int bodypartindex;

	int numlocalattachments;
	int localattachmentindex;

	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;

	int numflexdesc;
	int flexdescindex;

	int numflexcontrollers;
	int flexcontrollerindex;

	int numflexrules;
	int flexruleindex;

	int numikchains;
	int ikchainindex;

	int nummouths;
	int mouthindex;

	int numlocalposeparameters;
	int localposeparamindex;

	int surfacepropindex;

	int keyvalueindex;
	int keyvaluesize;

	int numlocalikautoplaylocks;
	int localikautoplaylockindex;

	float mass;
	int contents;

	int numincludemodels;
	int includemodelindex;

	mutable void* virtualModel;

	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;

	mutable void* animblockModel;

	int bonetablebynameindex;

	void* pVertexBase;
	void* pIndexBase;

	byte constdirectionallightdot;

	byte rootLOD;

	byte numAllowedRootLODs;

	byte unused[1];

	int unused4;

	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int unused3[1];
	int studiohdr2index;
	int unused2[1];
};

class CBaseEntity;

typedef struct
{
	byte r, g, b, a;
} color32;

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP, // A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN, // A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};
