#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <iostream>
#include <utility>
#include <fstream>
#include <clocale>
#include <random>
#include <string>
#include <cstdio>

static std::vector<std::pair<std::wstring, std::wstring>> results{};

static std::optional<std::pair<std::wstring, std::wstring>> parse_result(const std::wstring& str) {
	if (str.empty()) return {};
	const std::size_t eq = str.find('=');
	if (eq == std::wstring::npos) throw std::runtime_error("failed to parse line");
	else {
		const std::pair p = { str.substr(0, eq), str.substr(eq + 1) };
		return p;
	}
}

int main(const int argc, const char* argv[]) {
	if (argc != 2) {
		std::printf("Usage: %s <results>\n", *argv);
		return 1;
	}

	std::setlocale(LC_ALL, "de_DE.UTF-8");

	std::wifstream file(argv[1]);
	if (!file.is_open()) {
		std::printf("Can't access file %s\n", argv[1]);
		return 1;
	}
	results.clear();

	std::wstring str;
	std::size_t idx = 0;
	while (std::getline(file, str)) {
		++idx;
		try {
			const auto r = parse_result(str);
			if (r) results.push_back(r.value());
			std::printf("%ls=%ls\n", r.value().first.c_str(), r.value().second.c_str());
		} catch (...) {
			std::printf("Failed to parse line %zu\n", idx);
		}
	}

	{
		std::random_device rd{};
		std::mt19937 g(rd());
		std::shuffle(begin(results), end(results), g);
	}

	idx = 0;
	for (const auto r : results) {
		std::wstring tmp;
		std::printf("%ls=", r.first.c_str());
		std::fflush(stdout);
		std::getline(std::wcin, tmp);
		if (r.second == tmp) std::puts("correct!"), ++idx;
		else std::printf("incorrect! (%ls=%ls)\n", r.first.c_str(), r.second.c_str());
	}

	std::printf("%zu correct out of %zu\n", idx, results.size());

	return 0;
}
