#ifndef IMPORTWIDGET_H
#define IMPORTWIDGET_H

#include <QWidget>
#include <cassert>
#include "ui_import_widget.h"
#include "importphotothread.h"
#include "importmodelthread.h"
#include "passworddialog.h"

static QMap<QString, QString> map;
class ImportThread;
class ImportWidget : public QWidget
{
	Q_OBJECT

public:
	ImportWidget(QWidget *parent = 0);
	~ImportWidget();
	Ui::ImportWidgetClass ui;
private:
	QList<QString> errorList;	/* 保存出错记录的军人编号 */
	PasswordDialog *pwdDialog;
	ImportThread * importThread;
	int itemNum;
	QHash <QString, int> tableColumnsHash;
	void importCSVFile(QString &dowhat, QString &filepath);
	QStringList getSQL(QString dowhat);

private slots:
	void on_listWidget_clicked(const QModelIndex &);
	void on_dataComboBox_currentIndexChanged(int);
	void on_importModelBtn_clicked();
	void on_imPhotoBtn_clicked();
	void on_importButton_clicked();
	void on_openButton_clicked();
	void importDone();
	void importPhotoDone();
	void importModelDone();
	void workDone();
	void on_pushButton_clicked();
	void on_VisiblePushButton_clicked();
signals:
	void completedCount(int);
};

#endif // IMPORTWIDGET_H
