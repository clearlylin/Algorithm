#include <iostream>
#include "templateError.h"

using namespace std;

static int i = TemplateError<double>::get(0);

int main() {
	// TemplateError<double> ab;
	// int a = 1;
	// ab.set(a);
	// ab.get(0);
}

