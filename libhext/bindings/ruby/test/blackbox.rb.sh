#!/usr/bin/env bash

# Copyright 2016 Thomas Trapp
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


# This is a wrapper script for blackbox.sh.
# It tells blackbox.sh to use htmlext.rb and runs all the blackbox test cases.
# This script uses hardcoded paths to locations within this repository.
# If the build directory is found Ruby is told to use the build directory as an
# include path.

thisdir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
incldir="$(readlink -f "$thisdir/../build")"
htmlext="$(readlink -f "$thisdir/../htmlext.rb")"
testdir="$(readlink -f "$thisdir/../../../../test")"
casedir="$testdir/case"
blacksh="$testdir/blackbox.sh"

perror_exit() { echo "$1" >&2 ; exit 1 ; }
[[ -f "$htmlext" ]] || perror_exit "Cannot find htmlext.rb (tried '$htmlext')"
[[ -f "$blacksh" ]] || perror_exit "Cannot find blackbox.sh (tried '$blacksh')"
[[ -d "$casedir" ]] || perror_exit "Cannot find test cases (tried '$casedir')"

rb_param=""
[[ -d "$incldir" ]] && {
  rb_param="-I$incldir"
}
export HTMLEXT="ruby $rb_param $htmlext"
"$blacksh" "$casedir"/*.hext

