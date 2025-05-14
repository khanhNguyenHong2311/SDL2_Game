#include"TimeAndScore.h"


string calculateTime(Uint32 startTime) {
	Uint32 currentTime = SDL_GetTicks();
	int elapsedSeconds = (currentTime - startTime) / 1000;

	int minutes = elapsedSeconds / 60;
	int seconds = elapsedSeconds % 60;


	stringstream ss;
	ss << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;

	return ss.str();
}


void renderTimeGameText(SDL_Renderer* renderer , TTF_Font* font) {
	string strTimeGameText = "Time: " + calculateTime(startTime);
	timeGameText.setText(strTimeGameText);
	timeGameText.loadFromRenderText(font, renderer);
	timeGameText.render(renderer, SCREEN_HEIGHT - 200, 15);
}

void renderScoreText(SDL_Renderer* renderer , TTF_Font* font) {
	string strScoreText = "Score: ";
	string temp = to_string(score);
	strScoreText += temp;
	scoreText.setText(strScoreText);
	scoreText.loadFromRenderText(font, renderer);
	scoreText.render(renderer, SCREEN_HEIGHT - 500, 15);
}

void saveScore(int newScore, string filename) {
	vector<int> scores;
	string line;
	ifstream file(filename);
	while (getline(file, line)) {
		if (!line.empty()) {
			int score = stoi(line);
			scores.push_back(score);
		}
	}
	file.close();
	scores.push_back(newScore);

	sort(scores.begin(), scores.end(), greater<int>() );

	ofstream _file(filename);

	for (int i = 0;i < scores.size();i++) {
		_file << scores[i] << endl;
	}
	_file.close();
}