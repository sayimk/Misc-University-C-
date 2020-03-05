/*
 * Path.h
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <iosfwd>

/*
 * This assignment practices the usage of STL.
 * The class is a data structure that contains the points of a path
 * in 2D space.
 * The path always starts at the initial point (0,0) and then
 * can be extended by moving in one of 8 directions (see enum
 * Direction).
 *
 * There are various other options to do with the path the most
 * complicated of which is redirecting it to a stream.
 *
 * Comments near the different functions give further details about
 * the different members.
 */
class Path {
public:
	enum Direction { N, S, E, W, NE, NW, SE, SW };

	// Default constructor. A path that starts at (0,0)
	Path();

	// Copy and move constructors and assignment operators
	Path(const Path&);
	Path(Path&&);
	Path& operator=(const Path&);
	Path& operator=(Path&&);

	// A constructor from a list of directions
	// If a direction not of the above 8 appears in the list
	// you should throw an std::exception
	Path(std::vector<Direction> path);

	// Clean up
	~Path();

	// Show the current position of the path
	std::pair<int,int> current() const;

	// Extend the path by going in the
	// given direction.
	// Going in direction N increases the y coordinate
	// Going in direction E increases the x coordinate
	//
	// If the direction is not one of the 8 possible
	// directions this should throw and std::exception
	void move(const Direction& d);

	// The coordinates of the rectangle enclosing
	// the path
	int minX() const;
	int maxX() const;
	int minY() const;
	int maxY() const;

	// Check whether the point (x,y) was visited
	// by the path.
	// If it was visited return a location on the path
	// where this point was visited.
	// If it was not visited throw and std::exception
	unsigned int visited(int x,int y) const;

	// Compare two paths:
	// A path is smaller than another if the
	// second is an extension of the first
	// Two paths are equal if they are exactly the same
	bool operator<(const Path&) const;
	bool operator<=(const Path&) const;
	bool operator==(const Path&) const;
	bool operator>(const Path&) const;
	bool operator>=(const Path&) const;
	bool operator!=(const Path&) const;

	// Extend the first path by the second path.
	// So the (0,0) point of the second path is
	// put on the end point of the first path
	// and the same steps as in the second are retraced.
	//
	// For example, if the path through which this is called is:
	// (0,0), (0,1)
	// and the other path is:
	// (0,0), (1,1)
	// Then their sum should be:
	// (0,0), (0,1), (1,2)
	Path operator+(const Path&) const;

	// The - operation basically walks the other path
	// backwards along the original path.
	// So if the end of the first path does not end in
	// a matching way the operation should fail and send
	// std::exception.
	// Otherwise, walk back the other path from the end of
	// the first path.
	// If the first path gets empty (goes back to the origin)
	// then continue going backward.
	//
	// For example:
	// c=a+a  - + always works
	// d=c-a  - now c ends in the same directions as a
	// e=d-c  - now the suffix of c matches that of d and can
	//          be reduce. IT consists of the walking the reverse of
	//          a from the origin
	// f=0-a  - f should be equivalent to e
	//
	// Or starting from:
	// (0,0),(0,1),(0,2),(1,2),(1,1),(0,1)  - N,N,E,S,W
	// and subtracting:
	// (0,0),(1,0),(1,-1),(0,-1) - E,S,W
	// should get:
	// (0,0),(0,1),(0,2)
	// Now substracting:
	// (0,0),(1,0),(1,1),(1,2) - E,N,N
	// should get:
	// (0,0),(-1,0)
	// Which is equivalent to just going west on a fresh path
	Path operator-(const Path&) const;

	// The length of the path in points
	int length() const;
	// How many points are touched by the path
	// This is different from length because if a path visits
	// the same point multiple times in terms of space all the
	// visits are counted as 1.
	int space() const;

	// Output the path as follows.
	// Each point in the path is represented by a 3x3 textual area
	// where the point itself is in the center.
	// The path should be printed as we are used to seeing
	// the grid: 0,0 is below 0,1
	//           0,0 is to the left of 1,0
	//           -1,0 is to the left of 0,0
	//           0,-1 is below 0,0
	// and so on.
	//
	// The first point in the path should be marked by the letter s
	// The last point in the path should be marked by the letter e
	// every other point in the path should be marked by the letter o
	//
	// The path itself is marked by using the space around the point
	// by marking how the path went from point to point.
	// So for example a section where the path went E should
	// be represented by (where * marks the limit of the area that
	// I'm talking about (but should not be printed)
	// and ? mark things that need more
	// information about the parts before/after this E):
	// ********
	// *??????*
	// *?o--o?*
	// *??????*
	// ********
	// The path:
	// N,N,NE,E,E,SE,S,S,SW,W,NW,N
	// (0,0),(0,1),(0,2),(1,3),(2,3),(3,3),(4,2),(4,1),(4,0),
	// (3,-1),(2,-1),(1,0),(1,1)
	// Should be output like the area enclosed by the *:
	// *****************
	// *    o--o--o    *
	// *   /       \   *
	// *  /         \  *
	// * o           o *
	// * |           | *
	// * |           | *
	// * o  e        o *
	// * |  |        | *
	// * |  |        | *
	// * s  o        o *
	// *     \      /  *
	// *      \    /   *
	// *       o--o    *
	// *               *
	// *****************
	//
	// If you are revisiting the initial point it should
	// be overwritten (with either o or e depending if it's
	// the end of the pat).
	// The end of the path should always be marked
	friend std::ostream& operator<<(std::ostream&, const Path&);

public:
	// Bad habit to put anything public.
	// I'm doing it to hide my implementation.
	void* pms_[5];
private:
	static Direction difference_(std::pair<int,int>,std::pair<int,int>);
	void n_();
	void s_();
	void e_();
	void w_();
	void ne_();
	void nw_();
	void se_();
	void sw_();
};

#endif
/*
 * Path.h
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
