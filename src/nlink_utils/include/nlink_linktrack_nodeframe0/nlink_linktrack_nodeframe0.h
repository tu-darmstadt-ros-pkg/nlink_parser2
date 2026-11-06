#ifndef NLINK_LINKTRACK_NODEFRAME0_H
#define NLINK_LINKTRACK_NODEFRAME0_H
#ifdef __cplusplus
extern "C" {
#endif
#include "nlink_typedef.h"

#define NLT_NODEFRAME0_MAX_DATA_LENGTH 1024

typedef struct {
  linktrack_role_e role;
  uint8_t id;
  uint16_t data_length;
  // Max payload per node per frame. The upstream nlink_unpack version used 224
  // and copied without a length check, so larger frames overflowed the buffer.
  // UnpackData now rejects frames whose node payload exceeds this size.
  uint8_t data[NLT_NODEFRAME0_MAX_DATA_LENGTH];
} nlt_nodeframe0_node_t;

typedef struct {
  uint8_t role;
  uint8_t id;
  uint8_t valid_node_count;
  nlt_nodeframe0_node_t *nodes[256];
} nlt_nodeframe0_result_t;

typedef struct {
  const size_t fixed_part_size;
  const uint8_t frame_header;
  const uint8_t function_mark;
  nlt_nodeframe0_result_t result;
  uint8_t (*const UnpackData)(const uint8_t *data, size_t data_length);
} nlt_nodeframe0_t;

extern nlt_nodeframe0_t g_nlt_nodeframe0;

#ifdef __cplusplus
}
#endif

#endif // NLINK_LINKTRACK_NODEFRAME0_H
