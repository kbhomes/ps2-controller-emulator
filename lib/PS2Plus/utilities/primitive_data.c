#include "primitive_data.h"

#include <string.h>

const primitive_data primitive_data_unknown = { .type = PDT_Unknown };

void primitive_data_initialize_boolean(primitive_data *pd, bool value) {
  pd->type = PDT_Boolean;
  pd->boolean = value;
}

void primitive_data_initialize_uint8(primitive_data *pd, uint8_t value) {
  pd->type = PDT_Uint8;
  pd->uint8 = value;
}

void primitive_data_initialize_uint16(primitive_data *pd, uint16_t value) {
  pd->type = PDT_Uint16;
  pd->uint16 = value;
}

void primitive_data_initialize_uint32(primitive_data *pd, uint32_t value) {
  pd->type = PDT_Uint32;
  pd->uint32 = value;
}

void primitive_data_initialize_array(primitive_data *pd, uint8_t *value, uint8_t length) {
  pd->type = PDT_Array;
  pd->array.length = length;
  pd->array.data = value;
}

size_t primitive_data_length(primitive_data *pd) {
  switch (pd->type) {
    case PDT_Boolean: return 2;
    case PDT_Uint8: return 2;
    case PDT_Uint16: return 3;
    case PDT_Uint32: return 5;
    case PDT_Array: return 2 + pd->array.length;
    default: return 1;
  }
}

void primitive_data_serialize(primitive_data *pd, uint8_t *out) {
  out[0] = pd->type;

  switch (pd->type) {
    case PDT_Boolean:
      out[1] = pd->boolean ? 0xFF : 0x00;
      return;
    
    case PDT_Uint8:
      out[1] = pd->uint8;
      return;
      
    case PDT_Uint16:
      out[1] = (pd->uint16 & 0xFF);
      out[2] = (pd->uint16 >> 8) & 0xFF;
      return;
      
    case PDT_Uint32:
      out[1] = (pd->uint32 & 0xFF);
      out[2] = (pd->uint32 >> 8) & 0xFF;
      out[3] = (pd->uint32 >> 16) & 0xFF;
      out[4] = (pd->uint32 >> 24) & 0xFF;
      return;     

    case PDT_Array:
      out[1] = pd->array.length;
      memcpy(out + 2, pd->array.data, pd->array.length);
      return;

    case PDT_Unknown:
    default:
      out[1] = 0xFF;
      return;
  }
}

void primitive_data_deserialize(primitive_data *pd, uint8_t *in) {
  pd->type = in[0];

  switch (pd->type) {
    case PDT_Boolean:
      pd->boolean = in[1] != 0x00;
      return;
    
    case PDT_Uint8:
      pd->uint8 = in[1];
      return;
      
    case PDT_Uint16:
      pd->uint16 = in[1] | ((uint16_t)in[2] << 8);
      return;
      
    case PDT_Uint32:
      pd->uint32 = in[1] | ((uint32_t)in[2] << 8) | ((uint32_t)in[3] << 16) | ((uint32_t)in[4] << 24);
      return;     

    case PDT_Array:
      pd->array.length = in[1];
      pd->array.data = in + 2;
      return;

    case PDT_Unknown:
    default:
      return;
  }
}