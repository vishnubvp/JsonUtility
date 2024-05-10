

#ifndef BASEINCLUDE_H_
#define BASEINCLUDE_H_

#include <algorithm>

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <atomic>

#include <sstream>
#include <time.h>

#include <limits>
#include <float.h>
#include <stdint.h>

#include "core/external/rapidjson/document.h"
#include "core/external/rapidjson/stringbuffer.h"
#include "core/external/rapidjson/writer.h"

#define SMART_PTR std

#include "core/util/TypeDefs.h"

#ifdef ANDROID
#include "core/android/UTFUtils.h"
#endif

#ifdef __GNUC__
#define DEPRECATED __attribute__ ((deprecated))
#else
#define DEPRECATED
#endif


#endif /* BASEINCLUDE_H_ */
