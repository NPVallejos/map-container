#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <stdlib.h>	// for srand and rand
#include <time.h>		// for time
#include <stdio.h>	// //printf
#include <initializer_list>
#include <stdexcept>	// for throw std::out_of_range
#include <assert.h>
#include <iostream>


namespace cs540 {

template <typename Key_T, typename Mapped_T>
struct Node {
	Node * next;
	Node * prev;
	std::pair <const Key_T, Mapped_T> * value;
	std::vector <Node <Key_T, Mapped_T> *> links;
	
	Node () : next(nullptr), prev(nullptr), value(nullptr) {}
	
	Node (Node <Key_T, Mapped_T> &n_node, 
		  	Node <Key_T, Mapped_T> &p_node) { 
		next = &n_node; 
		prev = &p_node; 
		value = nullptr;
	}
	
	Node (Node <Key_T, Mapped_T> &n_node, 
		  	Node <Key_T, Mapped_T> &p_node, 
		  	const std::pair <Key_T, Mapped_T> &data) { 
		next = &n_node; 
		prev = &p_node; 
		next->prev = this;
		value = new std::pair <const Key_T, Mapped_T>(data);
		 
	}  
	
	~Node () {
		while (links.size() > 0) {
			delete links.at(0);
			links.erase (links.begin());
		}
		delete value;
	}
	
	Node &operator= (const Node <Key_T, Mapped_T> *other) {
		this->value = new std::pair <const Key_T, Mapped_T> (other->value);
		return *this;
	}
	
	void initializeHead (unsigned int height) {
			this->next = this;
			this->prev = this;
			for (unsigned int i = 0; i < height; ++i) {
				this->links.insert (this->links.begin() + i, new Node <Key_T, Mapped_T>(*this, *this));
			}
	}
};

template <typename Key_T, typename Mapped_T>
class Map;

template <typename Key_T, typename Mapped_T>
class Map {
	public:
		struct BaseIterator;
		struct Iterator;
		struct ConstIterator;
		struct ReverseIterator;
	private:
		Node <Key_T, Mapped_T> * head;
		unsigned int curr_max_height;
		int map_size;
	public:
		struct BaseIterator {
			Node <Key_T, Mapped_T> * curr_node;
			
			private:
				friend class Map;
				BaseIterator() {}
		};
		
		struct Iterator : BaseIterator {
			Iterator &operator= (const Iterator &other) {
				this->curr_node = other.curr_node;
				return *this;
			}
		
			Iterator &operator++ () {
				this->curr_node = this->curr_node->next;
				return *this;
			}		
		
			Iterator operator++ (int) {
				Iterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->next;
				return ret;
			}
			
			Iterator &operator--() {
				this->curr_node = this->curr_node->prev;
				return *this;
			}
			
			Iterator operator--(int) {
				Iterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->prev;
				return ret;
			}
		
			std::pair <const Key_T, Mapped_T> &operator*() const {
				return (*this->curr_node->value);
			}
			std::pair <const Key_T, Mapped_T> *operator->() const {
				return this->curr_node->value;
			}
			
			/* Make these free standing functions*/
			bool operator== (const Iterator &other) {
				return (this->curr_node == other.curr_node);
			}
			
			bool operator== (const ConstIterator &other) {
				return (this->curr_node == other.curr_node);
			}
			
			bool operator!= (const Iterator &other) {
				return (this->curr_node != other.curr_node);
			}
			
			bool operator!= (const ConstIterator &other) {
				return (this->curr_node != other.curr_node);
			}
			
			private:
				friend class Map;
				Iterator() {}
		};
		
		struct ConstIterator : BaseIterator {
			ConstIterator &operator= (const ConstIterator &other) {
				this->curr_node = other.curr_node;
				return *this;
			}
		
			ConstIterator &operator++ () {
				this->curr_node = this->curr_node->next;
				return *this;
			}		
		
			ConstIterator operator++ (int) {
				ConstIterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->next;
				return ret;
			}
			
			ConstIterator &operator--() {
				this->curr_node = this->curr_node->prev;
				return *this;
			}
			
			ConstIterator operator--(int) {
				ConstIterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->prev;
				return ret;
			}		
		
			const std::pair <const Key_T, Mapped_T> &operator*() const {
				return *this->curr_node->value;
			}
			const std::pair <const Key_T, Mapped_T> *operator->() const {
				return this->curr_node->value;
			}
			
			/* Make these free standing functions*/
			bool operator== (const Iterator &other) {
				return (this->curr_node == other.curr_node);
			}
			
			bool operator== (const ConstIterator &other) {
				return (this->curr_node == other.curr_node);
			}
			
			bool operator!= (const Iterator &other) {
				return (this->curr_node != other.curr_node);
			}
			
			bool operator!= (const ConstIterator &other) {
				return (this->curr_node != other.curr_node);
			}
			
			private:
				friend class Map;
				ConstIterator() {}
		};
		
		struct ReverseIterator : BaseIterator {
			ReverseIterator &operator= (const ReverseIterator &other) {
				this->curr_node = other.curr_node;
				return *this;
			}
		
			ReverseIterator &operator++ () {
				this->curr_node = this->curr_node->prev;
				return *this;
			}		
		
			ReverseIterator operator++ (int) {
				ReverseIterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->prev;
				return ret;
			}
			
			ReverseIterator &operator--() {
				this->curr_node = this->curr_node->next;
				return *this;
			}
			
			ReverseIterator operator--(int) {
				ReverseIterator ret;
				ret.curr_node = this->curr_node;
				this->curr_node = this->curr_node->next;
				return ret;
			}

			std::pair <const Key_T, Mapped_T> &operator*() const {
				return *this->curr_node->value;
			}
			
			std::pair <const Key_T, Mapped_T> *operator->() const {
				return this->curr_node->value;
			}

			/* Make these free standing functions*/
			bool operator== (const ReverseIterator &other) {
				return (this->curr_node == other.curr_node);
			}

			bool operator!= (const ReverseIterator &other) {
				return (this->curr_node != other.curr_node);
			}
			
			private:
				friend class Map;
				ReverseIterator() {}			
		};
		
		Map () {
			curr_max_height = 6; // generate a random number here
			map_size = 0;

			head = new Node <Key_T, Mapped_T> ();
			head->initializeHead(curr_max_height);
		}
		
		Map (const Map &other) {
			curr_max_height = other.curr_max_height;
			map_size = 0;
			
			head = new Node <Key_T, Mapped_T> ();
			head->initializeHead(curr_max_height);
			
			Node <Key_T, Mapped_T> * temp = other.head->next;
			
			/* Call insert N-1 times*/
			while (temp != other.head) {
				std::pair <Key_T, Mapped_T> pair_copy (*(temp->value));
				this->insert (pair_copy);
				temp = temp->next;
			}
		}
		
		Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> list) {
			curr_max_height = 6;	// generate a random number here
			map_size = 0;

			head = new Node <Key_T, Mapped_T> ();
			head->initializeHead(curr_max_height);

			/* call insert per pair */
			for (auto iter = list.begin(); iter != list.end(); ++iter) {
				insert (*iter);
			}
		}
		
		~Map () {
			Node <Key_T, Mapped_T> * temp = head->prev;
			while (temp != head) {
				Node <Key_T, Mapped_T> * garbage = temp;
				temp = temp->prev;
				delete garbage;
			}
			delete head;
		}
		
		
		size_t 
		size() const {
			return map_size;
		}
		
		bool 
		empty() const {
			return (size() == 0);
		}
		
		bool 
		coin_flip() {
			return (rand() / (float)RAND_MAX) < 0.5; // consider using int valeus 0 or 1
		}
		
		std::pair <Iterator, bool> 
		insert (const std::pair <const Key_T, Mapped_T> &data) {
			Iterator found;
			if (empty()) {
				head->next = new Node <Key_T, Mapped_T> (*head, *head, data);
				//Iterator found(*head->next);
				found.curr_node = head->next;
				
				/* Adding to links vector 
				*/
				unsigned int curr_height = 0;
				while (coin_flip()) {
					head->next->links.insert(head->next->links.begin() + curr_height, new Node <Key_T, Mapped_T> (*head, *head));				

					/* If curr_height exceeds curr_max_height then add another node into head->links */
					if (curr_height >= curr_max_height) {
						head->links.insert(head->links.begin() + curr_height, new Node <Key_T, Mapped_T> (*head, *head));
					}

					head->links.at(curr_height)->next = head->next;
					
					++curr_height;
				}
				if (curr_height >= curr_max_height) { curr_max_height = curr_height; }
				
				++map_size;
				return {found, false};
			}
			
			unsigned int curr_height = curr_max_height - 1; // start search at the top of the links vector
			Node <Key_T, Mapped_T> * temp = head;
			 
			assert (head->links.size() == curr_height + 1);

			while (1) {
				/* Here we are searching using the links vector - so skipping happens here*/
				if (temp->links.at(curr_height)->next == head) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (data.first < temp->links.at(curr_height)->next->value->first) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (data.first == temp->links.at(curr_height)->next->value->first) {
					found.curr_node = temp->links.at(curr_height)->next;
					return {found, true};
				}
				if (!(data.first < temp->links.at(curr_height)->next->value->first)) {
					temp = temp->links.at(curr_height)->next; 	// move forward in temp node by an unspecified amount (this is where we 'skip' forward)
					continue;
				}
			}
			
			while (1) {
				/* Now we can search linearly in the linked list starting at node pointed to by temp */
				if (temp->next == head) { break; }
				if (data.first == temp->next->value->first) {
					found.curr_node = temp->next;
					return {found, true};
				}
				if (data.first < temp->next->value->first) {
					break;
				}
				if (!(data.first < temp->next->value->first)) {
					temp = temp->next;
					continue;
				}
			}
			
			// insertion point: at temp->next
			Node <Key_T, Mapped_T> * t_next = &(*temp->next);
			
			temp->next = nullptr;
			temp->next = new Node <Key_T, Mapped_T> (*t_next, *temp, data); /* INSERTION INTO LINKED LIST HERE */
			
			//Iterator found(&temp->next);
			found.curr_node = temp->next;
			
			/* 
				Adding to links vector 
			*/
			temp = temp->next; 	// set temp to newly added node
			curr_height = 0;	 	// should not be necessary to make curr_height 0
			while (coin_flip()) {
				if (curr_height >= curr_max_height) {
					temp->links.insert (temp->links.begin() + curr_height, new Node <Key_T, Mapped_T> (*head, *head));
					head->links.insert (head->links.begin() + curr_height, new Node <Key_T, Mapped_T> (*head, *head));
					head->links.at(curr_height)->next = temp;
				} 
				else {
					/* Search left from current position (temp) for prev (search) and next node (search->links.at(curr_height)->next) */
					Node <Key_T, Mapped_T> * search = temp->prev;
				
					while (search != head) {
						if (search->links.size() >= curr_height + 1) { break; }
						search = search->prev;
					}
				
					temp->links.insert(temp->links.begin() + curr_height, new Node <Key_T, Mapped_T> (*search->links.at(curr_height)->next, *search));

					/* We have to update next->prev and prev->next in links vector w.r.t curr_height */
					temp->links.at(curr_height)->next->links.at(curr_height)->prev = temp;
					search->links.at(curr_height)->next = temp;
				}
				
				++curr_height;
			}
			if (curr_height >= curr_max_height) { curr_max_height = curr_height; }
			
			++map_size;
			return {found, false};
		}
		
		template <typename IT_T>
		void insert(IT_T range_beg, IT_T range_end) {
			while (range_beg.curr_node != range_end.curr_node) {
				insert ({range_beg.curr_node->value->first, range_beg.curr_node->value->second});
				range_beg.curr_node = range_beg.curr_node->next;
			}
		}

		Iterator 
		begin() {
			Iterator iter;
			iter.curr_node = head->next;
			return iter;
		}
		
		Iterator 
		end() {
			Iterator iter;
			iter.curr_node = head;
			return iter;
		}
		
		ConstIterator
		begin() const {
			ConstIterator iter;
			iter.curr_node = head->next;
			return iter;
		}
		
		ConstIterator 
		end() const {
			ConstIterator iter;
			iter.curr_node = head;
			return iter;
		}
		
		ReverseIterator 
		rbegin() {
			ReverseIterator riter;
			riter.curr_node = head->next;
			return riter;
		}
		
		ReverseIterator 
		rend() {
			ReverseIterator riter;
			riter.curr_node = head;
			return riter;
		}

		Iterator 
		find(const Key_T &key) {
			Iterator found;
			found.curr_node = head;	// make this initially point to end() ret val
			
			unsigned int curr_height = curr_max_height - 1;
			Node <Key_T, Mapped_T> * temp = head;	// start search at the top of the links vector
			
			while (1) {
				/* Here we are searching using the links vector - so skipping happens here*/
				if (temp->links.at(curr_height)->next == head) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (key < temp->links.at(curr_height)->next->value->first) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (key == temp->links.at(curr_height)->next->value->first) {
					found.curr_node = temp->links.at(curr_height)->next;	// set found iterator to found node
					break;
				}
				if (!(key < temp->links.at(curr_height)->next->value->first)) {
					temp = temp->links.at(curr_height)->next; 	// move forward in temp node by an unspecified amount (this is where we 'skip' forward)
					continue;
				}
			}
			
			if (found.curr_node == head) {
				while (1) {
					/* Now we can search linearly in the linked list starting at node pointed to by temp */
					if (temp->next == head) { break; }
					if (key < temp->next->value->first) {
						break;
					}
					if (key == temp->next->value->first) {
						found.curr_node = temp->next;
						break;
					}
					if (!(key < temp->next->value->first)) {
						temp = temp->next;
						continue;
					}
				}
			}
			
			return found;
		}
		
		ConstIterator 
		find(const Key_T &key) const {
			ConstIterator found;
			found.curr_node = head;	// make this initially point to end() ret val
			
			unsigned int curr_height = curr_max_height - 1;
			Node <Key_T, Mapped_T> * temp = head;	// start search at the top of the links vector
			
			while (1) {
				/* Here we are searching using the links vector - so skipping happens here*/
				if (temp->links.at(curr_height)->next == head) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (key < temp->links.at(curr_height)->next->value->first) {
					if (curr_height != 0) { --curr_height; continue; }
					break;
				}
				if (key == temp->links.at(curr_height)->next->value->first) {
					found.curr_node = temp->links.at(curr_height)->next;	// set found iterator to found node
					break;
				}
				if (!(key < temp->links.at(curr_height)->next->value->first)) {
					temp = temp->links.at(curr_height)->next; 	// move forward in temp node by an unspecified amount (this is where we 'skip' forward)
					continue;
				}
			}
			
			if (found.curr_node == head) {
				while (1) {
					/* Now we can search linearly in the linked list starting at node pointed to by temp */
					if (temp->next == head) { break; }
					if (key < temp->next->value->first) {
						break;
					}
					if (key == temp->next->value->first) {
						found.curr_node = temp->next;
						break;
					}
					if (!(key < temp->next->value->first)) {
						temp = temp->next;
						continue;
					}
				}
			}
			
			return found;
		}
		
		
		Mapped_T 
		&at(const Key_T &key) {
			const Iterator found = find(key);
			const Iterator it2 = end();
			
			if(found.curr_node == it2.curr_node) {
				throw std::out_of_range ("");
			}
			
			return (*found.curr_node->value).second;
		}
		
		const Mapped_T 
		&at(const Key_T &key) const {
			ConstIterator found = find(key);
			ConstIterator it2 = end();
			
			if(found.curr_node == it2.curr_node) {
				throw std::out_of_range ("");
			}
			
			return (*found.curr_node->value).second;
		}

		void 
		erase(Iterator pos) {
			const Iterator end_it = end();
			if(pos.curr_node == end_it.curr_node) {
				throw std::out_of_range (""); // Not sure if it should do this, but if the key is not found then it states throw std::out_of_range
			}
		
			// Before erasing node stored in pos we must first go through its link vector and reassign some things
			for (unsigned int i = 0; i < pos.curr_node->links.size(); ++i) {
				pos.curr_node->links.at(i)->next->links.at(i)->prev = pos.curr_node->links.at(i)->prev;
				pos.curr_node->links.at(i)->prev->links.at(i)->next = pos.curr_node->links.at(i)->next;
				pos.curr_node->links.at(i)->next = nullptr;
				pos.curr_node->links.at(i)->prev = nullptr;
			}
			pos.curr_node->next->prev = pos.curr_node->prev; 
			pos.curr_node->prev->next = pos.curr_node->next;
			delete pos.curr_node;
			--map_size;
		}
		
		void 
		erase(const Key_T &key) {
			Iterator pos = find(key);
			erase(pos);
		}
		
		void 
		clear () {
			while (map_size > 0) {
				auto garbage = end();
				garbage.curr_node = garbage.curr_node->prev;
				erase (garbage);
			}
		}
		
		Mapped_T 
		&operator[] (const Key_T &key) {
			Mapped_T default_value{}; // should default construct this value
			std::pair <Key_T, Mapped_T> data({key, default_value});
		
			std::pair <Iterator, bool> found = insert({key, default_value});	// insert if needed
	
			return (*found.first.curr_node->value).second;
		}
		
		Map 
		&operator= (const Map &other) {
			if (head == other.head) { return *this; } // self-assignment
			if (head == nullptr) {
				head = new Node <Key_T, Mapped_T> ();
				head->initializeHead(curr_max_height);
			}
			else {
				this->clear();
			}
			Node <Key_T, Mapped_T> * temp = other.head->next;
			
			/* Call insert N-1 times*/
			while (temp != other.head) {
				std::pair <Key_T, Mapped_T> pair_copy (*(temp->value));
				this->insert (pair_copy);
				temp = temp->next;
			}
			
			return *this;
		}
};
}

template <typename Key_T, typename Mapped_T>
bool 
operator==(const typename cs540::Map<Key_T, Mapped_T> &o1, const typename cs540::Map<Key_T, Mapped_T> &o2) {
	if (o1.size() == o2.size()) {
		auto it1 = o1.begin();
		auto it2 = o2.begin();
		auto end1 = o1.end();
		auto end2 = o2.end(); 
		while (it1 != end1 && it2 != end2) {
			if (!(it1.curr_node->value->first == it2.curr_node->value->first) || !(it1.curr_node->value->second == it2.curr_node->value->second)) { return false; }
			++it1;
			++it2;
		}
		return true;
	} 
	return false;
}

template <typename Key_T, typename Mapped_T>
bool 
operator!=(const typename cs540::Map<Key_T, Mapped_T> &o1, const typename cs540::Map<Key_T, Mapped_T> &o2) {
	if (o1.size() == o2.size()) {
		auto it1 = o1.begin();
		auto it2 = o2.begin();
		auto end1 = o1.end();
		auto end2 = o2.end(); 
		while (it1 != end1 && it2 != end2) {
			if (!(it1.curr_node->value->first == it2.curr_node->value->first) || !(it1.curr_node->value->second == it2.curr_node->value->second)) { return true; }
			++it1;
			++it2;
		}
		return false;
	}
	return true;
}

template <typename Key_T, typename Mapped_T>
bool 
operator<(const typename cs540::Map<Key_T, Mapped_T> &m1, const typename cs540::Map<Key_T, Mapped_T> &m2) {
	/* Corresponding elements from each maps must be compared one-by-one */
	auto it1 = m1.begin();
	auto it2 = m2.begin();
	auto end1 = m1.end();
	auto end2 = m2.end();
	while (it1 != end1 && it2 != end2) {
		if (it1->first < it2->first) { return true; }
		if (it1->second < it2->second) { return true; }
		++it1;
		++it2;
	}
	/* If all corresponding elements in both maps are equal, m1 < m2 if sizeof m1 < sizeof m2 */
	if (m1.size() < m2.size()) {
		return true;
	}
	return false;
}
#endif
