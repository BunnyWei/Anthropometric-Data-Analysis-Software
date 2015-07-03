#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <QToolButton>
#include "ui_shutdown.h"

class Shutdown : public QToolButton
{
	Q_OBJECT

public:
	Shutdown(QWidget *parent = 0);
	~Shutdown();

private:
	Ui::ShutdownClass ui;
};

#endif // SHUTDOWN_H
