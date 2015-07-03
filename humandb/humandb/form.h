#ifndef FORM_H
#define FORM_H

#include <QtGui/QWidget>
#include <QDialog>
#include <QtGui>
#include <QLineEdit>
#include "ui_form.h"
#include "QGlobalVar.h"

class Form : public QDialog
{
	Q_OBJECT

public:
	Form(QWidget *parent = 0);
	~Form();
	bool enterFlag;
	bool shutdownFlag;

private:
	Ui::FormClass ui;
	QLabel *typeLabel;
	QComboBox *logonType;
	QLabel *nameLabel;
	QLineEdit *userLineEdit;
	QLabel *passwordLabel;
	QLineEdit *passwordLineEdit;
	void test();

	private slots:
		void enterButtonClicked();
		void shutdownButtonClicked();
};

#endif // FORM_H
