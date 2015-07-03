#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QSqlQuery>
#include <QMap>
#include <QVariant>
#include <math.h>

enum parameter_t {NATIVEPLACE, DISTRICT, ARMTYPE, EDUCATION, MILITARYRANK, PARAMETER_SIZE};
enum table_t {HEAD, OPERATE, STATIC, FUNC, MENTAL, SPORT, JOINT, HAND, COAT, TABLESIZE};

class People {
public:
	QString number;				/* 军人编号 */
	QString name;				/* 姓名 */
	QString birthday;			/* 出生日期 */
	QString jointime;				/* 入伍时间 */
	QString nation;				/* 民族 */
	int nativeplace;		/* 籍贯 */
	QString soldierhome;		/* 兵源地 */
	int education;			/* 文化程度 */
	int armtype;			/* 兵种 */
	int military;			/* 军衔 */
	int district;				/* 区域 */

	People *next[PARAMETER_SIZE];
	float *data[TABLESIZE];		
	int colums[TABLESIZE];
	People()
	{
		int i;

		for (i = 0; i < PARAMETER_SIZE; i++) {
			next[i] = NULL;
		}
		for (i = 0; i < TABLESIZE; i++) {
			data[i] = NULL;
		}
	}
};

class List {
public:
	int key;
	People *first;
	List *next;
	List()
	{
		key = -1;
		first = NULL;
		next = NULL;
	}
};

class Table {
private:
	QMap<QString, int> column[TABLESIZE];
	//column[TABLESIZE]中存放了所有测量项的字段名
public:
	Table();
	//根据字段名得到表名（表的索引）
	int get_table_index(QString item);
	//得到某个表t的字段数目
	int columnsize(int t);
	//返回某个表t的所有字段，以逗号分隔
	QString all_column_str(int t);
	//返回某个表t的表名
	QString get_table_str(int t);
	//得到某个字段的索引
	int get_column_index(int t, QString item);
};

class Stat {
private:
	float *data;
	int size;
	double  sum, ex_sum;
public:
	Stat();
	~Stat();
	void reset();
	void add_element(float e);
	double stat_avg();
	double stat_min();
	double stat_max();
	double stat_std();
	int count();
	double percentile(float p);
};

class Query {
protected:
	static Query *query_instance;
	Query();//singleton constructor must be private or protected
private:
	List *lists[PARAMETER_SIZE];
	People *people;
	QMap<QString, int> people_map;
	QMap<QString, int> nativeplace_map;
	QMap<QString, int> district_map;
	QMap<QString, int> armtype_map;
	QMap<QString, int> education_map;
	QMap<QString, int> militaryrank_map;
	Table table;
	int npeople;
public:
	//Query();
	void fill_data(QSqlQuery &query, People *p, int t);
	void build_index(People *p, int key, enum parameter_t pm);
	void insert_list(List *list, People *p, int pm);
	List * find_list(int key, int pm);
	bool match_parameter(People *p, int pm, int parameter);
	void query_data(Stat &stat, QString item, QString nativeplace, QString district, 
							QString armtype, QString education, QString militaryrank);
	int select_data(QString itemX, QString itemY, double *dataX, double *dataY, QString *number);
	void init_parameter_map();
	void init_people();
	void init_data();
	int get_value_by_key(QMap<QString, int> &map, QString key);
	int get_people_count();
	float get_data_by_item(People *p, QString item);
	void query_data_by_others(Stat &stat, QString item, QString other, float min, float max);
    int get_all_people();
	/* Query的单例模式 */
	static Query *getQuery()
	{
		if (query_instance == NULL) {
			query_instance = new Query;
		}
		return query_instance;
	}

	static void freeQuery()
	{
		if (query_instance) {
			delete query_instance;
		}
		query_instance = NULL;
	}
};

#endif