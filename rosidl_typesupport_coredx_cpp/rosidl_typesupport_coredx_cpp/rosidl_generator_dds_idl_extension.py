# Copyright 2014 Open Source Robotics Foundation, Inc.
# Modifications copyright (C) 2017 Twin Oaks Computing, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from rosidl_generator_dds_idl import get_post_struct_lines as get_default_post_struct_lines

def get_post_struct_lines(message):
    lines = get_default_post_struct_lines(message)
    if message.structure.namespaced_type.name.endswith('_Request'):
         lines.append('//@request_type')
    elif message.structure.namespaced_type.name.endswith('_Response'):
         lines.append('//@reply_type')
    return lines
