#include "SoundEffectPlayer.h"

SoundEffectPlayer::SoundEffectPlayer(QObject* parent) :
	QObject{ parent } {
	// initialize and load move sound effect
	QSoundEffect* moveSF = new QSoundEffect(this);
	loadSoundEffect(moveSF, "qrc:/Ludo/resource/sound/move.wav");
	// initialize and load jump sound effect
	QSoundEffect* jumpSF = new QSoundEffect(this);
	loadSoundEffect(jumpSF, "qrc:/Ludo/resource/sound/jump.wav");
	// initialize and load knockback sound effect
	QSoundEffect* knockbackSF = new QSoundEffect(this);
	loadSoundEffect(knockbackSF, "qrc:/Ludo/resource/sound/knockback.wav");
	// initialize and load flight sound effect
	QSoundEffect* flightSF = new QSoundEffect(this);
	loadSoundEffect(flightSF, "qrc:/Ludo/resource/sound/flight.wav");
}

void SoundEffectPlayer::playSoundEffect(const int indexSF) const {
	this->soundEffects[indexSF]->play();
}

void SoundEffectPlayer::loadSoundEffect(QSoundEffect* sf, const QString& source, const float& volume) {
	// set source and volume of sound effect
	sf->setSource(QUrl(source));
	sf->setVolume(volume);
	// push back to sound effect container
	this->soundEffects.push_back(sf);
}
