// Copyright 2016 Thomas Trapp
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

%module hext

%include "typemaps.i"
%include "std_vector.i"
%include "std_string.i"

// Convert vector of multimaps to array of arrays, because swig has no
// std_multimap.i for PHP.
%typemap(out) std::vector<std::multimap<std::string, std::string>> {
  // Assuming $1 is of type SwigValueWrapper.
  array_init($result);
  for(const auto& map : *(&$1))
  {
    zval * out_map;
    MAKE_STD_ZVAL(out_map);
    array_init(out_map);

    for(const auto& p : map)
    {
      // Overwrite already existing keys (same behaviour as python's
      // std_multimap.i).
      add_assoc_string(
        out_map,
        p.first.c_str(),
        // Since we request that the string should be copied, this const_cast
        // should be safe.
        const_cast<char *>(p.second.c_str()),
        // Copy the string
        1
      );
    }

    add_next_index_zval($result, out_map);
  }
}

%include "exception.i"
%exception Rule::Rule {
  try
  {
    $action
  }
  catch(const hext::SyntaxError& e)
  {
    SWIG_exception(SWIG_ValueError, e.what());
  }
}

%ignore Html::root() const;
%{
#include "swig-html.h"
#include "swig-rule.h"
%}
%include "swig-html.h"
%include "swig-rule.h"
