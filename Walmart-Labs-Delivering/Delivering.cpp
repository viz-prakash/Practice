#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

struct food_restraunt_map_value {
	int count;
	int *list_of_restraunts;
};

struct request {
	int food_id;
	int person_id;
};

int lca_dist_from_root(int src, int dest, int root, int dist_from_root) {
	if (root > src && root > dest) {
		return 0;
	}
	if (root == src || root == dest) {
		return dist_from_root;
	}

	int left_child = root * 2;
	int left_lca_dist = 0;
	left_lca_dist = lca_dist_from_root(src, dest, left_child, dist_from_root+ 1);
	int right_lca_dist = 0;
	right_lca_dist = lca_dist_from_root(src, dest, left_child + 1, dist_from_root + 1);

	if (left_lca_dist && right_lca_dist) {
		return dist_from_root;
	}

	return (left_lca_dist != 0) ? left_lca_dist : right_lca_dist;
}


int cost_of_path(int src, int dest) {
	if (src == dest) {
		return 0;
	}
	set<int> src_path_to_root, dest_path_to_root, final_path;
	int dist_src = 0, dist_dest = 0;
	int element = src;
	while (element != 1) {
		element /= 2;
		src_path_to_root.insert(element);
		dist_src++;
	}

	element = dest;
	while (element != 1) {
		element /= 2;
		dest_path_to_root.insert(element);
		dist_dest++;
	}
	//int lca_dist = lca_dist_from_root(src, dest, 1, 0);
	//return (dist_src + dist_dest - 2 * lca_dist);
	if (src == 1 || dest == 1) {
		return dist_src + dist_dest;
	}
	else if (dest_path_to_root.find(src) != dest_path_to_root.end()) {
		//return dest_path_to_root.size() - src_path_to_root.size();
		return dist_dest - dist_src;
	}
	else if (src_path_to_root.find(dest) != src_path_to_root.end()) {
		//return src_path_to_root.size() - dest_path_to_root.size();
		return dist_src - dist_dest;
	}

	int common_elements = 0;
	for (std::set<int>::iterator it = src_path_to_root.begin(); it != src_path_to_root.end(); it++) {
		set<int>::iterator find_res = dest_path_to_root.find(*it);
		if (find_res != dest_path_to_root.end()) {
			//dest_path_to_root.erase(find_res);
			//	last_common_element = *it;
			common_elements++;
		}
		/*
		else {
		final_path.insert(*it);
		}*/
	}
	//for (std::set<int>::iterator it = dest_path_to_root.begin(); it != dest_path_to_root.end(); it++) {
	//}
	//if (src || last_common_element == dest) {
	//	final_path.size() + dest_path_to_root.size() + 1;
	//}
	//return final_path.size() + dest_path_to_root.size() + 2;
	return dist_src + dist_dest - 2 * (common_elements - 1);

}

int requests_processing(food_restraunt_map_value **adj_list, int num_dishes, request* requests, int num_requests) {
	int i, j;
	int target_dish;
	int target_person;

	int cur_pos = 1;
	int total_cost = 0;
	for (i = 0; i < num_requests; i++) {
		set<int> cost_of_paths;
		int dist_cur_pos_to_shop, dist_shop_to_target;
		int target_shop;
		int shortest_dist = -1;
		int cur_dist = -1;
		target_dish = requests[i].food_id;
		target_person = requests[i].person_id;
		
		for (j = 0; j < adj_list[target_dish - 1]->count; j++) {
			target_shop = adj_list[target_dish - 1]->list_of_restraunts[j];
			dist_cur_pos_to_shop = cost_of_path(cur_pos, target_shop);
			dist_shop_to_target = cost_of_path(target_shop, target_person);
			//cost_of_paths.insert(dist_cur_pos_to_shop + dist_shop_to_target);
			cur_dist = dist_cur_pos_to_shop + dist_shop_to_target;
			if (shortest_dist == -1) {
				shortest_dist = cur_dist;
			}
			else if (cur_dist < shortest_dist) {
				shortest_dist = cur_dist;
			}
		}
		//total_cost += *cost_of_paths.begin();
		total_cost += shortest_dist;
		//total_cost += *min_element(cost_of_paths.begin(), cost_of_paths.end());
		cur_pos = target_person;
	}

	return total_cost;
}


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N, M, Q;
	food_restraunt_map_value **adj_list;
	request *requests;
	int i,j;

	//cost_of_path(22, 15);
	//int lca_dist = lca_dist_from_root(23, 18, 1, 0);

	cin >> N >> M >> Q;

	adj_list = new food_restraunt_map_value* [M];

	for (i = 0; i < M ; i++) {
		int num_of_restraunts;
		cin >> num_of_restraunts;
		adj_list[i] = new food_restraunt_map_value();
		adj_list[i]->count = num_of_restraunts;
		adj_list[i]->list_of_restraunts = new int[num_of_restraunts];
		for (j = 0; j < num_of_restraunts; j++) {
			cin >> adj_list[i]->list_of_restraunts[j];
		}
	}

	requests = new request[Q];
	for (j = 0; j < Q; j++) {
		cin >> requests[j].food_id >> requests[j].person_id;
	}

	cout << requests_processing(adj_list, M, requests, Q);
	return 0;
}