#define CURL_STATICLIB 
#include <iostream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <algorithm> 
#include <windows.h> 
#include "curl.h" 

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param) { 
    std::string& text = *static_cast<std::string*>(param); 
    size_t totalsize = size * nmemb; 
    text.append(static_cast<char*>(buffer), totalsize); 
    return totalsize; 
} 

int get_index(const std::vector<std::string>& carrency, const std::string& val_name) { 
    auto found{ std::find(carrency.begin(), carrency.end(), val_name) }; 
    int index = std::distance(carrency.begin(), found); 
    return index; 
} 

double mid_value(const std::vector<std::vector<double> >& carrency_value, const unsigned& index, const unsigned& count_times) { 
        double rez = 0.0; 
        for (int i = 0; i < carrency_value[index].size(); ++i) { 
        rez += carrency_value[index][i]; 
    } 
    return rez / count_times; 
} 

double median_value(std::vector<std::vector<double> > carrency_value, const unsigned& index) { 
    unsigned size = carrency_value[index].size(); 
    if (size == 0) { 
        return 0; 
    } else { 
        sort(carrency_value[index].begin(), carrency_value[index].end()); 
        if (size % 2 == 0) 
            return (carrency_value[index][size / 2 + 1] + carrency_value[index][size / 2]) / 2; 
        else 
            return carrency_value[index][size / 2]; 
    } 
} 

int main() { 
    std::string result; 
    std::vector <std::string > carrency; 
    std::vector <std::vector<double> > carrency_values; 
    unsigned count_times = 0; 

    int ans = 0; 
    std::cout « "Do you want to get values? 1 - yes, 0 - no\t"; 
    std::cin » ans; 
    while (ans == 1) { 
        CURL* curl; 
        CURLcode result_from_net; 
        curl_global_init(CURL_GLOBAL_DEFAULT); //активирует функции библиотеки 
        curl = curl_easy_init(); //инициализация, если что-то не так - null 
        if (curl) { 
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_eng_utf8.xml"); 
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write); 
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); //куда записывать результат функции 
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); 
            result_from_net = curl_easy_perform(curl); 
            curl_easy_cleanup(curl); //отчищаем curl 
            if (CURLE_OK != result_from_net) { //curle_ok = 0, проверяем, что что-то есть 
                std::cerr « "CURL error: " « result_from_net « '\n'; 
                return 0; 
            } 

            ++count_times; 
            int pos = 0; 
            int pos_end = 0; 
            while (pos + 17 != result.find("</ValCurs>", pos)) { 
                std::string val_name; 
                pos = result.find("<CharCode>", pos) + 10; //находим позицию валюты 
                pos_end = result.find("</CharCode>", pos); 
                while (pos != pos_end) { 
                    val_name += result[pos]; 
                    ++pos; 
                } 

                std::string val_value; 
                pos = result.find("<Value>", pos) + 7; 
                pos_end = result.find("</Value>", pos); 
                int i = 0; 
                while (pos != pos_end) { 
                    if (result[pos] == ',') 
                        val_value += '.'; 
                    else 
                        val_value += result[pos]; 
                    ++i; 
                    ++pos; 
                } 

                int index = get_index(carrency, val_name); 
                if (count_times == 1) { 
                    carrency.push_back(val_name); 
                    carrency_values.resize(carrency_values.size() + 1);  
                    carrency_values[index].push_back(atof(val_value.c_str())); 
                } else { 
                    carrency_values[index].push_back(atof(val_value.c_str())); 
                } 
            } 
            std::cout « "Repeat after 5 seconds?\t"; 
            std::cin » ans; 
            if (ans) 
                Sleep(5 * 1000); 
            } 
            curl_global_cleanup(); 
        } 

    std::cout « "\n\nName\t|\tMid\t|\tMedian\n"; 
    std::cout « "_______________________________________\n"; 
    for (int i = 0; i < carrency.size(); ++i) { 
        std::cout « carrency[i] « "\t|\t" « mid_value(carrency_values, i, count_times); 
        std::cout « "\t|\t" « median_value(carrency_values, i) « std::endl; 
    } 
}
