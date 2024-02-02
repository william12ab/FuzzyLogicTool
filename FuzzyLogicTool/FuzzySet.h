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
	void SetSetType(int p) { fuzzy_set.set_type = p; }
	void SetOperatorValue(int p) { fuzzy_set.operator_value = p; }

	float GetMin() { return fuzzy_set.min; }
	float GetMax() { return fuzzy_set.max; }
	std::string GetxName() { return fuzzy_set.x_axis_name; }
	std::string GetGraphName() { return fuzzy_set.graph_name; }
	int GetGraphType() { return fuzzy_set.graph_type; }
	int GetSetType() { return fuzzy_set.set_type; }
	int GetOperatorValue() { return fuzzy_set.operator_value; }


	const float GetMin() const { return fuzzy_set.min; }
	const float GetMax() const { return fuzzy_set.max; }
	const std::string GetxName() const { return fuzzy_set.x_axis_name; }
	const std::string GetGraphName()const { return fuzzy_set.graph_name; }
	const int GetGraphType() const { return fuzzy_set.graph_type; }
	const int GetSetType() const { return fuzzy_set.set_type; }
	const int GetOperatorValue() const { return fuzzy_set.operator_value; }
private:
	struct set{
		float min;
		float max;
		std::string x_axis_name;
		std::string graph_name;
		int graph_type;
		int set_type;
		int operator_value;
	}fuzzy_set;
	
};

