#pragma once

#include <QObject>
#include <QSoundEffect>
#include <QUrl>
#include <vector>

class SoundEffectPlayer : public QObject {
	Q_OBJECT
public:
	SoundEffectPlayer(QObject* parent = nullptr);
	
	// play the corresponding sound effect
	void playSoundEffect(const int indexXF) const;

	// enum of the sound effects' vector index
	enum indexSF {
		move,
		jump,
		knockback,
		flight
	};

private:
	// vector of sound effects, initialized in the ctor
	// index 0: move sf
	//		 1: jump sf
	//		 2: knockback sf
	//		 3: flight sf
	std::vector<QSoundEffect*> soundEffects;

	// load sound effect 
	void loadSoundEffect(QSoundEffect* sf, const QString& source, const float& volume = 1.0);
};
