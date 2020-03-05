/*
 * Priority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include <iosfwd>
#include<map>

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
 * The easiest way to implement this (in my opinion) is to wrap
 * the functionality of std::multimap in a very light way.
 *
 * One sticky point that you have to notice is what happens when
 * there are multiple items with the same priority (hence the
 * multimap).
 */
template <class T>
class Priority {
public:

	enum Key { ONE, TWO };

	// Default constructor.
	// Initialize an empty priority queue
	Priority();

	// Copy and move constructors and assignment operators
	Priority(const Priority&);
	Priority(Priority&&);
	Priority& operator=(const Priority&);
	Priority& operator=(Priority&&);

	// Clean up
	~Priority();

	// Add an item to the queue
	// The first int is priority 1 and the second is priority 2
	// The pointer should be added to the queue
	// The memory behind the pointer is not your responsibility!
	void push_back(T *,int, int);

	// Pop an item from the queue.
	// If the key is ONE then the item with minimal
	// priority according to the first priority should be popped.
	// If the key is TWO then the item with minimal
	// priority according to the second priority should be popped.
	//
	// If the queue is empty return the nullptr
	T* pop_front(Key);

	// Iterate over the elements in the queue according to either
	// the first priority or the second priority
	class iterator {
	public:
		// This is required to allow Priority to access
		// the private members of the iterator
		friend class Priority;
		// Create an uninitialized iterator
		iterator();

		// Copy constructor and assignment operator
		iterator(const iterator&);
		iterator& operator=(const iterator&);

		// Access operators
		T& operator*();
		T* operator->();

		// Increment the iterator
		// pre-increment
		iterator& operator++();
		// post-increment
		iterator operator++(int);

		// Check if two iterators are the same or not
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	private:
		typename std::multimap<std::pair<int,int>,T>::iterator it_;
	};

	// Return an iterator that is going to work according
	// to first priority or second priority based on the key
	iterator begin(Key k);
	// Return an end marker for the iterator that works
	// according to the first priority or the second
	iterator end(Key k);

private:
	std::multimap<std::pair<int,int>,T> queue;
	std::multimap<std::pair<int,int>,T> orderedKeys;

};

template<class T>
Priority<T>::Priority(){}

template<class T>
Priority<T>::Priority(const Priority& other)
{
	queue = other.queue;
}

template<class T>
Priority<T>::Priority(Priority&& other)
{
	queue = other.queue;
}

template<class T>
Priority<T>& Priority<T>::operator=(const Priority<T>& other)
{
	queue = other.queue;
	return this;
}

template<class T>
Priority<T>& Priority<T>::operator=(Priority<T>&&other)
{
	queue = other.queue;
	return this;
}

template<class T>
Priority<T>::~Priority()
{
}

template<class T>
void Priority<T>::push_back(T *val,int key1, int key2)
{
	queue.insert(std::make_pair(std::make_pair(key1, key2),*val));
}

template<class T>
T* Priority<T>::pop_front(Key k)
{
	iterator output;
	iterator current;
	current.it_ = queue.begin();
	output.it_ = queue.begin();


	if (queue.empty())
		return nullptr;

	for (int i=0; i<queue.size(); i++){

		if(k == ONE){

			if((current.it_->first.first) < (output.it_->first.first)){
				current.it_ = output.it_;
			}

		}

		if(k == TWO){

			if((current.it_->first.second) < (output.it_->first.second)){
				current.it_ = output.it_;
			}

		}
		++current.it_;
	}


	T* outputVal = &output.it_->second;
	queue.erase(output.it_);
	return outputVal;
}

template<class T>
Priority<T>::iterator::iterator()
{
}

template<class T>
Priority<T>::iterator::iterator(const Priority<T>::iterator& other)
{
	it_ = other.it_;

}

template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator=(const Priority<T>::iterator& other)
{
	it_ = other.it_;
	return *this;
}

template<class T>
T& Priority<T>::iterator::operator*()
{
	return (it_->second);
}

template<class T>
T* Priority<T>::iterator::operator->()
{
	return &(it_->second);
}



template<class T>
typename Priority<T>::iterator& Priority<T>::iterator::operator++()
{
	++it_;
	return *this;
}



template<class T>
typename Priority<T>::iterator Priority<T>::iterator::operator++(int)
{
	iterator output = *this;

	++it_;

	return output;
}



template<class T>
bool Priority<T>::iterator::operator==(const Priority<T>::iterator& other) const
{
	if (other.it_==it_)
		return true;
	else
		return false;
}



template<class T>
bool Priority<T>::iterator::operator!=(const Priority<T>::iterator& other) const
{
	if (other.it_==it_)
		return false;
	else
		return true;
}



template<class T>
typename Priority<T>::iterator Priority<T>::begin(Key k)
{
	iterator search;
	iterator output;
	int highest = 0;
	//int lowest = queue //0;
	int current;
	search.it_=queue.begin();
	output.it_=queue.begin();

	orderedKeys.clear();

	//Yes, i know there is a more efficient way of sort queue for the internal sorted list,
	//but this works and because of time constraints, i will stay with this

	if(k == ONE){

		int lowest = queue.begin()->first.first;

		for (int i =0; i<queue.size(); i++){
			int current = search.it_->first.first;

			if(current < lowest){
				lowest = current;
			}

			if(current > highest){
			highest = current;
				}

			++search.it_;
		}

		//sort orderedKeys
			current = lowest;

			while(current <= highest){

				search.it_=queue.begin();

				for(int i = 0; i <queue.size(); i++){


					if(search.it_->first.first==current){
						orderedKeys.insert(std::make_pair(search.it_->first, search.it_->second));

					}
					++search.it_;

				}
				current = current+1;
			}

	}



	if(k == TWO){
		int lowest = queue.begin()->first.second;


		for (int i =0; i<queue.size(); i++){
					int current = search.it_->first.second;

					if(current < lowest){
						lowest = current;
					}

					if(current > highest){
						highest = current;

					}

					++search.it_;
				}


				//sort orderedKeys
					current = lowest;

					while(current <= highest){

						search.it_=queue.begin();

						for(int i = 0; i <queue.size(); i++){


							if(search.it_->first.second==current){
								orderedKeys.insert(std::make_pair(std::make_pair(search.it_->first.second, search.it_->first.first), search.it_->second));
							}
							++search.it_;

						}
						current = current+1;
					}
	}


	//reuse these for incrementing
	output.it_ = orderedKeys.begin();
	return output;
}



template<class T>
typename Priority<T>::iterator Priority<T>::end(Key k)
{
	iterator searchl;
	iterator output;
	iterator endit;
	searchl.it_=queue.begin();
	output.it_=queue.begin();
	/*
	if(k == ONE){
		for (int i =0; i<queue.size(); i++){
			int current = searchl.it_->first.first;
			int largest  = output.it_->first.first;

			if(current > largest){
				output = searchl;
			}
			++searchl.it_;
		}
	}


	if(k == TWO){
		for (int i =0; i<queue.size(); i++){
			int current = searchl.it_->first.second;
			int largest  = output.it_->first.second;

			if(current > largest){
				output = searchl;
			}
			++searchl.it_;
		}
	}

	//++output.it_;
	//output.end_=output.it_;
*/
	output.it_ = orderedKeys.end();
	//++output.it_;
	return output;
}

#endif
/*
 * Priority.h
 *
 *  Created on: Nov 28, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
