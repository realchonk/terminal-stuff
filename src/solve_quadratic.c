#include <complex>
#include <utility>
#include <cstdio>

// f(x) = ax² + bx + c

using complex = std::complex<double>;

std::pair<complex, complex> solve(double a0, double b0, double c0) {
	const complex a = a0;
	const complex b = b0;
	const complex c = c0;
	complex x0 = -b + std::sqrt(b*b - 4.0*a*c) / (2.0*a);
	complex x1 = -b - std::sqrt(b*b - 4.0*a*c) / (2.0*a);
	return { x0, x1 };
}

void print_complex(complex x) {
	if (x.imag() == 0) std::printf("%.4f", x.real());
	else std::printf("(%.4f+%.4fi)", x.real(), x.imag());
	std::putchar('\n');
}

int main(int argc, const char* argv[]) {
	if (argc != 4) {
		std::printf("Usage: %s <a> <b> <c>\n", *argv);
		return 1;
	}
	const double a = atof(argv[1]);
	const double b = atof(argv[2]);
	const double c = atof(argv[3]);
	const auto r = solve(a, b, c);
	std::printf("x0 = ");
	print_complex(r.first);
	std::printf("x1 = ");
	print_complex(r.second);
	return 0;
}
