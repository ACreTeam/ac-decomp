#ifndef ITERATOR_H
#define ITERATOR_H

#include "types.h"

#ifdef __cplusplus
namespace std {

/* TODO: these should be properly implemented */

struct input_iterator_tag {};

template <class InputIterator>
inline
s32
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	s32 result = 0;
	for (; first != last; ++first)
		++result;
	return result;
}

template <class InputIterator>
inline
s32
distance(InputIterator first, InputIterator last) {
    input_iterator_tag tag;
	return __distance(first, last, tag);
}

} // namespace std
#endif

#endif
