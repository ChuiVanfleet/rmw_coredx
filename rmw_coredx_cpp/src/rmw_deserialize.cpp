// Copyright 2018 Twin Oaks Computing, Inc.
// Modifications copyright (C) 2018 Twin Oaks Computing, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <rmw/error_handling.h>
#include <rmw/rmw.h>
#include <rmw/allocators.h>

#include "rmw_coredx_types.hpp"
#include "util.hpp"

extern "C"
{
  rmw_ret_t
  rmw_deserialize(
		  const rmw_serialized_message_t * serialized_message,
		  const rosidl_message_type_support_t * type_support,
		  void * ros_message)
  {
    const message_type_support_callbacks_t * callbacks = get_callbacks(type_support);
    if (!callbacks) {
      RMW_SET_ERROR_MSG("callbacks handle is null");
      return RMW_RET_ERROR;
    }

    if (!callbacks->deserialize(ros_message, serialized_message)) {
      RMW_SET_ERROR_MSG("can't convert cdr stream to ros message");
      return RMW_RET_ERROR;
    }

    return RMW_RET_OK;
  }

}  // extern "C"
