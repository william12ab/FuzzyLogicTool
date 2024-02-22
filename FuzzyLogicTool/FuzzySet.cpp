#include "FuzzySet.h"

FuzzySet::FuzzySet() {
	fuzzy_set.fuzzy_value = 0.f;
	fuzzy_set.min = 0.f;
	fuzzy_set.max = 0.f;
	fuzzy_set.x_axis_name="";
	fuzzy_set.graph_name="";
	fuzzy_set.graph_type=0;
	fuzzy_set.set_type=0;
	fuzzy_set.operator_value=0;
	fuzzy_set.peak_value=0.f;
}