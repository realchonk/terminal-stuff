#include <unordered_map>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cstdio>

static std::unordered_map<unsigned, unsigned> divisors{};

[[nodiscard]]
static unsigned count_divisors(unsigned n) noexcept {
	if (!n) return 0;
	else if (const auto it = divisors.find(n); it != divisors.end())
		return (*it).second;
	unsigned n_divs = 1;
	for (unsigned i = 1; i <= (n/2); ++i) {
		if (n % i == 0) ++n_divs;
	}
	divisors[n] = n_divs;
	return n_divs;
}

[[nodiscard]]
static bool is_perfect(unsigned n) noexcept {
	if (n == 1) return true;
	else if (n & 1) return false;
	else if (n > 60 && n % 60) return false;
	const unsigned n_divs = count_divisors(n);
	for (unsigned i = 1; i < n; ++i) {
		if (count_divisors(i) >= n_divs) return false;
	}
	return true;
}

[[nodiscard]]
inline std::vector<unsigned> list_perfects(unsigned start = 1, unsigned end = -1) noexcept {
	std::vector<unsigned> perfects{};
	for (unsigned i = start; i < end; ++i) {
		if (is_perfect(i)) perfects.push_back(i);
	}
	return perfects;
}

[[nodiscard]]
constexpr bool strieq(const char* s1, const char* s2) noexcept {
	for (size_t i = 0; ; ++i) {
		if (!s1[i]) return !s2[i];
		else if (s1[i] != s2[i]) return false;
	}
}

int main(const int argc, const char* argv[]) {
	const char* progname = std::strrchr(*argv, '/');
	if (!progname) progname = *argv;
	else progname++;

	if (strieq(progname, "count_divisors")) {
		if (argc != 2) {
			std::puts("Usage: count_divisors <integer>");
			return -1;
		}
		std::printf("%u\n", count_divisors(strtoul(argv[1], NULL, 10)));
		return 0;
	}
	else if (strieq(progname, "list_perfects")) {
		unsigned start, end;
		if (argc == 1) {
			start = 1;
			end   = -1;
		}
		else if (argc == 2) {
			start = 1;
			end   = std::strtoul(argv[1], NULL, 10);
		}
		else if (argc == 3) {
			start = std::strtoul(argv[1], NULL, 10);
			end   = std::strtoul(argv[2], NULL, 10);
		}
		else {
			std::puts("Usage: list_perfects [<start>] <end>");
			return -1;
		}
		for (unsigned i = start; i < end; ++i) {
			if (is_perfect(i)) std::printf("%u\n", i);
		}
		return 0;
	}
	else {
		if (argc != 2) {
			std::puts("Usage: is_perfect <integer>");
			return -1;
		}
		const bool r = is_perfect(strtoul(argv[1], NULL, 10));
#ifdef UNIX
		std::puts(r ? "0" : "1");
#else
		std::puts(r ? "1" : "0");
#endif
		return 0;
	}
}
