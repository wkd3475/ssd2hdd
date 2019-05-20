#include<vector>
#include<utility>
#include<sys/stat.h>
#include<string> 

#define TIMELOGNAME ".s2htimelog"
#define NUMBEROFSAVE (30)

using namespace std;

struct s2hData{
	int begin,end; 
	time_t lastAccessTime;
	time_t accessTime[NUMBEROFSAVE];
	int beginSubdir,endSubdir;
	time_t lastAccessTimeSubdir;
	time_t accessTimeSubdir[NUMBEROFSAVE];
	off_t sizeOfDir;
};

int getInfo(string path, struct stat *stat,struct s2hData *s2hData);
int getInfo(const char *path, struct stat *stat, struct s2hData *s2hData);

double calWeight(string path);

int main() {
    struct s2hData s2hdata;

    return 0;
}

double calWeight(string path) {
    struct stat stat;
    struct s2hData s2hData;
    getInfo(path, &stat, &s2hData);


}