/*
* sm_common.c
*
* Created: 26-06-2013 16:23:41
*  Author: pf
*/

#include <stdio.h>

#include "sm_common.h"

void sm_init(sm_t *psm, sm_state_t initial_state, sm_history_t hist_mode)
{
	psm->initial_state = initial_state;
	psm->history = hist_mode;
	psm->current_state = initial_state; // Regardless of history mode, state machine
										// should start in initial_state when it is
										// created.
	psm->parent_machine = NULL;
	sm_restart(psm);
}

void sm_restart(sm_t *psm){
	if(psm->history == HIST_NONE){
		psm->current_state = psm->initial_state;
	}
	psm->last_event = 0;
}

sm_state_t sm_get_current_state(sm_t *psm){
	return psm->current_state;
}

void sm_send_event(sm_t *psm, int event)
{
	if(( psm->parent_machine == NULL) || \
	(sm_get_current_state(psm->parent_machine)==psm->parent_state))
	{
		psm->last_event = event;
	}
}

