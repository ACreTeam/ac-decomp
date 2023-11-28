#ifndef ITERATOR_H
#define ITERATOR_H

#include "types.h"

namespace std {

struct input_iterator_tag {};

template<class Iterator>
struct iterator_traits {
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class InputIterator>
inline
typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	typename iterator_traits<InputIterator>::difference_type result = 0;
	for (; first != last; ++first)
		++result;
	return result;
}

template <class InputIterator>
inline
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	return __distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
}

} // namespace std

#endif
