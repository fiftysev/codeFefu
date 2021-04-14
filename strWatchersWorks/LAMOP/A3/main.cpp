#include <fstream>

typedef struct {
    int car_num;
    int order_num;
    int time;
} race_info;

bool car_number_comparator(race_info a, race_info b);

bool time_and_order_num_comparator(race_info a, race_info b);

void _merge_sort(race_info *arr, race_info *buf, int left_edge, int right_edge, bool comp(race_info, race_info));

void merge_sort(race_info* arr, race_info* buf, int len, bool comp(race_info, race_info)); 


int main() {
    using namespace std;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int races_count, current_race_time, best_time;
    fin >> races_count;
    race_info main_arr[races_count], buf[races_count];
    best_time = 0;
    // Заполнение буферного массива информацией о всех заездах
    for (int i = 0; i < races_count; i++) {
        fin >> buf[i].car_num;
        fin >> current_race_time;
        buf[i].time = best_time + current_race_time;
        buf[i].order_num = i;
        if (current_race_time < 0)
            best_time = buf[i].time;
    }

    // Сортировка буферного массива по возрастанию номера машины, чтобы состакать вместе информацию об одном и том же гонщике
    merge_sort(buf, main_arr, races_count, car_number_comparator);
    // Коприование в основной массив информации о лучших заездах
    main_arr[0] = buf[0];
    int main_arr_size = 1;
    for (int i = 1; i < races_count; ++i) {
        if (main_arr[main_arr_size - 1].car_num != buf[i].car_num)
            main_arr[main_arr_size++] = buf[i];
        else if (main_arr[main_arr_size - 1].time > buf[i].time)
            main_arr[main_arr_size - 1] = buf[i];
    }

    // Сортировка массива с лучшими заездами по времени и порядку, в котором это время было достигнуто
    merge_sort(main_arr, buf, main_arr_size, time_and_order_num_comparator);

    for (int i = 0; i < main_arr_size; ++i) {
        fout << main_arr[i].car_num << " ";
    }
}

void _merge_sort(race_info* arr, race_info* buf, int left_edge, int right_edge, bool comp(race_info, race_info)) {
    if (right_edge <= left_edge)
        return;

    int mid = (left_edge + right_edge) / 2;
    _merge_sort(arr, buf, left_edge, mid, comp);
    _merge_sort(arr, buf, mid + 1, right_edge, comp);

    for (int it = left_edge; it <= right_edge; it++)
        buf[it] = arr[it];

    int left_sub_array_it = left_edge, right_sub_array_it = mid + 1;
    for (int buf_arr_iterator = left_edge; buf_arr_iterator <= right_edge; buf_arr_iterator++) {
        if (left_sub_array_it > mid) {
            arr[buf_arr_iterator] = buf[right_sub_array_it++];
        }
        else if (right_sub_array_it > right_edge) {
            arr[buf_arr_iterator] = buf[left_sub_array_it++];
        }
        else if (comp(buf[right_sub_array_it], buf[left_sub_array_it])) {
            arr[buf_arr_iterator] = buf[right_sub_array_it++];
        }
        else {
            arr[buf_arr_iterator] = buf[left_sub_array_it++];
        }
    }
}

void merge_sort(race_info* arr, race_info* buf, int len, bool comp(race_info, race_info)) {
    _merge_sort(arr, buf, 0, len - 1, comp);
}

bool car_number_comparator(race_info a, race_info b) {
    return a.car_num < b.car_num;
}

bool time_and_order_num_comparator(race_info a, race_info b) {
    return a.time < b.time || a.time == b.time && a.order_num < b.order_num;
}