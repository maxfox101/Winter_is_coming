#include <string_view>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct Person {
    string name;
    int age;
};

struct DatabaseConfig {
    string_view db_name;
    int connection_timeout;
    bool allow_exceptions;
    int log_level;
};

struct PersonFilter {
    int min_age;
    int max_age;
    string_view name_filter;
};

class PersonLoader {
private:
    DatabaseConfig config_;
    PersonFilter filter_;
    
protected:
    string buildQuery() const {
        ostringstream query_str;
        query_str << "from Persons "s
                  << "select Name, Age "s
                  << "where Age between "s << filter_.min_age << " and "s << filter_.max_age << " "s
                  << "and Name like '%"s << filter_.name_filter << "%'"s;
        return query_str.str();
    }
    
    vector<Person> LoadPersonsFromDatabase() const {
        string query = buildQuery();
        vector<Person> persons;
        
        // Здесь была бы логика загрузки из БД
        // Вместо этого возвращаем пустой вектор для демонстрации структуры
        return persons;
    }

public:
    PersonLoader(DatabaseConfig config, PersonFilter filter) 
        : config_(config), filter_(filter) {}
    
    vector<Person> Load() const {
        // Здесь была бы логика подключения к БД
        // Вместо этого сразу возвращаем результат
        return LoadPersonsFromDatabase();
    }
};

vector<Person> LoadPersons(string_view db_name, int db_connection_timeout, bool db_allow_exceptions,
                           int db_log_level, int min_age, int max_age, string_view name_filter) {
  DatabaseConfig config{db_name, db_connection_timeout, db_allow_exceptions, db_log_level};
  PersonFilter filter{min_age, max_age, name_filter};
    
    PersonLoader loader(config, filter);
    return loader.Load();
} 
