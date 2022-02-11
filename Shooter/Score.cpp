#include "Score.h"
#include "Log.h"
#include <string>

Score::Score() {
	scorePts = 0;
}

Score::~Score() {}

void Score::OnNotify(int idEvent) {
	switch (idEvent) {
	case 0:
		scorePts += 100;
	}
	
	std::string info = std::to_string(scorePts);
	Log::info(info);
}