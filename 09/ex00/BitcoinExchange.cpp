#include "BitcoinExchange.hpp"

double _stod(std::string s)
{
	std::stringstream ss(s);
	double i;

	ss >> i;
	return i;
}


std::list<std::string> split(std::string str, char sep)
{
	std::list<std::string> list;
	std::stringstream ss(str);
	std::string buff;

	while (std::getline(ss, buff, sep))
		list.push_back(buff);
	return list;
}

static bool isInt(const std::string& s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!std::isdigit(s[i]))
			return (false);
	}
	return (true);
}

static bool isFloat(const std::string& s)
{
	bool pointReached = false;

	for (size_t i = 0; i < s.length(); i++)
	{
		if (!std::isdigit(s[i]))
		{
			if (!pointReached && s[i] == '.' && i+1 != s.length())
				pointReached = true;
			else if (!pointReached && s[i] == '.' && i+1 == s.length())
				return (false);
			else if (pointReached || s[i] != '.')
				return (false);
		}
	}
	// s.find_first_not_of("0123456789.") != std::string::npos; -> error
	// s.find_first_of(".") != s.find_last_of(".") -> error
	return (true);
}

BitcoinExchange::BitcoinExchange()
{
	storeDB("data.csv", this->_db, ',');	
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
	if (this == &src)
		return *this;
	this->_db = src._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::storeDB(std::string fileName,
	std::map<std::string, double>& db,
	char dateSep)
{
	bool isFirst = true;
	std::fstream file(std::string(fileName).c_str(), std::fstream::in);
	std::stringstream stream;
	std::string buff;

	if (file.fail())
		throw std::runtime_error("Error: could not open file.");

	stream << file.rdbuf();
	while (std::getline(stream, buff))
	{
		if ((buff.length() == 0) || isFirst)
		{
			isFirst = false;
			continue;
		}
		std::size_t sep = buff.find(dateSep);
		std::string dateString = buff.substr(0, sep);
		std::string valueString = buff.substr(sep + 1);
		if ((dateString.length() == 0) || (valueString.length() == 0) || !isFloat(valueString))
			throw std::runtime_error("Error: could not open file.");
		std::list<std::string> dateList = split(dateString, '-');
		db[dateString] = _stod(valueString);
	}
}


void BitcoinExchange::calculate(std::string fileName,
	char dateSep)
{
	bool isFirst = true;
	std::fstream file(std::string(fileName).c_str(), std::fstream::in);
	std::stringstream stream;
	std::string buff;

	if (file.fail())
		throw std::runtime_error("Error: could not open file.");

	stream << file.rdbuf();
	while (std::getline(stream, buff))
	{
		if ((buff.length() == 0) || isFirst)
		{
			isFirst = false;
			continue;
		}

		std::size_t sep = buff.find(dateSep);

		if (sep == std::string::npos)
		{
			std::cout <<  "Error: bad input => " + buff << "\n";
			continue ;
		}
        if (buff.find_first_of(dateSep) != buff.find_last_of(dateSep))
		{
			std::cout <<  "Error: bad input => " + buff << "\n";
			continue ;
		}
		std::string dateString = buff.substr(0, sep - 1);
		std::string valueString = buff.substr(sep+2);
		std::list<std::string> dateList = split(dateString, '-');
		double val = ( _stod(valueString) );
		if ((dateString.empty() && !isFirst))
			std::cout << "Error: bad input => " << dateString << "\n";
		else if (isBadDate(dateList))
			std::cout << "Error: bad input => " << dateString << "\n";
		else if ((val < 0) || !isFloat(valueString))
			std::cout <<  "Error: not a positive number.\n";
		else if (val > 1000)
			std::cout << "Error: too large a number.\n";
		else
		{
			std::cout << dateString << " => " << valueString << " = " <<
				val * findNearsetDate(dateString) << "\n";
		}
	}
}

bool    BitcoinExchange::isLeapYear(int year){
	return (!(year % 400) || (!(year % 4) && (year % 100)));
}

bool BitcoinExchange::isBadDate(std::list<std::string> dateList) {
    int type = 0; // year(0) - month(1) - day(2)
    int year = 0;
    int month = 0;
    int day = 0;

    for (std::list<std::string>::iterator it = dateList.begin(); it != dateList.end(); it++) {
        if (!isInt(*it))
            return true;
        
        std::stringstream ss(*it);
        int i;
        ss >> i;

        switch (type) {
            case 0:
                year = i;
                break;
            case 1:
                month = i;
                break;
            case 2:
                day = i;
                break;
        }

        if ((i <= 0) || (i > std::numeric_limits<int>::max()))
            return true;
        if ((type == 1) && (i > 12))
            return true;
        if (type == 2 && (i > 31))
            return true;
        ++type;
    }
    if (!isLeapYear(year)) {
        if (month == 2 && day > 28)
            return true;
    }
    else if (isLeapYear(year)) {
        if (month == 2 && day > 29)
            return true;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
        return true;
    return false;
}

double BitcoinExchange::findNearsetDate(std::string date)
{
	if (_db.count(date) == 1)
		return (_db.at(date));
	_db[date] = 0;
	std::map<std::string, double>::iterator it =  _db.find(date);
	if (it != _db.begin())
		--it;
	double val = ((*it).second);
	return val;
}
