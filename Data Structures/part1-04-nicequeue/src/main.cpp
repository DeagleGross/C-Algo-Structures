#include "NiceStack.h"
#include "NiceQueue.h"

int main (int /*argc*/, char* /*argv*/[])
{
	using namespace std;
	NiceStack<string> niceStack(10);
	NiceQueue<double> niceQueue(10);
}
