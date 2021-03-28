#include <fstream>
std::ifstream in("input.txt");
std::ofstream out("output.txt");
using namespace std;
 
struct racerStats{
    int racerNum;
    int lapTime;
    int lap;
};

void process();
void mergeSort(racerStats *arr, racerStats *buf, int left, int right, bool comp(racerStats a, racerStats b));
bool compFirst(racerStats a, racerStats b);
bool compSecond(racerStats a, racerStats b);




int main() {
    process();
    return 0;
}

void process() {
    int n, temp, bestTime;
    in >> n;
    racerStats racerArray[n], bufferArray[n];
    bestTime = 0;
    for (int i = 0; i < n; i++) {
        in >> bufferArray[i].racerNum;
        in >> temp;
        bufferArray[i].lapTime = bestTime + temp;
        bufferArray[i].lap = i;
        if (temp < 0)
            bestTime = bufferArray[i].lapTime;
    }
    mergeSort(bufferArray, racerArray, 0, n - 1, compFirst);
    racerArray[0] = bufferArray[0];
    int size = 1;
    for (int i = 1; i < n; ++i) {
        if (racerArray[size - 1].racerNum != bufferArray[i].racerNum)
            racerArray[size++] = bufferArray[i];
        else if (racerArray[size - 1].lapTime > bufferArray[i].lapTime)
            racerArray[size - 1] = bufferArray[i];
    }

    mergeSort(racerArray, bufferArray, 0, size - 1, compSecond);

    for (int i = 0; i < size; ++i) {
        out << racerArray[i].racerNum << ' ';
    }
}


void mergeSort(racerStats *arr, racerStats *buf, int left, int right, bool comp(racerStats a, racerStats b)) {
    if (right <= left)
        return;

    int mid = (left + right) / 2;
    mergeSort(arr, buf, left, mid, comp);
    mergeSort(arr, buf, mid + 1, right, comp);

    for (int k = left; k <= right; k++)
        buf[k] = arr[k];
    int i = left, j = mid + 1;

    for (int k = left; k <= right; k++) {
        if (i > mid) {
            arr[k] = buf[j];
            j++;
        } else if (j > right) {
            arr[k] = buf[i];
            i++;
        } else if (comp(buf[j], buf[i])) {
            arr[k] = buf[j];
            j++;
        } else {
            arr[k] = buf[i];
            i++;
        }
    }
}


bool compFirst(racerStats a, racerStats b) {
    return a.racerNum < b.racerNum;
}


bool compSecond(racerStats a, racerStats b) {
    return a.lapTime < b.lapTime || a.lapTime == b.lapTime && a.lap < b.lap;
}
