#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}



std::vector <std::string> read_from_file();
std::vector<std::string> split(std::vector<std::string> target, int start, int end);
std::map<std::string, int> merge_in_one_map(std::vector<std::map <std::string, int>> maps);
void creating_map(std::vector<std::string> &v, std::map<std::string, int> &m);
void sort_by_letters_and_write_into_file(std::map<std::string, int> m);
void sort_by_amount_and_write_into_file(std::map<std::string, int> m);


int main()
{
    std::vector<std::map <std::string, int>> maps;
    std::mutex m;
    std::vector<std::thread> threads;
    int nthreads = 4 ;
    for(int i = 0; i < nthreads; i++){
        std::map <std::string, int> map;
        maps.emplace_back(map);
    }



    auto stage1_start_time = get_current_time_fenced(); //time point
    std::vector <std::string> words = read_from_file();
    auto stage2_start_time = get_current_time_fenced(); // time point

    int st = words.size() / nthreads;


    int start = 0;
    int end = st;
    std::vector<std::vector<std::string>> parts;
    for(int i = 0; i < nthreads; ++i){
        if(i == nthreads-1){
            std::vector<std::string> part_of_words = split(words, start, words.size()-1);
            parts.emplace_back(part_of_words);
        } else {

            std::vector<std::string> part_of_words = split(words, start, end);
            parts.emplace_back(part_of_words);
            start = end + 1;
            end += st;
        }
    }

    auto stage3_time_counting_of_words = get_current_time_fenced();
   // std::cout<<"START = "<<start << " END = " <<end <<" ALL SIZE= "<<words.size()<<std::endl;
    for(int i = 0; i < nthreads; ++i){
        threads.emplace_back( std::thread(creating_map, std::ref(parts.at(i)) ,std::ref(maps.at(i))));

    }
    //creating_map(words, maps.at(0));

    for(auto& thread : threads){
        thread.join ();
    }

    std::map<std::string, int> map_of_all_words = merge_in_one_map(maps);

    auto stage4_time_counting_of_words = get_current_time_fenced();

    sort_by_letters_and_write_into_file(map_of_all_words);
    sort_by_amount_and_write_into_file(map_of_all_words);

    auto finish_time = get_current_time_fenced();

    auto total_time = finish_time - stage1_start_time;
    auto time_read_from_file = stage2_start_time - stage1_start_time;
    auto time_counting_of_words = stage4_time_counting_of_words - stage3_time_counting_of_words;


    std::cout << "Час читання, підрахунку слів і запису результату: " << to_us(total_time) << std::endl;
    std::cout << "Час читання: " << to_us(time_read_from_file) << std::endl;
    std::cout << "Час, власне, підрахунку їх кількості: " << to_us(time_counting_of_words) << std::endl;

    return 0;
}
std::vector <std::string> read_from_file(){
    std::vector <std::string> words; // Vector to hold our words we read in.

    std::string str;

    std::ifstream fin("here.txt"); // Open it up!
    while (fin >> str) // Will read up to eof() and stop at every
    {                  // whitespace it hits. (like spaces!)
        for (int i = 0, len = str.size(); i < len; i++) // delete all punctuation from string
        {
            if (ispunct(str[i]))
            {
                str.erase(i--, 1);
                len = str.size();
            }
        }

        if(str != ""){
            std::transform(str.begin(), str.end(), str.begin(), ::tolower); // make string lowercase
            words.push_back(str);
        }

    }
    fin.close(); // Close that file!

    return words;
}

void sort_by_letters_and_write_into_file(std::map<std::string, int> m){


    std::vector<std::string> retval;
    for (auto const& element : m) {
        retval.push_back(element.first);
    }
    std::sort( retval.begin(), retval.end() ); //sorts by letters

    std::ofstream outputFile;
    outputFile.open("res_a.txt");

    for (int i = 0; i < retval.size(); i++){
        std::string write_str = retval.at(i) + " - " + std::to_string(m[retval.at(i)]);
        outputFile << write_str << std::endl;
    }

    outputFile.close();
}

void sort_by_amount_and_write_into_file(std::map<std::string, int> m){
    std::vector<std::string> retval;
    for (auto const& element : m) {
        retval.push_back(element.first);
    }

    //sorts by values of map
    sort(retval.begin(),retval.end(),
         [&m](const std::string& a, const std::string& b){return m[a] > m[b]; });

    std::ofstream outputFile2;
    outputFile2.open("res_n.txt");

    for (int i = 0; i < retval.size(); i++){
        std::string write_str = retval.at(i) + " - " + std::to_string(m[retval.at(i)]);
        outputFile2 << write_str << std::endl;
    }

    outputFile2.close();
}

std::vector<std::string> split(std::vector<std::string> target, int start, int end){
    std::vector<std::string> splitted;

    for(int i = start; i<= end; i++){
        splitted.emplace_back(target.at(i));
    }
    return splitted;
}
void creating_map(std::vector<std::string> &v, std::map<std::string, int> &m){

    for (int i = 0; i < v.size(); ++i){
        //mutex.lock();
        if (m.count(v.at(i))){
            m[v.at(i)] += 1;
        }else{
            m[v.at(i)] = 1;
        }
        //mutex.lock();
    }
}

std::map<std::string, int> merge_in_one_map(std::vector<std::map <std::string, int>> maps){
    std::map<std::string, int> merged_map;

    for(auto map:maps){
        for (auto const& element : map) {
            if(merged_map.count(element.first)){
                merged_map[element.first]+=element.second;
            }else{
                merged_map[element.first] = element.second;
            }

        }
    }
    return merged_map;
}