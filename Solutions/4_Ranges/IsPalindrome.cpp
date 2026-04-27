/**************************************************************************************************
*
* \file IsPalindrome.cpp
* \brief C++ Training - Algorithm and Concepts Programming Example
*
* Copyright (C) 2015-2026 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the 'is_palindrome()' algorithm in the following example. The algorithm should
*         detect if the given range is the same when traversed forward and backward. The algorithm
*         should return 'true' only for true palindromes, and 'false' for empty ranges and
*         non-palindromes.
*
* Step 2: Restrict the algorithm to bidirectional iterators by means of C++20 concepts.
*
**************************************************************************************************/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <ranges>
#include <vector>


// The 'bidirectional_iteator' concept
/*
template< typename I >
using iterator_category_t =
   typename std::iterator_traits<I>::iterator_category;

template<class I>
concept bidirectional_iterator =
   std::forward_iterator<I> &&
   std::derived_from<iterator_category_t<I>, std::bidirectional_iterator_tag> &&
   requires( I i ) {
      { --i } -> std::same_as<I&>;
      { i-- } -> std::same_as<I>;
   };
*/


template< std::bidirectional_iterator BidirIt >
constexpr bool is_palindrome( BidirIt first, BidirIt last )
{
   // Manual solution ("the unsafe mode")
   /*
   if( first == last )
      return false;

   --last;

   while( first != last ) {
      if( *first != *last ) return false;
      ++first;
      if( first == last ) return true;
      --last;
   }

   return true;
   */

   // "Modern" algorithm-based solution (shorter, simpler, safer, but slower)
   return std::equal( first, last, std::make_reverse_iterator(last) );
}


int main()
{
   std::vector<int> v1{ 3, 2, 11, 5, 4, 4, 5, 11, 2, 3 };   // Palindrome with even number of elements
   std::list<int> v2{ 3, 2, 11, 5, 4, 5, 11, 2, 3 };        // Palindrome with odd number of elements
   std::deque<int> v3{ 3, 2, 11, 5, 4, 99, 5, 11, 2, 3 };   // Not a palindrome

   std::string s1{ "" };             // An empty string is a palindrome
   std::string s2{ "dad" };          // One of the shortest palindromes in the English language
   std::string s3{ "detartrated" };  // Longest palindrome in the English language
   std::string s4{ "random" };       // Not a palindrome

   assert(  is_palindrome( begin(v1), end(v1) ) );
   assert(  is_palindrome( begin(v2), end(v2) ) );
   assert( !is_palindrome( begin(v3), end(v3) ) );
   assert(  is_palindrome( begin(s1), end(s1) ) );
   assert(  is_palindrome( begin(s2), end(s2) ) );
   assert(  is_palindrome( begin(s3), end(s3) ) );
   assert( !is_palindrome( begin(s4), end(s4) ) );

   return EXIT_SUCCESS;
}
