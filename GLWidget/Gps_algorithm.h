#ifndef GPSALGORITHM_H
#define GPSALGORITHM_H
#include<vector>
#include"PublicValue.h"
#include"Gps_map.h"
#include <QString>
#include <QList>
using namespace std;
class Gps_algorithm
{
public:
	struct Node
	{
		int point_id;
		double cost;
		Node(int id,double c):point_id(id),cost(c){} 
		bool operator<(const Node & a) const
		{
			return (cost>a.cost);
		}
	};
	void print_road();
	int from_id,to_id;
	double road_cost(int line_id);
	vector<bool> be_search;
	vector<int> before_line,after_line;
	vector<double> cost;
    QList<QString> roadlst;
	Gps_map * map;
	void clear();
	Gps_algorithm(Gps_map * m);
	bool find_best_road(int from_id,int to_id);
	int find_point(double x, double y);
};
#endif
