#pragma once
#include <string>
class FuzzySet
{
public:
	void SetMin(float m) { fuzzy_set.min = m; }
	void SetMax(float m) { fuzzy_set.max = m; }
	void SetXAxisName(std::string n) { fuzzy_set.x_axis_name = n; }
	void SetGraphName(std::string n) { fuzzy_set.graph_name = n; }
	void SetGraphType(int p) { fuzzy_set.graph_type = p; }
private:
	struct set{
		float min;
		float max;
		std::string x_axis_name;
		std::string graph_name;
		int graph_type;
	}fuzzy_set;
};

