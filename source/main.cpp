#include <Program/Console.hpp>
#include <Grapher/Grapher.hpp>

#include <Grapher/Converters/CSVToSeries.hpp>
#include <CSV/Parser.hpp>

#include <iostream>
#include <fstream>

using namespace program;
using namespace grapher;

int main()
{
    Console::Show();

    std::ifstream csvFile("D:\\cities.csv", std::ifstream::in);
    std::string line;

    csv::Parser parser;

    while (std::getline(csvFile, line))
        parser << line << "\n";

    std::vector<Series> series = converters::CSVToSeries::convert(parser.table());

    Application::run<Grapher>();

    return 0;
}