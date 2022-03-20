#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

bool get_user_in_chat(const std::vector<std::string> &a, const std::string &b, std::vector<bool> &c);

int main(){
    const std::string user{};                     //Change this value to twitch specific username you want to check their precense in check_list's chatroom (lowercase)
    const std::vector<std::string> check_list{};  //Change this value to target username's chatroom (lowercase)
    std::vector<bool> join_quit(check_list.size(), 0);

    while (true)
    {
        if (!get_user_in_chat(check_list, user, join_quit)){
            return 1;
        }
    }
    return 0;
}

bool get_user_in_chat(const std::vector<std::string> &a, const std::string &b, std::vector<bool> &join_quit){
    
    std::ifstream in_file;
    size_t pos{};
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
        std::time_t now{std::time(nullptr)};
        std::string time_string{std::asctime(std::localtime(&now))};
        time_string.pop_back();

        if (founded && !join_quit.at(pos)){
            std::cout << std::setw(30);
            std::cout << std::left << time_string << " " << b + " joined " + i + "'s chatroom." << std::endl;
        }else if (!founded && join_quit.at(pos)){
            std::cout << std::setw(30);
            std::cout << std::left << time_string << " " << b << " Left " << i << "'s chatroom." << std::endl;
        }

        in_file.close();
        system("rm temp.tmp; rm chatters;");
        join_quit.at(pos) = founded;
        pos++;
    }
    
    return true;
}
