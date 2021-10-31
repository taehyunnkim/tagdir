# For dev purposes
default:
	g++ -std=c++17 TagDir.cpp TagDirUI.cpp Util.cpp -o tagdir-cli -lstdc++fs -lncursesw 
