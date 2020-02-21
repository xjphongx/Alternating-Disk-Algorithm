///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the 
// alternating disks problem.
//
// As provided, this header has four functions marked with 
// TODO comments.
// You need to write in your own implementation of these 
// functions.
///////////////////////////////////////////////////////////////////////////////

#pragma once

//testing git pushing again


#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

using namespace std;//so i dont have to use std::

// State of one disk, either light or dark.
enum disk_color { DISK_LIGHT, DISK_DARK };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:

  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

      assert(dark_count() > 0);

      for (size_t i = 1; i < _colors.size(); i += 2) {
        _colors[i] = DISK_DARK;
      }
  }

  // Equality operator for unit tests.
  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t dark_count() const {
    return total_count() / 2;
  }

  size_t light_count() const {
    return dark_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_alternating() const {
 
  for(int i = 0; i < _colors.size();i++)
  {
     //if first spot is light, else it starts with dark
     if(_colors[0]== DISK_LIGHT)
     {
         if(i%2 == 0)
         {
             if(_colors[i]==DISK_DARK)
             return false;
         }else
         {
             if(_colors[i]==DISK_LIGHT)
             return false;
         }
        
     }
     else//this else statements considers the case if black goes first
     {
         if(i%2 == 0)
         {
             if(_colors[i]==DISK_LIGHT)
             return false;
         }else
         {
             if(_colors[i]==DISK_DARK)
             return false;
         }
     }
 }
   return true;//assume that it is alternating unless proven otherwise
 }
 
 
  // Return true when this disk_state is fully sorted, with all light disks
  // on the left (low indices) and all dark disks on the right (high
  // indices).
  bool is_sorted() const {

    cout << endl;
    for(int a = 0; a < total_count();a++)
    {
      cout << _colors[a]<< " ";


    }
    

    //bool isWhite = true;//assume the first half is all white
    //check if there are any darks in the first half
    for (int j = 0; j < total_count();j++)
    {  
        if(j < total_count()/2)//first half must be white
        {
            if(_colors[j] == DISK_DARK)
            return false;
        }else//this is for last half must be dark
        {
            if(_colors[j] == DISK_LIGHT)
            return false;
        }
    }
    return true;//if everything is already sorted 

    
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the left-to-right algorithm.
sorted_disks sort_left_to_right(const disk_state& before) {

//Included this because before is a constant parameter 
disk_state temp = before;//doing this allows me to make changes to the temp
int swapCount = 0; //keeps track of the amount of swaps

for(int i =0; i < temp.total_count();i++)
{
    for(int j = 0; j < temp.total_count()-1;j++)//have to add -1 because of bound error
    {
      if(temp.get(j) > temp.get(j+1))//if the current disk is dark and the next is light, swap
      {
          temp.swap(j); // this takes the current index and swaps with the next
          swapCount++;
      }
    }
}
  return sorted_disks(disk_state(temp), swapCount);//return temp and it becomes the new sorted vector
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
 
disk_state temp = before;
int swapCount = 0;

for (int i = 0; i < temp.total_count()/2;i++)//divide 2 if possible
{
    //forloop to go forward
    for(int j = 0; j < temp.total_count()-1; j++)
    {
        if(temp.get(j) > temp.get(j+1))
        {
          temp.swap(j);//swaps with respect to the left 
          swapCount++;
        }

    }
    //forloop to go backward
    for(int k = temp.total_count()-1; k > 0; k--)
    {
        if(temp.get(k-1) > temp.get(k))//make the swap if (left) is greater than (right)
        {
          temp.swap(k-1);
          swapCount++;
        }
    }

}

  return sorted_disks(disk_state(temp), swapCount);
}
