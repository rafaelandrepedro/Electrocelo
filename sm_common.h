/* 
 * File:   sm_common.h
 * Author: cpereira
 *
 * Created on 15 de Setembro de 2014, 14:12
 */

#ifndef SM_COMMON_H
#define	SM_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>


/**
 * \typedef sm_event_t
 * \brief   Enum with all possible events (including NULL event)
 *
 * This enumeration should include all states of all state machines in
 * the system. The events are not associated to a specific state machine
 * because the same event can trigger actions in more than one
 * state machine.
 */
typedef enum {ev_NULL,
                    ev_ParameterIsSelected,
                    ev_ParameterIsEdited,
                    ev_CancelEdition,
                    ev_ParameterIsSaved,
                    ev_showCounter,
                    ev_goto_MenuConfig,
                    ev_goto_StandBy,
                    ev_addRemotes,
                    ev_NextRemote,
                    ev_GateClosed,
                    ev_GateOpened,
                    ev_OpenGate,
                    ev_StopGate,
                    ev_CloseGate,
                    ev_ClosedGate,
                    ev_ErrorGate,
                    ev_MotorIsOpen,
                    ev_ErrorLearning,
                    ev_LearningComplete,
                    ev_SartLearning,
                    } sm_event_t;
/**
 * History mode of state machines.
 */
typedef enum {
		HIST_NONE=0,		/**< No history */
		HIST_SHALLOW,		/**< Shallow history */
		HIST_DEEP			/**< Deep history */
} sm_history_t;

/** sm_state_t is simply an alias to int, so it can be the primitive type for all states */
#define sm_state_t	int

/**
 * \struct sm_t
 * \brief	State machine basic structure
 *
 * This is the main structure to implement the state machine. Every state machine in the
 * system is represented by an entity of sm_t type.
 *
 * All interactions with the state machine must be performed by sm_send_event(). The
 * main program should regularly update the state machine by invoking the corresponding
 * sm_execute().
 *
 */
typedef struct {
	sm_state_t current_state;			/**< Machine's current state */
	sm_state_t initial_state;			/**< Initial state */
	int last_event;					/**< Most recent event sent to the machine */
	sm_history_t history;				/**< History mode of the state machine. Aplicable only to sub-machines */
	/* Structure data: who is the parent? */
	void* parent_machine;				/**< For sub-machines: parent machine. NULL for a top level state machine */
	sm_state_t parent_state;			/**< For sub-machines: parent state in the parent machine. */
} sm_t;


/**
 * \fn void sm_init(sm_t *psm, sm_state_t initial_state, sm_history_t hist_mode)
 *
 * \param psm 			Pointer to the state machine structure
 * \param initial_state	Machine's initial state
 * \param hist_mode		History mode of the state machine (see #sm_history_t)
 *
 * \brief	Initialize a state machine
 *
 * Defines the start conditions for the state machine (initial state and
 * history mode) and restarts the machine.
 *
 */
void sm_init(sm_t *psm, sm_state_t initial_state, sm_history_t hist_mode);

/**
 * \fn void sm_restart(sm_t *psm)
 *
 * \brief	Restarts the state machine
 *
 * Restarts the state machine. sm_restart() uses the history mode to know whether the state
 * should be reset to the initial state. The machine's last event is cleared.
 *
 */
void sm_restart(sm_t *psm);

/**
 * \fn sm_state_t sm_get_current_state(sm_t *psm)
 *
 * \brief Getter for the current state of a state machine
 */
sm_state_t sm_get_current_state(sm_t *psm);

/**
 * \fn void sm_send_event(sm_t *psm, int event)
 *
 * \brief Send an event to a state machine.
 *
 * All the interactions with the state machine should be done by invoking
 * sm_send_event().
 */
void sm_send_event(sm_t *psm, int event);


#ifdef	__cplusplus
}
#endif

#endif	/* SM_COMMON_H */

