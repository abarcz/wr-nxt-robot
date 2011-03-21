/* 
 * controlling the robot's motors and tachometer
 * to use with a single robot only
 */ 
#include "debug.h"

#ifndef NXC_COMPILE					// for GCC
#endif

#ifdef NXC_COMPILE					// for NXC
	#define MOT_ALL OUT_AC
	#define MOT_L OUT_A
	#define MOT_R OUT_C

	#define RESET_TACHO() ResetAllTachoCounts(MOT_ALL)
	#define GET_TACHO() MotorTachoCount(MOT_ALL)
	
	#define ON_FWD(p) OnFwd(MOT_ALL, p)
	#define ON_REV(p) OnRev(MOT_ALL, p)
	#define ON_LEFT(p) OnFwd(MOT_R,p);OnRev(MOT_L,p)
	#define ON_RIGHT(p) OnFwd(MOT_L,p);OnRev(MOT_R,p)
	#define ENG_STOP() Coast(MOT_ALL);
	#define WAIT(t) Wait(t)
#endif

/* types of movement */
#define M_NONE  0
#define M_FWD   1
#define M_REV   2
#define M_LEFT  3
#define M_RIGHT 4 

/* time needed to turn 360 degrees */
#define A360_TURNTIME 100
#define TURN_PWR 75 //power needed for the turn

struct move_str
{
	int last_dir;
	int last_pwr;
	long last_tacho;
	int curr_angle;		// current angle (in degrees) - starting angle is 0deg
	long vx;			// distance travelled in 'x' direction since init
	long vy;			// distance travelled in 'y' direction since init
};

/* global container for robot moves data */
move_str robot_mov;

void eng_init ();
void eng_fwd (char power);
void eng_rev (char power);
void eng_left (char power);
void eng_right (char power);
void eng_stop ();

/* check if tacho changed since last check, if so return true */
bool tacho_changed ();

/* turn the robot 'angle' left and return to the current move mode */
void eng_turn_left (int angle);
void eng_turn_right (int angle);

/*** 				definitions 				***/

void eng_init ()
{
	robot_mov.last_dir = M_NONE;
	robot_mov.last_pwr = 0;
	robot_mov.last_tacho = 0;
	robot_mov.curr_angle = 0;
	robot_mov.vx = 0;
	robot_mov.vy = 0;
	RESET_TACHO();
}

/* for internal use only! adds the path (from tahometer) to the vx, vy deviations */
void add_path (long v)
{
	robot_mov.vx += v * cosd(robot_mov.angle - 90);
	robot_mov.vy += v * sind(robot_mov.angle - 90);
}
	

void eng_fwd (char power)
{
	if (robot_mov.last_dir == M_REV)
	{
		add_path(GET_TAHO());
		RESET_TACHO();
	}
	ON_FWD(power);
	robot_mov.last_dir = M_FWD;
	robot_mov.last_pwr = power;
}

void eng_rev (char power)
{
	if (robot_mov.last_dir == M_FWD)
	{
		add_path(GET_TAHO());
		RESET_TACHO();
	}
	ON_REV(power);
	robot_mov.last_dir = M_REV;
	robot_mov.last_pwr = power;
}

void eng_turn_left (int angle)
{
	int turn_time;
	if (angle > 360)
		return;
	add_path(GET_TAHO());			// save taho from last move
	turn_time = A360_TURNTIME / (360 / angle);
	ON_LEFT(TURN_PWR);
	WAIT(turn_time);
	robot_mov.curr_angle += angle;	// update the robot's angle information
	RESET_TACHO();					// reset taho for the next move
	/* return to last move mode */
	if (robot_mov.last_dir == M_FWD)
		ON_FWD(robot_mov.last_pwr);
	else if (robot_mov.last_dir == M_REV)
		ON_REV(robot_mov.last_pwr);
	else
		ENG_STOP();
}

void eng_turn_right (int angle)
{
	int turn_time;
	if (angle > 360)
		return;
	add_path(GET_TAHO());
	turn_time = A360_TURNTIME / (360 / angle);
	ON_RIGHT(TURN_PWR);
	WAIT(turn_time);
	robot_mov.curr_angle -= angle;
	RESET_TACHO();
	/* return to last move mode */
	if (robot_mov.last_dir == M_FWD)
		ON_FWD(robot_mov.last_pwr);
	else if (robot_mov.last_dir == M_REV)
		ON_REV(robot_mov.last_pwr);
	else
		ENG_STOP();
}

void eng_left (char power)
{
	ON_LEFT(power);
	robot_mov.last_dir = M_LEFT;
	robot_mov.last_pwr = power;
}

void eng_right (char power)
{
	ON_RIGHT(power);
	robot_mov.last_dir = M_RIGHT;
	robot_mov.last_pwr = power;
}

void eng_stop ()
{
	ENG_STOP();
	robot_mov.last_dir = M_NONE;
	robot_mov.last_pwr = 0;
}

/* check if tacho changed since last check, if so return true */
bool tacho_changed ()
{
	bool val = (robot_mov.last_tacho == GET_TACHO());
	robot_mov.last_tacho = GET_TACHO();
	return val;
}
