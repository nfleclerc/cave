#ifndef UTILS_H
#define UTILS_H

class Utils {
public:
	static unsigned int split(const std::string &text, std::vector<std::string> &strings, char ch) {
		int pos = text.find(ch);
		int initialPos = 0;
		strings.clear();
		while (pos != std::string::npos) {
			strings.push_back(text.substr(initialPos, pos - initialPos + 1));
			initialPos = pos + 1;
			pos = text.find(ch, initialPos);
		}
		strings.push_back(text.substr(initialPos, std::min<int>(pos, text.size() - (initialPos + 1))));
		return strings.size();
	}
};

#endif // !UTILS_H
