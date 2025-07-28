#include <vector>
#include <string>

using namespace std;

struct Language {
    string name;
};

struct Country {
    string name;
    string iso_code;
    string phone_code;
    string time_zone;
    vector<Language> languages;
};

struct City {
    string name;
    string iso_code;
    string phone_code;
    string country_name;
    string country_iso_code;
    string country_time_zone;
    vector<Language> languages;
};

struct Json {
    // Упрощенное определение JSON объекта
    vector<Json> AsList() const;
    Json AsObject() const;
    string AsString() const;
    Json operator[](const string& key) const;
};

template<typename T>
T FromString(const string& str);

class CityParser {
private:
    const Country& country_;
    
    string buildPhoneCode(const string& city_phone_code) const {
        return country_.phone_code + city_phone_code;
    }
    
    City createCityFromJson(const Json& city_obj) const {
        return {
            city_obj["name"s].AsString(),
            city_obj["iso_code"s].AsString(),
            buildPhoneCode(city_obj["phone_code"s].AsString()),
            country_.name,
            country_.iso_code,
            country_.time_zone,
            country_.languages
        };
    }

public:
    CityParser(const Country& country) : country_(country) {}
    
    void ParseCities(vector<City>& cities, const Json& cities_json) const {
        for (const auto& city_json : cities_json.AsList()) {
            const auto& city_obj = city_json.AsObject();
            cities.push_back(createCityFromJson(city_obj));
        }
    }
};

void ParseCitySubjson(vector<City>& cities, const Json& json, const string& country_name,
                      const string& country_iso_code, const string& country_phone_code, const string& country_time_zone,
                      const vector<Language>& languages) {
    Country country{country_name, country_iso_code, country_phone_code, country_time_zone, languages};
    CityParser parser(country);
    parser.ParseCities(cities, json);
}

void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        
        Country country{
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString()
        };
        
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        
        countries.push_back(country);
        Country& added_country = countries.back();
        
        CityParser parser(added_country);
        parser.ParseCities(cities, country_obj["cities"s]);
    }
} 
