
#include "soci/soci.h"
#include "soci/rowset.h"
#include "soci/odbc/soci-odbc.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>
#include <iomanip>
using namespace std;

using namespace soci;
std::string connectString = "Driver={SQL Server};server=localhost;uid=;pwd=;";
backend_factory const &backEnd = *soci::factory_odbc();

void run()
{
	soci::session sql(backEnd, connectString);
	string n;
	auto t = time(0);

	rowset<row> rs = (sql.prepare << "select * from sys.sysobjects where type = :type", use("U"s));
	for (auto &r : rs) {
		cout << r.get<string>("name") << " : " 
			<< std::put_time(&r.get<std::tm>("crdate"), "%F %T") << " : " 
			<< put_time(localtime(&t), "%F %T") << endl;
	}

}

int main()
{
	try {
		run();
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
	}
}


