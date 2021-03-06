// Copyright 2015 Twin Oaks Computing, Inc.
// Modifications copyright (C) 2017-2018 Twin Oaks Computing, Inc.
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

#ifndef RMW_COREDX_CPP__UTIL_HPP_
#define RMW_COREDX_CPP__UTIL_HPP_

#include "rosidl_typesupport_coredx_c/identifier.h"
#include "rosidl_typesupport_coredx_cpp/identifier.hpp"


bool get_datareader_qos(DDS::DomainParticipant  * participant,
                        const rmw_qos_profile_t * qos_profile,
                        DDS::DataReaderQos      & datareader_qos);
bool get_datawriter_qos(DDS::DomainParticipant  * participant,
                        const rmw_qos_profile_t * qos_profile,
                        DDS::DataWriterQos      & datawriter_qos);
rmw_ret_t check_attach_condition_error(DDS::ReturnCode_t retcode);

const message_type_support_callbacks_t *get_callbacks(const rosidl_message_type_support_t * type_supports );

/* ************************************************
 */
inline char *
do_strdup( const char *n)
{
  char * retval =
    reinterpret_cast<char *>(rmw_allocate(sizeof(char) * strlen((char*)n) + 1));
  if (retval)
    memcpy(const_cast<char *>(retval), n, strlen(n) + 1);
  return retval;
}

/* ************************************************
 */
inline std::string
_create_type_name(
  const message_type_support_callbacks_t * callbacks,
  const std::string & sep)
{
  return
    std::string(callbacks->package_name) +
    "::" + sep + "::dds_::" + callbacks->message_name + "_";
}

#define RMW_COREDX_EXTRACT_MESSAGE_TYPESUPPORT(TYPE_SUPPORTS, TYPE_SUPPORT) \
  do {                                                                  \
    if (!TYPE_SUPPORTS) {                                               \
      RMW_SET_ERROR_MSG("type supports handle is null");                \
      return NULL;                                                      \
    }                                                                   \
    TYPE_SUPPORT =                                                      \
      get_message_typesupport_handle                                    \
      (TYPE_SUPPORTS,                                                   \
       rosidl_typesupport_coredx_c__identifier);                        \
    if (!TYPE_SUPPORT)                                                  \
      TYPE_SUPPORT =                                                    \
        get_message_typesupport_handle                                  \
        (TYPE_SUPPORTS,                                                 \
         rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier); \
    if (!TYPE_SUPPORT) {                                                \
      char __msg[1024];                                                 \
      snprintf(__msg, 1024,                                             \
               "type support handle implementation '%s' (%p) does not match valid type supports " \
               "('%s' (%p), '%s' (%p))",                                \
               TYPE_SUPPORTS->typesupport_identifier,                   \
               static_cast<const void *>(TYPE_SUPPORTS->typesupport_identifier), \
               rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier,   \
               static_cast<const void *>(rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier), \
               rosidl_typesupport_coredx_c__identifier,                 \
               static_cast<const void *>(rosidl_typesupport_coredx_c__identifier)); \
      RMW_SET_ERROR_MSG(__msg);                                         \
      return NULL;                                                      \
    } } while(0)

#define RMW_COREDX_EXTRACT_SERVICE_TYPESUPPORT(TYPE_SUPPORTS, TYPE_SUPPORT) \
  do {                                                                  \
    if (!TYPE_SUPPORTS) {                                               \
      RMW_SET_ERROR_MSG("type supports handle is null");                \
      return NULL;                                                      \
    }                                                                   \
    TYPE_SUPPORT =                                                      \
      get_service_typesupport_handle                                    \
      ( TYPE_SUPPORTS, rosidl_typesupport_coredx_c__identifier);        \
    if (!TYPE_SUPPORT)                                                  \
      TYPE_SUPPORT =                                                    \
        get_service_typesupport_handle                                  \
        (TYPE_SUPPORTS,                                                 \
         rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier); \
    if (!TYPE_SUPPORT) {                                                \
      char __msg[1024];                                                 \
      snprintf(__msg, 1024,                                             \
               "type support handle implementation '%s' (%p) does not match valid type supports " \
               "('%s' (%p), '%s' (%p))",                                \
               TYPE_SUPPORTS->typesupport_identifier,                   \
               static_cast<const void *>(TYPE_SUPPORTS->typesupport_identifier), \
               rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier,   \
               static_cast<const void *>(rosidl_typesupport_coredx_cpp::typesupport_coredx_identifier), \
               rosidl_typesupport_coredx_c__identifier,                 \
               static_cast<const void *>(rosidl_typesupport_coredx_c__identifier)); \
      RMW_SET_ERROR_MSG(__msg);                                         \
      return NULL;                                                      \
    } } while (0)                                                                   
    
#endif // RMW_COREDX_CPP__UTIL_HPP_
