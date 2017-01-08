#include <iostream>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;


class Queuenode {
public:
	int freq;
	int count;
	//unorderd_map<int,int> key_map;
	list<int> LRUQueue;

	Queuenode(int freq = 0) {
		this->freq = freq;
		count = 0;
	}
};

class Mapvalue {
public:
	int value;
	list<Queuenode>::iterator LFUQueue_it;
	list<int>::iterator LRUQueue_it;

	Mapvalue(int value, list<Queuenode>::iterator LFUQueue_it, list<int>::iterator LRUQueue_it) {
		this->value = value;
		this->LFUQueue_it = LFUQueue_it;
		this->LRUQueue_it = LRUQueue_it;
	}
};


class LFUCache {
private:
	int capacity, length;
	unordered_map<int, Mapvalue> cached_map;
	list<Queuenode> LFU;
public:
	LFUCache(int capacity) {
		this->capacity = capacity;
		length = 0;
	}

	void shift_back(int key, unordered_map<int, Mapvalue>::iterator& map_it) {

		//push behind this element in LFU queue and add it to last of LRU queue of new LFU node
		list<Queuenode>::iterator nextto_del_it = map_it->second.LFUQueue_it;
		nextto_del_it++;
		map_it->second.LFUQueue_it->LRUQueue.erase(map_it->second.LRUQueue_it);
		map_it->second.LFUQueue_it->count--;
		list<Queuenode>::iterator target_node_it;
		if (nextto_del_it == LFU.end() || map_it->second.LFUQueue_it->freq + 1 != nextto_del_it->freq) {
			//next node in LFU queue has not same frequency as of elements getting accessed,
			//insert new node with element's frequency + 1
			Queuenode node(map_it->second.LFUQueue_it->freq + 1);
			target_node_it = LFU.insert(nextto_del_it, node);
		}
		else {
			target_node_it = nextto_del_it;
		}
		target_node_it->LRUQueue.push_back(key);
		target_node_it->count++;
		map_it->second.LRUQueue_it = --(target_node_it->LRUQueue.end());
		//store the iterator pointing to next node to mapvalue LFU iterator
		if (map_it->second.LFUQueue_it->count == 0) {
			//if LFU queue node doesn't have any element of frequency of queue node delete the node from LFU Queue
			map_it->second.LFUQueue_it = LFU.erase(map_it->second.LFUQueue_it);
		}
		else {
			//map_it->second.LFUQueue_it = map_it->second.LFUQueue_it + 1;
			map_it->second.LFUQueue_it = target_node_it;
		}
	}

	int get(int key) {
		if (length == 0) {
			return -1;
		}
		unordered_map<int, Mapvalue>::iterator it = cached_map.find(key);
		if (it == cached_map.end()) {
			return -1;
		}
		else {
			//push back in the queue
			//TODO change the call
			shift_back(key, it);
			return it->second.value;
		}
	}

	void put(int key, int value) {
		if (capacity <= 0) {
			return;
		}
		unordered_map<int, Mapvalue>::iterator it = cached_map.find(key);

		if (it != cached_map.end()) {
			shift_back(key, it);
			it->second.value = value;
			return;
		}

		if (length == capacity) {
			// throw out a LFU element
			// make a queue of queue(elements in LRU order, and store the iteratror to both of these in cached_map)
			int key_to_remove = LFU.begin()->LRUQueue.front();
			LFU.begin()->LRUQueue.pop_front();
			LFU.begin()->count--;
			if (LFU.begin()->count == 0) {
				LFU.pop_front();
			}
			cached_map.erase(key_to_remove);
			length--;
		}

		// insert this key value pair in cache
		if (LFU.size() == 0 || LFU.begin()->freq != 0) {
			//insert a new node in LFU queue with 0 frequency
			Queuenode node(0);
			LFU.push_front(node);
		}
		//insert the key in LFU queue at begining or at 0 frquency
		LFU.begin()->LRUQueue.push_back(key);
		LFU.begin()->count++;

		//TODO to make it faster use pointer instead of objects
		Mapvalue mapvalue(value, LFU.begin(), --(LFU.begin()->LRUQueue.end()));
		pair<int, Mapvalue> cached_map_pair(key, mapvalue);
		//cached_map.insert(std::make_pair<int, Mapvalue>(key,mapvalue));
		cached_map.insert(cached_map_pair);
		length++;
	}

	void print_cache() {
		cout << "Number of elements in cache : " << length << endl;
		for (unordered_map<int, Mapvalue>::iterator it = cached_map.begin(); it != cached_map.end(); it++) {
			cout << it->first << " -> " << it->second.value << ",  LFUQue_it : " << &(*it->second.LFUQueue_it);
			cout << " ,LRUQueue_it : " << &(*it->second.LRUQueue_it) << endl;
		}

		cout << "LFU Queue" << endl;
		for (list<Queuenode>::iterator it = LFU.begin(); it != LFU.end(); it++) {
			cout << it->freq << ", " << it->count << ", LFU it-ptr=" << &(*it) << " | ";
			for (list<int>::iterator LRU_it = it->LRUQueue.begin(); LRU_it != it->LRUQueue.end(); LRU_it++) {
				cout << *LRU_it << " LRU it-ptr = " << &(*LRU_it) << ", ";
			}
			cout << " |" << endl;
		}
	}
};


int main() {
	LFUCache cache(10 /* capacity */);
	
	list<vector<int>> input = { { 10,13 },{ 3,17 },{ 6,11 },{ 10,5 },{ 9,10 },{ 13 },{ 2,19 },{ 2 },{ 3 },{ 5,25 },{ 8 },{ 9,22 },{ 5,5 },{ 1,30 },{ 11 },{ 9,12 },{ 7 },{ 5 },{ 8 },{ 9 },{ 4,30 },{ 9,3 },{ 9 },{ 10 },{ 10 },{ 6,14 },{ 3,1 },{ 3 },{ 10,11 },{ 8 },{ 2,14 },{ 1 },{ 5 },{ 4 },{ 11,4 },{ 12,24 },{ 5,18 },{ 13 },{ 7,23 },{ 8 },{ 12 },{ 3,27 },{ 2,12 },{ 5 },{ 2,9 },{ 13,4 },{ 8,18 },{ 1,7 },{ 6 },{ 9,29 },{ 8,21 },{ 5 },{ 6,30 },{ 1,12 },{ 10 },{ 4,15 },{ 7,22 },{ 11,26 },{ 8,17 },{ 9,29 },{ 5 },{ 3,4 },{ 11,30 },{ 12 },{ 4,29 },{ 3 },{ 9 },{ 6 },{ 3,4 },{ 1 },{ 10 },{ 3,29 },{ 10,28 },{ 1,20 },{ 11,13 },{ 3 },{ 3,12 },{ 3,8 },{ 10,9 },{ 3,26 },{ 8 },{ 7 },{ 5 },{ 13,17 },{ 2,27 },{ 11,15 },{ 12 },{ 9,19 },{ 2,15 },{ 3,16 },{ 1 },{ 12,17 },{ 9,1 },{ 6,19 },{ 4 },{ 5 },{ 5 },{ 8,1 },{ 11,7 },{ 5,2 },{ 9,28 },{ 1 },{ 2,2 },{ 7,4 },{ 4,22 },{ 7,24 },{ 9,26 },{ 13,28 },{ 11,26 } };
	
	for (list<vector<int>>::iterator it = input.begin(); it != input.end(); it++) {
		if ((*it).size() == 1) {
			cout << "get( " << (*it)[0] << " )  " ;
			cout << cache.get((*it)[0]) << endl;
		}
		else if ((*it).size() == 2) {
			cout << "put( " << (*it)[0] << ", " << (*it)[1] << ")";
			cache.put((*it)[0], (*it)[1]);
			cout << "  null" << endl;
		}
		//cache.print_cache();
	}
	/*
	
	cache.put(2, 1);
	cache.print_cache();
	cache.put(2, 2);
	cache.print_cache();
	cache.get(2);       // returns 1
	cache.print_cache();
	cache.put(1, 1);    // evicts key 2
	cache.print_cache();
	cache.put(4, 1);       // returns -1 (not found)
	cache.print_cache();
	cache.get(2);       // returns 3.
	cache.print_cache();
/*
	cache.put(4, 4);    // evicts key 1.
	cache.print_cache();
	cache.get(1);       // returns -1 (not found)
	cache.print_cache();
	cache.get(3);       // returns 3
	cache.print_cache();
	cache.get(4);       // returns 4
	cache.print_cache();
	*/
	return 0;
}