*******************************************************************************
helicopter_project.c
    - Contains the main program and while loop to run backround tasks and call 
      support functions. Also inlcudes a scheduler and the state machine to move \
      between landed, flying and takeoff states.
      
*******************************************************************************      
Inits.c
    - Contains the set of functions to initialise ports, pins and timers

*******************************************************************************
PWM_rotors.c
    - Contains the set of functions to initialise and set PWM signals

*******************************************************************************
alt_ADC.c
    - Contains the set of functions to handle altitude ADC.

*******************************************************************************
buttons.c
    - Contains the set of functions to initialise buttons and deal with button 
      pushes.

*******************************************************************************
control_system.c
    - Contains the set of functions containing the PID controllers for yaw and 
      altitude.

*******************************************************************************
draw_display.c
    - Contains the set of functions to display on the orbit and the serial UART 
      terminal.

*******************************************************************************
yaw_functions.c
    - Contains the set of functions for the continuous monitoring of yaw.# HelicopterControlProgram
