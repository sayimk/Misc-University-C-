/*
 * ModelPriority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef MODELPRIORITY_H_
#define MODELPRIORITY_H_

#include <map>
#include <iosfwd>

/*
 * This assignment practices the usage of STL.
 * The class is a simple version of priority queue.
 *
 * It's a container that accepts pointers to some type.
 * You are NOT in charge of the memory deallocation for these pointers.
 * With every pointers you get two priorities (integers).
 *
 * Then, one can request to get the most important item according
 * to priority 1 or according to priority 2.
 * Once an item has been asked for it is removed from the data.
 *
 */
class intCont;

class ModelPriority {
public:

	enum Key { ONE, TWO };

	// Default constructor.
	// Initialize an empty priority queue
	ModelPriority();

	// Copy and move constructors and assignment operators
	ModelPriority(const ModelPriority&);
	ModelPriority(ModelPriority&&);
	ModelPriority& operator=(const ModelPriority&);
	ModelPriority& operator=(ModelPriority&&);

	// Clean up
	~ModelPriority();

	// Add an item to the queue
	// The first int is priority 1 and the second is priority 2
	// The pointer should be added to the queue
	// The memory behind the pointer is not your responsibility!
	void push_back(intCont* ,int, int);

	// Pop an item from the queue.
	// If the key is ONE then the item with minimal
	// priority according to the first priority should be popped.
	// If the key is TWO then the item with minimal
	// priority according to the second priority should be popped.
	//
	// If the queue is empty return the nullptr
	intCont* pop_front(Key);

	// Iterate over the elements in the queue according to either
	// the first priority or the second priority
	class iterator {
	public:
		friend class ModelPriority;
		// Create an uninitialized iterator
		iterator();

		// Copy constructor and assignment operator
		iterator(const iterator&);
		iterator& operator=(const iterator&);

		// Access operators
		intCont& operator*();
		intCont* operator->();

		// Increment the iterator
		// pre-increment
		iterator operator++();
		// post-increment
		iterator operator++(int);

		// Check if two iterators are the same or not
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	private:
		typename std::multimap<int,std::pair<intCont*,int>>::iterator it_;
	};

	// Return an iterator that is going to work according
	// to first priority or second priority based on the key
	iterator begin(Key k);
	// Return an end marker for the iterator that works
	// according to the first priority or the second
	iterator end(Key k);

private:
	std::multimap<int,std::pair<intCont*,int>> map1_;
	std::multimap<int,std::pair<intCont*,int>> map2_;
};


#endif
/*
 * ModelPriority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
