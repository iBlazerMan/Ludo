#pragma once

#include <QObject>

class SignalEmitter : public QObject {
	Q_OBJECT
public:
	SignalEmitter(QObject* parent = nullptr);

signals:
	void endRound();
};
