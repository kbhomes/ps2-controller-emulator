#ifndef COMMANDS_COMMAND_H
#define COMMANDS_COMMAND_H

#include "packet.h"

#include <platforms/platform.h>
#include <controller/state.h>

typedef enum {
  CRInitialized,
  CRProcessing,
  CRCompleted,
  CRError,
} command_result;

typedef struct command_processor {
  uint8_t id;
  command_result (*initialize)(volatile command_packet *packet, controller_state *);
  command_result (*process)(volatile command_packet *packet, controller_state *);

  // TODO: Add a `finalize` method that can receive the final command byte of the transmission
  //       (will help to correcltly implement the map motors command with all 6 actuator channels)
} command_processor;

// All available command processors
extern command_processor initialize_pressure_sensor_command;
extern command_processor button_inclusions_command;
extern command_processor main_polling_command;
extern command_processor enter_exit_config_command;
extern command_processor switch_digital_analog_mode_command;
extern command_processor status_info_command;
extern command_processor device_descriptor_46_command;
extern command_processor device_descriptor_47_command;
extern command_processor device_descriptor_4c_command;
extern command_processor map_motors_command;
extern command_processor configure_analog_response_command;

/**
 * @brief Table of polling commands indexed by the lower nibble of the command ID.
 * 
 * All polling commands that can be processed have a 4 as the higher nibble. The correct
 * command processor can be quickly obtained by taking the lower nibble of the command ID
 * and indexing into this array. An invalid command will have a NULL processor.
 */
extern command_processor *command_processors[];

command_processor *command_find_processor(uint8_t id);

#endif /* COMMANDS_COMMAND_H */