#include<vector>
#include<utility>
#include<sys/stat.h>
#include<string> 
#include<math.h>

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

int getInfo(string path, struct stat *stat, struct s2hData *s2hData);
int getInfo(const char *path, struct stat *stat, struct s2hData *s2hData);

double get_file_score(const int begin, const int end, const time_t accessTime[NUMBEROFSAVE], const time_t reference);
double get_subdir_score(const int begin, const int end, const time_t accessTime[NUMBEROFSAVE], const time_t reference);
double get_size_score(const off_t sizeOfDir);

double calWeight(string path,time_t reference,vector<time_t>const &list);

int main() {
    struct s2hData s2hdata;

    return 0;
}

double calWeight(string path, time_t reference) {
    struct stat stat;
    struct s2hData s2hdata;
	double file_score, subdir_score, size_score, total_score;
    getInfo(path, &stat, &s2hdata);

	file_score = get_file_score(s2hdata.begin, s2hdata.end, s2hdata.accessTime, reference);
	subdir_score = get_subdir_score(s2hdata.beginSubdir, s2hdata.endSubdir, s2hdata.accessTimeSubdir, reference);
	size_score = get_size_score(s2hdata.sizeOfDir);

	total_score = file_score + subdir_score + size_score;

	return total_score;
}

double get_file_score(const int begin, const int end, const time_t accessTime[NUMBEROFSAVE], const time_t reference) {
	double score = 0;
	double weight = 50;
	for(int i=0; i<NUMBEROFSAVE; i++) {
		if(accessTime[i] != NULL) {
			score = weight * (sigmoid(reference - accessTime[i]) * 0.5) + 0.5;
		}
	}

	return score;
}

double sigmoid(double x) {
	double val = 1/(1+exp(-x));
	return val;
}