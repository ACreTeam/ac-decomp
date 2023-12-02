#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "types.h"

namespace std {

template <class InputIterator, class Predicate>
inline
InputIterator
find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last && !pred(*first))
		++first;
	return first;
}

} // namespace std

#endif
