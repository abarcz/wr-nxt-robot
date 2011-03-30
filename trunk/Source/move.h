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
	
	#define ON_FWD(p) OnRevReg(MOT_ALL, p, OUT_REGMODE_SYNC)
	#define ON_FWDL(p) OnRev(MOT_L, p)
	#define ON_FWDR(p) OnRev(MOT_R, p)
	#define ON_REV(p) OnFwdReg(MOT_ALL, p, OUT_REGMODE_SYNC)
	#define ON_REVL(p) OnFwd(MOT_L, p)
	#define ON_REVR(p) OnFwd(MOT_R, p)
	#define ON_LEFT(p) OnRev(MOT_R,p);OnFwd(MOT_L,p)
	#define ON_RIGHT(p) OnRev(MOT_L,p);OnFwd(MOT_R,p)
	#define ENG_STOP() Coast(MOT_ALL)
	#define ENG_BRAKE() Off(MOT_ALL)
	#define WAIT(t) Wait(t)
#endif

/* types of movement */
#define M_NONE  0
#define M_FWD   1
#define M_REV   2
#define M_LEFT  3
#define M_RIGHT 4 

/* time needed to turn 360 degrees */
#define A360_TURNTIME 890
#define A90_TURNTIME 255
#define TURN_PWR 75 //power needed for the turn

/* lowspeed rotation */
#define A90_LS_TURNTIME 1000
#define TURN_LS_PWR 20

struct move_str
{
	int last_dir;
	int last_pwr;
	long last_tacho;
	int curr_angle;		// current angle (in degrees) - starting angle is 0deg
	long vx;			// distance travelled in 'x' direction since init
	long vy;			// distance travelled in 'y' direction since init
};

/************************** global variables **************************/

/* global container for robot moves data */
move_str robot_mov;


/*********************** function definitions ***********************/

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
	/*if (robot_mov.last_dir == M_FWD)
	{
		robot_mov.vx += v * cosd(robot_mov.curr_angle - 90);
		robot_mov.vy += v * sind(robot_mov.curr_angle - 90);
	}
	else // M_REV
	{
		robot_mov.vx -= v * cosd(robot_mov.curr_angle - 90);
		robot_mov.vy -= v * sind(robot_mov.curr_angle - 90);
	}*/
}
	
void eng_fwd_reg(char power_l, char power_r)
{
	ON_FWDL(power_l);
	ON_FWDR(power_r);
}

void eng_rev_reg(char power_l, char power_r)
{
	ON_REVL(power_l);
	ON_REVR(power_r);
}

void eng_fwd (char power)
{
	if (robot_mov.last_dir == M_REV)
	{
		add_path(GET_TACHO());	// save vector info if last move rev
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
		add_path(GET_TACHO());
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
	add_path(GET_TACHO());			// save taho from last move
	if (angle > 90)
		turn_time = A360_TURNTIME * angle / 360;
	else
		turn_time = A90_TURNTIME * angle / 90;

	ON_LEFT(TURN_PWR);				// rotate the robot
	WAIT(turn_time);
	robot_mov.curr_angle += angle;	// update the robot's angle information
	RESET_TACHO();					// reset taho for the next move
	/* return to last move mode */
	/*if (robot_mov.last_dir == M_FWD)
		ON_FWD(robot_mov.last_pwr);
	else if (robot_mov.last_dir == M_REV)
		ON_REV(robot_mov.last_pwr);
	else
		ENG_STOP();*/
	ENG_BRAKE();
}

void eng_turn_right (int angle)
{
	int turn_time;
	if (angle > 360)
		return;
	add_path(GET_TACHO());
	if (angle > 90)
		turn_time = A360_TURNTIME * angle / 360;
	else
		turn_time = A90_TURNTIME * angle / 90;
	ON_RIGHT(TURN_PWR);
	WAIT(turn_time);
	robot_mov.curr_angle -= angle;
	RESET_TACHO();
	/* return to last move mode */
	/*if (robot_mov.last_dir == M_FWD)
		ON_FWD(robot_mov.last_pwr);
	else if (robot_mov.last_dir == M_REV)
		ON_REV(robot_mov.last_pwr);
	else
		ENG_STOP();*/
	ENG_BRAKE();
}

void eng_turn_ls_left (int angle)
{
	int turn_time;
	if (angle > 90)
		return;
	turn_time = A90_LS_TURNTIME * angle / 90;

	ON_LEFT(TURN_LS_PWR);				// rotate the robot
	WAIT(turn_time);
	ENG_BRAKE();
}

void eng_turn_ls_right (int angle)
{
	int turn_time;
	if (angle > 90)
		return;
	turn_time = A90_LS_TURNTIME * angle / 90;

	ON_RIGHT(TURN_LS_PWR);				// rotate the robot
	WAIT(turn_time);
	ENG_BRAKE();
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
	ENG_BRAKE();
	add_path(GET_TACHO());		// save the last move vector
	RESET_TACHO();
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

long get_tacho ()
{
	return GET_TACHO();
}

