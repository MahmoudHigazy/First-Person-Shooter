
//===========================================================================
//
// Name:		R7_c.c
// Function:		chat lines for R7
// Programmer:		MrElusive (MrElusive@idsoftware.com)
// Author:		R.A. Salvatore & The Seven Swords
//Editor: 		Paul Jaquays
// Last update:		Oct.05, 1999
// Tab Size:		3 (real tabs)
//===========================================================================

//example initial chats
chat "R7"
{
	//the teamplay.h file is included for all kinds of teamplay chats
	#include "teamplay.h"

	//======================================================
	//======================================================

	type "game_enter" //initiated when the bot enters the game
	{
	      "We are R7...fear us...";
		"Hsssss...prepare...die....";
		"cower weaklingssss...";
		0, " senses your fear...the weak must be culled...";
            "...the weak must be culled...";
		// 0 = bot name
	} //end type

	type "game_exit" //initiated when the bot exits the game
	{
		"sssss...the altar calls for my return...";
		"Pfffah! You are unworthy of our sport...";
		// 0 = bot name
	} //end type

	type "level_start" //initiated when a new level starts
	{
		"...fear us...hide...die...";
		"hrrrmmm....";
		"Hssssss...clean floors to bloody...";
		// 0 = bot name
	} //end type

	type "level_end" //initiated when a level ends and the bot is not first and not last in the rankings
	{
		"Hssssss...your rankings mean NOTHING....";
		"...higher...you rise...ssss...farther...fall...";
		"...will be punished...for your impudence...";
		// 0 = bot name
	} //end type

	type "level_end_victory" //initiated when a level ends and the bot is first in the rankings
	{
		"...all shall cower...";
		"'The Fallen'....risen...";
		"Hssssss...the weak have been culled...";
		// 0 = bot name
	} //end type

	type "level_end_lose" //initiated when a level ends and the bot is last in the rankings
	{
		"HSSSSSSSSSSSSSSS...";
		"Hssssss...your rankings mean NOTHING....";
		"sssss...", 2, "...your head...first to the altar...";
		"sssss...never shall I be of the weak again....NEVER!";
		// 0 = bot name
	} //end type

	//======================================================
	//======================================================

	type "hit_talking" //bot is hit while chat balloon is visible; lecture attacker on poor sportsmanship
	{
		"hssssss...your attack bears your fear, ", 0, "...";
		"...coward...weakling...";
		//0 = shooter
	} //end type

	type "hit_nodeath" //bot is hit by an opponent's weapon attack; either praise or insult
	{
		"...such pain ", 0, "...delightful...";
		"...stung by insect...";
		"...with every wound, ", 0, ", I strengthen...";
		"...hssss!...you dare attack?!...impudence...";
		"...sssssssss...pain...unimportant...";
		//0 = shooter
	} //end type

	type "hit_nokill" //bot hits an opponent but does not kill it
	{
		"mmmmmm....blood....", 0, "'s blood!...";
		"...'The Fallen'...smell your fear, ", 0, "...";
		"...flee, ", 0, ", flee...";
		HIT_NOKILL1;
		//0 = opponent
	} //end type

	//======================================================
	//======================================================

	type "death_telefrag" //initiated when the bot is killed by a telefrag
	{
		"...glglggllll.....";
		// 0 = eneour name
	} //end type

	type "death_cratered" //initiated when the bot is killed by taking "normal" falling damage
	{
		"Aiyeeeeeee!";
		"nnnnnnooooooooo!!!";
		// 0 = eneour name
	} //end type

	type "death_lava" //initiated when the bot dies in lava
	{
		"...blood boils...cleanses...";
		// 0 = eneour name
	} //end type

	type "death_slime" //initiated when the bot dies in slime
	{
		"...no mortal shall claim my defeat...";
		"...hsssssss...ending...as vile as...my oponents...";
		// 0 = eneour name
	} //end type

	type "death_drown" //initiated when the bot drowns
	{
		"...glub...glub...";
		"...thissss water...must be holy...";
		// 0 = eneour name
	} //end type

	type "death_suicide" //initiated when bot blows self up with a weapon or craters
	{
		"...too eager...for blood...";
		"...may my blood sting your eyes...";
		// 0 = eneour name
	} //end type

	type "death_gauntlet" //initiated when the bot is killed by a gauntlet attack
	{
		"...your courage...", 0, "...only matched by...your luck...";
		"...SSSSSSSSS...you dare touch 'The Fallen', ", 0, "!?!";
		// 0 = eneour name
	} //end type

	type "death_rail" //initiated when the bot is killed by a rail gun shot
	{
		"...hsssss only a coward strikes but once...";
		0, ", you strike...from distance...but your fear...is everywhere...";
		// 0 = eneour name
	} //end type

	type "death_bfg" //initiated when the bot died by a BFG
	{
		"...a weapon...worthy of my destruction...";
		// 0 = eneour name
	} //end type

	type "death_insult" //insult initiated when the bot died
	{
		"...hssssss...shall feed you...own bones, ", 0, "...";
		"...sssssss...shall rend you....", 0, "...";
		"HSSSSSSSSSSS...VENGENCE...MINE...", 0, "...";
		"...I welcome death...will return anew...";
		"...your impudence...great, ", 0, "...";
		// 0 = eneour name
	} //end type

	type "death_praise" //praise initiated when the bot died
	{
		"...your skill....finally approaches your fear, ", 0, "...";
		"...you fight like 'The Fallen'...no greater honor...";
		"...will honor your skills, ", 0, ", by killing you next...";
		"...ssssssssss...";
		"...well done....your flesh will be...";
		"...almost...impressed.......almost...";
		"...fighting as such...makes you more worthy...to kill...";
		// 0 = eneour name
	} //end type

	//======================================================
	//======================================================

	type "kill_rail" //initiated when the bot kills someone with rail gun
	{
		"...your agility, ", 0, "...pathetic...";
		"...you deserve no more than one shot, ", 0, "...";
		// 0 = eneour name
	} //end type

	type "kill_gauntlet" //initiated when the bot kills someone with gauntlet
	{
		"...you warrant no weapon, ", 0, ", so we used our hand...";
		"...you bear...scar of honor, ", 0, "...";
		// 0 = eneour name
	} //end type

	type "kill_telefrag" //initiated when the bot telefragged someone
	{
		"...ssssss!!... you hinder our conquest, ", 0, "!";
		"...your shower of blood...cleanses...";
		// 0 = eneour name
	} //end type

	type "kill_suicide" //initiated when the players kills self
	{
		"...must fear me...more than death, ", 0, "...";
		"...'The Fallen' mock you, ", 0, "!";
		"...you are as foolish as weak...";
		// 0 = eneour name
	} //end type

	type "kill_insult" //insult initiated when the bot killed someone
	{
		"...your death...", 0, "...purifies the arena...";
		"...your head...unworthy of an altar spike, ", 0, "...";
		"...the weak have been culled...";
		"...regret, ", 0, ", you didn't suffer more...";
		"...in pieces...you are attractive, ", 0, "...";
		"...'The Fallen' accept your soul, ", 0, "...";
		"...you were almost worth the ammo, ", 0, "...almost...";
		"...pfah!...your weakness, ", 0, "...insulting...";
		"...seek challenge...find weakness...";
		// 0 = eneour name
	} //end type

	type "kill_praise" //praise initiated when the bot killed someone
	{
		"...you died without fear, ", 0, "...no greater praise...";
		"...well fought, ", 0, "...and well lost...";
		"...if the gods show pity... you may return as 'The Fallen'...";
		"...you controlled you fear...I controlled your fate...";
		// 0 = eneour name
	} //end type

	//======================================================
	//======================================================

	type "random_insult" //insult initiated randomly (just when the bot feels like it)
	{
		"...smell fear...", 0, "...and sweat..";
		"...hssssss...blood...smell BLOOD...";
		"...your death...my victory...";
		MISC12;
		// 0 = name of randomly chosen player
		// 1 = bot name
	} //end type

	type "random_misc" //miscellanous chats initiated randomly
	{
		"...sizzling flesh....like perfume...";
		"...this place...", 4, "...reminds us of the core...";
		"...I sense fear...blood...death....triumph...";
		"...ssssss...surrounded...by the weak...and foolish...";
		// 0 = name of randomly chosen player
		// 1 = bot name
	} //end type
} //end R7 chat

