# Icinga 2
# Copyright (C) 2012-present Icinga Development Team (http://www.icinga.org)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

include(BoostTestTargets)

add_boost_test(base
  SOURCES base-array.cpp base-convert.cpp base-dictionary.cpp base-fifo.cpp
          base-match.cpp base-netstring.cpp base-object.cpp base-serialize.cpp
          base-shellescape.cpp base-stacktrace.cpp base-stream.cpp
          base-string.cpp base-timer.cpp base-type.cpp base-value.cpp
          icinga-perfdata.cpp test.cpp
  LIBRARIES base config icinga
  TESTS base_array/construct
        base_array/getset
        base_array/insert
        base_array/remove
        base_array/foreach
        base_array/clone
        base_array/json
        base_convert/tolong
        base_convert/todouble
        base_convert/tostring
        base_convert/tobool
        base_dictionary/construct
        base_dictionary/get1
        base_dictionary/get2
        base_dictionary/foreach
        base_dictionary/remove
        base_dictionary/clone
        base_dictionary/json
        base_fifo/construct
        base_fifo/io
        base_match/tolong
        base_netstring/netstring
        base_object/construct
        base_object/getself
        base_object/weak
        base_serialize/scalar
        base_serialize/array
        base_serialize/dictionary
        base_serialize/object
        base_shellescape/escape_basic
        base_shellescape/escape_quoted
        base_stacktrace/stacktrace
        base_stream/readline_stdio
        base_string/construct
        base_string/equal
        base_string/clear
        base_string/append
        base_string/trim
	base_string/contains
        base_string/replace
        base_string/index
        base_string/find
        base_timer/construct
        base_timer/interval
        base_timer/invoke
        base_timer/scope
        base_value/scalar
        base_value/convert
        base_value/format
	icinga_perfdata/simple
	icinga_perfdata/multiple
	icinga_perfdata/uom
	icinga_perfdata/warncritminmax
	icinga_perfdata/invalid
)

