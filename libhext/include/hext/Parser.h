// This file was generated from Parser.h.rl.

#line 1 "Parser.h.rl"
#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/StringUtil.h"
#include "hext/Builtins.h"
#include "hext/Rule.h"
#include "hext/RuleBuilder.h"
#include "hext/PatternBuilder.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <memory>

#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>


/// Convenience macro to store the start of a token. Used within the hext
/// machine definition. Accesses local variables of `Parser::parse()`.
#define TK_START \
  tok_begin = p; \
  tok_end = nullptr;


/// Convenience macro to complete a token. Used within the hext
/// machine defintion. Accesses local variables of `Parser::parse()`.
#define TK_STOP                 \
  assert(tok_begin != nullptr); \
  tok_end = p;                  \
  tok = std::string(tok_begin, std::distance(tok_begin, tok_end));


namespace hext {


/// ParseError is a custom exception class thrown for all errors that occur
/// while parsing hext.
/// Note: Clang warns (-Wweak-vtables) that a vtable for ParseError may be
/// placed in every translation unit, because ParseError doesn't have any
/// 'out-of-line virtual method definitions', where it would normally put
/// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
/// is a non-issue; the linker will clean it up.
class ParseError : public std::runtime_error
{
public:
  explicit ParseError(const std::string& msg);
};


/// The ragel namespace holds ragel's static data.
namespace ragel {
  /// Embed the ragel state machine.
  
#line 61 "Parser.h.tmp"
static const char _hext_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 1, 25, 1, 26, 1, 
	27, 1, 28, 1, 29, 1, 30, 1, 
	31, 1, 32, 1, 33, 1, 35, 1, 
	36, 1, 37, 1, 38, 1, 41, 1, 
	42, 1, 44, 2, 1, 45, 2, 24, 
	25, 2, 26, 27, 2, 28, 29, 2, 
	29, 37, 2, 31, 34, 2, 31, 37, 
	2, 33, 34, 2, 33, 37, 2, 39, 
	41, 2, 40, 41, 2, 41, 43, 2, 
	42, 43, 3, 0, 1, 45, 3, 28, 
	29, 37, 3, 39, 41, 43, 3, 40, 
	41, 43
};

static const short _hext_key_offsets[] = {
	0, 0, 2, 7, 8, 16, 22, 26, 
	42, 43, 44, 46, 48, 50, 58, 66, 
	67, 68, 69, 70, 71, 72, 73, 74, 
	75, 76, 77, 78, 79, 80, 81, 83, 
	86, 89, 90, 91, 92, 93, 94, 95, 
	96, 97, 98, 99, 100, 102, 105, 106, 
	107, 108, 109, 112, 113, 114, 115, 116, 
	117, 119, 120, 121, 122, 123, 126, 127, 
	128, 129, 130, 131, 132, 135, 136, 137, 
	138, 139, 141, 142, 143, 144, 145, 148, 
	149, 150, 151, 152, 153, 154, 157, 158, 
	159, 160, 163, 164, 165, 166, 167, 168, 
	172, 176, 179, 181, 183, 186, 187, 188, 
	189, 190, 191, 192, 193, 194, 195, 196, 
	197, 199, 200, 201, 202, 203, 204, 208, 
	212, 215, 217, 219, 222, 223, 224, 225, 
	226, 227, 228, 229, 230, 231, 232, 233, 
	234, 235, 236, 240, 244, 247, 249, 251, 
	254, 255, 256, 257, 258, 259, 260, 261, 
	262, 263, 264, 265, 266, 267, 268, 272, 
	276, 279, 281, 283, 286, 287, 288, 289, 
	290, 291, 292, 293, 294, 295, 296, 297, 
	298, 299, 300, 301, 302, 305, 306, 307, 
	308, 311, 318, 329, 337, 338, 341, 343, 
	345, 352, 359, 360, 363, 366, 368, 370, 
	376, 382, 383, 399, 404, 409
};

static const char _hext_trans_keys[] = {
	32, 35, 32, 35, 60, 62, 126, 10, 
	32, 58, 62, 63, 65, 90, 97, 122, 
	32, 64, 65, 90, 97, 122, 65, 90, 
	97, 122, 32, 33, 36, 42, 45, 61, 
	62, 94, 95, 126, 48, 57, 65, 90, 
	97, 122, 61, 34, 34, 92, 34, 92, 
	32, 62, 32, 58, 62, 63, 65, 90, 
	97, 122, 97, 99, 101, 102, 108, 110, 
	111, 116, 116, 116, 114, 105, 98, 117, 
	116, 101, 45, 99, 111, 117, 110, 116, 
	40, 48, 57, 41, 48, 57, 32, 58, 
	62, 104, 105, 108, 100, 45, 99, 111, 
	117, 110, 116, 40, 48, 57, 41, 48, 
	57, 109, 112, 116, 121, 32, 58, 62, 
	105, 114, 115, 116, 45, 99, 111, 104, 
	105, 108, 100, 32, 58, 62, 102, 45, 
	116, 121, 112, 101, 32, 58, 62, 97, 
	115, 116, 45, 99, 111, 104, 105, 108, 
	100, 32, 58, 62, 102, 45, 116, 121, 
	112, 101, 32, 58, 62, 116, 104, 45, 
	99, 108, 111, 104, 105, 108, 100, 40, 
	101, 111, 48, 57, 41, 110, 48, 57, 
	32, 58, 62, 41, 43, 48, 57, 41, 
	48, 57, 118, 101, 110, 41, 100, 100, 
	41, 97, 115, 116, 45, 99, 111, 104, 
	105, 108, 100, 40, 101, 111, 48, 57, 
	41, 110, 48, 57, 32, 58, 62, 41, 
	43, 48, 57, 41, 48, 57, 118, 101, 
	110, 41, 100, 100, 41, 102, 45, 116, 
	121, 112, 101, 40, 101, 111, 48, 57, 
	41, 110, 48, 57, 32, 58, 62, 41, 
	43, 48, 57, 41, 48, 57, 118, 101, 
	110, 41, 100, 100, 41, 102, 45, 116, 
	121, 112, 101, 40, 101, 111, 48, 57, 
	41, 110, 48, 57, 32, 58, 62, 41, 
	43, 48, 57, 41, 48, 57, 118, 101, 
	110, 41, 100, 100, 41, 110, 108, 121, 
	45, 99, 104, 105, 108, 100, 32, 58, 
	62, 101, 120, 116, 32, 58, 62, 32, 
	58, 62, 65, 90, 97, 122, 32, 45, 
	58, 62, 95, 48, 57, 65, 90, 97, 
	122, 32, 58, 62, 63, 65, 90, 97, 
	122, 92, 34, 47, 123, 47, 92, 47, 
	92, 32, 33, 62, 65, 90, 97, 122, 
	32, 33, 62, 65, 90, 97, 122, 92, 
	47, 123, 125, 47, 123, 125, 47, 92, 
	47, 92, 33, 125, 65, 90, 97, 122, 
	33, 125, 65, 90, 97, 122, 92, 32, 
	33, 36, 42, 45, 61, 62, 94, 95, 
	126, 48, 57, 65, 90, 97, 122, 32, 
	35, 60, 62, 126, 32, 35, 60, 62, 
	126, 10, 32, 35, 60, 62, 126, 0
};

static const char _hext_single_lengths[] = {
	0, 2, 5, 1, 4, 2, 0, 10, 
	1, 1, 2, 2, 2, 4, 8, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 0, 1, 
	3, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 0, 1, 1, 1, 
	1, 1, 3, 1, 1, 1, 1, 1, 
	2, 1, 1, 1, 1, 3, 1, 1, 
	1, 1, 1, 1, 3, 1, 1, 1, 
	1, 2, 1, 1, 1, 1, 3, 1, 
	1, 1, 1, 1, 1, 3, 1, 1, 
	1, 3, 1, 1, 1, 1, 1, 2, 
	2, 3, 2, 0, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	2, 1, 1, 1, 1, 1, 2, 2, 
	3, 2, 0, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 2, 2, 3, 2, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 2, 2, 
	3, 2, 0, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 3, 1, 1, 1, 
	3, 3, 5, 4, 1, 3, 2, 2, 
	3, 3, 1, 3, 3, 2, 2, 2, 
	2, 1, 10, 5, 5, 6
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 2, 2, 2, 3, 
	0, 0, 0, 0, 0, 2, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 0, 0, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	0, 0, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 0, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	0, 0, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 2, 3, 2, 0, 0, 0, 0, 
	2, 2, 0, 0, 0, 0, 0, 2, 
	2, 0, 3, 0, 0, 0
};

static const short _hext_index_offsets[] = {
	0, 0, 3, 9, 11, 18, 23, 26, 
	40, 42, 44, 47, 50, 53, 60, 69, 
	71, 73, 75, 77, 79, 81, 83, 85, 
	87, 89, 91, 93, 95, 97, 99, 101, 
	104, 108, 110, 112, 114, 116, 118, 120, 
	122, 124, 126, 128, 130, 132, 135, 137, 
	139, 141, 143, 147, 149, 151, 153, 155, 
	157, 160, 162, 164, 166, 168, 172, 174, 
	176, 178, 180, 182, 184, 188, 190, 192, 
	194, 196, 199, 201, 203, 205, 207, 211, 
	213, 215, 217, 219, 221, 223, 227, 229, 
	231, 233, 237, 239, 241, 243, 245, 247, 
	251, 255, 259, 262, 264, 267, 269, 271, 
	273, 275, 277, 279, 281, 283, 285, 287, 
	289, 292, 294, 296, 298, 300, 302, 306, 
	310, 314, 317, 319, 322, 324, 326, 328, 
	330, 332, 334, 336, 338, 340, 342, 344, 
	346, 348, 350, 354, 358, 362, 365, 367, 
	370, 372, 374, 376, 378, 380, 382, 384, 
	386, 388, 390, 392, 394, 396, 398, 402, 
	406, 410, 413, 415, 418, 420, 422, 424, 
	426, 428, 430, 432, 434, 436, 438, 440, 
	442, 444, 446, 448, 450, 454, 456, 458, 
	460, 464, 470, 479, 486, 488, 492, 495, 
	498, 504, 510, 512, 516, 520, 523, 526, 
	531, 536, 538, 552, 558, 564
};

static const unsigned char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 13, 187, 
	0, 204, 3, 5, 14, 205, 185, 186, 
	186, 0, 5, 6, 202, 202, 0, 7, 
	7, 0, 5, 8, 8, 8, 7, 189, 
	205, 8, 7, 8, 7, 7, 7, 0, 
	9, 0, 10, 0, 12, 188, 11, 12, 
	188, 11, 5, 205, 0, 5, 14, 205, 
	185, 186, 186, 0, 15, 33, 46, 51, 
	69, 86, 171, 181, 0, 16, 0, 17, 
	0, 18, 0, 19, 0, 20, 0, 21, 
	0, 22, 0, 23, 0, 24, 0, 25, 
	0, 26, 0, 27, 0, 28, 0, 29, 
	0, 30, 0, 31, 0, 32, 31, 0, 
	5, 14, 205, 0, 34, 0, 35, 0, 
	36, 0, 37, 0, 38, 0, 39, 0, 
	40, 0, 41, 0, 42, 0, 43, 0, 
	44, 0, 45, 0, 32, 45, 0, 47, 
	0, 48, 0, 49, 0, 50, 0, 5, 
	14, 205, 0, 52, 0, 53, 0, 54, 
	0, 55, 0, 56, 0, 57, 62, 0, 
	58, 0, 59, 0, 60, 0, 61, 0, 
	5, 14, 205, 0, 63, 0, 64, 0, 
	65, 0, 66, 0, 67, 0, 68, 0, 
	5, 14, 205, 0, 70, 0, 71, 0, 
	72, 0, 73, 0, 74, 79, 0, 75, 
	0, 76, 0, 77, 0, 78, 0, 5, 
	14, 205, 0, 80, 0, 81, 0, 82, 
	0, 83, 0, 84, 0, 85, 0, 5, 
	14, 205, 0, 87, 0, 88, 0, 89, 
	0, 90, 108, 151, 0, 91, 0, 92, 
	0, 93, 0, 94, 0, 95, 0, 101, 
	105, 96, 0, 97, 98, 96, 0, 5, 
	14, 205, 0, 97, 99, 0, 100, 0, 
	97, 100, 0, 102, 0, 103, 0, 104, 
	0, 97, 0, 106, 0, 107, 0, 97, 
	0, 109, 0, 110, 0, 111, 0, 112, 
	0, 113, 131, 0, 114, 0, 115, 0, 
	116, 0, 117, 0, 118, 0, 124, 128, 
	119, 0, 120, 121, 119, 0, 5, 14, 
	205, 0, 120, 122, 0, 123, 0, 120, 
	123, 0, 125, 0, 126, 0, 127, 0, 
	120, 0, 129, 0, 130, 0, 120, 0, 
	132, 0, 133, 0, 134, 0, 135, 0, 
	136, 0, 137, 0, 138, 0, 144, 148, 
	139, 0, 140, 141, 139, 0, 5, 14, 
	205, 0, 140, 142, 0, 143, 0, 140, 
	143, 0, 145, 0, 146, 0, 147, 0, 
	140, 0, 149, 0, 150, 0, 140, 0, 
	152, 0, 153, 0, 154, 0, 155, 0, 
	156, 0, 157, 0, 158, 0, 164, 168, 
	159, 0, 160, 161, 159, 0, 5, 14, 
	205, 0, 160, 162, 0, 163, 0, 160, 
	163, 0, 165, 0, 166, 0, 167, 0, 
	160, 0, 169, 0, 170, 0, 160, 0, 
	172, 0, 173, 0, 174, 0, 175, 0, 
	176, 0, 177, 0, 178, 0, 179, 0, 
	180, 0, 5, 14, 205, 0, 182, 0, 
	183, 0, 184, 0, 5, 14, 205, 0, 
	5, 14, 205, 186, 186, 0, 5, 186, 
	14, 205, 186, 186, 186, 186, 0, 5, 
	14, 205, 185, 186, 186, 0, 188, 11, 
	10, 190, 195, 0, 192, 194, 191, 192, 
	194, 191, 5, 193, 205, 193, 193, 0, 
	5, 193, 205, 193, 193, 0, 194, 191, 
	0, 0, 0, 196, 197, 0, 12, 196, 
	199, 201, 198, 199, 201, 198, 200, 12, 
	200, 200, 0, 200, 12, 200, 200, 0, 
	201, 198, 5, 8, 8, 8, 202, 189, 
	205, 8, 202, 8, 202, 202, 202, 0, 
	1, 3, 4, 13, 187, 0, 1, 3, 
	4, 13, 187, 0, 204, 1, 3, 4, 
	13, 187, 0, 0
};

static const unsigned char _hext_trans_actions[] = {
	0, 0, 1, 75, 0, 75, 75, 75, 
	1, 0, 0, 77, 77, 77, 77, 116, 
	116, 1, 0, 0, 65, 65, 1, 61, 
	61, 1, 101, 98, 98, 98, 0, 63, 
	101, 98, 0, 98, 0, 0, 0, 1, 
	0, 1, 0, 1, 86, 49, 49, 51, 
	0, 0, 73, 73, 1, 110, 110, 110, 
	110, 130, 130, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 21, 1, 23, 0, 1, 
	0, 0, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 25, 1, 27, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 19, 
	19, 19, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	35, 35, 35, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	37, 37, 37, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 39, 
	39, 39, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 41, 
	41, 41, 1, 0, 1, 0, 1, 0, 
	1, 0, 0, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	0, 9, 1, 11, 11, 0, 1, 29, 
	29, 29, 1, 13, 13, 1, 15, 1, 
	17, 0, 1, 0, 1, 0, 1, 0, 
	1, 5, 1, 0, 1, 0, 1, 7, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 0, 
	9, 1, 11, 11, 0, 1, 31, 31, 
	31, 1, 13, 13, 1, 15, 1, 17, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	5, 1, 0, 1, 0, 1, 7, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 0, 
	9, 1, 11, 11, 0, 1, 43, 43, 
	43, 1, 13, 13, 1, 15, 1, 17, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	5, 1, 0, 1, 0, 1, 7, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 0, 
	9, 1, 11, 11, 0, 1, 33, 33, 
	33, 1, 13, 13, 1, 15, 1, 17, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	5, 1, 0, 1, 0, 1, 7, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 45, 45, 45, 1, 0, 1, 
	0, 1, 0, 1, 47, 47, 47, 1, 
	79, 79, 79, 119, 119, 1, 81, 0, 
	81, 81, 0, 0, 0, 0, 1, 113, 
	113, 113, 113, 134, 134, 1, 0, 0, 
	0, 0, 0, 1, 89, 53, 53, 55, 
	0, 0, 126, 57, 126, 57, 57, 1, 
	95, 0, 95, 0, 0, 1, 0, 0, 
	1, 1, 1, 69, 71, 1, 71, 0, 
	89, 53, 53, 55, 0, 0, 57, 92, 
	57, 57, 1, 0, 59, 0, 0, 1, 
	0, 0, 107, 104, 104, 104, 0, 67, 
	107, 104, 0, 104, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 1, 3, 3, 
	3, 3, 3, 1, 0, 0, 0, 0, 
	0, 0, 1, 0
};

static const unsigned char _hext_eof_actions[] = {
	0, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 122, 122, 122, 122, 122, 
	122, 122, 122, 83, 83, 83
};

static const int hext_start = 203;
static const int hext_first_final = 203;
static const int hext_error = 0;

static const int hext_en_main = 203;


#line 61 "Parser.h.rl"

} // namespace ragel


/// Parser is responsible for parsing hext and producing Rules.
class Parser
{
public:
  /// Construct a Parser to parse hext rule definitions described in range
  /// `begin` to `end`. Pointers must stay valid until the last call to
  /// `Parser::parse()`.
  Parser(const char * begin, const char * end);

  /// Parse hext and produce a Rule.
  /// Throw `ParseError` on invalid input.
  std::unique_ptr<Rule> parse(Option flags = DefaultOption);

private:
  /// Throw `ParseError` with an error message marking an unexpected character.
  void throw_unexpected() const;

  /// Throw `ParseError` with an error message marking an unknown token.
  void throw_unknown_token(
    const std::string& tok,
    const std::string& tok_name
  ) const;

  /// Throw `ParseError` with an error message marking an invalid regular
  /// expression.
  void throw_regex_error(
    std::string::size_type mark_len,
    boost::regex_constants::error_type e_code
  ) const;

  /// Throw `ParseError` with error message `error_msg`. Mark the error location
  /// in hext with `mark_len` amount of characters up to the currently
  /// processed character.
  void throw_error(
    const std::string& error_msg,
    std::string::size_type mark_len
  ) const;

  /// Print an error at the current location within hext. Print hext with line
  /// numbers up to the currently examined character. `mark_len` denotes the
  /// amount of '^' characters that are used to mark the error location up to
  /// the current character.
  void print_error_location(
    std::string::size_type mark_len,
    std::ostream& out
  ) const;

  /// The beginning of the hext input.
  const char * p_begin_;

  /// The current character that ragel is processing within the hext input.
  const char * p;

  /// The end of the hext input.
  const char * pe;

  /// The end of the hext input. Same as `Parser::pe`.
  const char * eof;

  /// Ragel's current state.
  int cs;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

