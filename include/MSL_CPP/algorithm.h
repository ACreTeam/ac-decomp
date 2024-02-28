#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "types.h"

#ifdef __cplusplus
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
#endif
