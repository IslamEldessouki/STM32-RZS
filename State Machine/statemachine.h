 /** @file statemachine.h
 * @brief class declaration for finite state machine */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H

typedef void (*fptr)(void); //!< Pointer to function type

#define DO_NOTHING 0 //!< dummy function pointer, no action performed

//! Single field for transition matrix
typedef struct
{
   fptr action;         //!< pointer to action performed on transition
   state_type target_state;    //!< target state for transition
} transition_matrix_element;

//! Transition Matrix type for Finite State Machine
typedef transition_matrix_element transition_matrix_type[N_STATEMACHINE_EVENTS][N_STATES];

//! Transition Matrix for Rolltor
extern const transition_matrix_type transition_matrix;

//! general finite stat-machine
class statemachine
{
public:
   statemachine(const transition_matrix_type &init_matrix, state_type initial_state)
      : matrix( init_matrix),
        current_state( initial_state)
   {};
   state_type signal_event( statemachine_event_type event)
   {
      // find correct field within matrix
      const transition_matrix_element * tile =
            &(transition_matrix[event][current_state]);

      // perform transition
      if (tile->target_state != PRESERVE_STATE)
            current_state = tile->target_state;

      // call back action if any
      if( tile->action != DO_NOTHING)
            tile->action();

      return current_state;
   }
   state_type get_state( void) const
   {
      return current_state;
   }
private:
   const transition_matrix_type &matrix;
   state_type current_state;
};

#endif /* STATEMACHINE_H_ */
