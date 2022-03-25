#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cctype>
#include <algorithm>

bool get_user_in_chat(const std::vector<std::string> &a, const std::string &b, std::vector<bool> &c);
void add_user_in_check_list(std::vector<std::string> &check_list,const std::string &user);


int main(){
    const std::string user{};                     //Change this value to twitch specific username you want to check their precense in check_list's chatroom (lowercase)
    const std::vector<std::string> check_list{};  //Change this value to target username's chatroom (lowercase)
    
    add_user_in_check_list(check_list, user);
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
    std::ofstream out_file {"logs.txt", std::ios::app};
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
            out_file << std::setw(30) << std::left << time_string << " " << b + " joined " + i + "'s chatroom." << std::endl;
            std::cout << std::setw(30);
            std::cout << std::left << time_string << " " << b + " joined " + i + "'s chatroom." << std::endl;
        }else if (!founded && join_quit.at(pos)){
            out_file << std::setw(30) << std::left << time_string << " " << b << " Left " << i << "'s chatroom." << std::endl;
            std::cout << std::setw(30);
            std::cout << std::left << time_string << " " << b << " Left " << i << "'s chatroom." << std::endl;
        }

        in_file.close();
        system("rm temp.tmp; rm chatters;");
        join_quit.at(pos) = founded;
        pos++;
    }
    out_file.close();
    return true;
}


void add_user_in_check_list(std::vector<std::string> &check_list,const std::string &user){
    std::cin.clear();
    char choice{'n'};
    std::string new_user{};
    std::cout << std::setw(70) << std::setfill('-') << "-" << std::endl;
    std::cout << "You're currently scanning/tracking " << user << " in : \n";
    std::cout << "\n" << std::setw(70) << std::setfill('-') << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (size_t i = 0; i < check_list.size(); i++){
        std::cout << std::setw(25) << std::left << check_list.at(i);
        if ((i+1)%3 == 0){
            std::cout << "\n" << std::setw(70) << std::setfill('-') << "-" << "\n" << std::endl;
            std::cout << std::setfill(' ');
        }
    }
    std::cout << "\n" << std::setw(70) << std::setfill('-') << "-" << "\n" << std::endl;
    
    std::cout << std::setfill(' ');
    std::cout << std::endl;
    std::cout << "Do you want to add a new user(s) ? (y/n) : ";
    std::cin >> choice;
    choice = std::tolower(choice);
    
    while(choice == 'y'){
        size_t count{};
        std::cout << "Enter how many user(s) you want to add and the users separated by space (for example: 4 sunshinebread jdcr 39daph erobb221) \n: ";
        std::cin >> count;
        
        for (size_t i = 0; i < count; i++){
            bool user_exist{false};
            std::cin >> new_user;
            std::for_each(new_user.begin(), new_user.end(), [](char &c){c = std::tolower(c);});
            
            for(const auto &u : check_list){
                if (u == new_user){
                    std::cout << new_user << " already exist in scan/track list." << std::endl;
                    user_exist = true;
                    break;
                }
            }

            if (!user_exist){
                check_list.push_back(new_user);
            }
        }
        
        choice = 'n';
        add_user_in_check_list(check_list, user);
    }

    return;
}
