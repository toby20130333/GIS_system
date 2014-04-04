#include"Gps_algorithm.h"
#include "PublicValue.h"
#include<queue>
#include<cmath>

Gps_algorithm::Gps_algorithm(Gps_map * m)
{
    map = m;
    for (int i = 0;i < map->point_vector.size(); ++i)
	{
		be_search.push_back(false);
		before_line.push_back(-1);
		after_line.push_back(-1);
        cost.push_back(MAXNUM);
	}
    //qDebug()<<"size="<<be_search.size();

    from_id = to_id=-1;
}
void Gps_algorithm::clear()
{
    for (int i = 0; i < be_search.size(); ++i)
	{
        be_search[i] = false;
        before_line[i] = -1;
        cost[i] = MAXNUM;
	}
}

double rad(double d)
{
    return d * PI / 180.0;
}
double Gps_algorithm::road_cost(int line_id)
{
	//预留交通规则
    Gps_point from = map->point_vector[map->line_vector[line_id].Begin_point_id];
    Gps_point to=map->point_vector[map->line_vector[line_id].End_point_id];

    double radLat1 = rad(from.x);
    double radLat2 =  rad(to.x);
	double a =radLat1 - radLat2;
    double b = rad(from.y) - rad(to.y);
	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
    cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));

    s = s * EARTH_RADIUS;
    s = floor(s * 10000) / 10000;

    return s;
}
void Gps_algorithm::print_road()
{
    int t = from_id;
    double sum = 0;
    int before_road = -1;
    roadlst.clear();
    while (after_line[t] != -2)
	{
        int road_id = map->line_vector[after_line[t]].Road_section_id;

        if (road_id != before_road && before_road != -1)
		{
            qDebug() << "沿1" << map->road_vector[before_road].name << "走" << sum << "公里";
            QString str;
            str.append("沿 ");
            if(map->road_vector[before_road].name == "")
            {
                str.append("某某路");
            }else{
               str.append(map->road_vector[before_road].name);
            }
            str.append("走");
            if(sum >1.0){
                str.append(QString::number(sum));
                str.append("公里");
            }else{
                sum = sum*1000;
                str.append(QString::number(sum));
                str.append("米");
            }
            roadlst<<str;
            sum = 0;
		}
        sum += road_cost(after_line[t]);
        t = map->line_vector[after_line[t]].End_point_id;
        if (t == to_id)
            break;
        before_road = road_id;
		
	}
    QString str1;
    str1.append("沿 ");
    if(map->road_vector[before_road].name == "")
    {
        str1.append("某某路");
    }else{
       str1.append(map->road_vector[before_road].name);
    }
    str1.append("走");
    if(sum >1.0){
        str1.append(QString::number(sum));
        str1.append("公里");
    }else{
        sum = sum*1000;
        str1.append(QString::number(sum));
        str1.append("米");
    }
    roadlst<<str1;
    qDebug() << "沿" << map->road_vector[before_road].name << "走" << sum << "公里";
}
bool Gps_algorithm::find_best_road(int from_id,int to_id)
{
	clear();
    //qDebug()<<"in_al";

    if (from_id == to_id)
        return false;

    before_line[from_id] = -2;
    cost[from_id] = 0;

	priority_queue<Node> q;

    while(!q.empty())
    {
        q.pop();
    }

    q.push(Node(from_id,0));

	while (!q.empty())
	{
        Node now = q.top();

        be_search[now.point_id] = true;
        q.pop();

        if (now.point_id == to_id)
		{
            qDebug()<<"find_road_success\n";

            int t = to_id;
            after_line[t] = -2;

			while (before_line[t]!=-2)
			{
                after_line[map->line_vector[before_line[t]].Begin_point_id] = before_line[t];
                t = map->line_vector[before_line[t]].Begin_point_id;

                if (t == from_id)
                    break;
			}

            print_road();

            return true;
		}
        Gps_point& p = map->point_vector[now.point_id];
        for (int i = 0;i < p.lines_id.size(); ++i)
		{
            int  line_id = p.lines_id[i];

            int from_id = map->line_vector[line_id].Begin_point_id;
            int to_id = map->line_vector[line_id].End_point_id;

            if (be_search[to_id] == false &&
                    cost[to_id] > (cost[from_id] + road_cost(line_id)))
			{
                cost[to_id] = cost[from_id] + road_cost(line_id);

				before_line[to_id]=line_id;

                q.push(Node(to_id,cost[to_id]));
			}
		}
	}

	return false;
}
int Gps_algorithm::find_point(double x, double y)
{
    double min_l = MAXNUM;
	int index;

    for (int i = 0;i < map->point_vector.size(); ++i)
	{
        double d = sqrt((map->point_vector[i].x-x)*(map->point_vector[i].x-x)+
                        (map->point_vector[i].y-y)*(map->point_vector[i].y-y));

        if (d < min_l)
        {
            min_l = d;
            index = i;
        }
	}

	return index;
}
