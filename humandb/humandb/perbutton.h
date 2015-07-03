#ifndef PERBUTTON_H
#define PERBUTTON_H

#include <QPushButton>

class PerButton : public QPushButton
{
	Q_OBJECT

public:
	PerButton(const QString &itemnumber, const QString & text, QWidget *parent);
	~PerButton();
	inline QString getItemNum() const
	{
		return itemnumber;
	}
	inline QString getItemName() const
	{
		return itemName;
	}

private:
	QString itemnumber;
	QString itemName;
private slots:
	void showItem();

signals:
	void clickItem(QString itemnum, QString itemName);
	
};

#endif // PERBUTTON_H
