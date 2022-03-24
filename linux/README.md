## Requirements and installation
```
1). build-essential package
2). Change the value of variable user to twitch specific username you want to check their precense in check_list's chatroom (lowercase)
3). Change the value of variable check_list to target username's chatroom (lowercase)
    for example if you want to check if mizkif is in mizkif, emiru, erobb221, and syn4ack, the variable should look like this
    
    const std::string user{"\"mizkif\""};
    const std::vector<std::string> check_list{"mizkif", "emiru", "erobb221", "syn4ack"};
    
4). compile the cpp file
```
```bash
g++ <cpp file> -o <output name>
```
for example:
```bash
g++ tracker.cpp -o tracker.exe
```
5). run the program
```bash
./filename.exe
```
in this case
```bash
./tracker.exe
```
if you do it right, the tracker should look like this:
----
![tracker](https://cdn.discordapp.com/attachments/948676856364806187/955158033300848640/unknown.png "tracker")

and the scanner should look like this:
----
![scanner](https://media.discordapp.net/attachments/948676856364806187/955159998864982046/unknown.png "scanner")
