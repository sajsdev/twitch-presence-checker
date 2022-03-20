#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

bool get_user_in_chat(const std::vector<std::string> &a, const std::string &b);

int main(){
    const std::string user{};                   // Change this value to twitch specific username you want to check their precense in scan_list's chatroom (lowercase)
    const std::vector<std::string> scan_list{}; // Change this value to target's chatroom (username)(lowercase)

    if (!get_user_in_chat(scan_list, user)){
        return 1;
    }

    return 0;
}

bool get_user_in_chat(const std::vector<std::string> &a, const std::string &b){
    
    std::ifstream in_file;
    
    for (std::string i : a){
        
        std::string systteem{};
        systteem = std::string("wget -o temp.tmp https://tmi.twitch.tv/group/") + "user/" + i + "/chatters";
        system(systteem.c_str());
        in_file.open("chatters");
        
        if (!in_file){
            std::cout << "Problem opening file";
            system("rm temp.tmp");
            return false;
        }

        std::string line{};
        bool founded{false};
        
        while (std::getline(in_file, line)){
            size_t where = line.find(b);
            if (where != std::string::npos){
                founded = true;
                break;
            }
        }

        if (founded){
            std::time_t now{std::time(nullptr)};
            std::string time_string{std::asctime(std::localtime(&now))};
            time_string.pop_back();
            std::cout << std::setw(30);
            std::cout << std::left << time_string << " " << b.substr(1,5) + " is in " + i + "'s chatroom." << std::endl;
        }
        
        in_file.close();
        system("rm temp.tmp; rm chatters;");
    }
    
    return true;
}
