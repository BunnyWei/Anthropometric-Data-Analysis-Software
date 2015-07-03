#include "basic_manage_thread.h"

void WorkThread::generate_statistic_data()
{
	QString sql;
	Stat stat;
	QSqlQuery itemQuery;
	QList<QString> districts;	/* 地域列表 */
	QList<QString> armtypes;
	Query *query = Query::getQuery();

	districts << "东北区";
	districts << "华北区";
	districts << "西北区";
	districts << "东南区";
	districts << "华中区";
	districts << "华南区";
	districts << "西南区";

	armtypes << "防化兵";
	armtypes << "装甲兵";
	armtypes << "工程兵";
	armtypes << "炮兵";
	armtypes << "步兵";

	sql = get_insert_sql();
	itemQuery.exec("select item_id, itemnumber, itemname from item");

	int item_count = 1;
	while (itemQuery.next()) {
		emit complete_count(item_count);
		QString item_name = itemQuery.value(2).toString();
		QListWidgetItem *li = new QListWidgetItem(QString("正在计算 %1 %2...").arg(item_count++).arg(item_name));
		this->listWidget->addItem(li);

		int item_id = itemQuery.value(0).toInt();
		QString item = itemQuery.value(1).toString();
		if (item == "") {
			continue;
		}

		for (int i = 0; i < armtypes.size(); i++) {
			query->query_data(stat, item,  "", "", armtypes[i], "", "");
			db_insert_statistic_data(item_id, armtypes[i], sql, stat);
		}
		for (int i = 0; i < districts.size(); i++) {
			query->query_data(stat, item,  "", districts[i], "", "", "");
			db_insert_statistic_data(item_id, districts[i], sql, stat);
		}
		query->query_data(stat, item,  "", "", "", "", "");
		db_insert_statistic_data(item_id, QString("全部"), sql, stat);
	}
};

QString WorkThread::get_insert_sql()
{
	QString sql;
	QString percent_str, bind_str;

	for (int j = 1; j < 100; j++) {
		percent_str += QString(",p_%1").arg(j);
	}

	bind_str = "?";
	for (int j = 0; j < 104; j++) {
		bind_str += QString(",?");
	}

	sql = QString("replace into statistic(item_id, social, s_min, s_max, s_avg, s_std %1) values (%2)").arg(percent_str).arg(bind_str);

	return sql;
}

void WorkThread::db_insert_statistic_data(int item_id, QString &social, QString &sql, Stat &stat)
{
	QSqlQuery insertQuery;

	insertQuery.prepare(sql);
	insertQuery.addBindValue(item_id);
	insertQuery.addBindValue(social);
	insertQuery.addBindValue(stat.stat_min());
	insertQuery.addBindValue(stat.stat_max());
	insertQuery.addBindValue(stat.stat_avg());
	insertQuery.addBindValue(stat.stat_std());

	for (int j = 1; j < 100; j++) {
		float p = (float)j/100;
		insertQuery.addBindValue(stat.percentile(p));
	}

	insertQuery.exec();
}