#pragma once

#include <QObject>
#include <QPointF>

class Piece;

class SignalEmitter : public QObject {
	Q_OBJECT
public:
	SignalEmitter(QObject* parent = nullptr);

signals:
	void endRound();
	void checkKnockback(Piece* p, bool firstCheck);
};
