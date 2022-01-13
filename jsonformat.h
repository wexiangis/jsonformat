#ifndef _JSON_FORMAT_INCLUDE_
#define _JSON_FORMAT_INCLUDE_

#include <stdint.h>

#ifdef cplusplus
extern "C" {
#endif

/* space换行缩进空格数 */
size_t JsonFormat(const char* json, char* buff, size_t buffSize, uint32_t space);

#ifdef cplusplus
}
#endif

#endif
