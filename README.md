# Bookmark You Directories
A simple directory bookmarking tool for my machine using C++
 
## Installation
```console
user@taehyunnkim:~$ ./install.sh
```
 
## Usage
**Textbased UI**\
`td`
 
**Adding a bookmark**\
`td add [TAG] [PATH TO DIRECTORY]`

**Deleting a bookmark**\
`td del [TAG]`
 
**Navigating to the bookmarked directory**\
`td [TAG]`
 
Example:
```console
user@taehyunnkim:~$ td add nginx-log /var/log/nginx/
user@taehyunnkim:~$ td nginx-log
```
