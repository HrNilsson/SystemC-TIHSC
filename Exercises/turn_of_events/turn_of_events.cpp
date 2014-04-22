//BEGIN turn_of_events.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "turn_of_events.h"

void turn_of_events::turn_knob_thread(void) {
  enum directions {LEFT='l', RIGHT='r', OFF='f', STOP='s', QUIT='q'};
  bool left_on, right_on, stop_on;
  char direction;
  left_on = right_on = stop_on = false;

  wait(SC_ZERO_TIME);
  std::cout << "Commands are (case sensitive):" << endl
            << "   l => Left turn signal on" << endl
            << "   r => Right turn signal on" << endl
            << "   s => Stop signal on" << endl
            << "   f => turn all signals oFF" << endl
            << "   q => Quit program" << endl
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  for(;;) {
    std::cout << "Signal command [l/r/s/f/q]: ";
    std::cin >> direction;
    switch (direction) {
      case RIGHT: 
        signal_right.notify(); 
        if (!right_on) wait(right_blinking);
        else std::cout << "INFO: Right signal is already on" << endl;
        right_on = true;
        break;
      case LEFT: 
        signal_left.notify(); 
        if (!left_on) wait(left_blinking);
        else std::cout << "INFO: Left signal is already on" << endl;
        left_on = true;
        break;
      case STOP: 
        signal_stop.notify(); 
        if (!stop_on) wait(stop_blinking);
        else std::cout << "INFO: Stop signal is already on" << endl;
        stop_on = true;
        break;
      case OFF: 
        signals_off.notify(); 
        if (right_on && left_on && stop_on) wait(right_off & left_off & stop_off);
        else if (right_on && left_on) wait(right_off & left_off);
        else if (right_on && stop_on) wait(right_off & stop_off);
        else if (left_on  && stop_on) wait(left_off  & stop_off);
        else if (right_on) wait(right_off);
        else if (left_on)  wait(left_off);
        else if (stop_on)  wait(stop_off);
        right_on = left_on = stop_on = false;
        break;
      case QUIT:
        std::cout << "Quiting" << std::endl;
        sc_stop();
        return;
        break;
    }//endswitch
  }//endforever
}//end turn_knob_thread()

void turn_of_events::right_signal_thread(void) {
  for(;;) {
    wait(signal_right);
    std::cout << "Turning right ->->->" << std::endl;
    right_blinking.notify();
    wait(signals_off);
    std::cout << "Right off     ------" << std::endl;
    right_off.notify();
  }//endforever
}//end right_signal_thread()

void turn_of_events::left_signal_thread(void) {
  for(;;) {
    wait(signal_left);
    std::cout << "Turning left  <-<-<-" << std::endl;
    left_blinking.notify();
    wait(signals_off);
    std::cout << "Left off      ------" << std::endl;
    left_off.notify();
  }//endforever
}//end left_signal_thread()

void turn_of_events::stop_signal_thread(void) {
  for(;;) {
    wait(signal_stop);
    std::cout << "Stopping      !!!!!!" << std::endl;
    stop_blinking.notify();
    wait(signals_off);
    std::cout << "Stop off      ------" << std::endl;
    stop_off.notify();
  }//endforever
}//end right_signal_thread()


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: turn_of_events.cpp,v 1.5 2004/04/02 18:06:02 dcblack Exp $
