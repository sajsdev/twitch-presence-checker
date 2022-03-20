## Requirements and installation
```
1). build-essential package
2). Change the value of variable user to twitch specific username you want to check their precense in check_list's chatroom (lowercase)
3). Change the value of variable check_list to target username's chatroom (lowercase)
    for example if you want to check if mizkif is in xqcow, emiru, dareon, and syn4ack, the variable should look like this
    
    const std::string user{"mizkif"};
    const std::vector<std::string> check_list{"xqcow", "emiru", "dareon, "syn4ack"};
    
2). compile the cpp file
```
```bash
g++ <cpp file> -o <output name>
```
for example:
```bash
g++ tracker.cpp -o tracker.exe
```
run the program
```bash
./filename.exe
```
in this case
```bash
./tracker.exe
```
