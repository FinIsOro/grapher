#include <Grapher/Core.hpp>
#include <CSV/Core.hpp>

#include <iostream>
#include <fstream>

using namespace graph;
using namespace grapher;
using namespace csv;
using namespace std;

int main(int argumentsNumber, char** arguments)
{
    program::Console::Show();

	auto application = new Application();

	for (size_t argumentIndex = 1; argumentIndex < argumentsNumber; argumentIndex++)
	{
		cout << arguments[argumentIndex] << endl;
		
		ifstream csvFile(arguments[argumentIndex]);

		Reader csvReader(csvFile);
		Table table;
		Table::Builder tableBuilder(table);
		
		while (csvReader.continuable())
			tableBuilder.append(csvReader.read(), Table::Builder::Append::Unsafely);

		CSVConverter csvConverter(table);

		while (csvConverter.continuable())
			application->chart.add(csvConverter.next());
	}

    application->run();

    delete application;

    return 0;
}