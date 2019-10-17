#include <boost/stacktrace.hpp>
#include <iostream>
#include <signal.h>     // ::signal, ::raise

#include <boost/filesystem.hpp>
// using namespace boost::filesystem;

void my_signal_handler(int signum) {
    ::signal(signum, SIG_DFL);
    boost::stacktrace::safe_dump_to("./backtrace.dump");
    ::raise(SIGABRT);
}


bool foo( int& count )
{
	if( count == 200 )
	{
		// ... somewhere inside the `bar(int)` function that is called recursively:
		//
		std::terminate();
		// std::cout << boost::stacktrace::stacktrace();
		return false;
	}
	foo( ++count );
	return true;
}



int main()
{
	::signal(SIGSEGV, &my_signal_handler);
	::signal(SIGABRT, &my_signal_handler);


	if (boost::filesystem::exists("./backtrace.dump")) 
	{
		// there is a backtrace
		std::ifstream ifs("./backtrace.dump");

	    	boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
	    	std::cout << "Previous run crashed:\n" << st << std::endl;

	    	// cleaning up
	    	ifs.close();
	    	boost::filesystem::remove("./backtrace.dump");
	}
	

	int i = 0;
	foo( i );

	/*
	for( int i = 0; i < 1000; ++i )
	{
		if( i % 10 == 0 )
			std::cout << "Count = " << i << std::endl;
		if( i == 999 )
		{
			// ... somewhere inside the `bar(int)` function that is called recursively:
			std::cout << boost::stacktrace::stacktrace();

		}

	}
	*/
	return 0;
}

