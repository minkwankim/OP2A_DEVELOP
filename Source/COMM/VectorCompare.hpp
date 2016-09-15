/*
 * Open-source multi-Physics Phenomena Analyzer (OP2A) ver. 1.0
 * 
 *         Copyright (c) 2014-2016 MINKWAN KIM
 *
 * VectorCompare.hpp
 *
 *  Created on: 21 Apr 2016
 *      Author: a1633125
 *
 *	@brief Brief description of the file
 */

#ifndef COMM_VECTORCOMPARE_HPP_
#define COMM_VECTORCOMPARE_HPP_


#include <vector>

#include "common.hpp"
#include "noninstantiable.hpp"



namespace Common {

class VectorCompare: public NonInstantiable<VectorCompare> {

public:

	/*
	 * Check whether the given INT vector has same component
	 */
	static bool hasSameComponentINT(const std::vector<int>& data);
	static bool hasSameComponentINT(const std::vector<int>& data, int m);

	/*
	 * Check the range of vector
	 */
	static bool hasSatisfyRangeINT(const std::vector<int>& data, int low, int top);
	static bool hasSatisfyRangeINT(const std::vector<int>& data, int m, int low, int top);



};




} /* namespace Common */

#endif /* COMM_VECTORCOMPARE_HPP_ */
