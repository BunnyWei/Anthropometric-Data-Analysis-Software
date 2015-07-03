#include "query.h"
#include <QDebug>

Query *Query::query_instance = NULL;

/*============= class Query 方法开始 ==================*/
Query::Query()
{
	init_parameter_map();
	init_people();
	init_data();
}

void Query::init_parameter_map()
{
	this->armtype_map.insert(QString("防化兵"), 0);
	this->armtype_map.insert(QString("装甲兵"), 1);
	this->armtype_map.insert(QString("工程兵"), 2);
	this->armtype_map.insert(QString("炮兵"), 3);
	this->armtype_map.insert(QString("步兵"), 4);

	this->district_map.insert(QString("东北区"), 0);
	this->district_map.insert(QString("华北区"), 1);
	this->district_map.insert(QString("西北区"), 2);
	this->district_map.insert(QString("东南区"), 3);
	this->district_map.insert(QString("华中区"), 4);
	this->district_map.insert(QString("华南区"), 5);
	this->district_map.insert(QString("西南区"), 6);

	this->education_map.insert(QString("小学"), 0);
	this->education_map.insert(QString("初中"), 1);
	this->education_map.insert(QString("高中"), 2);
	this->education_map.insert(QString("中专"), 3);
	this->education_map.insert(QString("大专"), 4);
	this->education_map.insert(QString("本科"), 5);
	this->education_map.insert(QString("硕士"), 6);
	this->education_map.insert(QString("博士"), 7);

	QSqlQuery query("select Province from province order by Province asc");
	query.exec();
	while (query.next()) {
		this->nativeplace_map.insert(query.value(0).toString(), this->nativeplace_map.size());
	}

	this->militaryrank_map.insert(QString("列兵"), 0);
	this->militaryrank_map.insert(QString("上等兵"), 1);
	this->militaryrank_map.insert(QString("下士"), 2);
	this->militaryrank_map.insert(QString("中士"), 3);
	this->militaryrank_map.insert(QString("上士"), 4);
	this->militaryrank_map.insert(QString("四级士官"), 5);
	this->militaryrank_map.insert(QString("少尉"), 6);
	this->militaryrank_map.insert(QString("中尉"), 7);
	this->militaryrank_map.insert(QString("上尉"), 8);
	this->militaryrank_map.insert(QString("少校"), 9);
	this->militaryrank_map.insert(QString("中校"), 10);
} 

void Query::init_people()
{
	int i;
	QSqlQuery query;
	QString sql;

	for (i = 0; i < PARAMETER_SIZE; i++) {
		this->lists[i] = NULL;
	}
	this->people =  new People[11000];
	this->npeople = 0;

	i = 0;
	sql = "select number,name,birthday,jointime,people,jiguan,\
		  bingyuan,wenhua,bingzhong,junxian,region from info";
	query.exec(sql);
	while (query.next()) {
		QString number = query.value(0).toString().toUpper();
		QString name = query.value(1).toString();
		QString birthday = query.value(2).toString();
		QString jointime = query.value(3).toString();
		QString nation = query.value(4).toString();
		int nativeplace = get_value_by_key(nativeplace_map, query.value(5).toString());
		QString soldierhome = query.value(6).toString();
		int education = get_value_by_key(education_map, query.value(7).toString());
		int armtype = get_value_by_key(armtype_map, query.value(8).toString());
		int military = get_value_by_key(militaryrank_map, query.value(9).toString());
		int district = get_value_by_key(district_map, query.value(10).toString());

		people[i].number = number;
		people[i].name = name;
		people[i].birthday = birthday;
		people[i].birthday = birthday;
		people[i].jointime = jointime;
		people[i].nation = nation;
		people[i].nativeplace = nativeplace;
		people[i].soldierhome = soldierhome;
		people[i].education = education;
		people[i].armtype = armtype;
		people[i].military = military;
		people[i].district = district;
//void Query::build_index(People *p, int key, enum parameter_t pm)
		build_index(&people[i], nativeplace, NATIVEPLACE);
		build_index(&people[i], education, EDUCATION);
		build_index(&people[i], military, MILITARYRANK);
		build_index(&people[i], armtype, ARMTYPE);
		build_index(&people[i], district, DISTRICT);

		people_map.insert(number, i);
		i = i + 1;
	}
	this->npeople = i;
}

void Query::init_data()
{
	QString sql;
	QSqlQuery query;

	for (int t = 0; t < TABLESIZE; t++) {
		sql = "select number, " + table.all_column_str(t) + " from " + table.get_table_str(t);
		//qDebug() << sql;
		query.exec(sql);
		while (query.next()) {
			QString number = query.value(0).toString().toUpper();
			int ind = get_value_by_key(people_map, number);
			if (ind != -1) {
				People *p = &people[ind];
				fill_data(query, p, t);
			} else {
				//qDebug() << "找不到军人 " << number;
			}
		}
	}
}

int Query::get_people_count()
{
	return this->npeople;
}
//新增
int i=0;
int Query::get_all_people()
{
	QSqlQuery query;
	QString sql = "select count(*)  from info where  jiguan=ui.jiguanComboBox->currentText() AND region= ui.districtComboBox->currentText() AND wenhua = ui.wenhuaComboBox->currentText() AND  bingzhong = ui.bingzhongComboBox->currentText() 	AND junxian = ui.junxianComboBox->currentText()";
	qDebug() << sql << endl;
	query.exec(sql);
	while (query.next()) {
		QString itemname = query.value(0).toString();
       i++;
	}
	return i;
}

int Query::get_value_by_key(QMap<QString, int> &map, QString key)
{
	QMap<QString, int>::iterator it = map.find(key);

	if (it != map.end() && it.key() == key)  {
		return it.value();
	}

	return -1;
}
/*
 * 查找某一个具体属性节点
 * 例如：查找兵种中的防化兵节点
 * 通过pm（兵种、文化、地域等）一级属性查询得到键值为key的二级属性
 */
List * Query::find_list(int key, int pm)
{//key代表兵种中的（装甲兵、防化兵等）编号
	List *p = lists[pm];
//查找二级属性节点
	while (p != NULL) {
		if (p->key == key) {
			break;
		} 
		p = p->next;
	}
//若没有找到节点，则使用头插法插入新节点
	if (p == NULL) {
		p = new List;
		p->key = key;
		p->next = lists[pm];//？？是不是应该改为p->next = lists[pm]->next;
		lists[pm] = p;
	}

	return p;
}
/*
 * 将某一具有二级属性的people指针插入到list指针后面
 * 例如：将某一防化兵插入到防化兵节点后面
 * pm决定一级属性，list决定二级属性
 */
void Query::insert_list(List *list, People *p, int pm)
{
	if (list->first != NULL) {//原来有节点，头插法插入一个新的people节点
		p->next[pm] = list->first->next[pm];
		list->first->next[pm] = p;
	} else {//原来没有节点，作为第一个节点插入
		list->first = p;
	}
}

void Query::fill_data(QSqlQuery &query, People *p, int t)
{
	int i;
	int columnsize = table.columnsize(t);

	if (p->data[t] == NULL) {
		p->data[t] = new float[columnsize];
		for (i = 0; i < columnsize; i++) {
			p->data[t][i] = 9999;
		}
	}

	for (i = 0; i < columnsize; i++) {
		p->data[t][i] = query.value(i+1).toDouble();
	}
}

void Query::build_index(People *p, int key, enum parameter_t pm)
{
	//得到某个二级属性节点
	List *list = find_list(key, pm);
	//将查到的people指针插入到二级属性节点后面
	insert_list(list, p, pm);
}

/* 测量项目other在min和max之间的人找出来，统计他们的item的值 */
void Query::query_data_by_others(Stat &stat, QString item, QString other, float min, float max)
{
	stat.reset();

	for (int i = 0; i < npeople; i++) {
		float other_data = get_data_by_item(&people[i], other);
		if (other_data <= max && other_data >= min) {
			float data = get_data_by_item(&people[i], item);
			if (data != -1) {
				stat.add_element(data);
			}
		}
	}
}

void Query::query_data(Stat &stat, QString item, QString nativeplace, 
					   QString district, QString armtype, QString education, QString militaryrank)
{
	int pm;
	QList<int> parameters;

	stat.reset();
	if (item == "") return;

	parameters << get_value_by_key(nativeplace_map, nativeplace);
	parameters << get_value_by_key(district_map, district);
	parameters << get_value_by_key(armtype_map, armtype);
	parameters << get_value_by_key(education_map, education);
	parameters << get_value_by_key(militaryrank_map, militaryrank);

	pm = 0;
	while (pm < PARAMETER_SIZE && parameters[pm] == -1) {
		pm++;
	}
	if (pm == PARAMETER_SIZE) {
		for (int i = 0; i < this->npeople; i++) {
			People *p = &people[i];
			float item_data = get_data_by_item(p, item);
			if (item_data > 0) {
				stat.add_element(item_data);
			}
		}
	} else {
		List *l = find_list(parameters[pm], pm);
		People *p = l->first;

		while (p) {
			bool all_parameter_match = true;
			for (int ii = pm + 1; ii < PARAMETER_SIZE; ii++) {
				if (parameters[ii] != -1 && !match_parameter(p, ii, parameters[ii])) {
					all_parameter_match = false;
					break;
				}
			}
			float item_data = get_data_by_item(p, item);
			if (all_parameter_match && item_data > 0) {
				stat.add_element(item_data);
			}
			p = p->next[pm];
		}
	}
}

int Query::select_data(QString itemX, QString itemY, double *dataX, double *dataY, QString *number)
{
	int data_size = 0;
	int i;

	for (i = 0; i < npeople; i++) {
		float xd = get_data_by_item(&people[i], itemX);
		float yd = get_data_by_item(&people[i], itemY);
		if (xd > 0 && yd > 0) {
			number[data_size] = people[i].number;
			dataX[data_size] = xd;
			dataY[data_size] = yd;
			data_size++;
		}
	}

	return data_size;
}

float Query::get_data_by_item(People *p, QString item)
{
	int t = table.get_table_index(item);
	int c = table.get_column_index(t, item);

	if (p->data[t] != NULL && p->data[t][c] > 0 && p->data[t][c] < 9999) {
		return p->data[t][c];
	}

	return -1;
}

bool Query::match_parameter(People *p, int pm, int parameter)
{
	switch(pm) {
	case NATIVEPLACE:
		return (p->nativeplace == parameter);
	case DISTRICT:
		return (p->district == parameter);
	case ARMTYPE:
		return (p->armtype == parameter);
	case EDUCATION:
		return (p->education == parameter);
	case MILITARYRANK:
		return (p->military == parameter);
	default:
		return false;
	}
}

Table::Table()
{
	QSqlQuery query;
	QMap<QString, int>::iterator it;
	int count;
	int t;

	query.exec("select itemnumber from item");
	while (query.next()) {
		QString itemnumber = query.value(0).toString();
		t = get_table_index(itemnumber);
		column[t].insert(itemnumber, 0);
	}

	for (t = 0; t < TABLESIZE; t++) {
		count = 0;
		for (it = column[t].begin(); it != column[t].end(); it++) {
			column[t][it.key()] = count++;
		}
	}
}

int Table::get_table_index(QString item)
{
	int t = -1;

	if (item.startsWith("hand")) {
		t = HAND;
	} else if (item.startsWith("h")) {
		t = HEAD;
	} else if (item.startsWith("f")) {
		t = FUNC;
	} else if (item.startsWith("o")) {
		t = OPERATE;
	} else if (item.startsWith("st")) {
		t = STATIC;
	} else if (item.startsWith("s"))  {
		t = SPORT;
	} else if (item.startsWith("j")) {
		t = JOINT;
	} else if (item.startsWith("m")) {
		t = MENTAL;
	}

	return t;
}
/*============= class Query 方法结束 ==================*/


/*=========   class Table 方法开始 =======================*/
int Table::columnsize(int t)
{
	return column[t].size();
}

QString Table::all_column_str(int t)
{
	QString str;
	QMap<QString, int>::iterator it;

	for (it = column[t].begin(); it != column[t].end(); it++) {
		str += it.key() + ",";
	}

	return str.left(str.size()-1);
}

QString Table::get_table_str(int t)
{
	QString table_str[TABLESIZE] = {"head", "operate", "static", "func", "mental", "sport", "joint", "hand", "coat"};
	return table_str[t];
}

int Table::get_column_index(int t, QString item)
{
	QMap<QString, int>::iterator it = column[t].find(item);

	if (it != column[t].end() && it.key() == item)  {
		return it.value();
	}

	return -1;
}
/*=========   class Table 方法结束 =======================*/


/*=========   class Stat 方法开始 =======================*/
Stat::Stat()
{
	reset();
	int npeople = Query::getQuery()->get_people_count();
	this->data = new float[npeople];
}

Stat::~Stat()
{
	delete [] this->data;
}

void Stat::reset()
{
	size = 0;
	sum = 0;
	ex_sum = 0;
}

void Stat::add_element(float e)
{
	int i;

	/* 插入法排序 */
	for (i = size; i > 0 && data[i-1] > e; i--) {
		data[i] = data[i-1];
	}
	data[i] = e;

	sum +=  e;
	ex_sum += e*e;
	size++;
}

double Stat::stat_avg()
{
	if (size < 1) return -1;
	return sum/size;
}
double Stat::stat_min()
{
	if (size < 1) return -1;
	return data[0];
}

double Stat::stat_max()
{
	if (size < 1) return -1;
	return data[size-1];
}

double Stat::stat_std()
{
	if (size < 1) return -1;
	double _avg = stat_avg();
	return sqrt(ex_sum/size - _avg*_avg);
}

int Stat::count()
{
	return this->size;
}

double Stat::percentile(float p)
{
	if (size < 1) return -1;

	double result;
	double r;
	int  s, t;

	r = size *  p;
	s = (int) floor(r);//下取整
	t = (int) ceil(r);//上取整
	if (t == size) t = size-1;
	result = ((s == t) ? data[s] : (data[t] * (t - r) + data[t] * (r - s)));

	return result;
}
/*=========   class Stat 方法结束 =======================*/