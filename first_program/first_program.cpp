#include "buffer.h"
#include "reader.h"
#include "writer.h"
#include <string>
#include <thread>

using namespace std;

int main()
{	
	Buffer buffer;
	Reader reader(buffer);
	Writer writer(buffer);
	thread ft(&Reader::run, &reader);
	thread st(&Writer::process_data, &writer);
	ft.join();
	st.join();
	return 0;
}
