#include "../command.h"

const uint8_t DD47_CONSTANT_BYTES[5] = { 0x00, 0x02, 0x00, 0x01, 0x00 };

command_result dd47_initialize(volatile command_packet *packet, controller_state *state) {
  // No initialization or memory state management needed
  return CRInitialized;
}

command_result dd47_process(volatile command_packet *packet, controller_state *state) {
  if (packet->data_index == 0) {
    packet->write(0x00);
  } else {
    packet->write(DD47_CONSTANT_BYTES[packet->data_index - 1]);
  }

  // If the final byte hasn't been written, mark this command as still processing
  if (packet->data_index + 1 != 6) {
    return CRProcessing;
  }

  return CRCompleted;
}

command_processor command_controller_device_descriptor_47 = {
    .id = 0x47,
    .initialize = &dd47_initialize,
    .process = &dd47_process,
};