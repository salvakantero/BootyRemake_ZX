// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// config.h
// game engine configuration & behaviour

// ============================================================================
// I. General configuration
// ============================================================================

// 128K support
#define MODE_128K 						// 128K mode.

// Music engine
//#define USE_ARKOS						// Just comment this to use the default WYZ player.
//#define ARKOS_SFX_CHANNEL		1		// SFX Channel (0-2)

// Multi-level support (experimental!)
//#define COMPRESSED_LEVELS	 			// use levels.h/levels128.h instead of mapa.h and enems.h (!)
//#define SCRIPTED_GAME_ENDING			// Game ending is triggered from the script

// In this section we define map dimmensions, initial and authomatic ending conditions, etc.
#define MAP_W					4		//
#define MAP_H					5		// Map dimmensions in screens
//#define ENABLE_CUSTOM_CONNECTIONS 	// Custom connections array. MAP_W/MAP_H just define how many screens
#define SCR_INICIO				0		//  Initial screen
#define PLAYER_INI_X			9		//
#define PLAYER_INI_Y			1		// Initial tile coordinates
#define SCR_FIN 				99		// Last screen. 99 = deactivated.
#define PLAYER_FIN_X			99		//
#define PLAYER_FIN_Y			99		// Player tile coordinates to finish game
#define PLAYER_NUM_OBJETOS		99		// Objects to get to finish game
#define PLAYER_LIFE 			9		// Max and starting life gauge.
//#define DONT_LIMIT_LIFE				// If defined, no upper limit to life gauge.
//#define PLAYER_REFILL			1		// Life recharge
//#define MAX_LEVELS			1		// # of compressed levels
//#define REFILL_ME	 					// If defined, refill player on each level
//#define WIN_CONDITION			2		// 0 = objects collected, 1 = screen 'N', 2 = scripting, 3 = SIM

// ============================================================================
// II. Engine type
// ============================================================================

// This section is used to define the game engine behaviour. Many directives are related,
// and others are mutually exclusive. I think this will be pretty obvious when you look at them.

// Bounding box size
// -----------------
										// Comment both for normal 16x16 bounding box
#define BOUNDING_BOX_8_BOTTOM			// 8x8 aligned to bottom center in 16x16
//#define BOUNDING_BOX_8_CENTERED		// 8x8 aligned to center in 16x16
//#define SMALL_COLLISION 				// 8x8 centered collision instead of 12x12

// General directives:
// -------------------

//#define PLAYER_CHECK_MAP_BOUNDARIES	// If defined, you can't exit the map.
#define PLAYER_CANNOT_FLICK_SCREEN		// If defined, automatic screen flicking is disabled.
//#define PLAYER_WRAP_AROUND			// If defined, wrap-around. Needs PLAYER_CANNOT_FLICK_SCREEN
#define DIRECT_TO_PLAY					// If defined, title screen is also the game frame.
#define DEACTIVATE_KEYS 				// If defined, keys are not present.
#define DEACTIVATE_OBJECTS				// If defined, objects are not present.
//#define ONLY_ONE_OBJECT				// If defined, only one object can be carried at a time.
//#define OBJECT_COUNT			1		// Defines which FLAG will be used to store the object count.
//#define DEACTIVATE_EVIL_TILE			// If defined, no killing tiles (behaviour 1) are detected.
//#define FULL_BOUNCE 					// If defined, evil tile bounces equal MAX_VX, otherwise v/2
//#define PLAYER_BOUNCES				// If defined, collisions make player bounce
//#define SLOW_DRAIN					// Works with bounces. Drain is 4 times slower
//#define PLAYER_FLICKERS 				// If defined, collisions make player flicker instead.
//#define MAP_BOTTOM_KILLS				// If defined, exiting the map bottomwise kills.
#define WALLS_STOP_ENEMIES				// If defined, enemies react to the scenary (new: if bit 5 on!)
//#define EVERYTHING_IS_A_WALL			// If defined, any tile <> type 0 is a wall, otherwise just 8.
//#define COUNT_SCR_ENEMS_ON_FLAG 1		// If defined, count # of enems on screen and store in flag #
//#define SHOW_LEVEL_ON_SCREEN			// If defined, show level # whenever we enter a new screen

// Enemy engine
// ------------
#define MAX_ENEMS				4		// Enemies per screen. Salva(18/11/18)
// General directives
#define ENABLE_PATROLLERS				// Yeah, you can now deactivate good ol' patrollers...
/*
#define ENABLE_FLYING_ENEMIES			// If defined, add code for flying enemies.
//#define TYPE_6_FIXED_SPRITE 	2		// Sprite used - 1.
#define SIGHT_DISTANCE			96		// Used in our type 6 enemies.
//#define TYPE_6_KILL_ON_TOUCH			// If defined, enemy also dies when collision happens
#define FANTY_MAX_V 			256 	// Flying enemies max speed (also for custom type 6 if you want)
#define FANTY_A 				16		// Flying enemies acceleration.
#define FANTIES_LIFE_GAUGE		1		// Amount of shots needed to kill flying enemies.
*/
//#define ENABLE_PURSUE_ENEMIES 		// If defined, type 7 enemies are active
//#define DEATH_COUNT_EXPRESSION	20+(rand()&15)
//#define TYPE_7_FIXED_SPRITE	4		// If defined, type 7 enemies are always #

//#define MAX_COCOS 			3		// Max # of cocos.

//#define ENABLE_SHOOTERS				// Activate this if your raise bit 4 in any enemies.
/*
#define TYPE_8_SHOOT_FREQ		63		// Shoot frequency (2^n-1)
#define TYPE_8_SAFE_DISTANCE	64		// if closer won't shoot
#define TYPE_8_FIRE_ONE 				// If defined, just fire one coco per enemy
#define COCO_SPEED_8			4		// pixels per frame
*/

//#define ENABLE_DROPS					// Enemy type 9 = drops
#define ENABLE_ARROWS					// Enemy type 10 = arrows

//#define USE_TWO_BUTTONS 				// Alternate keyboard scheme for two-buttons games
//#define USE_HOTSPOTS_TYPE_3 			// Alternate logic for recharges.
#define TILE_GET_KEY			27		// If defined, player can "get" tile # (KEYS,DOORS,OBJECTS)
//#define TILE_GET_SCRIPT				// Run PLAYER_GETS_COIN when player gets tile TILE_GET
#define TILE_GET_KEY_FLAG 		1		// And this update flag #
#define TILE_GET_DOOR_DOWN		28		// 2 tiles
#define TILE_GET_DOOR_UP		6		//
#define TILE_GET_OBJ_MIN		16		// first tile number of multiple objects
#define TILE_GET_OBJ_MAX		26		// last tile number of multiple objects
#define TILE_GET_OBJ_FLAG 		2		// And this update flag #

//#define DIE_AND_RESPAWN				// If defined, dying = respawn on latest safe.
//#define DISABLE_AUTO_SAFE_SPOT		// If defined, you have to define the save spot via scripting
//#define REENTER_ON_DEATH				// Reenter screen when killed, for 1-screen arcades.
#define PLAYER_STEP_SOUND				// Sound while walking. No effect in the BOOTEE engine.
//#define DISABLE_PLATFORMS				// If defined, type 4 are enemies in side-view mode
//#define ENABLE_CONVEYORS

// Body count
// ----------
// In Churrera, every kill was counted on the p_killed variable, which offers
// little control but can be enough for simple games. If you want to have more control
// over # of enemies killed (for example, to reset it!) just define this. p_killed will
// no longer work, instead flag # will be used. 
//#define BODY_COUNT_ON			2		// Increment flag # everytime the player kills an enemy
//#define RUN_SCRIPT_ON_KILL			// If defined, PLAYER_KILLS_ENEMY scripts are triggered on kills
//#define ENEMY_BACKUP					// If you want a backup in case you change the enemy types
										// ingame, define this. Useful for 48K or non-compressed level
										// games (in compressed level games you can save this and just
										// decompress the enemies again!)
//#define RESTORE_ON_INIT				// Restore enemies when entering game.										

// Pushable tile
// -------------

//#define PLAYER_PUSH_BOXES 			// If defined, tile #14 is pushable. Must be type 10.
//#define FIRE_TO_PUSH					// If defined, you have to press FIRE+direction to push.
//#define ENABLE_PUSHED_SCRIPTING		// If defined, nice goodies (below) are activated:
//#define MOVED_TILE_FLAG		1		// Current tile "overwritten" with block is stored here.
//#define MOVED_X_FLAG			2		// X after pushing is stored here.
//#define MOVED_Y_FLAG			3		// Y after pushing is stored here.
//#define PUSHING_ACTION				// If defined, pushing a tile runs PRESS_FIRE script

// Shooting / killing behaviour
// ----------------------------

//#define PLAYER_CAN_FIRE 				// If defined, shooting engine is enabled.
//#define CAN_FIRE_UP					// If defined, player can fire upwards and diagonal.
//#define PLAYER_CAN_FIRE_FLAG	1		// If defined, player can only fire when flag # is 1
//#define PLAYER_CAN_FIRE_INV	45		// If defined, player con only fire if item # is selected!
//#define PLAYER_BULLET_SPEED 	8		// Pixels/frame.
//#define MAX_BULLETS 			1		// Max number of bullets on screen. Be careful!.
//#define PLAYER_BULLET_Y_OFFSET	6	// vertical offset from the player's top.
//#define PLAYER_BULLET_X_OFFSET	0	// vertical offset from the player's left/right.
//#define PLAYER_BULLETS_STRENGTH 	1	// Amount of life bullets take from baddies.
//#define BULLETS_BREAK_WALLS			// If defined, bullets break breakable walls.
/*
#define LIMITED_BULLETS 				// If defined, bullets die after N frames
#define LB_FRAMES				4		// If defined, defines the # of frames bullets live (fixed)
#define LB_FRAMES_FLAG			2		// If defined, defines which flag determines the # of frames
*/

// Hitter. Define only *ONE* of these. More to come.
//#define PLAYER_CAN_PUNCH				// Player can punch. (Ninjajar!)
//#define PLAYER_HAZ_SWORD				// Player haz sword. (Espadewr)
//#define PLAYER_HAZ_WHIP				// Player haz whip. (Nicanor)

//#define PLAYER_HITTER_INV		46		// If defined, player can use hitter only if item # is selected!
//#define PLAYER_HITTER_STRENGTH	0	// Hitter strength. 0 = just makes monsters turn around.
//#define HITTER_BREAKS_WALLS			// If defined, hitter breaks breakable walls.

//#define PLAYER_SIMPLE_BOMBS			// If defined, bombs-s.h module is enabled (Nicanor)
//#define PLAYER_BOMBS_STRENGTH	1		// Amount of life bombs take from baddies.
//#define BOMBS_EXPLOSION_TILE	42		// Tile # for explosion.
//#define BOMBS_BREAK_WALLS				// If defined, bombs break breakable walls.
//#define PLAYER_BOMBS_TILE		44		// ... You know the drill...
//#define PLAYER_BOMBS_INV		44		// If defined, player can use bombs only if item # is selected!
										// NOTE! As of 0.89, this is the only option implemented! 

//#define ENEMIES_LIFE_GAUGE	1		// Amount of shots/hits needed to kill enemies.
//#define RESPAWN_ON_ENTER				// Enemies respawn when entering screen
//#define RESPAWN_ON_REENTER			// Respawn even on a REENTER in the script (by default REENTER doesn't respawn enemies!)
//#define FIRE_MIN_KILLABLE 	3		// If defined, only enemies >= N can be killed.

//#define MAX_AMMO				5		// If defined, ammo is not infinite!
//#define AMMO_REFILL			5		// ammo refill, using tile 20 (hotspot #4)
//#define INITIAL_AMMO			0		// If defined, ammo = X when entering game.

//#define BREAKABLE_WALLS_SIMPLE

//#define BREAKABLE_ANIM				// If defined, breakable tiles look "broken"
//#define BREAKABLE_TILE		43		// "broken tile"
//#define MAX_BREAKABLE			7		// Max tiles showing "breaking"
//#define MAX_BREAKABLE_FRAMES	4		// Frames to show "breaking"
/*
#define BREAKABLE_TILE_GET		12		// If defined, tile "TILE GET" may appear when breaking tile #
#define BREAKABLE_TILE_FREQ 	3		// Breakable tile frequency (AND)
#define BREAKABLE_TILE_FREQ_T	2		// <= this value = true.
*/
//#define PERSISTENT_BREAKABLE			// Only works with compressed levels/128K games.

// Scripting
// ---------

#define ACTIVATE_SCRIPTING				// Activates msc scripting and flag related stuff.
#define SCRIPT_PAGE				7		// Which RAM page holds the script (128)
//#define CLEAR_FLAGS					// If defined, clear flags each level/beginning.
//#define SCRIPTING_DOWN				// Use DOWN as the action key.
//#define SCRIPTING_KEY_M				// Use M as the action key instead.
#define SCRIPTING_KEY_FIRE				// User FIRE as the action key instead.
//#define ENABLE_EXTERN_CODE			// Enables custom code to be run from the script using EXTERN n
//#define EXTERN_E						// Uncomment this as well if you use EXTERN_E in your script
//#define ENABLE_FIRE_ZONE				// Allows to define a zone which auto-triggers "FIRE"

// Simple Item Manager
// -------------------
// Uncompatible with scripting. USE ONLY WITH SCRIPTING OFF!
//#define ENABLE_SIM

// General
//#define SIM_MAXCONTAINERS 	6
//#define SIM_DOWN
//#define SIM_KEY_M
//#define SIM_KEY_FIRE

// Display:
/*
#define SIM_DISPLAY_HORIZONTAL
#define SIM_DISPLAY_MAXITEMS	2
#define SIM_DISPLAY_X			24
#define SIM_DISPLAY_Y			21
#define SIM_DISPLAY_ITEM_EMPTY	31
#define SIM_DISPLAY_ITEM_STEP	3
#define SIM_DISPLAY_SEL_C		66
#define SIM_DISPLAY_SEL_CHAR1	62
#define SIM_DISPLAY_SEL_CHAR2	63
*/

// Timer
// -----

//#define TIMER_ENABLE					// Enable timer
//#define TIMER_INITIAL		99			// For unscripted games, initial value.
//#define TIMER_REFILL		30			// Timer refill, using tile 21 (hotspot #5)
//#define TIMER_LAPSE 		32			// # of frames between decrements
//#define TIMER_START 					// If defined, start timer from the beginning
//#define TIMER_SCRIPT_0					// If defined, timer = 0 runs "ON_TIMER_OFF" in the script
//#define TIMER_GAMEOVER_0				// If defined, timer = 0 causes "game over"
//#define TIMER_KILL_0					// If defined, timer = 0 causes "one life less".
//#define TIMER_WARP_TO 0				// If defined, warp to screen X after "one life less".
//#define TIMER_WARP_TO_X	1			//
//#define TIMER_WARP_TO_Y	1			// "warp to" coordinates.
//#define TIMER_AUTO_RESET				// If defined, timer resets after "one life less"
//#define SHOW_TIMER_OVER				// If defined, "TIME OVER" shows when time is up.

// Lava:
// -----
// Experimental & custom. Use @ your own risk. Not supported __AT ALL__
// Only 128K/Multilevel/Enhaced levels.
/*
#define ENABLE_LAVA
#define LAVA_FLAG			30
#define LAVA_PERIOD 		7
#define LAVA_X1 			2
#define LAVA_X2 			28			// LAVA_X1 <= x < LAVA_X2
#define LAVA_T				18
*/

// Floating objects:
// -----------------

//#define ENABLE_FLOATING_OBJECTS			// Activate this for floating objects support

//#define FO_GRAVITY						// If defined, floating objects are affected by gravity
//#define FO_SOLID_FLOOR					// If defined, floating objects won't fall off the screen
//#define FO_DETECT_INTERACTION_CENTER	// If defined, "active" hotspot is @ player center
										// Otherwise it's on the floor, depending where he's facing.

/*
#define ENABLE_FO_CARRIABLE_BOXES		// Boxes the player can carry/place elsewhere.
#define FT_CARRIABLE_BOXES			17	// Tile for carriable boxes.
#define CARRIABLE_BOXES_ALTER_JUMP 180	// You jump less if defined. Modifies "player_max_vy_saltando"
#define CARRIABLE_BOXES_THROWABLE 	// If defined, carriable boxes are throwable!
#define CARRIABLE_BOXES_COUNT_KILLS 2 // If defined, count # of kills and store in flag N.
#define CARRIABLE_BOXES_DRAIN		7	// Boxes drain life if held every N+1 frames (power of two minus 1!)
#define CARRIABLE_BOXES_CORCHONETA		// Corchonetas de sartar!
#define CARRIABLE_BOXES_MAX_C_VY	1024	// Max vertical velocity
*/
/*
#define ENABLE_FO_SCRIPTING 			// Anytime a FO falls, PRESS_FIRE script is ran
#define FO_X_FLAG					1
#define FO_Y_FLAG					2
#define FO_T_FLAG					3	// Flags to store X, Y, and Type of object which just fell.
*/
//#define ENABLE_FO_OBJECT_CONTAINERS 	// Use with scripting. Helps to manage item collecting
//#define SHOW_EMPTY_CONTAINER			// If defined, show empty container tile

// Engine type: No effect if PHANTOMAS_ENGINE is defined...

// Top view:
// ---------

//#define PLAYER_MOGGY_STYLE				// Enable top view.
//#define TOP_OVER_SIDE 				// UP/DOWN has priority over LEFT/RIGHT

// Side view:
// ----------

#define PLAYER_HAS_JUMP 				// If defined, player is able to jump.
//#define PLAYER_BOOTEE 				// Always jumping engine. Don't forget to disable "HAS_JUMP" and "HAS_JETPAC"!!!
//#define PLAYER_BOUNCE_WITH_WALLS		// Bounce when hitting a wall. Only really useful in MOGGY_STYLE mode
//#define PLAYER_CUMULATIVE_JUMP		// Keep pressing JUMP to JUMP higher in several bounces

//#define PLAYER_HAS_JETPAC 			// If defined, player can thrust a vertical jetpac
//#define JETPAC_DEPLETES			4	// If defined, jetpac depletes each # frames.
//#define JETPAC_FUEL_INITIAL		25	// needed by "JETPAC_DEPLETES", initial fuel value.
//#define JETPAC_FUEL_MAX			25	// needed by "JETPAC_DEPLETES" & "JETPAC_REFILLS", max fuel value.
//#define JETPAC_AUTO_REFILLS		2	// If defined, jetpac refills each # frames when not in use.
//#define JETPAC_REFILLS				// If defined, type 6 hotspots are refills.
//#define JETPAC_FUEL_REFILL		25	// needed by "JETPAC_REFILLS"

// Stepping over enemies...
//#define PLAYER_KILLS_ENEMIES			// If defined, stepping on enemies kills them
//#define PLAYER_CAN_KILL_FLAG	1		// If defined, player can only kill when flag # is "1"
//#define PLAYER_MIN_KILLABLE	  3 	// Only kill enemies with id >= PLAYER_MIN_KILLABLE
/*
#define PLAYER_HAS_SWIM 				// If defined, player is able to swim
#define SWITCHABLE_ENGINES				// WIP! VERY, VERY, VERY WIP! See Sir Ababol DX or Ninjajar!
*/
// ============================================================================
// III. Screen configuration
// ============================================================================

// This sections defines how stuff is rendered, where to show counters, etcetera

#define VIEWPORT_X				0		//
#define VIEWPORT_Y				5		// Viewport character coordinates
#define LIFE_X					4		//
#define LIFE_Y					4		// Life gauge counter character coordinates
/*
#define OBJECTS_X				99		//
#define OBJECTS_Y				99		// Objects counter character coordinates
#define OBJECTS_ICON_X			99		//
#define OBJECTS_ICON_Y			99		// Objects icon character coordinates (use with ONLY_ONE_OBJECT)
#define KEYS_X					99		//
#define KEYS_Y					99		// Keys counter character coordinates
#define KILLED_X				99		//
#define KILLED_Y				99		// Kills counter character coordinates
//#define PLAYER_SHOW_KILLS 			// If defined, show kill counter.
//#define AMMO_X				14		//
//#define AMMO_Y				0		// Ammo counter character coordinates
//#define TIMER_X 				9		//
//#define TIMER_Y 				0		// Timer counter coordinates
//#define PLAYER_SHOW_TIMER 			// If defined, show timer counter
//#define FLAG_X					99		//
//#define FLAG_Y					99		// Custom flag character coordinates
//#define PLAYER_SHOW_FLAG		1		// If defined, show flag #
//#define FUEL_X				99		//
//#define FUEL_Y				99		// Fuel counter in bla bla bla
//#define PLAYER_SHOW_FUEL				// If defined, show fuel counter.
*/
// Text
//#define LINE_OF_TEXT			1		// If defined, scripts can show text @ Y = #
//#define LINE_OF_TEXT_X		1		// X coordinate.
//#define LINE_OF_TEXT_ATTR 	71		// Attribute

// Graphic FX, uncomment which applies...

//#define USE_AUTO_SHADOWS				// Automatic shadows made of darker attributes
//#define USE_AUTO_TILE_SHADOWS 		// Automatic shadows using specially defined tiles 32-47.
//#define UNPACKED_MAP					// Full, uncompressed maps. Shadows settings are ignored.
//#define NO_MASKS						// Sprites are rendered using OR instead of masks.
//#define PLAYER_ALTERNATE_ANIMATION	// If defined, animation is 1,2,3,1,2,3...
//#define MASKED_BULLETS				// If needed
#define ENABLE_TILANIMS			5		// If defined, animated tiles are enabled.
										// the value especifies firt animated tile pair.
#define PAUSE_ABORT						// Add h=PAUSE, y=ABORT
//#define GET_X_MORE					// Shows "get X more" when getting an object
#define NO_ALT_TILE 					// No alternate automatic tile 19 for tile 0.
//#define TWO_SETS						// If defined, use two 16 sets in one (just ask)
//#define TWO_SETS_SEL (n_pant>8?32:0)	// This expresion must equal 0 for set 1 to be used, or 32 for set 2 to be used (just ask)
//#define ENABLE_LEVEL_NAMES			// Give a name for each level in engine/levelnames.h
//#define ENABLE_EXTRA_PRINTS			// Configure extra tile prints for some screens in engine/extraprints.h

// ============================================================================
// IV. Player movement configuration
// ============================================================================

// No effect if PHANTOMAS_ENGINE is on!

// This section is used to define which constants are used in the gravity/acceleration engine.
// If a side-view engine is configured, we have to define vertical and horizontal constants
// separately. If a top-view engine is configured instead, the horizontal values are also
// applied to the vertical component, vertical values are ignored.

// IV.1. Vertical movement. Only for side-view.

#define PLAYER_MAX_VY_CAYENDO	160	 	// Max falling speed (512/64 = 8 pixels/frame)
#define PLAYER_G				48		// Gravity acceleration (32/64 = 0.5 p?xeles/frame^2)

#define PLAYER_VY_INICIAL_SALTO 128   	// Initial junp velocity (64/64 = 1 p?xel/frame)
#define PLAYER_MAX_VY_SALTANDO	144	 	// Max jump velocity (320/64 = 5 p?xels/frame)
#define PLAYER_INCR_SALTO		128		// acceleration while JUMP is pressed (48/64 = 0.75 p?xeles/frame^2)

//#define PLAYER_INCR_JETPAC	32		// Vertical jetpac gauge
//#define PLAYER_MAX_VY_JETPAC	256 	// Max vertical jetpac speed

// IV.2. Horizontal (side view) or general (top view) movement.

#define PLAYER_MAX_VX			256 	// Max velocity (192/64 = 3 p?xels/frame)
#define PLAYER_AX				64		// Acceleration (24/64 = 0,375 p?xels/frame^2)
#define PLAYER_RX				128		// Friction (32/64 = 0,5 p?xels/frame^2)

// IV.3. Swimming

//#define PLAYER_MAX_VSWIM		128
//#define PLAYER_ASWIM			32

// ============================================================================
// V. Tile behaviour
// ============================================================================

// Defines the behaviour for each tile. Remember that if keys are activated, tile #15 is a bolt
// and, therefore, it should be made a full obstacle!

// 0 = Walkable (no action)
// 1 = Walkable and kills.
// 2 = Walkable and hides.
// 4 = Platform (only stops player if falling on it)
// 8 = Full obstacle (blocks player from all directions)
// 10 = special obstacle (pushing blocks OR locks!)
// 16 = Breakable (#ifdef BREAKABLE_WALLS)
// 32 = (Conveyor)
// 64 = (CUSTOM F.O. -> CORCHONETA!)	NOT CORCHONETA, BUT STAIRS!! (use with platforms, +4)
// You can add the numbers to get combined behaviours
// Save for 10 (special), but that's obvious, innit?
#ifndef COMPRESSED_LEVELS
unsigned char behs [] = {
	0, 0, 4, 4, 4, 4, 4, 4, 0,68, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 4, 4,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
#endif

// WARNING!! Don't touch these.
#if defined(CARRIABLE_BOXES_ALTER_JUMP)
#define PLAYER_VARIABLE_JUMP
#endif

#ifdef ENABLE_FLYING_ENEMIES
#define ENABLE_CUSTOM_TYPE_6
#endif
#ifdef ENABLE_PURSUE_ENEMIES
#define ENABLE_PURSUERS
#endif

#ifdef SWITCHABLE_WEAPONS
#define SW_NOTHING				0
#define SW_HITTER				1
#define SW_GUN					2		// You don't need to touch these. JUST DON'T

#endif

// Sound driver macro

#ifdef MODE_128K
#ifdef USE_ARKOS
	#define _AY_PL_SND arkos_play_sound
	#define _AY_PL_MUS arkos_play_music
	#define _AY_ST_ALL arkos_stop_sound
#else
	#define _AY_PL_SND wyz_play_sound
	#define _AY_PL_MUS wyz_play_music
	#define _AY_ST_ALL wyz_stop_sound
#endif
#else
	#define _AY_PL_SND peta_el_beeper
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP)
#define PLAYER_HAZ_HITTER
#endif

#if (defined (PLAYER_CAN_FIRE) + defined (PLAYER_HAZ_HITTER) + defined (PLAYER_SIMPLE_BOMBS)) == 0
#define WAYS_TO_DIE 0
#elif (defined (PLAYER_CAN_FIRE) + defined (PLAYER_HAZ_HITTER) + defined (PLAYER_SIMPLE_BOMBS)) == 1
#define WAYS_TO_DIE 1
#else
#define WAYS_TO_DIE 2
#endif

// END OF WARNING.

