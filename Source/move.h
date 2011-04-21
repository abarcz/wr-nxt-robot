/* 
 * Controlling the robot's movement
 */ 

/* motors configuration */
#define MOT_ALL OUT_AC		// all the motors
#define MOT_L OUT_A			// left motor
#define MOT_R OUT_C			// right motor

/* move functions */
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

/* angle rotate constants */
#define A360_TURNTIME 850	// time needed to turn 360 degrees with const power
#define A90_TURNTIME 235	// time needed to turn 90 degrees with const power
#define TURN_PWR 75 		//power supplied during the turn
	
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
	ON_FWD(power);
}

void eng_rev (char power)
{
	ON_REV(power);
}

void eng_turn_left (int angle)
{
	int turn_time;
	if (angle > 360)
		return;
	if (angle > 90)
		turn_time = A360_TURNTIME * angle / 360;
	else
		turn_time = A90_TURNTIME * angle / 90;
	ON_LEFT(TURN_PWR);				// rotate the robot
	Wait(turn_time);
	ENG_BRAKE();
}

void eng_turn_right (int angle)
{
	int turn_time;
	if (angle > 360)
		return;
	if (angle > 90)
		turn_time = A360_TURNTIME * angle / 360;
	else
		turn_time = A90_TURNTIME * angle / 90;
	ON_RIGHT(TURN_PWR);
	Wait(turn_time);
	ENG_BRAKE();
}

void eng_left (char power)
{
	ON_LEFT(power);
}

void eng_right (char power)
{
	ON_RIGHT(power);
}

void eng_stop ()
{
	ENG_BRAKE();
}
