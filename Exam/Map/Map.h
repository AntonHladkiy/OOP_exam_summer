#pragma once
#include "../Interface/Container.h"
#include "../Interface/ContainerStrategy.h"
template <typename First,typename Second>
class Map {
private:
	ContainerStrategy<Pair<First, Second>>* strategy;

public:
	Container<Pair<First,Second>>* container;
	Map(ContainerStrategy<Pair<First, Second>>* _strategy = new ListContainer<Pair<First, Second>>()) {
		strategy = _strategy;
		container = strategy->get_container();
	}
	Second find_by_key(First key);
};

template<typename First, typename Second>
inline Second Map<First, Second>::find_by_key(First key)
{
	vector<Pair<First, Second>> res = container->get_all_values();
	for (int i = 0; i < res.size(); i++) {
		if (res[i].first == key) {
			return res[i].second;
		}
	}
}
