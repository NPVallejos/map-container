#include <iostream>
#include "Map.hpp"
#include <vector>

int main() {
	// Testing intialization list + insertion
	cs540::Map<char, int> map {{'i', 1}, {'e', 5}, {'q', 90}, {'Q', 99}, {'f', 150}, {'o', 300}};
	map.insert({'E', 1});
	map.insert({'a', 2});
	map.insert({'L', 5});
	map.insert({'j', 7});
	map.insert({'W', 1});
	
	// Handle self assignment
	map = map;
	assert (map == map);
	assert (!(map < map));
	
	auto end_it = map.end();
	{
		// Testing find
		auto it = map.find('E');
		assert (it != end_it);
		it = map.find('j');
		assert (it != end_it);
		it = map.find('a');
		assert (it != end_it);
		it = map.find('L');
		assert (it != end_it);
		it = map.find('w');
		assert (it == end_it);
		it = map.find('f');
		assert (it != end_it);
		it = map.find('i');
		assert (it != end_it);
		it = map.find('e');
		assert (it != end_it);
		it = map.find('o');
		assert (it != end_it);
		it = map.find('q');
		assert (it != end_it);
		it = map.find('Q');
		assert (it != end_it);
   }
   
   {
   	// ***** To test that default constructor is not allowed for each iterator class, uncomment the below comments ONE AT A TIME *****
   	//cs540::Map<char, int>::Iterator it0; // Test Iterator() does not work
   	//cs540::Map<char, int>::ConstIterator it0; // Test ConstIterator() does not work
   	//cs540::Map<char, int>::ReverseIterator it0; // Test ReverseIterator() does not work
   
		// iterator operator== test
		auto it1 = map.find('z');
		auto it2 = map.find('g');
		assert (it1 == it2);
	
		// iterator copy constructor test
		auto it4(it2); 
		assert (it4 == it2);
	
		// Test out operator* and operator-> for iterator
		auto it0 = map.begin();
		assert (it0->first == 'E');
		assert (it0->second == 1);
		assert ((*it0).first == 'E');
		assert ((*it0).second == 1);
		
		// Test changing mapped value with operator* and operator->
		(*it0).second = 200;
		assert (it0->second == 200);
		it0->second++;
		assert (it0->second == 201);
		
		/* ***** Test that you cannot change key values, uncomment the below comments ONE AT A TIME ***** */
		// (*it0).first = 'A';
		// it0->first = 'A';
	
		// iterator operator= overload test
		cs540::Map<char, int>::Iterator it5 (map.begin());
		it5 = it4; 
		assert (it5 == it2);
		assert (it5 == it4);
	
		// iterator post-increment vs pre-increment
		assert ((it1++) != (++it2));
		assert (it1 == it2);
		assert ((++it1) == (++it2));
		
		// iterator post-decrement vs pre-decrement
		assert ((it1--) == (it2--));
		assert (it1 == it2);
		assert (--it1 == --it2);
		assert (it1 == it2);
	}
	
	{
		// test erase(iterator)
		auto it3 = map.find('E');
		map.erase(it3);
		it3 = map.find('E');
		assert (it3 == map.end()); // test that map.end() works
		
		// test erase throwing out of range exception
		it3 = map.find('z');
		try {
			map.erase(it3);
		} catch (std::out_of_range) {
			map.insert({'z', 1});
		}
		assert (map.find('z') != map.end());
		
		// test at() throwing out of range exception
		try {
			map.at('9');
		} catch (std::out_of_range) {
			map.insert({'9', 9});
		}
		assert (map.find('9') != map.end());
		map.at('9'); // should not throw out of range exception now
	
		// test erase(key);
		map.erase('j');
		it3 = map.find('j');
		assert (it3 == end_it);
	
		map.erase('a'); 
		it3 = map.find('a');
		assert (it3 == end_it);

		map.erase('L');
		it3 = map.find('L');
		assert (it3 == end_it);
	
		map.erase('W');
		it3 = map.find('W');
		assert (it3 == end_it);
	
		// Test map copy constructor
		auto m_copy = map;
		map.insert({'E', 1});
		assert (map != m_copy);
	
		// Test Map operator=() 
		cs540::Map<char, int> map2;
		map2.insert({'P', 20});
		map.insert({'a', 2});
		map.insert({'L', 5});
		map.insert({'j', 7});
		map.insert({'W', 1});
		map2 = map;
		assert (map2 == map);
		
		// Test self assignment
		map2 = map2;
		assert (map2 == map);
	
		// Test map independence
		map.erase('W');
		assert (map2 != map);
	
		// Test operator<
		assert (map2 < map); 
	
		// Clear all maps
		m_copy = map;
		assert (m_copy != map2);
		m_copy.clear(); 
		map2.clear();
		assert (m_copy == map2);
	}
	
	{
		// Test from test1-kec.cpp
		cs540::Map <int, int> map3;
		auto it = map3.begin();
		auto it2 = map3.end();
		assert (it == it2);
		
		//Empty container, should print nothing.
      for (auto it = map3.begin(); it != map3.end(); ++it) {
           abort();
      }
	}
	
	{
		// Test from test.cpp
		cs540::Map<std::string, int> words_count;
		
		// just a big list of words
    	auto words = {"this", "is", "a", "string", "with", "words", "some",
        "words", "in", "the", "string", "repeat", "the", "more", "they",
        "repeat", "the", "more", "they", "should", "count", "they", "more",
        "they", "count", "the", "more", "they", "will", "have", "their",
        "count", "increased"};

      for (auto& word : words) {
        // this works because int can be default constructed, and the 
        // default of int (by doing int{} ) is 0.
        words_count[word] += 1; // add 1 to the count
    	}
	}
	
	{
		/* Testing template: insert (IT_T range_beg, IT_T range_end) */
		cs540::Map<char, int> range_map;
		range_map.insert (map.begin(), map.end()); // ERROR: Something weird is happening here
		
		auto it = range_map.begin();
		auto it2 = map.begin();
		while (it != range_map.end()) {
			assert (it.curr_node->value->first == it2.curr_node->value->first);
			assert (it.curr_node->value->second == it2.curr_node->value->second);
			++it;
			++it2;
		}
		
		// Testing operator< between two maps
		assert (range_map == map); // ERROR invalid read of size 1 here
	}
	
	{
		/* TEST COMPARING OTHER TYPES OF MAPS:
			- copy constructed maps
			- opeartor= maps
			- regular maps
			- initialize_list maps
		*/ 
		cs540::Map<int, int> m1{{20, 0}, {21, 1}, {22, 2}};
		
		cs540::Map<int, int> m2(m1);
		m2.insert({23,3});
		
		cs540::Map<int, int> m3;
		m3 = m2;
		
		cs540::Map<int, int> m4;
		m4.insert({5, 0});
		
		assert (m1 < m2);
		assert (m1 < m3);
		assert (m4 < m1);
		assert (m4 < m2);
		assert (m4 < m3);
	}
	
	printf ("**************************************************************************\n**************************************************************************\n\nTo test that default constructors are not allowed for each iterator class:\n\tGo to line 45 in main.cpp and follow the instructions\n\nTo test that you cannot change key values with operator* and operator-> for iterator class:\n\tGo to line 72 in main.cpp and follow the instructions\n\n**************************************************************************\n**************************************************************************\n"); 
}
